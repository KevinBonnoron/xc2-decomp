#include "gmk/gmk_manager.h"

#include "bdat.h"
#include "framework/memory/framework_memory.h"
#include "gmk/gmk_anti_blade_area.h"
#include "gmk/gmk_area_bgm.h"
#include "gmk/gmk_area_weather.h"
#include "gmk/gmk_battle_lock.h"
#include "gmk/gmk_blade.h"
#include "gmk/gmk_climbing.h"
#include "gmk/gmk_collection.h"
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
#include "gmk/gmk_se.h"
#include "gmk/gmk_set.h"
#include "gmk/gmk_squad.h"
#include "gmk/gmk_target_point.h"
#include "gmk/gmk_tbox.h"
#include "gmk/gmk_tutorial.h"
#include "gmk/gmk_warp.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace gmk {

static const char *const s_gmkFileNames[] = {
    "enemy",       "enemy",      "enemy",         "npc",         "npc",        "npc",        "mapObj",     "mapObj",   "mapObj",
    "tbox",        "event",      "enemy",         "fieldLock",   "effect",     "effect",     "se",         "se",       "se",
    "mob",         "mob",        "mob",           "landmark",    nullptr,      nullptr,      "formPc",     "formPc",   "formPcEv",
    "formPcEv",    "collection", "areaBgm",       "areaWeather", "salvage",    nullptr,      "mapGimmick", "precious", "grave",
    "kizunaTalk",  "jump",       "warp",          "squad",       "squad",      "door",       "elevator",   "elevator", "mapJump",
    "fieldVolume", "climbing",   "blade",         "dmgGimmick",  "dmgGimmick", "dmgGimmick", "dmgGimmick", nullptr,    "enemy",
    "footPrint",   "footPrint",  "antiBladeArea", "tutorial",
};

const char *GmkManager::getFilenameByType(int gmkSetId, GmkType type) const {
  const char *column = s_gmkFileNames[type];
  if (column == nullptr) {
    return nullptr;
  }
  u8 *bdat = gmkSetListBdat;
  if (Bdat::getMember(bdat, column) == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(Bdat::getValCheck(bdat, column, gmkSetId, 7));
}

const char *GmkManager::getSheetnameByType(int gmkSetId, GmkType type) const {
  mm::mtl::FixStr<256> column;
  column.format("%s_bdat", s_gmkFileNames[type]);
  u8 *bdat = gmkSetListBdat;
  if (Bdat::getMember(bdat, column.c_str()) == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(Bdat::getValCheck(bdat, column.c_str(), gmkSetId, 7));
}

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
    info.memory = memory;
    info.set = this;
    info.path = "gmk/";
    info.path += fileName;
    info.path += ".lvb";
    if (bdatName != nullptr) {
      info.bdatName = bdatName;
    }
    info.position = position;
    info.rotation = rotation;
    list->create(info);
  }
}

} // namespace gmk

// clang-format off
#include "gmk/gmk_base.cpp"
#include "gmk/gmk_gob_event_listener_impl.h" // IWYU pragma: keep
// clang-format on
