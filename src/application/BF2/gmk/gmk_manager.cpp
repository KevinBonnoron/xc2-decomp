#include "gmk/gmk_manager.h"

#include "bdat.h"
#include "dr/dr_man.h"
#include "framework/memory/framework_memory.h"
#include "framework/navi/navi_util.h"
#include "framework/resource/common_resource.h"
#include "framework/script/script_manager.h"
#include "fw/fw_bdat_manager.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "gf/script/gf_script_manager.h"
#include "gmk/gmk_anti_blade_area.h"
#include "gmk/gmk_area_bgm.h"
#include "gmk/gmk_area_weather.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_battle_lock.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_blade.h"
#include "gmk/gmk_climbing.h"
#include "gmk/gmk_collection.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_dmg_gimmick.h"
#include "gmk/gmk_door.h"
#include "gmk/gmk_effect.h"
#include "gmk/gmk_elevator.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_event.h"
#include "gmk/gmk_field_lock.h"
#include "gmk/gmk_field_volume.h"
#include "gmk/gmk_foot_print.h"
#include "gmk/gmk_form_pc.h"
#include "gmk/gmk_grave.h"
#include "gmk/gmk_jump.h"
#include "gmk/gmk_kizuna_talk.h"
#include "gmk/gmk_landmark.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_map_gimmick.h"
#include "gmk/gmk_map_jump.h"
#include "gmk/gmk_map_obj.h"
#include "gmk/gmk_mob/gmk_mob.h"
#include "gmk/gmk_mob/gmk_routed_mob.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "gmk/gmk_npc/gmk_routed_npc.h"
#include "gmk/gmk_precious.h"
#include "gmk/gmk_route.h"
#include "gmk/gmk_salvage.h"
#include "gmk/gmk_script.h"
#include "gmk/gmk_se.h"
#include "gmk/gmk_set.h"
#include "gmk/gmk_squad.h"
#include "gmk/gmk_target_point.h"
#include "gmk/gmk_tbox.h"
#include "gmk/gmk_tutorial.h"
#include "gmk/gmk_warp.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"

namespace gmk {

constexpr u16 SCENARIO_FLAG_KEEP_BATTLE_LOCK_IN_BATTLE = 7039;
const ml::FILE_PRIO GMK_SCRIPT_FILE_PRIO = static_cast<ml::FILE_PRIO>(7);

static const char *const s_gmkFileNames[] = {
    "enemy",       "enemy",      "enemy",         "npc",         "npc",        "npc",        "mapObj",     "mapObj",   "mapObj",
    "tbox",        "event",      "enemy",         "fieldLock",   "effect",     "effect",     "se",         "se",       "se",
    "mob",         "mob",        "mob",           "landmark",    nullptr,      nullptr,      "formPc",     "formPc",   "formPcEv",
    "formPcEv",    "collection", "areaBgm",       "areaWeather", "salvage",    nullptr,      "mapGimmick", "precious", "grave",
    "kizunaTalk",  "jump",       "warp",          "squad",       "squad",      "door",       "elevator",   "elevator", "mapJump",
    "fieldVolume", "climbing",   "blade",         "dmgGimmick",  "dmgGimmick", "dmgGimmick", "dmgGimmick", nullptr,    "enemy",
    "footPrint",   "footPrint",  "antiBladeArea", "tutorial",
};

bool GmkBdat::isValid() const { return data != nullptr && fw::BdatManager::isEnableBdat(createInfo.bdatId); }

bool GmkBdat::create(const CreateInfo &info) {
  dispose();
  createInfo = info;
  resource = fw::CommonResource::request(info.memory, createInfo.path.c_str(), 9, false);
  if (resource->getRefCount() != 1) {
    return false;
  }
  seq = &GmkBdat::seqWaitResourceLoaded;
  return true;
}

void GmkBdat::dispose() {
  seq = nullptr;
  if (createInfo.bdatId >= 0) {
    fw::BdatManager::unregistBdat(createInfo.bdatId);
    createInfo.bdatId = -1;
  }
  mm::mtl::safeRelease(resource);
  data = nullptr;
  createInfo = CreateInfo();
}

void GmkBdat::update(f32 deltaTime) {
  if (seq) {
    (this->*seq)(deltaTime);
  }
}

const char *GmkManager::getFilenameByType(int gmkSetId, GmkType type) const {
  const char *column = s_gmkFileNames[type];
  if (column == nullptr) {
    return nullptr;
  }
  u8 *bdat = gmkSetListBdat;
  if (Bdat::getMember(bdat, column) == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(Bdat::getValCheck(bdat, column, gmkSetId, BDAT_TYPE_STRING));
}

const char *GmkManager::getSheetnameByType(int gmkSetId, GmkType type) const {
  mm::mtl::FixStr<256> column;
  column.format("%s_bdat", s_gmkFileNames[type]);
  u8 *bdat = gmkSetListBdat;
  if (Bdat::getMember(bdat, column.c_str()) == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(Bdat::getValCheck(bdat, column.c_str(), gmkSetId, BDAT_TYPE_STRING));
}

int getCurrentMapBdatId() { return gf::GfGameManager::getMapID(); }

void GmkSet::createGmkLists(int gmkSetId) {
  npcManager.setUpdateNpcNumPerFrame(32);
  for (int i = 0; i < GMK_TYPE_NUM; i++) {
    delete lists[i];
    lists[i] = nullptr;
  }
  lists[GMK_TYPE_ENEMY] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEnemyList(32);
  lists[GMK_TYPE_ROUTED_ENEMY] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedEnemyList(8);
  lists[GMK_TYPE_ROUTED_ENEMY_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedEnemyPointList(1);
  lists[GMK_TYPE_NPC] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkNpcList(0);
  lists[GMK_TYPE_ROUTED_NPC] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedNpcList(0);
  lists[GMK_TYPE_NPC_ROUTE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
  lists[GMK_TYPE_MAP_OBJ] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMapObjList(8);
  lists[GMK_TYPE_ROUTED_MAP_OBJ] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedMapObjList(4);
  lists[GMK_TYPE_MAP_OBJ_ROUTE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
  lists[GMK_TYPE_TBOX] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkTboxList(8);
  lists[GMK_TYPE_EVENT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEventList(8);
  lists[GMK_TYPE_BATTLE_LOCK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkBattleLockList(8);
  lists[GMK_TYPE_FIELD_LOCK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFieldLockList(8);
  lists[GMK_TYPE_EFFECT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEffectList(8);
  lists[GMK_TYPE_EFFECT_LOCATOR] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEffectLocatorList(1);
  lists[GMK_TYPE_SE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSeList(8);
  lists[GMK_TYPE_SE_LINE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSeLineList(4);
  lists[GMK_TYPE_SE_LINE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSeLinePointList(1);
  lists[GMK_TYPE_MOB] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMobList(8);
  lists[GMK_TYPE_ROUTED_MOB] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedMobList(4);
  lists[GMK_TYPE_MOB_ROUTE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
  lists[GMK_TYPE_LANDMARK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkLandmarkList(8);
  lists[GMK_TYPE_ROUTE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRouteList(1);
  lists[GMK_TYPE_ROUTE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
  lists[GMK_TYPE_FORM_PC] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFormPcList(1);
  lists[GMK_TYPE_FORM_PCNPC] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFormPcnpcList(1);
  lists[GMK_TYPE_FORM_PC_EV] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFormPcEvList(1);
  lists[GMK_TYPE_FORM_PCNPC_EV] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFormPcnpcEvList(1);
  lists[GMK_TYPE_COLLECTION] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkCollectionList(1);
  lists[GMK_TYPE_AREA_BGM] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkAreaBgmList(1);
  lists[GMK_TYPE_AREA_WEATHER] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkAreaWeatherList(1);
  lists[GMK_TYPE_SALVAGE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSalvageList(1);
  lists[GMK_TYPE_SALVAGE_LOCATOR] = nullptr;
  lists[GMK_TYPE_MAP_GIMMICK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMapGimmickList(1);
  lists[GMK_TYPE_PRECIOUS] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkPreciousList(1);
  lists[GMK_TYPE_GRAVE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkGraveList(1);
  lists[GMK_TYPE_KIZUNA_TALK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkKizunaTalkList(1);
  lists[GMK_TYPE_JUMP] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkJumpList(1);
  lists[GMK_TYPE_WARP] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkWarpList(1);
  lists[GMK_TYPE_SQUAD_LEADER] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSquadLeaderList(1);
  lists[GMK_TYPE_SQUAD_MEMBER] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSquadMemberList(1);
  lists[GMK_TYPE_DOOR] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDoorList(1);
  lists[GMK_TYPE_ELEVATOR] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkElevatorList(1);
  lists[GMK_TYPE_ELEVATOR_LOCATOR] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkElevatorLocatorList(1);
  lists[GMK_TYPE_MAP_JUMP] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMapJumpList(1);
  lists[GMK_TYPE_FIELD_VOLUME] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFieldVolumeList(1);
  lists[GMK_TYPE_CLIMBING] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkClimbingList(1);
  lists[GMK_TYPE_BLADE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkBladeList(1);
  lists[GMK_TYPE_DMG_GIMMICK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgGimmickList(1);
  lists[GMK_TYPE_DMG_PHANTOM] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgPhantomList(1);
  lists[GMK_TYPE_DMG_EFFECT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgEffectList(1);
  lists[GMK_TYPE_DMG_SE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgSeList(1);
  lists[GMK_TYPE_TRIGGER] = nullptr;
  lists[GMK_TYPE_TARGET_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkTargetPointList(1);
  lists[GMK_TYPE_ROUTED_FOOT_PRINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedFootPrintList(1);
  lists[GMK_TYPE_ROUTED_FOOT_PRINT_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedFootPrintPointList(1);
  lists[GMK_TYPE_ANTI_BLADE_AREA] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkAntiBladeAreaList(1);
  lists[GMK_TYPE_TUTORIAL] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkTutorialList(1);
  for (u32 type = 0; type < GMK_TYPE_NUM; type++) {
    IGmkList *list = lists[type];
    if (list == nullptr) {
      continue;
    }
    const char *fileName = GmkManager::get()->getFilenameByType(gmkSetId, static_cast<GmkType>(type));
    if (fileName == nullptr || fileName[0] == '\0') {
      continue;
    }
    const char *bdatName = GmkManager::get()->getSheetnameByType(gmkSetId, static_cast<GmkType>(type));
    IGmkList::CreateInfo info;
    info.memory = createInfo.memory;
    info.set = this;
    info.path = "gmk/";
    info.path += fileName;
    info.path += ".lvb";
    if (bdatName != nullptr) {
      info.bdatName = bdatName;
    }
    info.position = createInfo.position;
    info.rotation = createInfo.rotation;
    list->create(info);
  }
}

bool isInEvent() { return gf::GfGameManager::isEvent(false); }

} // namespace gmk

// clang-format off
#include "gmk/gmk_base.cpp"
#include "gmk/gmk_gob_event_listener_impl.h" // IWYU pragma: keep
// clang-format on

namespace gmk {

GmkBdat::GmkBdat(const CreateInfo *info) : resource(nullptr), data(nullptr), seq(nullptr) {
  if (info != nullptr) {
    create(*info);
  }
}

void GmkBdat::seqWaitResourceLoaded(f32) {
  if (!resource->valid()) {
    return;
  }
  data = resource->getAssetData();
  if (data == nullptr || fw::BdatManager::isExistBdat(createInfo.bdatId)) {
    dispose();
    return;
  }
  fw::BdatManager::loadBdatFromMemory(createInfo.bdatId, data);
  seq = nullptr;
}

static InterestType getInterestType() {
  GmkManager *manager = GmkManager::get();
  if (manager == nullptr) {
    return INTEREST_TYPE_CAMERA;
  }
  return manager->interestType;
}

bool isInterestPosExist() {
  switch (getInterestType()) {
  case INTEREST_TYPE_PLAYER:
    return isPlayerExist();
  case INTEREST_TYPE_CAMERA:
    return isCameraExist();
  }
  return false;
}

bool isPlayerExist() { return gf::GfGameManager::getControlMover() != gf::INVALID_HANDLE; }

bool isCameraExist() { return ml::Scn::sys() != nullptr && ml::Scn::sys()->getCam(-1) != nullptr; }

const mm::Vec3 &getInterestPos() {
  switch (getInterestType()) {
  case INTEREST_TYPE_PLAYER:
    return getPlayerPos();
  case INTEREST_TYPE_CAMERA:
    return getCameraPos();
  }
  return mm::Vec3::zero;
}

const mm::Vec3 &getPlayerPos() {
  return gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
}

const mm::Vec3 &getCameraPos() { return ml::Scn::sys()->getCam(-1)->renderInfo->position; }

bool isPlayerInDoor() { return gf::GfGameManager::isRoom(); }

gf::GF_OBJ_HANDLE *getPlayer() { return gf::GfGameManager::getControlMover(); }

bool toScreenPos(mm::Vec2 &screenPos, const mm::Vec3 &position) {
  mm::Vec3 screen;
  bool isOnScreen = ml::ScnCamUtil::getScreenPos(screen, ml::Scn::sys()->getCam(-1), position);
  screenPos.x = screen.x;
  screenPos.y = screen.y;
  return isOnScreen;
}

AGmkBase *getBindedGmkInst(gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE) {
    return nullptr;
  }
  gf::GfObjAcc acc(handle);
  if (!acc.isValid() || acc.isDestroy() || acc.testFlag(gf::OBJ_FLAG_UI_HIDDEN) || acc.getObj() == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<AGmkBase *>(acc.getUserData(gf::OBJ_USER_DATA_GMK));
}

GmkType getBindedGmkInstType(gf::GF_OBJ_HANDLE *handle) {
  AGmkBase *gmk = getBindedGmkInst(handle);
  if (gmk == nullptr) {
    return GMK_TYPE_INVALID;
  }
  return gmk->getGmkType();
}

void setEventDisp(gf::GF_OBJ_HANDLE *handle, bool isDisp) {
  gf::GfObjAcc acc(handle);
  if (acc.isValid()) {
    acc.setDisp(gf::OBJDISP_GMK_EVENT, isDisp);
  }
}

bool getGobPosRot(mm::Vec3 &position, mm::Quat &rotation, gf::GF_OBJ_HANDLE *handle) {
  gf::GfObjAcc acc(handle);
  if (!acc.isValidTransform()) {
    return false;
  }
  fw::Transform transform = acc.getWorldTransformNoSync();
  position = transform.position;
  rotation = transform.rotation;
  return true;
}

bool isModelRendered(gf::GF_OBJ_HANDLE *handle) {
  gf::GfObjAcc acc(handle);
  gf::GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return false;
  }
  gf::GfComModel *model = obj->getComponent<gf::GfComModel>();
  if (model == nullptr) {
    return false;
  }
  return model->isRender();
}

bool isNaviMeshExist(const mm::Vec3 &position) {
  mm::Vec3 result;
  return fw::NaviUtil::testNaviColi(result, position, 2.0f, 2.0f);
}

bool isGfObjNumFull(u32 objectType) {
  int capacity = gf::GfObjManager::getGfObjCapacity(objectType);
  if (capacity <= 0) {
    return false;
  }
  return capacity <= gf::GfObjManager::getObjectNum(objectType);
}

bool isInBattle() { return gf::GfGameManager::isBattle(); }

bool isInMapJumpWithLoadingSaveData() { return gf::GfGameManager::isMapjumpWithSaveData(); }

void setOpenMainMenuEnable(bool isEnable) { gf::GfGameManager::setStopMainMenuOpenForGimmick(!isEnable); }

void createMenuObj(gf::GF_OBJ_HANDLE *handle) {
  gf::GfObjAcc acc(handle);
  gf::GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return;
  }
  gf::GfComBehaviorGmk *behavior = obj->getComponent<gf::GfComBehaviorGmk>();
  if (behavior != nullptr) {
    behavior->createMenuObj();
  }
}

u32 getDefeatedNum(int enemy) { return gf::GfDataEnemy::getEnemySuppress(enemy); }

void disposeGobInst(gf::GF_OBJ_HANDLE *handle, f32 fadeTime) {
  gf::GfObjAcc acc(handle);
  if (acc.getObj() == nullptr || acc.isDestroy() || acc.testFlag(gf::OBJ_FLAG_UI_HIDDEN)) {
    return;
  }
  gf::SCOM_DESTROY_GAME_OBJ::create(handle, fadeTime, 0);
}

void disposeGobInstWithAttr(gf::GF_OBJ_HANDLE *handle, u32 attribute, f32 fadeTime) {
  gf::GfObjAcc acc(handle);
  if (acc.getObj() == nullptr || acc.isDestroy() || acc.testFlag(gf::OBJ_FLAG_UI_HIDDEN)) {
    return;
  }
  gf::SCOM_DESTROY_GAME_OBJ::create(handle, fadeTime, attribute);
}

bool canObtainPreciousItem() { return gf::GfGameManager::isEnableGetFieldPrecious(); }

bool canCreateBattleLock() { return gf::GfGameManager::isEnableCreateBattleLock(); }

bool canDisposeBattleLock() {
  if (gf::GfDataUtil::getScenarioFlag() == SCENARIO_FLAG_KEEP_BATTLE_LOCK_IN_BATTLE) {
    return !gf::GfGameManager::isBattle();
  }
  return true;
}

const char *debugGetGmkTypeName(GmkType type) { return "(null)"; }

const char *debugGetShapeTypeName(ShapeType type) { return "(null)"; }

const char *debugGetGmkFileName(const AGmkBase &gmk) { return "(null)"; }

const char *debugGetGmkBdatRowName(const AGmkBase &gmk) { return "(null)"; }

const char *debugGetGmkBdatSheetName(const AGmkBase &gmk) { return "(null)"; }

static bool s_isScriptStart = false;
static bool s_isScriptEnd = false;
static int s_scriptStartId = -1;

GmkScript::GmkScript(const CreateInfo *info) : seq(nullptr) {
  if (info != nullptr) {
    createInfo = *info;
  }
}

void GmkScript::create(const CreateInfo &info) {
  endScript();
  createInfo = info;
}

void GmkScript::vmSetStartId(int id) { s_scriptStartId = id; }

int GmkScript::vmGetStartId() { return s_scriptStartId; }

bool GmkScript::isScriptStart() { return s_isScriptStart; }

bool GmkScript::isScriptEnd() { return s_isScriptEnd; }

bool GmkScript::isScriptExecuting() {
  const fw::ScriptManager *manager = fw::ScriptManager::get();
  return manager->scripts[gf::SCRIPT_SLOT_FIELD].isActive();
}

const char *GmkScript::getExecutingScriptName() {
  const fw::ScriptManager *manager = fw::ScriptManager::get();
  return manager->scripts[gf::SCRIPT_SLOT_FIELD].name.c_str();
}

void GmkScript::vmBeginScript() {
  s_isScriptStart = true;
  s_isScriptEnd = false;
}

void GmkScript::vmEndScript() {
  s_isScriptStart = false;
  s_isScriptEnd = true;
}

void GmkScript::dispose() { endScript(); }

void GmkScript::endScript() {
  if (seq) {
    seq = nullptr;
    vmEndScript();
    vmSetStartId(-1);
  }
}

void GmkScript::beginScript() {
  if (isScriptExecuting()) {
    return;
  }
  endScript();
  fw::ScriptManager::get()->loadScript(gf::SCRIPT_SLOT_FIELD, createInfo.name.c_str(), GMK_SCRIPT_FILE_PRIO);
  vmSetStartId(createInfo.startId);
  fw::ScriptManager::get()->scripts[gf::SCRIPT_SLOT_FIELD].start();
  vmBeginScript();
  seq = &GmkScript::seqWaitEndScript;
}

void GmkScript::seqWaitEndScript(f32) {
  const fw::ScriptManager *manager = fw::ScriptManager::get();
  if (!manager->scripts[gf::SCRIPT_SLOT_FIELD].isFinish()) {
    endScript();
  }
}

void GmkScript::update(f32 deltaTime) {
  if (seq) {
    (this->*seq)(deltaTime);
  }
}

ScenarioFlagCond::ScenarioFlagCond(const CBdatWrapper &bdat, int id, const AGmkBase &gmk) {
  u16 scenarioFlagMin = bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16);
  u16 scenarioFlagMax = bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16);
  if (scenarioFlagMax >= scenarioFlagMin) {
    min = scenarioFlagMin;
    max = scenarioFlagMax;
  }
}

ScenarioFlagCond::ScenarioFlagCond(const CBdatWrapper &bdat, int id, const char *prefix) {
  u16 scenarioFlagMin;
  u16 scenarioFlagMax;
  if (prefix == nullptr) {
    scenarioFlagMin = bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16);
    scenarioFlagMax = bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16);
  } else {
    mm::mtl::FixStr<32> name;
    name.format("%s%s", prefix, "ScenarioFlagMin");
    scenarioFlagMin = bdat.getValCheck(name.c_str(), id, BDAT_TYPE_U16);
    name.format("%s%s", prefix, "ScenarioFlagMax");
    scenarioFlagMax = bdat.getValCheck(name.c_str(), id, BDAT_TYPE_U16);
  }
  if (scenarioFlagMax >= scenarioFlagMin) {
    min = scenarioFlagMin;
    max = scenarioFlagMax;
  }
}

bool ScenarioFlagCond::isMatch() const {
  u16 scenarioFlag = gf::GfDataUtil::getScenarioFlag();
  return min <= scenarioFlag && scenarioFlag <= max;
}

QuestFlagCond::QuestFlagCond(const CBdatWrapper &bdat, int id, const AGmkBase &gmk) {
  u16 questFlag = bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16);
  u8 questFlagMin = bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8);
  u8 questFlagMax = bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8);
  if (questFlagMax >= questFlagMin) {
    quest = questFlag;
    minState = questFlagMin;
    maxState = questFlagMax;
  }
}

QuestFlagCond::QuestFlagCond(const CBdatWrapper &bdat, int id, const char *prefix) {
  u16 questFlag;
  u8 questFlagMin;
  u8 questFlagMax;
  if (prefix == nullptr) {
    questFlag = bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16);
    questFlagMin = bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8);
    questFlagMax = bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8);
  } else {
    mm::mtl::FixStr<32> name;
    name.format("%s%s", prefix, "QuestFlag");
    questFlag = bdat.getValCheck(name.c_str(), id, BDAT_TYPE_U16);
    name.format("%s%s", prefix, "QuestFlagMin");
    questFlagMin = bdat.getValCheck(name.c_str(), id, BDAT_TYPE_U8);
    name.format("%s%s", prefix, "QuestFlagMax");
    questFlagMax = bdat.getValCheck(name.c_str(), id, BDAT_TYPE_U8);
  }
  if (questFlagMax >= questFlagMin) {
    quest = questFlag;
    minState = questFlagMin;
    maxState = questFlagMax;
  }
}

bool QuestFlagCond::isMatch() const {
  u8 state = gf::GfQuestInfo::getState(gf::toQuestID(quest));
  return (minState <= state) & (state <= maxState);
}

bool DistCond::isMatch(f32 distSq, const mm::Vec3 &position) {
  if (!isInterestPosExist()) {
    return false;
  }
  const mm::Vec3 &interestPos = getInterestPos();
  f32 x = interestPos.x - position.x;
  f32 y = interestPos.y - position.y;
  f32 z = interestPos.z - position.z;
  if (x * x + y * y + z * z > distSq) {
    return false;
  }
  return true;
}

bool TimeCond::isMatch() const {
  bool isMatched = false;
  if (gf::GfFieldTime::get() != nullptr) {
    isMatched = (gf::GfFieldTime::get()->getTimeRangeBits() & timeRangeBits) != 0;
  }
  return isMatched;
}

bool WeatherCond::isMatch() const { return (gf::GfFieldWeather::getCurrentMapWeatherBit(false) & weatherBits) != 0; }

bool CloudCond::isMatch() const {
  int cloudSea = gf::GfFieldWeather::getCurrentCloudSea();
  if (type == TYPE_NO_CLOUD_SEA) {
    return cloudSea == 0;
  }
  if (type == TYPE_CLOUD_SEA) {
    return cloudSea == 1;
  }
  return false;
}

bool InOutDoorCond::isMatch() const {
  if (isIndoor && isOutdoor) {
    return true;
  }
  if (gf::GfGameManager::isRoom()) {
    return isIndoor;
  }
  return isOutdoor;
}

bool GameFlagCond::isMatch(u32 value) const {
  switch (size) {
  case 1:
    return gf::GfGameFlag::getLocal(1, index) == value;
  case 2:
    return gf::GfGameFlag::getLocal(2, index) == value;
  case 3:
    return gf::GfGameFlag::getLocal(4, index) == value;
  case 4:
    return gf::GfGameFlag::getLocal(8, index) == value;
  case 5:
    return gf::GfGameFlag::getLocal(16, index) == value;
  case 6:
    return gf::GfGameFlag::getLocal(32, index) == value;
  }
  return false;
}

PopPosSafeCond::PopPosSafeCond(const CreateInfo *info) : isCreated(false) {
  if (info != nullptr) {
    create(*info);
  }
}

BootedGmkCond::BootedGmkCond(u8 gimmickType, u16 gimmickId) : gimmickType(0), gimmickId(0) { createIfEnable(gimmickType, gimmickId); }

void BootedGmkCond::create(u8 gimmickType, u16 gimmickId) {
  this->gimmickType = gimmickType;
  this->gimmickId = gimmickId;
}

BootedGmkCond::BootedGmkCond(const CBdatWrapper &bdat, int id, const char *prefix) : gimmickType(0), gimmickId(0) {
  mm::mtl::FixStr<32> name;
  if (prefix == nullptr) {
    name = "gimmickType";
  } else {
    name.format("%sgimmickType", prefix);
  }
  u8 type = bdat.getValCheck(name.c_str(), id, BDAT_TYPE_U8);
  if (prefix == nullptr) {
    name = "gimmickID";
  } else {
    name.format("%sgimmickID", prefix);
  }
  u16 gmkId = bdat.getValCheck(name.c_str(), id, BDAT_TYPE_U16);
  createIfEnable(type, gmkId);
}

void BootedGmkCond::dispose() { gimmickType = 0; }

} // namespace gmk

// clang-format off
#include "gmk/gmk_enemy/gmk_enemy.cpp"
#include "gmk/gmk_npc/gmk_npc_manager_impl.h" // IWYU pragma: keep
#include "gmk/gmk_npc/gmk_npc.cpp"
#include "gmk/gmk_map_obj.cpp"
#include "gmk/gmk_tbox.cpp"
#include "gmk/gmk_event.cpp"
#include "gmk/gmk_field_lock.cpp"
#include "gmk/gmk_effect.cpp"
#include "gmk/gmk_se.cpp"
#include "gmk/gmk_landmark.cpp"
#include "gmk/gmk_route.cpp"
#include "gmk/gmk_collection.cpp"
#include "gmk/gmk_area_bgm.cpp"
#include "gmk/gmk_salvage.cpp"
#include "gmk/gmk_map_gimmick.cpp"
#include "gmk/gmk_precious.cpp"
#include "gmk/gmk_grave.cpp"
#include "gmk/gmk_kizuna_talk.cpp"
#include "gmk/gmk_jump.cpp"
#include "gmk/gmk_warp.cpp"
#include "gmk/gmk_door.cpp"
#include "gmk/gmk_elevator.cpp"
#include "gmk/gmk_map_jump.cpp"
#include "gmk/gmk_field_volume.cpp"
#include "gmk/gmk_climbing.cpp"
#include "gmk/gmk_blade.cpp"
#include "gmk/gmk_dmg_gimmick.cpp"
#include "gmk/gmk_foot_print.cpp"
#include "gmk/gmk_anti_blade_area.cpp"
#include "gmk/gmk_tutorial.cpp"
// clang-format on
