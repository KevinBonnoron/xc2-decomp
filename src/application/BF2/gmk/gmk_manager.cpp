#include "gmk/gmk_manager.h"

#include <math.h>

#include "bdat.h"
#include "dr/dr_man.h"
#include "framework/coli/coli_object.h"
#include "framework/debug/debug_draw.h"
#include "framework/memory/framework_memory.h"
#include "framework/navi/navi_util.h"
#include "framework/resource/common_resource.h"
#include "framework/script/script_manager.h"
#include "fw/fw_bdat_manager.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/field/gf_field_lod.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/field/gf_mob_slot_manager.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_target.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/menu/gf_menu_common_window_param.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
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
#include "gmk/gmk_phantom.h"
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
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"

namespace mm {
struct Col4;
} // namespace mm

namespace gmk {

constexpr u16 SCENARIO_FLAG_KEEP_BATTLE_LOCK_IN_BATTLE = 7039;
const ml::FILE_PRIO GMK_SCRIPT_FILE_PRIO = static_cast<ml::FILE_PRIO>(7);

static const char *const s_gmkFileNames[] = {
    "enemy",       "enemy",    "enemy", "npc",        "npc",        "npc",        "mapObj",     "mapObj", "mapObj", "tbox",      "event",     "enemy",         "fieldLock", "effect",     "effect",
    "se",          "se",       "se",    "mob",        "mob",        "mob",        "landmark",   nullptr,  nullptr,  "formPc",    "formPc",    "formPcEv",      "formPcEv",  "collection", "areaBgm",
    "areaWeather", "salvage",  nullptr, "mapGimmick", "precious",   "grave",      "kizunaTalk", "jump",   "warp",   "squad",     "squad",     "door",          "elevator",  "elevator",   "mapJump",
    "fieldVolume", "climbing", "blade", "dmgGimmick", "dmgGimmick", "dmgGimmick", "dmgGimmick", nullptr,  "enemy",  "footPrint", "footPrint", "antiBladeArea", "tutorial",
};

bool GmkBdat::isValid() const { return unknown120 != nullptr && fw::BdatManager::isEnableBdat(unknown08.unknown108); }

bool GmkBdat::create(const CreateInfo &info) {
  dispose();
  unknown08 = info;
  unknown118 = fw::CommonResource::request(info.unknown00, unknown08.unknown04.c_str(), 9, false);
  if (unknown118->getRefCount() != 1) {
    return false;
  }
  unknown128 = &GmkBdat::seqWaitResourceLoaded;
  return true;
}

void GmkBdat::dispose() {
  unknown128 = nullptr;
  if (unknown08.unknown108 >= 0) {
    fw::BdatManager::unregistBdat(unknown08.unknown108);
    unknown08.unknown108 = -1;
  }
  mm::mtl::safeRelease(unknown118);
  unknown120 = nullptr;
  unknown08 = CreateInfo();
}

bool GmkSet::isValid() const { return unknown10.unknown00.isValid() && unknown10.unknown04 > 0 && (!unknown40.unknown08.isValid() || unknown40.isValid()); }

void GmkBdat::update(f32 deltaTime) {
  if (unknown128) {
    (this->*unknown128)(deltaTime);
  }
}

const char *GmkManager::getFilenameByType(int gmkSetId, GmkType type) const {
  const char *column = s_gmkFileNames[type];
  if (column == nullptr) {
    return nullptr;
  }
  u8 *bdat = unknown190;
  if (Bdat::getMember(bdat, column) == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(Bdat::getValCheck(bdat, column, gmkSetId, BDAT_TYPE_STRING));
}

const char *GmkManager::getSheetnameByType(int gmkSetId, GmkType type) const {
  mm::mtl::FixStr<256> column;
  column.format("%s_bdat", s_gmkFileNames[type]);
  u8 *bdat = unknown190;
  if (Bdat::getMember(bdat, column.c_str()) == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(Bdat::getValCheck(bdat, column.c_str(), gmkSetId, BDAT_TYPE_STRING));
}

int GmkManager::getMapBdatId(int gmkSetId) const {
  u8 *bdat = unknown190;
  int count = Bdat::getIdCount(bdat);
  int top = Bdat::getIdTop(bdat);
  if (gmkSetId < top || gmkSetId >= top + count) {
    return -1;
  }
  return static_cast<u16>(Bdat::getValCheck(bdat, "mapId", gmkSetId, BDAT_TYPE_U16));
}

const AGmkBase *GmkManager::findFirstGmkInstByBdatId(GmkType type, int bdatId) const {
  for (GmkSet *const *it = unknownf358.begin(); it != unknownf358.end(); ++it) {
    const GmkSet *set = *it;
    if (set == nullptr || !set->isValid()) {
      continue;
    }
    const AGmkBase *gmk = set->findFirstGmkInstByBdatId(type, bdatId);
    if (gmk != nullptr) {
      return gmk;
    }
  }
  return nullptr;
}

const AGmkBase *GmkSet::findFirstGmkInstByBdatId(GmkType type, int bdatId) const {
  IGmkList *list = unknown1b8[type];
  if (list == nullptr) {
    return nullptr;
  }
  u32 num = list->getInstNum();
  for (u32 i = 0; i < num; i++) {
    const AGmkBase *gmk = list->getInst(i);
    if (gmk->isValid() && gmk->unknown20.unknown18 == bdatId) {
      return gmk;
    }
  }
  return nullptr;
}

const AGmkBase *GmkManager::findGmkInstByGmkInstIndex(int gmkSetId, GmkType type, u32 index) const {
  const GmkSet *set = findGmkSet(gmkSetId);
  if (set == nullptr) {
    return nullptr;
  }
  return set->findGmkInstByGmkInstIndex(type, index);
}

bool GmkManager::isValid() const {
  if (unknown58.unknown120 == nullptr || !fw::BdatManager::isEnableBdat(unknown58.unknown08.unknown108)) {
    return false;
  }
  return unknown190 != nullptr;
}

void GmkManager::update(f32 deltaTime) {
  unknown58.update(deltaTime);
  if (unknownf380) {
    (this->*unknownf380)(deltaTime);
  }
}

void GmkManager::clearGmkSets() {
  if (unknownf358.empty()) {
    return;
  }
  for (GmkSet **it = unknownf358.begin(); it != unknownf358.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
  }
  unknownf358.clear();
}

void GmkManager::disposeGmkSet(int gmkSetId) {
  if (unknownf358.empty()) {
    return;
  }
  for (GmkSet **it = unknownf358.begin(); it != unknownf358.end(); ++it) {
    if ((*it)->unknown10.unknown04 == gmkSetId) {
      delete *it;
      unknownf358.erase(it);
      return;
    }
  }
}

int GmkManager::findFirstBdatId_RSC_GmkSetList(int map) const {
  if (!unknown58.isValid()) {
    return -1;
  }
  u8 *bdat = unknown190;
  int count = Bdat::getIdCount(bdat);
  int top = Bdat::getIdTop(bdat);
  for (int id = top; id < top + count; id++) {
    if (getMapBdatId(id) == map) {
      return id;
    }
  }
  return -1;
}

bool GmkManager::isBdatIdOfGmkInstExist(int gmkSetId, GmkType type, int bdatId) const {
  if (gmkSetId <= 0) {
    return false;
  }
  const char *sheetName = getSheetnameByType(gmkSetId, type);
  if (sheetName == nullptr) {
    return false;
  }
  if (sheetName[0] != '\0') {
    u8 *bdat = Bdat::isExistFP(sheetName);
    if (bdat != nullptr) {
      int count = Bdat::getIdCount(bdat);
      int top = Bdat::getIdTop(bdat);
      return top <= bdatId && bdatId < top + count;
    }
  }
  return false;
}

int GmkManager::findFirstBdatId_RSC_GmkSetList(GmkType type, int bdatId) const {
  int gmkSetId = findFirstBdatId_RSC_GmkSetList(gf::GfGameManager::getMapID());
  if (gmkSetId > 0 && isBdatIdOfGmkInstExist(gmkSetId, type, bdatId)) {
    return gmkSetId;
  }
  u8 *bdat = unknown190;
  if (bdat == nullptr) {
    return -1;
  }
  int count = Bdat::getIdCount(bdat);
  int top = Bdat::getIdTop(bdat);
  for (int id = top; id < top + count; id++) {
    if (isBdatIdOfGmkInstExist(id, type, bdatId)) {
      return id;
    }
  }
  return -1;
}

GmkSet *GmkManager::findGmkSet(int gmkSetId) const {
  for (GmkSet *const *it = unknownf358.begin(); it != unknownf358.end(); ++it) {
    GmkSet *set = *it;
    if (set != nullptr && set->unknown10.unknown04 == gmkSetId) {
      return set;
    }
  }
  return nullptr;
}

const AGmkBase *GmkSet::findGmkInstByGmkInstIndex(GmkType type, u32 index) const {
  IGmkList *list = unknown1b8[type];
  if (list != nullptr && index < list->getInstNum()) {
    return list->getInst(index);
  }
  return nullptr;
}

int getCurrentMapBdatId() { return gf::GfGameManager::getMapID(); }

void GmkSet::update(f32 deltaTime) {
  const GmkManager *manager = GmkManager::get();
  if (!manager->unknown58.isValid() || manager->unknown190 == nullptr) {
    return;
  }
  unknown40.update(deltaTime);
  unknown178.update(deltaTime);
  if (unknown388) {
    (this->*unknown388)(deltaTime);
  }
}

GmkSet::GmkSet(const CreateInfo *info) : unknown40(nullptr), unknown178(0xffffffff) {
  for (u32 type = 0; type < GMK_TYPE_NUM; type++) {
    unknown1b8[type] = nullptr;
  }
  unknown388 = nullptr;
  if (info != nullptr) {
    create(*info);
  }
}

void GmkSet::create(const CreateInfo &info) {
  dispose();
  unknown10 = info;
  unknown178.unknown3c = !info.unknown24;
  unknown388 = &GmkSet::seqWaitToValidate_GfGameManager_m_mapID;
}

void GmkSet::dispose() {
  unknown388 = nullptr;
  disposeGmkLists();
  disposeMapBdat();
  unknown10 = CreateInfo();
}

GmkSet::~GmkSet() { dispose(); }

const IGmkList *GmkSet::getGmkList(GmkType type) const { return unknown1b8[type]; }

IGmkList *GmkSet::getGmkList(GmkType type) { return unknown1b8[type]; }

void GmkSet::seqWaitToValidate_GfGameManager_m_mapID(f32 deltaTime) {
  if (gf::GfGameManager::getMapID() != 0) {
    unknown388 = &GmkSet::seqCreateMapBdat;
  }
}

void GmkSet::disposeGmkLists() {
  for (u32 type = 0; type < GMK_TYPE_NUM; type++) {
    if (unknown1b8[type] != nullptr) {
      delete unknown1b8[type];
      unknown1b8[type] = nullptr;
    }
  }
}

void GmkSet::disposeMapBdat() { unknown40.dispose(); }

void GmkSet::seqUpdate(f32 deltaTime) {
  for (u32 type = 0; type < GMK_TYPE_NUM; type++) {
    if (unknown1b8[type] != nullptr) {
      unknown1b8[type]->update(deltaTime);
    }
  }
}

bool GmkSet::createMapBdat(int map) {
  unknown40.dispose();
  GmkBdat::CreateInfo info;
  const char *name = reinterpret_cast<const char *>(Bdat::getValCheck(GmkManager::get()->unknown190, "bdat", map, BDAT_TYPE_STRING));
  if (name == nullptr || name[0] == '\0') {
    return false;
  }
  info.unknown00 = unknown10.unknown00;
  info.unknown04 = "gmk/";
  info.unknown04 += name;
  info.unknown04 += ".bdat";
  info.unknown108 = 4;
  return unknown40.create(info);
}

void GmkSet::createGmkLists(int gmkSetId) {
  unknown178.setUpdateNpcNumPerFrame(32);
  for (int i = 0; i < GMK_TYPE_NUM; i++) {
    delete unknown1b8[i];
    unknown1b8[i] = nullptr;
  }
  unknown1b8[GMK_TYPE_ENEMY] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEnemyList(32);
  unknown1b8[GMK_TYPE_ROUTED_ENEMY] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedEnemyList(8);
  unknown1b8[GMK_TYPE_ROUTED_ENEMY_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedEnemyPointList(1);
  unknown1b8[GMK_TYPE_NPC] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkNpcList(0);
  unknown1b8[GMK_TYPE_ROUTED_NPC] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedNpcList(0);
  unknown1b8[GMK_TYPE_NPC_ROUTE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
  unknown1b8[GMK_TYPE_MAP_OBJ] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMapObjList(8);
  unknown1b8[GMK_TYPE_ROUTED_MAP_OBJ] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedMapObjList(4);
  unknown1b8[GMK_TYPE_MAP_OBJ_ROUTE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
  unknown1b8[GMK_TYPE_TBOX] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkTboxList(8);
  unknown1b8[GMK_TYPE_EVENT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEventList(8);
  unknown1b8[GMK_TYPE_BATTLE_LOCK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkBattleLockList(8);
  unknown1b8[GMK_TYPE_FIELD_LOCK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFieldLockList(8);
  unknown1b8[GMK_TYPE_EFFECT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEffectList(8);
  unknown1b8[GMK_TYPE_EFFECT_LOCATOR] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEffectLocatorList(1);
  unknown1b8[GMK_TYPE_SE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSeList(8);
  unknown1b8[GMK_TYPE_SE_LINE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSeLineList(4);
  unknown1b8[GMK_TYPE_SE_LINE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSeLinePointList(1);
  unknown1b8[GMK_TYPE_MOB] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMobList(8);
  unknown1b8[GMK_TYPE_ROUTED_MOB] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedMobList(4);
  unknown1b8[GMK_TYPE_MOB_ROUTE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
  unknown1b8[GMK_TYPE_LANDMARK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkLandmarkList(8);
  unknown1b8[GMK_TYPE_ROUTE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRouteList(1);
  unknown1b8[GMK_TYPE_ROUTE_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
  unknown1b8[GMK_TYPE_FORM_PC] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFormPcList(1);
  unknown1b8[GMK_TYPE_FORM_PCNPC] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFormPcnpcList(1);
  unknown1b8[GMK_TYPE_FORM_PC_EV] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFormPcEvList(1);
  unknown1b8[GMK_TYPE_FORM_PCNPC_EV] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFormPcnpcEvList(1);
  unknown1b8[GMK_TYPE_COLLECTION] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkCollectionList(1);
  unknown1b8[GMK_TYPE_AREA_BGM] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkAreaBgmList(1);
  unknown1b8[GMK_TYPE_AREA_WEATHER] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkAreaWeatherList(1);
  unknown1b8[GMK_TYPE_SALVAGE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSalvageList(1);
  unknown1b8[GMK_TYPE_SALVAGE_LOCATOR] = nullptr;
  unknown1b8[GMK_TYPE_MAP_GIMMICK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMapGimmickList(1);
  unknown1b8[GMK_TYPE_PRECIOUS] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkPreciousList(1);
  unknown1b8[GMK_TYPE_GRAVE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkGraveList(1);
  unknown1b8[GMK_TYPE_KIZUNA_TALK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkKizunaTalkList(1);
  unknown1b8[GMK_TYPE_JUMP] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkJumpList(1);
  unknown1b8[GMK_TYPE_WARP] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkWarpList(1);
  unknown1b8[GMK_TYPE_SQUAD_LEADER] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSquadLeaderList(1);
  unknown1b8[GMK_TYPE_SQUAD_MEMBER] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSquadMemberList(1);
  unknown1b8[GMK_TYPE_DOOR] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDoorList(1);
  unknown1b8[GMK_TYPE_ELEVATOR] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkElevatorList(1);
  unknown1b8[GMK_TYPE_ELEVATOR_LOCATOR] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkElevatorLocatorList(1);
  unknown1b8[GMK_TYPE_MAP_JUMP] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMapJumpList(1);
  unknown1b8[GMK_TYPE_FIELD_VOLUME] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkFieldVolumeList(1);
  unknown1b8[GMK_TYPE_CLIMBING] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkClimbingList(1);
  unknown1b8[GMK_TYPE_BLADE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkBladeList(1);
  unknown1b8[GMK_TYPE_DMG_GIMMICK] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgGimmickList(1);
  unknown1b8[GMK_TYPE_DMG_PHANTOM] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgPhantomList(1);
  unknown1b8[GMK_TYPE_DMG_EFFECT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgEffectList(1);
  unknown1b8[GMK_TYPE_DMG_SE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgSeList(1);
  unknown1b8[GMK_TYPE_TRIGGER] = nullptr;
  unknown1b8[GMK_TYPE_TARGET_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkTargetPointList(1);
  unknown1b8[GMK_TYPE_ROUTED_FOOT_PRINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedFootPrintList(1);
  unknown1b8[GMK_TYPE_ROUTED_FOOT_PRINT_POINT] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedFootPrintPointList(1);
  unknown1b8[GMK_TYPE_ANTI_BLADE_AREA] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkAntiBladeAreaList(1);
  unknown1b8[GMK_TYPE_TUTORIAL] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkTutorialList(1);
  for (u32 type = 0; type < GMK_TYPE_NUM; type++) {
    IGmkList *list = unknown1b8[type];
    if (list == nullptr) {
      continue;
    }
    const char *fileName = GmkManager::get()->getFilenameByType(gmkSetId, static_cast<GmkType>(type));
    if (fileName == nullptr || fileName[0] == '\0') {
      continue;
    }
    const char *bdatName = GmkManager::get()->getSheetnameByType(gmkSetId, static_cast<GmkType>(type));
    IGmkList::CreateInfo info;
    info.unknown00 = unknown10.unknown00;
    info.unknown08 = this;
    info.unknown10 = "gmk/";
    info.unknown10 += fileName;
    info.unknown10 += ".lvb";
    if (bdatName != nullptr) {
      info.unknown114 = bdatName;
    }
    info.unknown140 = unknown10.unknown10;
    info.unknown150 = unknown10.unknown20;
    list->create(info);
  }
}

void GmkSet::seqCreateMapBdat(f32 deltaTime) {
  createGmkLists(unknown10.unknown04);
  unknown388 = &GmkSet::seqUpdate;
}

void GmkSet::seqCreateMapGmk(f32 deltaTime) {
  if (unknown40.isValid() || !unknown40.unknown08.isValid()) {
    createGmkLists(unknown10.unknown04);
    unknown388 = &GmkSet::seqUpdate;
  }
}

bool isInEvent() { return gf::GfGameManager::isEvent(false); }

} // namespace gmk

// clang-format off
#include "gmk/gmk_base.cpp"
#include "gmk/gmk_gob_event_listener_impl.h" // IWYU pragma: keep
#include "gmk/gmk_acc.cpp"
// clang-format on

namespace gmk {

GmkBdat::GmkBdat(const CreateInfo *info) : unknown118(nullptr), unknown120(nullptr), unknown128(nullptr) {
  if (info != nullptr) {
    create(*info);
  }
}

void GmkBdat::seqWaitResourceLoaded(f32) {
  if (!unknown118->valid()) {
    return;
  }
  unknown120 = unknown118->getAssetData();
  if (unknown120 == nullptr || fw::BdatManager::isExistBdat(unknown08.unknown108)) {
    dispose();
    return;
  }
  fw::BdatManager::loadBdatFromMemory(unknown08.unknown108, unknown120);
  unknown128 = nullptr;
}

static InterestType getInterestType() {
  GmkManager *manager = GmkManager::get();
  if (manager == nullptr) {
    return INTEREST_TYPE_CAMERA;
  }
  return manager->unknown198;
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

const mm::Vec3 &getPlayerPos() { return gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition(); }

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
  position = transform.unknown00;
  rotation = transform.unknown10;
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

bool getYSnapPos(mm::Vec3 &result, const mm::Vec3 &position, f32 distance) {
  fw::ColiCheckConfig config;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown15 = false;
  config.unknown14 = true;
  config.unknown10 = 2;
  config.unknown04 = 0x80000020;
  config.unknown00 = 9;
  return getYSnapPos(result, position, distance, config);
}

void reqDrawCmnMsg(u32 messageId) {
  gf::MenuCommonWindowParam param;
  param.unknown10 = gf::GfDataBdat::getFP(gf::BDAT_FLD_HELPMS);
  param.unknown18 = messageId;
  gf::GfPlayFactory::createCommonMessage(param);
}

int getCapaOfGmkDmgPhantomTargetInfo() {
  int capacity = gf::GfObjManager::getGfObjCapacity(gf::OBJECT_TYPE_ENEMY);
  return capacity > 0 ? capacity + 3 : 3;
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

f32 getMobPopDistSq() {
  const gf::GfFieldGimmick *gimmick = mm::mtl::PtrSingleton<gf::GfFieldGimmick>::get();
  if (gimmick == nullptr) {
    return 1e12f;
  }
  return gimmick->unknownf910.unknown528;
}

void resetMobPopDistSq() {
  gf::GfFieldGimmick *gimmick = mm::mtl::PtrSingleton<gf::GfFieldGimmick>::get();
  if (gimmick == nullptr) {
    return;
  }
  if (gimmick->unknownf910.unknown520 != 0) {
    gimmick->unknownf910.unknown520 = 0;
  }
  gimmick->unknownf910.unknown528 = 1e12f;
}

bool addFailedPopDistSq(f32 distSq) {
  gf::GfFieldGimmick *gimmick = mm::mtl::PtrSingleton<gf::GfFieldGimmick>::get();
  if (gimmick == nullptr) {
    return false;
  }
  return gimmick->unknownf910.addFailedPopDistSq(distSq);
}

u32 getBindedFsId(const AGmkBase &gmk) {
  GmkType type = gmk.getGmkType();
  if (type == GMK_TYPE_TBOX) {
    const GmkTbox &tbox = static_cast<const GmkTbox &>(gmk);
    const char *column = "FSID";
    if (tbox.getBdatInfo()->unknown02 && tbox.getProgress() == GmkTbox::PROGRESS_CLOSED) {
      column = "FSID2";
    }
    return Bdat::getValCheck(gmk.getBindedBdatFp(), column, gmk.unknown20.unknown18, BDAT_TYPE_U16);
  }
  if (type == GMK_TYPE_JUMP || type == GMK_TYPE_WARP || type == GMK_TYPE_MAP_GIMMICK) {
    return Bdat::getValCheck(gmk.getBindedBdatFp(), "FSID", gmk.unknown20.unknown18, BDAT_TYPE_U16);
  }
  return 0;
}

bool isMapJumpingWithSaveData() {
  const gf::GfFieldGimmick *gimmick = mm::mtl::PtrSingleton<gf::GfFieldGimmick>::get();
  if (gimmick == nullptr) {
    return false;
  }
  return gimmick->unknownfe40;
}

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

u32 GmkTbox::getProgress() const { return gf::GfGameFlag::getLocal(2, unknown20.unknown18 + GAME_FLAG_PROGRESS); }

u32 getBdatIdOfQuestTargetIcon(gf::GF_OBJ_HANDLE *handle, u16 iconType) {
  if (handle == gf::INVALID_HANDLE) {
    return 0xffffffff;
  }
  gf::GfObjAcc acc(handle);
  if (!acc.isValid() || acc.isDestroy() || acc.testFlag(gf::OBJ_FLAG_UI_HIDDEN) || acc.getObj() == nullptr) {
    return 0xffffffff;
  }
  gf::QuestID questId = {iconType, 0};
  return getBdatIdOfQuestTargetIcon(gf::GfQuestTarget::getIconType(handle, questId));
}

u32 getBdatIdOfQuestTargetIcon(u32 iconType) {
  u8 *bdat = gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA);
  switch (iconType) {
  case 1:
    return Bdat::getValCheck(bdat, 1, 0xf, BDAT_TYPE_U16).valueU16;
  case 2:
    return Bdat::getValCheck(bdat, 1, 0x10, BDAT_TYPE_U16).valueU16;
  case 3:
    return Bdat::getValCheck(bdat, 1, 0x11, BDAT_TYPE_U16).valueU16;
  case 4:
    return Bdat::getValCheck(bdat, 1, 0x12, BDAT_TYPE_U16).valueU16;
  case 6:
    return Bdat::getValCheck(bdat, 1, 0x13, BDAT_TYPE_U16).valueU16;
  default:
    return 0xffffffff;
  }
}

bool isEnemyPopCondOfQuestMatched(u16 enemy) {
  int remain = gf::GfQuestUtil::getEnemyPopRemainNumber(enemy);
  if (remain < 0) {
    return true;
  }
  if (remain == 0) {
    return false;
  }
  return remain > static_cast<int>(gf::GfGameUtil::getObjNumberByEnArrangeId(enemy));
}

bool canDepop(gf::GF_OBJ_HANDLE *handle) {
  gf::GfObjAcc acc(handle);
  gf::GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    if (obj->unknown28 == gf::OBJECT_TYPE_ENEMY) {
      if (acc.isBattle()) {
        return false;
      }
    } else if (obj->unknown28 == gf::OBJECT_TYPE_NPC) {
      gf::GfComBehaviorNpc *behavior = obj->getComponent<gf::GfComBehaviorNpc>();
      if (behavior != nullptr && behavior->unknown100) {
        return false;
      }
    }
  }
  return true;
}

void applyLodFade(u16 lodId, bool isImmediate) {
  const gf::GfFieldLod::unknown001 *info = gf::GfFieldLod::get()->findBdatInfo(lodId);
  if (info == nullptr) {
    return;
  }
  if (info->unknown04 > 0.0f) {
    gf::GfFieldLod::get()->setFade(lodId, true, isImmediate);
  } else if (info->unknown08 > 0.0f) {
    gf::GfFieldLod::get()->setFade(lodId, false, isImmediate);
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

GmkScript::GmkScript(const CreateInfo *info) : unknown30(nullptr) {
  if (info != nullptr) {
    unknown08 = *info;
  }
}

void GmkScript::create(const CreateInfo &info) {
  endScript();
  unknown08 = info;
}

void GmkScript::vmSetStartId(int id) { s_scriptStartId = id; }

int GmkScript::vmGetStartId() { return s_scriptStartId; }

bool GmkScript::isScriptStart() { return s_isScriptStart; }

bool GmkScript::isScriptEnd() { return s_isScriptEnd; }

bool GmkScript::isScriptExecuting() {
  const fw::ScriptManager *manager = fw::ScriptManager::get();
  return manager->unknown20[gf::SCRIPT_SLOT_FIELD].isActive();
}

const char *GmkScript::getExecutingScriptName() {
  const fw::ScriptManager *manager = fw::ScriptManager::get();
  return manager->unknown20[gf::SCRIPT_SLOT_FIELD].unknown118.c_str();
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
  if (unknown30) {
    unknown30 = nullptr;
    vmEndScript();
    vmSetStartId(-1);
  }
}

void GmkScript::beginScript() {
  if (isScriptExecuting()) {
    return;
  }
  endScript();
  fw::ScriptManager::get()->loadScript(gf::SCRIPT_SLOT_FIELD, unknown08.unknown00.c_str(), GMK_SCRIPT_FILE_PRIO);
  vmSetStartId(unknown08.unknown24);
  fw::ScriptManager::get()->unknown20[gf::SCRIPT_SLOT_FIELD].start();
  vmBeginScript();
  unknown30 = &GmkScript::seqWaitEndScript;
}

void GmkScript::seqWaitEndScript(f32) {
  const fw::ScriptManager *manager = fw::ScriptManager::get();
  if (!manager->unknown20[gf::SCRIPT_SLOT_FIELD].isFinish()) {
    endScript();
  }
}

void GmkScript::update(f32 deltaTime) {
  if (unknown30) {
    (this->*unknown30)(deltaTime);
  }
}

GmkPhantom::GmkPhantom(const CreateInfo *info) : unknown70(nullptr), unknown78(nullptr), unknown80(false), unknown81(false), unknown82(false), unknown83(false) {
  if (info != nullptr) {
    create(*info);
  }
  GmkPhantomManager::get()->addGmkPhantom(this);
}

GmkPhantom::~GmkPhantom() {
  if (GmkPhantomManager::get() != nullptr) {
    GmkPhantomManager::get()->removeGmkPhantom(this);
  }
  dispose();
}

void GmkPhantom::dispose() {
  if (unknown78 != nullptr) {
    unknown78->setColiUserData(nullptr);
    unknown78->setListener(nullptr);
  }
  unknown83 = false;
  mm::mtl::safeRelease(unknown78);
  unknown70 = nullptr;
}

void GmkPhantomManager::addGmkPhantom(GmkPhantom *phantom) { unknown08.push_back(phantom); }

void GmkPhantomManager::removeGmkPhantom(GmkPhantom *phantom) {
  if (phantom != nullptr) {
    unknown08.erase(phantom);
  }
}

GmkPhantomManager::GmkPhantomManager() {}

GmkPhantomManager::~GmkPhantomManager() {}

ScenarioFlagCond::ScenarioFlagCond(const CBdatWrapper &bdat, int id, const AGmkBase &gmk) {
  u16 scenarioFlagMin = bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16);
  u16 scenarioFlagMax = bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16);
  if (scenarioFlagMax >= scenarioFlagMin) {
    unknown00 = scenarioFlagMin;
    unknown02 = scenarioFlagMax;
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
    unknown00 = scenarioFlagMin;
    unknown02 = scenarioFlagMax;
  }
}

bool ScenarioFlagCond::isMatch() const {
  u16 scenarioFlag = gf::GfDataUtil::getScenarioFlag();
  return unknown00 <= scenarioFlag && scenarioFlag <= unknown02;
}

QuestFlagCond::QuestFlagCond(const CBdatWrapper &bdat, int id, const AGmkBase &gmk) {
  u16 questFlag = bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16);
  u8 questFlagMin = bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8);
  u8 questFlagMax = bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8);
  if (questFlagMax >= questFlagMin) {
    unknown00 = questFlag;
    unknown02 = questFlagMin;
    unknown03 = questFlagMax;
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
    unknown00 = questFlag;
    unknown02 = questFlagMin;
    unknown03 = questFlagMax;
  }
}

bool QuestFlagCond::isMatch() const {
  u8 state = gf::GfQuestInfo::getState(gf::toQuestID(unknown00));
  return (unknown02 <= state) & (state <= unknown03);
}

bool DistHvCond::isMatch(const mm::Vec3 &position) const {
  if (!isInterestPosExist()) {
    return false;
  }
  const mm::Vec3 &interestPos = getInterestPos();
  f32 y = interestPos.y - position.y;
  f32 verticalSq = y * y;
  if (unknown04 < verticalSq) {
    return false;
  }
  f32 x = interestPos.x - position.x;
  f32 z = interestPos.z - position.z;
  f32 horizontalSq = x * x + z * z;
  if (unknown00 < horizontalSq) {
    return false;
  }
  return true;
}

void DistHvCond::debugDraw(const mm::Vec3 &position, const mm::Col4 &color) const {
  f32 horizontalDist = sqrtf(unknown00);
  f32 verticalDist = sqrtf(unknown04);
  mm::Vec3 center = position;
  mm::Mat44 matrix;
  matrix.rows[0][0] = 1.0f;
  matrix.rows[0][1] = 0.0f;
  matrix.rows[0][2] = 0.0f;
  matrix.rows[0][3] = 0.0f;
  matrix.rows[1][0] = 0.0f;
  matrix.rows[1][1] = 1.0f;
  matrix.rows[1][2] = 0.0f;
  matrix.rows[1][3] = 0.0f;
  matrix.rows[2][0] = 0.0f;
  matrix.rows[2][1] = 0.0f;
  matrix.rows[2][2] = 1.0f;
  matrix.rows[2][3] = 0.0f;
  matrix.rows[3][0] = center.x;
  matrix.rows[3][1] = center.y;
  matrix.rows[3][2] = center.z;
  matrix.rows[3][3] = 1.0f;
  fw::debug::drawCylinder(matrix, verticalDist + verticalDist, horizontalDist, color, 8);
}

void DistCond::debugDraw(const mm::Vec3 &position, const mm::Col4 &color) const {
  mm::Vec3 center = position;
  mm::Mat44 matrix;
  matrix.rows[0][0] = 1.0f;
  matrix.rows[0][1] = 0.0f;
  matrix.rows[0][2] = 0.0f;
  matrix.rows[0][3] = 0.0f;
  matrix.rows[1][0] = 0.0f;
  matrix.rows[1][1] = 1.0f;
  matrix.rows[1][2] = 0.0f;
  matrix.rows[1][3] = 0.0f;
  matrix.rows[2][0] = 0.0f;
  matrix.rows[2][1] = 0.0f;
  matrix.rows[2][2] = 1.0f;
  matrix.rows[2][3] = 0.0f;
  matrix.rows[3][0] = center.x;
  matrix.rows[3][1] = center.y;
  matrix.rows[3][2] = center.z;
  matrix.rows[3][3] = 1.0f;
  fw::debug::drawSphere(matrix, sqrtf(unknown00), color, 12);
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
    isMatched = (gf::GfFieldTime::get()->getTimeRangeBits() & unknown08) != 0;
  }
  return isMatched;
}

bool WeatherCond::isMatch() const { return (gf::GfFieldWeather::getCurrentMapWeatherBit(false) & unknown08) != 0; }

bool CloudCond::isMatch() const {
  int cloudSea = gf::GfFieldWeather::getCurrentCloudSea();
  if (unknown08 == TYPE_NO_CLOUD_SEA) {
    return cloudSea == 0;
  }
  if (unknown08 == TYPE_CLOUD_SEA) {
    return cloudSea == 1;
  }
  return false;
}

bool InOutDoorCond::isMatch() const {
  if (unknown08 && unknown09) {
    return true;
  }
  if (gf::GfGameManager::isRoom()) {
    return unknown08;
  }
  return unknown09;
}

bool GameFlagCond::isMatch(u32 value) const {
  switch (unknown08) {
  case 1:
    return gf::GfGameFlag::getLocal(1, unknown0c) == value;
  case 2:
    return gf::GfGameFlag::getLocal(2, unknown0c) == value;
  case 3:
    return gf::GfGameFlag::getLocal(4, unknown0c) == value;
  case 4:
    return gf::GfGameFlag::getLocal(8, unknown0c) == value;
  case 5:
    return gf::GfGameFlag::getLocal(16, unknown0c) == value;
  case 6:
    return gf::GfGameFlag::getLocal(32, unknown0c) == value;
  }
  return false;
}

PopPosSafeCond::PopPosSafeCond(const CreateInfo *info) : unknown20(false) {
  if (info != nullptr) {
    create(*info);
  }
}

BootedGmkCond::BootedGmkCond(u8 gimmickType, u16 gimmickId) : unknown00(0), unknown02(0) { createIfEnable(gimmickType, gimmickId); }

void BootedGmkCond::create(u8 gimmickType, u16 gimmickId) {
  this->unknown00 = gimmickType;
  this->unknown02 = gimmickId;
}

BootedGmkCond::BootedGmkCond(const CBdatWrapper &bdat, int id, const char *prefix) : unknown00(0), unknown02(0) {
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

void BootedGmkCond::dispose() { unknown00 = 0; }

} // namespace gmk

// clang-format off
#include "gmk/gmk_collision.cpp"
#include "gmk/gmk_enemy/gmk_enemy.cpp"
#include "gmk/gmk_enemy/gmk_routed_enemy.cpp"
#include "gmk/gmk_npc/gmk_npc_manager_impl.h" // IWYU pragma: keep
#include "gmk/gmk_npc/gmk_npc_manager.cpp"
#include "gmk/gmk_npc/gmk_npc.cpp"
#include "gmk/gmk_npc/gmk_routed_npc.cpp"
#include "gmk/gmk_map_obj.cpp"
#include "gmk/gmk_tbox.cpp"
#include "gmk/gmk_event.cpp"
#include "gmk/gmk_battle_lock.cpp"
#include "gmk/gmk_field_lock.cpp"
#include "gmk/gmk_effect.cpp"
#include "gmk/gmk_se.cpp"
#include "gmk/gmk_squad.cpp"
#include "gmk/gmk_mob/gmk_mob.cpp"
#include "gmk/gmk_mob/gmk_routed_mob.cpp"
#include "gmk/gmk_landmark.cpp"
#include "gmk/gmk_route.cpp"
#include "gmk/gmk_collection.cpp"
#include "gmk/gmk_area_bgm.cpp"
#include "gmk/gmk_area_weather.cpp"
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
#include "gmk/gmk_trigger.cpp"
#include "gmk/gmk_target_point.cpp"
#include "gmk/gmk_foot_print.cpp"
#include "gmk/gmk_anti_blade_area.cpp"
#include "gmk/gmk_tutorial.cpp"
#include "gmk/gmk_camera.cpp"
// clang-format on
