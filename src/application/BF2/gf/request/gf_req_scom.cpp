#include "gf/request/gf_req_scom.h"

#include <math.h>
#include <string.h>

#include "framework/lang_util.h"
#include "fw/fw_bdat_manager.h"
#include "fw/fw_debug.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_data_field.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_field_bgm.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/field/gf_field_manager.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/auto_talk/gf_auto_talk.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_camera.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_ride.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_game_unit.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_target.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/game/salvage/gf_salvage_voice.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/gf_info.h"
#include "gf/map/gf_map_manager.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/object/gf_menu_obj_popup.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/scom/gf_scom_enbook.h"
#include "gf/scom/gf_scom_fade.h"
#include "gf/scom/gf_scom_obj.h"
#include "gf/scom/gf_scom_script.h"
#include "gf/script/gf_script_manager.h"
#include "gf/util/gf_item_util.h"
#include "gf/util/gf_util.h"
#include "gmk/gmk_manager.h"
#include "ml/rand.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "ui/ui_manager.h"
#include "ui/ui_util.h"

namespace gf {

static const u32 unknown001 = 4; // Inferred role: object attribute bit cleared when destroying a game object; original name unknown.
static const u32 unknown002 = 4; // Inferred role: game speed layer set by the speed command; original name unknown.
static const u32 unknown003 = 1; // Inferred role: game speed layer set by the local speed command; original name unknown.

SCOM::SCOM(GF_SCOM_HANDLE *handle, SCOM_TYPE type, SCOM_EXEC exec, u16 unknown10) : m_GF_SCOM_HANDLE(handle), unknown10(unknown10), unknown14(exec), unknown18(type) {}

GF_OBJ_HANDLE *SCOM::getObjHandle() const { return unknown020; }

GfReqSmallCom::GfReqSmallCom() : unknownd868(0), unknownd870(false) { SCOM_PARTY_ADD::initialize(); }

GfReqSmallCom::~GfReqSmallCom() {}

GF_SCOM_HANDLE *GfReqSmallCom::allocate() {
  s64 handle = unknownd868++;
  if (handle == -1) {
    handle++;
    unknownd868++;
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(handle);
}

GF_SCOM_HANDLE *GfReqSmallCom::addRequest(SCOM *scom) {
  get()->unknown08.push_back(scom);
  return scom->m_GF_SCOM_HANDLE;
}

GF_SCOM_HANDLE *GfReqSmallCom::addRequestParallel(SCOM *scom) {
  GfReqSmallCom *smallCom = get();
  if (!smallCom->unknownd870) {
    smallCom->unknown4828.push_back(scom);
  } else {
    smallCom->unknown9048.push_back(scom);
  }
  return scom->m_GF_SCOM_HANDLE;
}

bool SCOM_ENBOOK_IN_BATTLE::exec(const fw::UpdateInfo &) {
  GfDataEnBook::setAttackFlag(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_IN_BATTLE::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4274
  SCOM_ENBOOK_IN_BATTLE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ENBOOK_IN_BATTLE(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_BOSS_TIME::exec(const fw::UpdateInfo &) {
  GfDataEnBook::setClearNamedTime(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_BOSS_TIME::create(GF_OBJ_HANDLE *handle, u32 time) {
  DataParamAcc acc(handle);
#line 4289
  SCOM_ENBOOK_BOSS_TIME *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ENBOOK_BOSS_TIME(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0, time);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_DEFEAT_ENEMY::exec(const fw::UpdateInfo &) {
  GfDataEnBook::incDefeatNum(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_DEFEAT_ENEMY::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4304
  SCOM_ENBOOK_DEFEAT_ENEMY *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEFEAT_ENEMY(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_DEAD_PLAYER::exec(const fw::UpdateInfo &) {
  GfDataEnBook::incDeadNum(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_DEAD_PLAYER::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4319
  SCOM_ENBOOK_DEAD_PLAYER *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEAD_PLAYER(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_MISSION_COMPLETE::exec(const fw::UpdateInfo &) {
  switch (GfGameMercenaries::getMissionFlag(unknown1c)) {
  case 2: {
    u32 team = GfDataMercenaries::getTeamIDByMissionID(unknown1c);
    GfGameMercenaries::setMissionCompleteForce(unknown1c);
    GfGameMercenaries::execMissionRewardAchievementBonusForBlade(unknown1c);
    GfGameMercenaries::execMissionAchievementForBlade(unknown1c);
    GfGameMercenaries::clearTeamMember(team);
    return false;
  }
  case 3:
    GfGameMercenaries::execMissionReward(unknown1c);
    break;
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_MISSION_COMPLETE::create(u32 mission) {
  switch (GfGameMercenaries::getMissionFlag(mission)) {
  case 2:
  case 3: {
#line 505
    SCOM_MISSION_COMPLETE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_MISSION_COMPLETE(GfReqSmallCom::get()->allocate(), mission);
    return GfReqSmallCom::addRequest(command);
  }
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_TRUST::exec(const fw::UpdateInfo &) {
  if (unknown20 == 0) {
    mm::mtl::FixedVector<u16, 422> blades;
    GfDataBlade::getListPartyAll(blades);
    for (const u16 *it = blades.begin(); it != blades.end(); ++it) {
      GfGameUtil::addTrustPoint(*it, unknown1c);
    }
  } else {
    GfGameUtil::addTrustPoint(unknown20, unknown1c);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_TRUST::create(u32 blade, u32 point) {
  if (point != 0) {
#line 535
    SCOM_ADD_TRUST *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_TRUST(GfReqSmallCom::get()->allocate(), blade, point);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_SET_TRUST_FOR_DEBUG::exec(const fw::UpdateInfo &) {
  if (unknown20 == 0) {
    mm::mtl::FixedVector<u16, 422> blades;
    GfDataBlade::getListParty(blades);
    for (const u16 *it = blades.begin(); it != blades.end(); ++it) {
      GfGameUtil::setTrustPointForDebug(*it, unknown1c);
    }
  } else {
    GfGameUtil::setTrustPointForDebug(unknown20, unknown1c);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_TRUST_FOR_DEBUG::create(u32 blade, u32 point) {
  if (point != 0) {
#line 562
    SCOM_SET_TRUST_FOR_DEBUG *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_SET_TRUST_FOR_DEBUG(GfReqSmallCom::get()->allocate(), blade, point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_TARGET_UI::exec(const fw::UpdateInfo &) {
  GfGameManager::setTargetUI(m_GF_OBJ_HANDLE);
  return true;
}

void SCOM_TARGET_UI::create(GF_OBJ_HANDLE *target) {
#line 1942
  SCOM_TARGET_UI *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_TARGET_UI(GfReqSmallCom::get()->allocate(), target);
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_REFRESH_COMPASS::SCOM_REFRESH_COMPASS(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown28(3) {}

GF_SCOM_HANDLE *SCOM_REFRESH_COMPASS::create() {
  if (get() == nullptr) {
#line 4841
    SCOM_REFRESH_COMPASS *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_REFRESH_COMPASS(GfReqSmallCom::get()->allocate());
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_REFRESH_COMPASS::exec(const fw::UpdateInfo &) {
  if (--unknown28 > 0) {
    return false;
  }
  GfQuestManager::requestRefreshQuestTaskState();
  return true;
}

SCOM_BATTLE_TASK_RESET::SCOM_BATTLE_TASK_RESET(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown28(3) {}

bool SCOM_BATTLE_TASK_RESET::exec(const fw::UpdateInfo &) {
  if (--unknown28 > 0) {
    return false;
  }
  GfQuestManager::resetBattleTaskForBattleEnd();
  return true;
}

GF_SCOM_HANDLE *SCOM_BATTLE_TASK_RESET::create() {
  if (get() == nullptr) {
#line 4865
    SCOM_BATTLE_TASK_RESET *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_BATTLE_TASK_RESET(GfReqSmallCom::get()->allocate());
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

SCOM_FSKILLMAX_FOR_DEBUG::SCOM_FSKILLMAX_FOR_DEBUG(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_74, SCOM_EXEC_UNKNOWN_0, 1) {
  GfDataBlade::getListParty(unknown20);
  GfDataBlade::getListReserver(unknown20);
}

bool SCOM_FSKILLMAX_FOR_DEBUG::exec(const fw::UpdateInfo &) {
  if (unknown20.empty()) {
    return true;
  }
  GfKizunaringBlade::completeAllAchievementForDebug(unknown20.back());
  unknown20.pop_back();
  return unknown20.empty();
}

void SCOM_FSKILLMAX_FOR_DEBUG::create() {
#line 4345
  SCOM_FSKILLMAX_FOR_DEBUG *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FSKILLMAX_FOR_DEBUG(GfReqSmallCom::get()->allocate());
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_SOLO_REX::SCOM_SOLO_REX(GF_SCOM_HANDLE *handle, bool isSolo) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(isSolo) {}

bool SCOM_SOLO_REX::exec(const fw::UpdateInfo &) {
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = GfDataBlade::getBladeID(i);
    if (blade == 0) {
      continue;
    }
    u32 creator = GfDataBlade::getCreator(blade);
    if (creator == 0 || creator == DRIVER_UNKNOWN_1) {
      continue;
    }
    if (!GfDataBlade::isDummyBlade(blade)) {
      GfDataBlade::setUnselect(blade, unknown1c);
    }
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_SOLO_REX::create(bool isSolo) {
#line 4901
  SCOM_SOLO_REX *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_SOLO_REX(GfReqSmallCom::get()->allocate(), isSolo);
  return GfReqSmallCom::addRequest(command);
}

SCOM_CURRENT_BLADE::SCOM_CURRENT_BLADE(GF_SCOM_HANDLE *handle, u32 blade) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(blade) {}

bool SCOM_CURRENT_BLADE::exec(const fw::UpdateInfo &) {
  int slot = GfDataBlade::getDriverSetID(unknown1c);
  u32 driver = GfDataBlade::getSetDriver(unknown1c);
  if (slot >= 0 && slot < static_cast<int>(SET_UNKNOWN_5) && driver != 0) {
    GfDataDriver::setEquipBlade(driver, true, slot);
  }
  if (unknown1c == BLADE_HOMURA) {
    GfDataBlade::setHikariCurrent(false);
  } else if (unknown1c == BLADE_HIKARI) {
    GfDataBlade::setHikariCurrent(true);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_CURRENT_BLADE::create(u32 blade) {
  SCOM_PARTY_ADD::setCurrentBlade(blade);
#line 4737
  SCOM_CURRENT_BLADE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_CURRENT_BLADE(GfReqSmallCom::get()->allocate(), blade);
  return GfReqSmallCom::addRequest(command);
}

// The game clears unknown28 before it calls getPartyId, so unknown20 is assigned in the body.
SCOM_REBUILD_PARTY_WEAPON::SCOM_REBUILD_PARTY_WEAPON(GF_SCOM_HANDLE *handle, u32 blade) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(blade), unknown28(0) {
  unknown20 = GfGameParty::getPartyId(OBJECT_TYPE_BLADE, blade);
  DataParamAcc acc(GfGameParty::getHandleDriver(unknown20));
  unknown24 = -1;
  int count = GfDataDriver::getMaxSetBladeNum(acc.getValidDriverId());
  for (int slot = 0; slot < count; ++slot) {
    if (acc.getBlade(slot, false) == blade) {
      unknown24 = slot;
      break;
    }
  }
}

bool SCOM_REBUILD_PARTY_WEAPON::exec(const fw::UpdateInfo &) {
  if (unknown28 == 0) {
    GfAppendHandles handles = *GfGameParty::getHandleWeapon(unknown20, unknown24);
    for (u32 index = 0; index < HANDLE_UNKNOWN_10; index++) {
      GfObjUtil::destroy(handles.getCurrentHandles()[index]);
    }
    unknown28 = 1;
    return false;
  }

  if (unknown28 == 1) {
    GfAppendHandles handles = *GfGameParty::getHandleWeapon(unknown20, unknown24);
    for (u32 index = 0; index < HANDLE_UNKNOWN_10; index++) {
      GF_OBJ_HANDLE *handle = handles.getCurrentHandles()[index];
      if (handle != unknown020 && GfObjUtil::isValid(handle)) {
        return false;
      }
    }
  }

  GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(unknown20);
  GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(unknown20, unknown24);
  DataParamAcc bladeAcc(blade);
  if (bladeAcc.getEquipWeapon(-1, false) != 0) {
    DataParamAcc driverAcc(GfGameParty::getHandleDriver(unknown20));
    GfInitParamWeapon param;
    param.unknown003(unknown20, unknown24, bladeAcc.getEquipWeapon(-1, false), driver, blade, GfGameParty::getHandleDriver(unknown20), driverAcc.getBladeSet(false) == unknown24);
    GfObjFactory::createDriverWeapon(param);
    GfMountManager::setMountType(driver, GFATTACH_UNKNOWN_0, OPTMNT_UNKNOWN_2);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_REBUILD_PARTY_WEAPON::create(u32 blade) {
#line 4819
  SCOM_REBUILD_PARTY_WEAPON *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_REBUILD_PARTY_WEAPON(GfReqSmallCom::get()->allocate(), blade);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ZONE::exec(const fw::UpdateInfo &) {
  if (!GfGameManager::isControlFree()) {
    return false;
  }
  u32 map = GfGameManager::getMapID();
  if (map == unknown1c && !GfDataMap::isMapCompleteFlag(map)) {
    GfDataMap::setMapCompleteFlag(unknown1c);
  }
  return true;
}

void SCOM_ZONE::create(u32 map) {
#line 4259
  SCOM_ZONE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ZONE(GfReqSmallCom::get()->allocate(), map);
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_LEVELUP_DEVELOP::exec(const fw::UpdateInfo &) {
  if (!GfGameManager::isControlFree()) {
    return false;
  }
  GfGameUtil::execDevelopLevelUp();
  return true;
}

void SCOM_LEVELUP_DEVELOP::create() {
#line 431
  SCOM_LEVELUP_DEVELOP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_LEVELUP_DEVELOP(GfReqSmallCom::get()->allocate());
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_OBJ_WARP_POS::exec(const fw::UpdateInfo &) {
  GfObjUtil::setWarpTransform(m_GF_OBJ_HANDLE, m_transform, unknown50);
  return true;
}

GF_SCOM_HANDLE *SCOM_OBJ_WARP_POS::create(GF_OBJ_HANDLE *handle, const mm::Vec3 &position, const mm::Vec3 &rotation, bool isFollow) {
  fw::Transform transform;
  transform.unknown00 = position;
  mm::unknown009(transform.unknown10, rotation);
#line 629
  SCOM_OBJ_WARP_POS *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(GfReqSmallCom::get()->allocate(), handle, transform, isFollow);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_OBJ_WARP_POS::create(const mm::Vec3 &position, const mm::Vec3 &rotation, bool isFollow) {
  fw::Transform transform;
  transform.unknown00 = position;
  mm::unknown009(transform.unknown10, rotation);
#line 637
  SCOM_OBJ_WARP_POS *command =
      new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(GfReqSmallCom::get()->allocate(), GfGameManager::getControlMover(), transform, isFollow);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_OBJ_WARP_POS::create(GF_OBJ_HANDLE *handle, const fw::Transform &transform, bool isFollow) {
#line 642
  SCOM_OBJ_WARP_POS *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(GfReqSmallCom::get()->allocate(), handle, transform, isFollow);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_OBJ_WARP_POS::create(const fw::Transform &transform, bool isFollow) {
#line 647
  SCOM_OBJ_WARP_POS *command =
      new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(GfReqSmallCom::get()->allocate(), GfGameManager::getControlMover(), transform, isFollow);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_GAME_OBJ::exec(const fw::UpdateInfo &) {
  GfGameObj::destroyGameObjWithAttribute(m_GF_OBJ_HANDLE, unknown28, unknown2c);
  return true;
}

void SCOM_DESTROY_GAME_OBJ::create(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute) {
  GfObjAcc acc(handle);
  acc.setFlag(OBJ_FLAG_UNKNOWN_17, true);
  acc.setAttribute(acc.getAttribute() & ~unknown001);
#line 692
  SCOM_DESTROY_GAME_OBJ *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_DESTROY_GAME_OBJ(GfReqSmallCom::get()->allocate(), handle, fadeTime, attribute);
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_OBJ_VFADE_OFF::SCOM_OBJ_VFADE_OFF(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_67, SCOM_EXEC_UNKNOWN_0, 1), m_GF_OBJ_HANDLE(target) {}

bool SCOM_OBJ_VFADE_OFF::exec(const fw::UpdateInfo &) {
  GfObjUtil::setVolumeFadeUserFlag(m_GF_OBJ_HANDLE, false);
  return true;
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE_OFF::create(GF_OBJ_HANDLE *handle) {
  if (handle != unknown020) {
#line 1305
    SCOM_OBJ_VFADE_OFF *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE_OFF(GfReqSmallCom::get()->allocate(), handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

SCOM_OBJ_VFADE::SCOM_OBJ_VFADE(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time, f32 ratio, VFPARTS parts, VFACC acc, VFEFF effect, bool isKeyFrame, bool isSingle)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_67, SCOM_EXEC_UNKNOWN_0, 1), m_objHandle(target), unknown28(time), unknown2c(0.0f), unknown30(ratio), unknown34(-1.0f), unknown38(parts), unknown3c(acc),
      unknown40(effect), unknown70(isSingle), unknown71(false) {
  if (isKeyFrame) {
    GfVolumeFade::setupKeyFrame(unknown48, effect);
    unknown28 = getKeyFrameSec();
  }
  DataParamAcc paramAcc(target);
  if (paramAcc.getObjType() == OBJECT_TYPE_BLADE && paramAcc.isValid() && paramAcc.getBdatId() == BLADE_KAGUTSUCHI) {
    unknown40 = VFEFF_UNKNOWN_16;
  } else if (paramAcc.getObjType() == OBJECT_TYPE_PC_WEAPON) {
    DataParamAcc bladeAcc(GfGameParty::getHandleBlade(GfGameParty::getPartyId(target), -1));
    if (bladeAcc.getObjType() == OBJECT_TYPE_BLADE && bladeAcc.isValid() && bladeAcc.getBdatId() == BLADE_KAGUTSUCHI) {
      unknown40 = VFEFF_UNKNOWN_16;
    }
  }
}

f32 SCOM_OBJ_VFADE::getKeyFrameSec() const {
  if (unknown48.size() < 2) {
    return 0.0f;
  }
  // back(), not begin()[size() - 1] or end() - 1: the copy inlined into the constructor (0x71005c5e6c) then addresses the key from
  // this (86 instructions, as in the game; 89 with begin() or end(), which keeps &unknown48 in a register across setupKeyFrame).
  return unknown48.back().unknown00;
}

void SCOM_OBJ_VFADE::applyPartsRatio(GfVolumeFade *fade, f32 ratio) {
  fade->setFadeRatio(unknown3c, unknown38, ratio);
  if (unknown70 && unknown38 != VFPARTS_UNKNOWN_FFFFFFFF) {
    for (s32 parts = 0; parts < 6; parts++) {
      if (unknown38 != parts) {
        fade->setFadeRatio(unknown3c, static_cast<VFPARTS>(parts), 0.0f);
      }
    }
  }
}

bool SCOM_OBJ_VFADE::updateFade(const fw::UpdateInfo &info) {
  if (GfObjUtil::isValid(m_objHandle)) {
    if (!GfObjUtil::isUpdate(m_objHandle)) {
      return false;
    }
    GfVolumeFade *fade = GfObjUtil::getVolumeFade(m_objHandle);
    if (fade != nullptr) {
      GfObjUtil::setVolumeFadeUserFlag(m_objHandle, true);
      unknown2c += info.unknown04;
      if (unknown2c > unknown28) {
        unknown2c = unknown28;
      }
      fade->setEffectType(unknown40);
      if (unknown48.size() != 0) {
        f32 ratio;
        bool isEnd = getRatioBySec(ratio, unknown48, unknown2c);
        applyPartsRatio(fade, ratio);
        return isEnd;
      }
      f32 current = unknown34;
      if (current < 0.0f) {
        current = fade->getFadeRatio(unknown3c, unknown38);
        unknown34 = current;
      }
      if (unknown28 > 0.000001f && fabsf(unknown30 - current) >= 0.000001f) {
        f32 rate = unknown2c / unknown28;
        applyPartsRatio(fade, unknown30 * rate + current * (1.0f - rate));
        if (unknown2c < unknown28) {
          return false;
        }
      } else {
        applyPartsRatio(fade, unknown30);
      }
    }
  }
  return true;
}

bool SCOM_OBJ_VFADE::getRatioBySec(f32 &ratio, const mm::mtl::FixedVector<VFKEYDATA, 4> &keys, f32 time) {
  ratio = 0.0f;
  if (keys.size() == 0) {
    return true;
  }
  // back(), not end() - 1 or begin()[size() - 1] (151 and 152 instructions, the game has 150): the game tests last.unknown00 before
  // size() == 1 (0x71005c626c fcmp, then ccmp), and the vector's own checked access keeps both tests in that order; its assertion
  // is provably true here and leaves no code.
  const VFKEYDATA &last = keys.back();
  if (last.unknown00 <= time || keys.size() == 1) {
    ratio = last.unknown04;
    return true;
  }
  // The game compares i with a bound computed once from the size read before the loop (0x71005c6258, sign-extended at 0x71005c6294
  // before the loop); `keys.size() - 1` in the condition costs one more instruction (151).
  int count = keys.size();
  for (int i = 0; i < count - 1; i++) {
    if (keys[i].unknown00 <= time && time < keys[i + 1].unknown00) {
      // The game indexes the three time keys (index assertions at 0x71005c6370, 0x71005c6398, 0x71005c63c0; loads at 0x71005c6394,
      // 0x71005c63bc, 0x71005c63e4) before the first ratio key (assertion 0x71005c63e8): the rate is evaluated before
      // `keys[i].unknown04`. Written as one expression, the ratio key is indexed first and the loads come in another order.
      f32 rate = (time - keys[i].unknown00) / (keys[i + 1].unknown00 - keys[i].unknown00);
      ratio = keys[i].unknown04 + rate * (keys[i + 1].unknown04 - keys[i].unknown04);
      return false;
    }
  }
  ratio = keys[0].unknown04;
  return false;
}

bool SCOM_OBJ_VFADE::exec(const fw::UpdateInfo &info) {
  if (!updateFade(info)) {
    return false;
  }
  SCOM_OBJ_VFADE_OFF::create(m_objHandle);
  return true;
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE::create(GF_OBJ_HANDLE *handle, f32 time, f32 ratio, VFPARTS parts, VFACC acc, VFEFF effect) {
#line 1508
  SCOM_OBJ_VFADE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE(GfReqSmallCom::get()->allocate(), handle, time, ratio, parts, acc, effect, false, false);
  return GfReqSmallCom::addRequestParallel(command);
}

SCOM_OBJ_VFADE *SCOM_OBJ_VFADE::createKeyFrame(GF_OBJ_HANDLE *handle, VFPARTS parts, VFACC acc, VFEFF effect) {
  if (GfObjUtil::getVolumeFade(handle) == nullptr) {
    return nullptr;
  }
#line 1528
  SCOM_OBJ_VFADE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE(GfReqSmallCom::get()->allocate(), handle, 1.0f, 1.0f, parts, acc, effect, true, false);
  GfReqSmallCom::addRequestParallel(command);
  return command;
}

// createParts, createPartsWithSingle, createAnim and createAnimParts each repeat the attribute lookup (ruling 8: the game's code repeats the same
// statements in each function). A shared static helper in place of the written-out lookup does not match: the four functions come out 4
// instructions longer (78, 79, 82 and 82 against the game's 74, 75, 78 and 78; createPartsWithSingle 0x71005c6854, 0x138 bytes), first
// difference `mov w22, wzr` where the game has `mov w22, w0` (0x71005c68a0).
GF_SCOM_HANDLE *SCOM_OBJ_VFADE::createParts(GF_OBJ_HANDLE *handle, f32 time, f32 ratio, VFPARTS parts, VFACC acc) {
  DataParamAcc paramAcc(handle);
  VFEFF effect = getAttribute2VfEff(paramAcc.getAttribute(-1, false), handle);
  if (effect == VFEFF_UNKNOWN_0) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  return create(handle, time, ratio, parts, acc, effect);
}

VFEFF SCOM_OBJ_VFADE::getAttribute2VfEff(u32 attribute, GF_OBJ_HANDLE *handle) {
  // One return at the end, as the game's cases all end on one ret: a return per case gives a range test and 21 instructions (the game has 25).
  VFEFF effect = VFEFF_UNKNOWN_0;
  switch (attribute) {
  case 1: {
    GfObjAcc acc(handle);
    effect = acc.getBdatId() == BLADE_KAGUTSUCHI ? VFEFF_UNKNOWN_16 : VFEFF_UNKNOWN_1;
    break;
  }
  case 2:
    effect = VFEFF_UNKNOWN_2;
    break;
  case 3:
    effect = VFEFF_UNKNOWN_3;
    break;
  case 4:
    effect = VFEFF_UNKNOWN_4;
    break;
  case 5:
    effect = VFEFF_UNKNOWN_5;
    break;
  case 6:
    effect = VFEFF_UNKNOWN_6;
    break;
  case 7:
    effect = VFEFF_UNKNOWN_7;
    break;
  case 8:
    effect = VFEFF_UNKNOWN_8;
    break;
  }
  return effect;
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE::createPartsWithSingle(GF_OBJ_HANDLE *handle, f32 time, f32 ratio, VFPARTS parts, VFACC acc) {
  DataParamAcc paramAcc(handle);
  VFEFF effect = getAttribute2VfEff(paramAcc.getAttribute(-1, false), handle);
  if (effect == VFEFF_UNKNOWN_0) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1563
  SCOM_OBJ_VFADE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE(GfReqSmallCom::get()->allocate(), handle, time, ratio, parts, acc, effect, false, true);
  return GfReqSmallCom::addRequestParallel(command);
}

f32 SCOM_OBJ_VFADE::createDead(GF_OBJ_HANDLE *handle, u32 attribute) {
  f32 keyFrameSec = 0.0f;
  VFEFF effect = getAttribute2VfEff(attribute, handle);
  if (effect == VFEFF_UNKNOWN_0) {
    return keyFrameSec;
  }
  SCOM_OBJ_VFADE *fade = createKeyFrame(handle, VFPARTS_UNKNOWN_FFFFFFFF, VFACC_UNKNOWN_0, effect);
  if (fade != nullptr) {
    fade->unknown71 = true;
    keyFrameSec = fade->getKeyFrameSec();
  }
  return keyFrameSec;
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE::createBattle(GF_OBJ_HANDLE *handle, f32 ratio, u32 attribute) {
  if (handle == unknown020) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  VFEFF effect = getAttribute2VfEff(attribute, handle);
  if (effect == VFEFF_UNKNOWN_0) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  return create(handle, 0.0f, ratio, VFPARTS_UNKNOWN_FFFFFFFF, VFACC_UNKNOWN_4, effect);
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE::createBattleParts(GF_OBJ_HANDLE *handle, f32 time, f32 ratio, u32, VFPARTS parts) {
  if (handle == unknown020) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  GfObjAcc acc(handle);
  return createPartsWithSingle(handle, time, ratio, acc.getType() == OBJECT_TYPE_BLADE ? VFPARTS_UNKNOWN_0 : parts, VFACC_UNKNOWN_4);
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE::createAnim(GF_OBJ_HANDLE *handle, f32 time, f32 ratio) {
  DataParamAcc paramAcc(handle);
  VFEFF effect = getAttribute2VfEff(paramAcc.getAttribute(-1, false), handle);
  if (effect == VFEFF_UNKNOWN_0) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  return create(handle, time, ratio, VFPARTS_UNKNOWN_FFFFFFFF, VFACC_UNKNOWN_1, effect);
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE::createAnimParts(GF_OBJ_HANDLE *handle, f32 time, f32 ratio, VFPARTS parts) {
  DataParamAcc paramAcc(handle);
  VFEFF effect = getAttribute2VfEff(paramAcc.getAttribute(-1, false), handle);
  if (effect == VFEFF_UNKNOWN_0) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  return create(handle, time, ratio, parts, VFACC_UNKNOWN_1, effect);
}

bool SCOM_ADD_WP::exec(const fw::UpdateInfo &) {
  if (unknown30 == unknown004_3) {
    GfGameUtil::addWpForObject(unknown20_int, unknown2c, unknown28);
    return true;
  }
  GfObjAcc acc(unknown20);
  u32 driverId = acc.getType() == OBJECT_TYPE_PC ? acc.getDriverId() : 0;
  switch (unknown30) {
  case unknown004_0:
    GfGameUtil::addWp(driverId, unknown2c, unknown28);
    break;
  case unknown004_1:
    GfGameUtil::addWpForObject(driverId, unknown2c, unknown28);
    break;
  case unknown004_2:
    GfGameUtil::addWpForReserve(unknown28);
    break;
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_WP::create(int weaponPoint, u32 weaponType) {
  if (weaponPoint != 0) {
#line 306
    SCOM_ADD_WP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_WP(GfReqSmallCom::get()->allocate(), unknown020, weaponPoint, weaponType, unknown004_0);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_WP::createForReserve(int weaponPoint) {
  if (weaponPoint != 0) {
#line 313
    SCOM_ADD_WP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_WP(GfReqSmallCom::get()->allocate(), unknown020, weaponPoint, 0, unknown004_2);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_WP::createForObject(GF_OBJ_HANDLE *handle, int weaponPoint, u32 weaponType) {
  if (weaponPoint != 0) {
#line 320
    SCOM_ADD_WP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_WP(GfReqSmallCom::get()->allocate(), handle, weaponPoint, weaponType, unknown004_1);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_WP::createForBdatid(int driver, int weaponPoint, u32 weaponType) {
  if (weaponPoint != 0) {
#line 327
    SCOM_ADD_WP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_WP(GfReqSmallCom::get()->allocate(), driver, weaponPoint, weaponType, unknown004_3);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_SP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (m_GF_OBJ_HANDLE == unknown020) {
      driverId = 0;
    } else {
      GfObjAcc acc(m_GF_OBJ_HANDLE);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::addSP(driverId, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_SP::create(GF_OBJ_HANDLE *handle, int skillPoint) {
  if (skillPoint != 0) {
#line 348
    SCOM_ADD_SP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_SP(GfReqSmallCom::get()->allocate(), skillPoint, 0, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_SP::create(u32 driver, int skillPoint) {
  if (skillPoint != 0) {
#line 353
    SCOM_ADD_SP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_SP(GfReqSmallCom::get()->allocate(), skillPoint, driver, unknown020);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_IDEA::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (m_GF_OBJ_HANDLE == unknown020) {
      driverId = 0;
    } else {
      GfObjAcc acc(m_GF_OBJ_HANDLE);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::addIdeaPoint(driverId, unknown24, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_IDEA::create(GF_OBJ_HANDLE *handle, u32 idea, int point) {
  if (point != 0) {
#line 375
    SCOM_ADD_IDEA *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_IDEA(GfReqSmallCom::get()->allocate(), point, 0, idea, handle);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_IDEA::create(u32 driver, u32 idea, int point) {
  if (point != 0) {
#line 380
    SCOM_ADD_IDEA *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_IDEA(GfReqSmallCom::get()->allocate(), point, driver, idea, unknown020);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_EXEC_DRIVER_ARTS_LVUP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (m_GF_OBJ_HANDLE == unknown020) {
      driverId = 0;
    } else {
      GfObjAcc acc(m_GF_OBJ_HANDLE);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::execDriverArtsLevelUp(driverId, unknown24, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_DRIVER_ARTS_LVUP::create(u32 level, u32 arts, GF_OBJ_HANDLE *handle) {
  if (level != 0) {
#line 265
    SCOM_EXEC_DRIVER_ARTS_LVUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_EXEC_DRIVER_ARTS_LVUP(GfReqSmallCom::get()->allocate(), level, 0, arts, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_EXEC_DRIVER_ARTS_LVUP::create(u32 level, u32 arts, u32 driver) {
  if (level != 0) {
#line 270
    SCOM_EXEC_DRIVER_ARTS_LVUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_EXEC_DRIVER_ARTS_LVUP(GfReqSmallCom::get()->allocate(), level, driver, arts, unknown020);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_EXEC_LVUP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (m_GF_OBJ_HANDLE == unknown020) {
      driverId = 0;
    } else {
      GfObjAcc acc(m_GF_OBJ_HANDLE);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::execLevelUp(driverId, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_LVUP::create(u32 level, GF_OBJ_HANDLE *handle) {
  if (level != 0) {
#line 238
    SCOM_EXEC_LVUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_EXEC_LVUP(GfReqSmallCom::get()->allocate(), level, 0, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_EXEC_LVUP::create(u32 level, u32 driver) {
  if (level != 0) {
#line 243
    SCOM_EXEC_LVUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_EXEC_LVUP(GfReqSmallCom::get()->allocate(), level, driver, unknown020);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

SCOM_OBJ_ALPHA::SCOM_OBJ_ALPHA(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time, f32 alpha)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_40, SCOM_EXEC_UNKNOWN_0, 1), m_GF_OBJ_HANDLE(target), unknown28(time), unknown2c(0.0f), unknown30(alpha), unknown34(-1.0f) {}

bool SCOM_OBJ_ALPHA::exec(const fw::UpdateInfo &info) {
  GfObjAcc acc(m_GF_OBJ_HANDLE);
  if (!acc.isValid()) {
    return true;
  }
  if (unknown34 < 0.0f) {
    unknown34 = acc.getAlphaNormal();
  }
  f32 time = unknown28;
  f32 alpha = unknown30;
  f32 startAlpha = unknown34;
  if (time > 0.000001f && fabsf(alpha - startAlpha) >= 0.000001f) {
    f32 elapsed = info.unknown04 + unknown2c;
    if (elapsed > time) {
      elapsed = time;
    }
    unknown2c = elapsed;
    acc.setAlphaNormal(alpha * (elapsed / time) + startAlpha * (1.0f - elapsed / time));
    if (unknown2c < unknown28) {
      return false;
    }
  } else {
    acc.setAlphaNormal(alpha);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_OBJ_ALPHA::create(GF_OBJ_HANDLE *handle, f32 time, f32 alpha) {
  if (handle != unknown020) {
#line 1268
    SCOM_OBJ_ALPHA *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_ALPHA(GfReqSmallCom::get()->allocate(), handle, time, alpha);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_OBJ_ALPHA::createWeapon(GF_OBJ_HANDLE *handle, f32 time, f32 alpha) {
  if (handle != unknown020) {
    GfWeapon *weapon = GfMountManager::getAppendHandles(handle, GFATTACH_UNKNOWN_0);
    if (weapon != nullptr) {
      for (u32 i = 0; i < 10; i++) {
        GF_OBJ_HANDLE *target = weapon->getCurrentHandles()[i];
        if (target != unknown020) {
#line 1282
          SCOM_OBJ_ALPHA *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_OBJ_ALPHA(GfReqSmallCom::get()->allocate(), target, time, alpha);
          GfReqSmallCom::addRequestParallel(command);
        }
      }
    }
  }
}

bool SCOM_ADD_EXP::exec(const fw::UpdateInfo &) {
  u32 driver = unknown20;
  if (driver == 0) {
    if (m_GF_OBJ_HANDLE == unknown020) {
      driver = 0;
    } else {
      GfObjAcc acc(m_GF_OBJ_HANDLE);
      driver = acc.getDriverId();
    }
  }
  if (!unknown30) {
    GfGameUtil::addExpBattle(driver, unknown1c);
  } else {
    GfGameUtil::addExpInn(unknown1c);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_EXP::createBattleExp(u32 exp, GF_OBJ_HANDLE *handle) {
  if (exp != 0) {
#line 204
    SCOM_ADD_EXP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_EXP(GfReqSmallCom::get()->allocate(), exp, 0, handle, false);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_EXP::createBattleExp(u32 exp, u32 driver) {
  if (exp != 0) {
#line 209
    SCOM_ADD_EXP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_EXP(GfReqSmallCom::get()->allocate(), exp, driver, unknown020, false);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_EXP::createInnExp(u32 exp) {
  if (exp != 0) {
#line 214
    SCOM_ADD_EXP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_EXP(GfReqSmallCom::get()->allocate(), exp, 0, unknown020, true);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

SCOM_POPUP::SCOM_POPUP(GF_SCOM_HANDLE *handle, GfMenuObjPopup::OpenParam &param) : SCOM(handle, SCOM_TYPE_UNKNOWN_75, SCOM_EXEC_UNKNOWN_0, 1), m_openParam(param) {}

bool SCOM_POPUP::exec(const fw::UpdateInfo &) {
  if (m_openParam.unknown00 == GfMenuObjPopup::unknown005_7 && GfGameManager::isBusyBladeCreateEvent()) {
    return false;
  }
  GfMenuObjPopup::open(m_openParam);
  return true;
}

GF_SCOM_HANDLE *SCOM_POPUP::createQuest(QuestID quest) {
  if (!GfGameManager::isStartGame()) {
    if (QuestListAcc::get()->getListVisible(quest) != 0) {
      GfMenuObjPopup::OpenParam param = {};
      param.unknown00 = GfMenuObjPopup::unknown005_9;
      param.unknown04 = quest.unknown00;
#line 4407
      SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
      return GfReqSmallCom::addRequestParallel(command);
    }
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_POPUP::createMercenaryReturn(u32 map, u32 teamID) {
  if (GfGameManager::isStartGame()) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_8, map, teamID, GfDataMercenaries::getTeamLeader(teamID)};
#line 4420
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createMercenaryAdd(u32 mission) {
  if (mission != 0 && !GfGameManager::isStartGame()) {
    GfMenuObjPopup::OpenParam param = {};
    param.unknown00 = GfMenuObjPopup::unknown005_7;
    param.unknown04 = GfDataMercenaries::getMissionMapID(mission);
#line 4433
    SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_POPUP::createDevelop(u32 location, u32 level) {
  if (GfGameManager::isStartGame()) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_6, location, level, 0};
#line 4445
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createAffinity(u32 blade, u32 driver, u32 trustRank) {
  if (GfGameManager::isStartGame()) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_5, blade, driver, trustRank};
#line 4458
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createAchievement(u32 blade, u32 achievement, u32 level) {
  GfGameManager::isStartGame();
  if (GfMenuObjUtil::getMenuCondition(15) && !GfGameUtil::setupSaveAchievementPopup(blade, achievement, level)) {
    GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_4, blade, achievement, level};
#line 4476
    SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_POPUP::createIdea(u32 driver, u32 idea, u32 level) {
  if (GfGameManager::isStartGame()) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_3, driver, idea, level};
#line 4489
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createPouch(u32 driver, u32 item, u32 unknown3) {
  bool isStart = GfGameManager::isStartGame();
  if (driver != 0 && !isStart) {
    GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_2, driver, item, unknown3};
#line 4503
    SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_POPUP::createArts(u32 driver, u32 arts) {
  if (GfGameManager::isStartGame()) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_1, driver, GfBdatBtl::get()->getArtsDrWpnType(arts), arts};
#line 4516
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createCrystalOK(u32 item) {
  if (GfGameManager::isStartGame()) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_10, item, 0, 0};
#line 4529
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

SCOM_BC_PARTICLE::SCOM_BC_PARTICLE(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_77, SCOM_EXEC_UNKNOWN_0, 1), m_GF_OBJ_HANDLE(target), unknown28(0), unknown30(time), unknown34(time) {
  DataParamAcc acc(target);
  unknown2c = acc.getAttribute(-1, false);
  if (acc.getObjType() == OBJECT_TYPE_BLADE && acc.isValid() && acc.getBdatId() == 0x3f1) {
    unknown2c = 0x11;
  }
}

bool SCOM_BC_PARTICLE::exec(const fw::UpdateInfo &info) {
  GfObjAcc acc(m_GF_OBJ_HANDLE);
  if (acc.getObj() != nullptr) {
    u32 attribute = unknown2c;
    switch (unknown28) {
    case 0:
      unknown28 = 1;
      GfObjUtil::setDeadParticle(m_GF_OBJ_HANDLE, true, attribute, acc.getAlpha());
      return false;
    case 1:
      if (unknown30 > 0.0f) {
        f32 remain = unknown30 - info.unknown04;
        if (remain <= 0.0f) {
          remain = 0.0f;
        }
        unknown30 = remain;
        f32 ratio = remain / unknown34;
        GfObjUtil::setDeadParticle(m_GF_OBJ_HANDLE, ratio > 0.0f, attribute, ratio);
        return unknown30 <= 0.0f;
      }
      break;
    }
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_BC_PARTICLE::create(GF_OBJ_HANDLE *handle, f32 time) {
  if (time < 0.000001f) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 4706
  SCOM_BC_PARTICLE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_BC_PARTICLE(GfReqSmallCom::get()->allocate(), handle, time);
  return GfReqSmallCom::addRequestParallel(command);
}

SCOM_DEAD_PARTICLE::SCOM_DEAD_PARTICLE(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, u32 attribute, f32 time)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_77, SCOM_EXEC_UNKNOWN_0, 1), m_GF_OBJ_HANDLE(target), unknown28(0), unknown2c(attribute), unknown30(time), unknown34(time) {}

bool SCOM_DEAD_PARTICLE::exec(const fw::UpdateInfo &info) {
  GfObjAcc acc(m_GF_OBJ_HANDLE);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return true;
  }
  GfComAsm *comAsm = obj->getComponent<GfComAsm>();
  switch (unknown28) {
  case 0:
    if (comAsm != nullptr && !comAsm->isEnd(ANIM_LAYER_UNKNOWN_0) && !comAsm->isLoop(ANIM_LAYER_UNKNOWN_0)) {
      return false;
    }
    unknown28 = 1;
    GfObjUtil::setDeadParticle(m_GF_OBJ_HANDLE, true, unknown2c, acc.getAlpha());
    GfObjUtil::setDeadParticle(GfMountManager::getHandle(m_GF_OBJ_HANDLE, GFATTACH_UNKNOWN_0, OPTMNT_UNKNOWN_3), true, unknown2c, 1.0f);
    return false;
  case 1:
    if (unknown30 > 0.0f) {
      f32 remain = unknown30 - info.unknown04;
      if (remain <= 0.0f) {
        remain = 0.0f;
      }
      unknown30 = remain;
      f32 ratio = remain / unknown34;
      GF_OBJ_HANDLE *blade = GfMountManager::getHandle(m_GF_OBJ_HANDLE, GFATTACH_UNKNOWN_0, OPTMNT_UNKNOWN_3);
      GfObjUtil::setDeadParticle(m_GF_OBJ_HANDLE, ratio > 0.0f, unknown2c, ratio);
      GfObjUtil::setDeadParticle(blade, ratio > 0.0f, unknown2c, ratio);
    }
    DataParamAcc param(m_GF_OBJ_HANDLE);
    if (param.getHp() != 0) {
      GF_OBJ_HANDLE *blade = GfMountManager::getHandle(m_GF_OBJ_HANDLE, GFATTACH_UNKNOWN_0, OPTMNT_UNKNOWN_3);
      GfObjUtil::setDeadParticle(m_GF_OBJ_HANDLE, false, unknown2c, acc.getAlpha());
      GfObjUtil::setDeadParticle(blade, false, unknown2c, acc.getAlpha());
      return true;
    }
    return false;
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_DEAD_PARTICLE::create(GF_OBJ_HANDLE *handle, u32 attribute, f32 time) {
  if (time < 0.000001f) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 4645
  SCOM_DEAD_PARTICLE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_DEAD_PARTICLE(GfReqSmallCom::get()->allocate(), handle, attribute, time);
  return GfReqSmallCom::addRequestParallel(command);
}

mm::mtl::FixedQueue<SCOM_PARTY_ADD::unknown002, 16> SCOM_PARTY_ADD::s_info;

bool SCOM_PARTY_ADD::exec(const fw::UpdateInfo &) {
  RQ_SETUP_PARTY info;
  GfGameParty::getPartyPosition(info.m_partyPosInfo);
  mm::mtl::FixedVector<u32, PARTY_UNKNOWN_3> drivers;
  bool isChange = false;
  bool isBladeRemove = false;
  for (mm::mtl::FixedQueue<unknown002, 16>::iterator it = s_info.begin(); it != s_info.end(); ++it) {
    unknown002 &entry = *it;
    switch (entry.unknown10) {
    case unknown001_3:
      isChange |= GfDataDriver::setActivateParty(entry.unknown04, entry.unknown08 >= 0 ? entry.unknown08 : PARTY_UNKNOWN_4294967295);
      break;
    case unknown001_4:
      if (entry.unknown0c) {
        isChange |= GfDataDriver::setActivateReserver(entry.unknown04, PARTY_UNKNOWN_4294967295);
      } else {
        isChange |= GfDataDriver::setActivateUnuse(entry.unknown04);
      }
      break;
    }
  }
  for (mm::mtl::FixedQueue<unknown002, 16>::iterator it = s_info.begin(); it != s_info.end(); ++it) {
    unknown002 &entry = *it;
    switch (entry.unknown10) {
    case unknown001_1: {
      if (entry.unknown00 == BLADE_UNKNOWN_1050 && !GfDataBlade::isAttachedParty(BLADE_UNKNOWN_1050)) {
        GfDataBlade::setCreator(entry.unknown00, GfDataBlade::getCreator(BLADE_UNKNOWN_1022));
      }
      u32 slotMax = GfMenuObjUtil::getBladeSlotMax();
      if (slotMax == 3) {
        slotMax = 0;
      }
      if (GfDataBlade::setActivateDriver(entry.unknown00, entry.unknown08, entry.unknown04, slotMax)) {
        if (mm::mtl::find(drivers.begin(), drivers.end(), entry.unknown04) == drivers.end()) {
          drivers.push_back(entry.unknown04);
        }
        if (entry.unknown0e) {
          DataParamAcc acc(OBJECT_TYPE_PC, entry.unknown04, GIMMICK_TYPE_UNKNOWN_0);
          int bladeSet = entry.unknown08;
          if (bladeSet < 0) {
            bladeSet = GfDataDriver::getSetIdByBlade(entry.unknown04, entry.unknown00);
          }
          acc.setBladeSet(bladeSet);
        }
        isChange = true;
      }
      break;
    }
    case unknown001_2: {
      bool isExist = GfDataParty::isExistBlade(entry.unknown00);
      u32 driver = GfDataBlade::getSetDriver(entry.unknown00);
      u32 blade = GfDataDriver::getBlade(driver, -1);
      if (entry.unknown0c) {
        GfGameUtil::execActivateReserverForBlade(entry.unknown00);
      } else {
        GfGameUtil::execActivateUnuseForBlade(entry.unknown00, entry.unknown0d);
      }
      isChange |= isExist;
      if (driver == DRIVER_UNKNOWN_1) {
        GfGameUtil::execEquipMercenariesBlade(DRIVER_UNKNOWN_1, GfDataBlade::getStartCommonBlade());
      }
      if (blade != GfDataDriver::getBlade(driver, -1)) {
        if (mm::mtl::find(drivers.begin(), drivers.end(), driver) == drivers.end()) {
          drivers.push_back(driver);
        }
      }
      isBladeRemove = true;
      break;
    }
    }
  }
  if (isChange || GfGameParty::isExistMismatchScenarioMask(PARTY_UNKNOWN_4294967295)) {
    GfGameParty::getCurrentPartyInfo(info);
    for (u32 i = 0; i < drivers.size(); i++) {
      for (u32 partyId = 0; partyId < PARTY_UNKNOWN_3; partyId++) {
        if (info.unknown00[partyId].unknown00 == drivers[i]) {
          info.unknown00[partyId].unknown12 = true;
        }
      }
    }
    for (u32 partyId = 0; partyId < PARTY_UNKNOWN_3; partyId++) {
      if (GfGameParty::isExistMismatchScenarioMask(partyId)) {
        info.unknown00[partyId].unknown12 = true;
      }
    }
    GfReqCommand::reqChangeParty(info);
  } else if (isBladeRemove) {
    GfEvent::callPartyChange();
  }
  s_info.clear();
  return true;
}

void SCOM_PARTY_ADD::addBlade(u32 blade, u32 driver, int slot) {
  if (blade == 0) {
    return;
  }
  unknown002 info = {GfDataBlade::getActBlade2CommonBlade(blade), driver, slot, true, false, false, unknown001_1};
  s_info.push(info);
  create();
}

GF_SCOM_HANDLE *SCOM_PARTY_ADD::create() {
  if (get() == nullptr) {
#line 2479
    SCOM_PARTY_ADD *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_PARTY_ADD(GfReqSmallCom::get()->allocate());
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_PARTY_ADD::removeBlade(u32 blade, bool isForce) {
  if (blade == 0) {
    return;
  }
  unknown002 info = {GfDataBlade::getActBlade2CommonBlade(blade), 0, -1, isForce, false, false, unknown001_2};
  s_info.push_front(info);
  create();
}

void SCOM_PARTY_ADD::removeBlade(u32 driver, int slot, bool isForce) {
  DataParamAcc acc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
  if (acc.isValid()) {
    u32 blade = acc.getBlade(slot, false);
    if (blade != 0) {
      removeBlade(blade, isForce);
    }
  }
}

void SCOM_PARTY_ADD::releaseBlade(u32 blade) {
  if (blade == 0) {
    return;
  }
  unknown002 info = {GfDataBlade::getActBlade2CommonBlade(blade), 0, -1, false, true, false, unknown001_2};
  s_info.push(info);
  create();
}

void SCOM_PARTY_ADD::addDriver(u32 driver, u32 partyId) {
  unknown002 info = {0, driver, static_cast<int>(partyId), true, false, false, unknown001_3};
  s_info.push(info);
  if (driver == DRIVER_UNKNOWN_2) {
    removeBlade(BLADE_UNKNOWN_1011, false);
  }
  create();
}

void SCOM_PARTY_ADD::removeDriver(u32 driver, bool isForce) {
  unknown002 info = {0, driver, -1, isForce, false, false, unknown001_4};
  s_info.push(info);
  create();
}

void SCOM_PARTY_ADD::setCurrentBlade(u32 blade) {
  for (mm::mtl::FixedQueue<unknown002, 16>::iterator it = s_info.begin(); it != s_info.end(); ++it) {
    unknown002 &info = *it;
    if (info.unknown10 == unknown001_1 && info.unknown00 == blade) {
      info.unknown0e = true;
      return;
    }
  }
  SCOM_EXEC_CURRENT_BLADE::create(blade);
}

void SCOM_PARTY_ADD::initialize() { s_info.clear(); }

SCOM_EXEC_CURRENT_BLADE::SCOM_EXEC_CURRENT_BLADE(GF_SCOM_HANDLE *handle, u32 blade) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(blade) {}

bool SCOM_EXEC_CURRENT_BLADE::exec(const fw::UpdateInfo &) {
  u32 driver = GfDataBlade::getSetDriver(unknown1c);
  if (driver != 0) {
    int bladeSet = GfDataDriver::getSetIdByBlade(driver, unknown1c);
    if (bladeSet >= 0) {
      GF_OBJ_HANDLE *handle = GfGameParty::getHandleDriverByBdatID(driver);
      if (!GfObjUtil::isValid(handle)) {
        DataParamAcc paramAcc(OBJECT_TYPE_PC, DRIVER_UNKNOWN_1, GIMMICK_TYPE_UNKNOWN_0);
        paramAcc.setBladeSet(bladeSet);
      } else {
        GfGameUtil::setBladeSelect(handle, bladeSet);
        RQ_SETUP_PARTY info;
        GfGameParty::getCurrentPartyInfo(info);
        GfReqCommand::reqChangeParty(info);
      }
    }
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_CURRENT_BLADE::create(u32 blade) {
#line 4942
  SCOM_EXEC_CURRENT_BLADE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_EXEC_CURRENT_BLADE(GfReqSmallCom::get()->allocate(), blade);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_PARTY_LEADER::exec(const fw::UpdateInfo &) {
  if (unknown1c == OBJECT_TYPE_BLADE) {
    for (u32 partyId = 0; partyId < PARTY_UNKNOWN_3; partyId++) {
      DataParamAcc acc(GfGameParty::getHandleDriver(partyId));
      if (acc.isValid()) {
        int setBladeNum = GfDataDriver::getMaxSetBladeNum(acc.getValidDriverId());
        for (int slot = 0; slot < setBladeNum; slot++) {
          if (acc.getBlade(slot, false) == unknown20 && slot != acc.getBladeSet(false)) {
            GfPlayFactory::createResetBladeForBladeSwitch(partyId, slot);
            break;
          }
        }
      }
    }
  }
  RQ_SETUP_PARTY info;
  GfGameParty::getCurrentPartyInfo(info);
  info.unknownc8 = unknown1c;
  info.unknowncc = unknown20;
  u32 partyId = GfGameParty::getPartyId(unknown1c, unknown20);
  if (partyId != 0) {
    RQ_SETUP_PARTY::Member member = info.unknown00[0];
    info.unknown00[0] = info.unknown00[partyId];
    info.unknown00[partyId] = member;
  }
  GfReqCommand::reqChangeParty(info);
  return true;
}

GF_SCOM_HANDLE *SCOM_PARTY_LEADER::create(u32 objectType, u32 leader) {
#line 3388
  SCOM_PARTY_LEADER *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_PARTY_LEADER(GfReqSmallCom::get()->allocate(), objectType, leader);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_SET_BLADE::exec(const fw::UpdateInfo &) {
  RQ_SETUP_PARTY info;
  GfGameParty::getCurrentPartyInfo(info);
  u32 partyId = GfDataParty::getDriverPartyID(m_RQ_SETUP_BLADE.unknown00);
  RQ_SETUP_PARTY::Member &member = info.unknown00[partyId];
  member.unknown12 = true;
  // The game copies the 10 bytes in one go (0x71005c9d70 to 0x71005c9d84 load and store one 2 byte and one 8 byte word).
  memcpy(member.unknown08.begin(), m_RQ_SETUP_BLADE.unknown04, sizeof(m_RQ_SETUP_BLADE.unknown04));
  member.unknown04 = -1;
  u32 current = m_RQ_SETUP_BLADE.unknown02;
  u32 blade = GfDataDriver::getBlade(member.unknown00, -1);
  for (int slot = 0; slot < 5; slot++) {
    if (m_RQ_SETUP_BLADE.unknown04[slot] == m_RQ_SETUP_BLADE.unknown02) {
      member.unknown04 = slot;
      break;
    }
  }
  if (member.unknown04 < 0) {
    for (int slot = 0; slot < 5; slot++) {
      if (m_RQ_SETUP_BLADE.unknown04[slot] == blade) {
        member.unknown04 = slot;
        current = blade;
        break;
      }
    }
  }
  if (member.unknown04 < 0) {
    for (int slot = 0; slot < 5; slot++) {
      if (member.unknown08[slot] != 0) {
        member.unknown04 = slot;
        current = member.unknown08[slot];
        break;
      }
    }
  }
  if (partyId == 0 && info.unknownc8 == OBJECT_TYPE_BLADE) {
    bool isExist = false;
    for (u32 slot = 0; slot < 5; slot++) {
      if (member.unknown08[slot] == info.unknowncc) {
        isExist = true;
      }
    }
    if (!isExist || current != info.unknowncc) {
      info.unknownc8 = OBJECT_TYPE_PC;
      info.unknowncc = member.unknown00;
    }
  }
  GfReqCommand::reqChangeParty(info);
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_BLADE::create(const RQ_SETUP_BLADE &info) {
  if (info.unknown00 == 0) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 2572
  SCOM_SET_BLADE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_SET_BLADE(GfReqSmallCom::get()->allocate(), info);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_NIA_BLADE::exec(const fw::UpdateInfo &) {
  if (!unknown1c) {
    RQ_SETUP_PARTY info;
    GfGameParty::getCurrentPartyInfo(info);
    if (GfDataBlade::getSetDriver(BLADE_UNKNOWN_1011) == DRIVER_UNKNOWN_1) {
      GfDataDriver::unsetBlade(BLADE_UNKNOWN_1011);
    }
    if (GfDataDriver::isActivateUnuse(DRIVER_UNKNOWN_2)) {
      GfDataDriver::setActivateReserver(DRIVER_UNKNOWN_2, PARTY_UNKNOWN_4294967295);
    }
    if (GfDataBlade::isActivateUnuse(BLADE_UNKNOWN_1011)) {
      return true;
    }
    GfDataDriver::equipDriverBladeFromReserverBlade(DRIVER_UNKNOWN_2);
    u32 driver = GfDataBlade::getSetDriver(BLADE_UNKNOWN_1011);
    GfDataBlade::setActivateUnuse(BLADE_UNKNOWN_1011);
    GfGameParty::getCurrentPartyInfo(info);
    for (u32 index = 0; index < 10; index++) {
      RQ_SETUP_PARTY::Member &member = info.unknown00[index];
      if (member.unknown00 == driver) {
        for (u32 slot = 0; slot < 3; slot++) {
          if (member.unknown08[slot] == BLADE_UNKNOWN_1011) {
            member.unknown08[slot] = 0;
            break;
          }
        }
        break;
      }
    }
    bool isSet = false;
    for (u32 index = PARTY_UNKNOWN_3; index < 5; index++) {
      RQ_SETUP_PARTY::Member &member = info.unknown00[index];
      if (member.unknown00 == 0) {
        member.unknown00 = DRIVER_UNKNOWN_2;
        for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(DRIVER_UNKNOWN_2); slot++) {
          member.unknown08[slot] = GfDataDriver::getBlade(DRIVER_UNKNOWN_2, slot);
        }
        isSet = true;
        break;
      }
    }
    if (!isSet) {
      for (u32 index = 0; index < PARTY_UNKNOWN_3; index++) {
        RQ_SETUP_PARTY::Member &member = info.unknown00[index];
        if (member.unknown00 == 0) {
          member.unknown00 = DRIVER_UNKNOWN_2;
          for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(DRIVER_UNKNOWN_2); slot++) {
            member.unknown08[slot] = GfDataDriver::getBlade(DRIVER_UNKNOWN_2, slot);
          }
          break;
        }
      }
    }
    info.unknowncc = 0;
    GfReqCommand::reqChangeParty(info);
  } else {
    GfPartyPosInfo position;
    GfGameParty::getPartyPosition(position);
    if (GfGameRide::isRideOnPair()) {
      GfGameRide::setRideOn(false);
    }
    RQ_SETUP_PARTY info;
    GfGameParty::getCurrentPartyInfo(info);
    if (GfDataBlade::isActivateUnuse(BLADE_UNKNOWN_1011)) {
      GfDataBlade::setActivateReserver(BLADE_UNKNOWN_1011);
    }
    if (GfDataDriver::isActivateUnuse(DRIVER_UNKNOWN_2)) {
      return true;
    }
    for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(DRIVER_UNKNOWN_2); slot++) {
      u32 blade = GfDataDriver::getBlade(DRIVER_UNKNOWN_2, slot);
      if (blade != 0) {
        GfDataDriver::unsetBlade(blade);
      }
    }
    GfDataDriver::setActivateUnuse(DRIVER_UNKNOWN_2);
    for (u32 index = 0; index < 10; index++) {
      RQ_SETUP_PARTY::Member &member = info.unknown00[index];
      if (member.unknown00 == DRIVER_UNKNOWN_2) {
        member.unknown00 = 0;
        for (u32 slot = 0; slot < SET_UNKNOWN_5; slot++) {
          member.unknown08[slot] = 0;
        }
      }
      member.unknown12 = true;
    }
    if (info.unknown00[0].unknown00 == 0 && info.unknown00[1].unknown00 == 0 && info.unknown00[2].unknown00 == 0) {
      for (u32 index = PARTY_UNKNOWN_3; index < 10; index++) {
        if (info.unknown00[index].unknown00 == DRIVER_UNKNOWN_1) {
          info.unknown00[0] = info.unknown00[index];
          info.unknown00[0].unknown12 = true;
          info.unknown00[index].clear();
        }
      }
    }
    info.unknownc8 = OBJECT_TYPE_PC;
    info.unknowncc = 0;
    info.m_partyPosInfo = position;
    GfReqCommand::reqChangeParty(info);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_NIA_BLADE::create(bool isBlade) {
#line 2730
  SCOM_NIA_BLADE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_NIA_BLADE(GfReqSmallCom::get()->allocate(), isBlade);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_QUEST_REACH::checkEventScequence() const {
  if (!GfGameManager::isInnerState(GF_STATE_UNKNOWN_20)) {
    return true;
  }
  if (GfGameEvent::get() != nullptr && GfGameEvent::get()->unknown1914 >= GfGameEvent::PLAY_STATE_UNKNOWN_2) {
    return true;
  }
  return false;
}

bool SCOM_QUEST_REACH::exec(const fw::UpdateInfo &) {
  if (unknown1c == unknown001_3 && !checkEventScequence()) {
    return false;
  }
  GfQuestTask::completeReachTask(unknown1c, unknown20);
  return true;
}

void SCOM_QUEST_REACH::createDiscoverLandmark(u32 landmark) {
#line 1723
  SCOM_QUEST_REACH *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(GfReqSmallCom::get()->allocate(), unknown001_1, landmark);
  GfReqSmallCom::addRequestParallel(command);
  createArriveLandmark(landmark);
}

void SCOM_QUEST_REACH::createArriveLandmark(u32 landmark) {
#line 1730
  SCOM_QUEST_REACH *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(GfReqSmallCom::get()->allocate(), unknown001_2, landmark);
  GfReqSmallCom::addRequestParallel(command);
}

void SCOM_QUEST_REACH::createArrivePlace(u32 place) {
#line 1736
  SCOM_QUEST_REACH *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(GfReqSmallCom::get()->allocate(), unknown001_3, place);
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_QUEST_GIMMICK::exec(const fw::UpdateInfo &) {
  GfQuestTask::completeGimmickTask(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createDoor(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_DOOR, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1780
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_DOOR, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createElevator(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_ELEVATOR, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1799
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_ELEVATOR, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createJump(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_JUMP, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1818
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_JUMP, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createMapGimmick(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_MAP_GIMMICK, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1837
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_MAP_GIMMICK, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createWarp(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_WARP, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1855
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_WARP, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createSalvage(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_SALVAGE, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1874
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_SALVAGE, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createTresure(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_TBOX, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1893
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_TBOX, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

void SCOM_SALVAGER_POINT::setPoint(u32 point) { GfDataUtil::setSalvagerPoint(point); }

void SCOM_RANDOM_INN::setRandom() { GfDataUtil::setRandomInn(); }

bool SCOM_ADD_MONEY::exec(const fw::UpdateInfo &) {
  GfGameUtil::addMoney(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_MONEY::create(int money) {
  if (money != 0) {
#line 117
    SCOM_ADD_MONEY *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_MONEY(GfReqSmallCom::get()->allocate(), money);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_COIN::exec(const fw::UpdateInfo &) {
  GfGameUtil::addCoin(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_COIN::create(int coin) {
  if (coin != 0) {
#line 132
    SCOM_ADD_COIN *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_COIN(GfReqSmallCom::get()->allocate(), coin);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_MAXIMUM_HEAL::exec(const fw::UpdateInfo &) {
  GfObj *obj = GfObjUtil::getObj(m_GF_OBJ_HANDLE);
  if (obj != nullptr) {
    DataParamAcc acc(m_GF_OBJ_HANDLE);
    {
      MsgObjectMaxHp message(acc.getHpMax(false));
      obj->sendMessage(obj, message);
    }
    {
      MsgObjectHealHp message(0, HEAL_TYPE_UNKNOWN_1);
      obj->sendMessage(obj, message);
    }
  }
  return true;
}

void SCOM_MAXIMUM_HEAL::create(GF_OBJ_HANDLE *handle) {
#line 162
  SCOM_MAXIMUM_HEAL *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_MAXIMUM_HEAL(GfReqSmallCom::get()->allocate(), handle);
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ADD_DEVELOP::exec(const fw::UpdateInfo &) {
  GfGameUtil::addDevelopPoint(unknown20, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_DEVELOP::create(u32 nation, u32 point) {
  if (nation != 0 && point != 0) {
#line 409
    SCOM_ADD_DEVELOP *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_DEVELOP(GfReqSmallCom::get()->allocate(), nation, point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_ADD_DEVELOP::createGmk(u32 fieldZone, u32 point) { create(GfDataMap::getFieldZoneId(fieldZone), point); }

bool SCOM_ACCESS_TARGET::exec(const fw::UpdateInfo &) {
  GfGameManager::setAccessTarget(m_GF_OBJ_HANDLE);
  return true;
}

GF_SCOM_HANDLE *SCOM_ACCESS_TARGET::create(GF_OBJ_HANDLE *target) {
#line 1925
  SCOM_ACCESS_TARGET *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ACCESS_TARGET(GfReqSmallCom::get()->allocate(), target);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_SET_FLAG::exec(const fw::UpdateInfo &) {
  switch (unknown1c) {
  case 1:
    GfGameFlag::setLocal(1, unknown20, unknown24);
    break;
  case 2:
    GfGameFlag::setLocal(2, unknown20, unknown24);
    break;
  case 4:
    GfGameFlag::setLocal(4, unknown20, unknown24);
    break;
  case 8:
    GfGameFlag::setLocal(8, unknown20, unknown24);
    break;
  case 16:
    GfGameFlag::setLocal(16, unknown20, unknown24);
    break;
  case 32:
    GfGameFlag::setLocal(32, unknown20, unknown24);
    break;
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_FLAG::create(u32 size, u32 index, u32 value) {
#line 1982
  SCOM_SET_FLAG *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_SET_FLAG(GfReqSmallCom::get()->allocate(), size, index, value);
  return GfReqSmallCom::addRequest(command);
}

SCOM_CHAR_DEAD::SCOM_CHAR_DEAD(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, const MsgObjectNotifyDead &message)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_50, SCOM_EXEC_UNKNOWN_0, 1), m_msgObjectNotifyDead(DEAD_TYPE_UNKNOWN_1, nullptr) {
  m_GF_OBJ_HANDLE = target;
  m_msgObjectNotifyDead = message;
  m_msgObjectNotifyDead.unknown10 = nullptr;
}

bool SCOM_CHAR_DEAD::exec(const fw::UpdateInfo &) {
  GfObjAcc acc(m_GF_OBJ_HANDLE);
  GfObjAcc killerAcc(m_msgObjectNotifyDead.m_GF_OBJ_HANDLE);
  if (m_GF_OBJ_HANDLE != m_msgObjectNotifyDead.m_GF_OBJ_HANDLE) {
    GfGameParty::getPartyId(m_GF_OBJ_HANDLE);
  }
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    if (!GfGameManager::isPlayerDeadSequence()) {
      GfQuestTask::incSuppressEnemy(acc.getEnArrangeId());
      GfGameUtil::incEnemySuppress(acc.getEnArrangeId());
    }
    if (GfGameScene::get() != nullptr) {
      GfGameScene::get()->setEnemyDead(m_GF_OBJ_HANDLE);
    }
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_CHAR_DEAD::create(GF_OBJ_HANDLE *target, const MsgObjectNotifyDead &message) {
  GfObjAcc acc(target);
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    if (message.unknown08 == DEAD_TYPE_UNKNOWN_4) {
      DataParamAcc paramAcc(target);
      if (paramAcc.getHp() == 0) {
        return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
      }
      SCOM_DESTROY_GAME_OBJ::create(target, 0.5f, 0);
    }
    SCOM_ACHIEV_INC::createKillEnemy(message.m_GF_OBJ_HANDLE);
    QuestID quest = GfQuestUtil::getCurrentEnemyWithEvent(acc.getEnArrangeId());
    if (!quest.empty()) {
      GfPlayFactory::createEventWait(3.0f, target);
      if (GfGameScene::get() != nullptr) {
        GfGameScene::get()->setEraseQuestEnemyForEventStart(quest);
      }
    }
  }
  if (GfGameScene::get() != nullptr && message.unknown10 != nullptr) {
    MsgObjectNotifyDamage damage(message.unknown10);
    damage.m_GF_OBJ_HANDLE = message.m_GF_OBJ_HANDLE;
    GfGameScene::get()->addDamage(target, damage);
  }
  GfGameObj::addCharDeadMessage(target, message);
#line 2163
  SCOM_CHAR_DEAD *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_CHAR_DEAD(GfReqSmallCom::get()->allocate(), target, message);
  return GfReqSmallCom::addRequest(command);
}

void SCOM_CHAR_DMG::create(GF_OBJ_HANDLE *target, const MsgObjectNotifyDamage &message) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->addDamage(target, message);
  }
  GfAchievStats::checkFallLength(target, message);
  if (GfObjUtil::getObjType(target) == OBJECT_TYPE_ENEMY && GfQuestTarget::getIconType(target, QuestID()) == 0) {
    return;
  }
  mm::mtl::FixedVector<QuestID, 128> quests;
  u32 orderMax = GfQuestManager::getOrderQuestMax();
  for (u32 i = 0; i < orderMax; i++) {
    QuestID quest = GfQuestManager::getOrderQuest(i);
    if (quest.empty()) {
      continue;
    }
    if (GfQuestTask::isReduceHpObj(quest, target)) {
      if (!GfQuestTask::isReduceHpObj(quest, target) && GfGameScene::get() != nullptr) {
        GfGameScene::get()->setEraseQuestEnemyForEventStart(quest);
      }
      quests.push_back(quest);
    }
  }
  for (QuestID quest : quests) {
    GfQuestManager::eventCheckTask(quest);
  }
}

bool SCOM_GAME_SPEED::exec(const fw::UpdateInfo &) {
  GfGameSpeed::setLayerSpeed(unknown002, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_GAME_SPEED::create(f32 speed) {
#line 675
  SCOM_GAME_SPEED *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_GAME_SPEED(GfReqSmallCom::get()->allocate(), speed);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_INTERVAL_SPEED::exec(const fw::UpdateInfo &) {
  GfGameSpeed::setIntervalSpeed(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_INTERVAL_SPEED::create(f32 speed, f32 time) {
#line 661
  SCOM_INTERVAL_SPEED *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_INTERVAL_SPEED(GfReqSmallCom::get()->allocate(), speed, time);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_SET_CAMTYPE::exec(const fw::UpdateInfo &) {
  GfGameCamera::setCameraControlType(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_CAMTYPE::create(int type) {
#line 1996
  SCOM_SET_CAMTYPE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_SET_CAMTYPE(GfReqSmallCom::get()->allocate(), type);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_QUEST_EVENT::exec(const fw::UpdateInfo &) {
  GfQuestTask::completeEventTask(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_QUEST_EVENT::create(u32 event) {
#line 1908
  SCOM_QUEST_EVENT *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_EVENT(GfReqSmallCom::get()->allocate(), event);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_QUEST_ORDER::exec(const fw::UpdateInfo &) {
  GfQuestManager::openOrder(m_questID, false);
  return true;
}

GF_SCOM_HANDLE *SCOM_QUEST_ORDER::create(QuestID quest) {
#line 1688
  SCOM_QUEST_ORDER *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_QUEST_ORDER(GfReqSmallCom::get()->allocate(), quest);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ITEM_USE::exec(const fw::UpdateInfo &) {
  GfQuestTask::completeItemUseTask(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_ITEM_USE::create(u32 item, u32 count) {
#line 1751
  SCOM_ITEM_USE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ITEM_USE(GfReqSmallCom::get()->allocate(), item, count);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_PARTY_OBJ::exec(const fw::UpdateInfo &) {
  if (!unknown1c) {
    unknown1c = true;
    GfGameUnit::destroyParty(m_RQ_SETUP_PARTY, &unknown1c0);
  }
  for (GF_OBJ_HANDLE **it = unknown1c0.begin(); it != unknown1c0.end(); it++) {
    if (GfObjUtil::getObj(*it) != nullptr) {
      return false;
    }
  }
  GfEvent::callPartyChange();
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_PARTY_OBJ::create(const RQ_SETUP_PARTY &info) {
#line 882
  SCOM_DESTROY_PARTY_OBJ *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_DESTROY_PARTY_OBJ(GfReqSmallCom::get()->allocate(), info);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_FIELD_OBJ::exec(const fw::UpdateInfo &) {
  GfFieldManager::destroyObj();
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_FIELD_OBJ::create() {
#line 898
  SCOM_DESTROY_FIELD_OBJ *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_DESTROY_FIELD_OBJ(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_MAP_OBJ::exec(const fw::UpdateInfo &) {
  GfMapManager::destroyObj();
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_MAP_OBJ::create() {
#line 914
  SCOM_DESTROY_MAP_OBJ *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_DESTROY_MAP_OBJ(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_CREATE_MAP_OBJ::exec(const fw::UpdateInfo &) {
  if (GfMapManager::getMapJumpID() == unknown1c) {
    if (unknown20 != 0) {
      GfInitParamMapSeamless param;
      param.m_bladeID = unknown20;
      param.unknown90 = true;
      GfObjFactory::createMap(param);
    }
  } else {
    GfInitParamMapSeamless param;
    param.m_bladeID = unknown1c;
    GfObjFactory::createMap(param);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_CREATE_MAP_OBJ::create(u32 mapJump, u32 map) {
#line 939
  SCOM_CREATE_MAP_OBJ *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_CREATE_MAP_OBJ(GfReqSmallCom::get()->allocate(), mapJump, map);
  return GfReqSmallCom::addRequest(command);
}

SCOM_FADE::unknown001 SCOM_FADE::s_fades[GfMenuFade::FADE_UNKNOWN_3];
GF_SCOM_HANDLE *SCOM_FADE::s_hCreatedReq = reinterpret_cast<GF_SCOM_HANDLE *>(-1);

bool SCOM_FADE::exec(const fw::UpdateInfo &) {
  if (!GfMenuFade::isInitialized()) {
    return false;
  }
  for (u32 i = 0; i < GfMenuFade::FADE_UNKNOWN_3; i++) {
    if (s_fades[i].unknown00 != 0xffffffff) {
      GfMenuFade::setFade(s_fades[i].unknown00, s_fades[i].unknown04, s_fades[i].unknown08);
      s_fades[i].unknown00 = 0xffffffff;
    }
  }
  s_hCreatedReq = reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  return true;
}

SCOM_FADE::SCOM_FADE(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_FADE, SCOM_EXEC_UNKNOWN_0, 1) {}

GF_SCOM_HANDLE *SCOM_FADE::create(u32 channel, u32 frame, const mm::Col4 &color) {
  s_fades[channel].unknown00 = channel;
  s_fades[channel].unknown04 = frame;
  s_fades[channel].unknown08 = color;
  if (s_hCreatedReq == reinterpret_cast<GF_SCOM_HANDLE *>(-1)) {
#line 973
    SCOM_FADE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FADE(GfReqSmallCom::get()->allocate());
    s_hCreatedReq = GfReqSmallCom::addRequest(command);
  }
  return s_hCreatedReq;
}

bool SCOM_RELOAD_BDAT::exec(const fw::UpdateInfo &) {
  GfEvent::get()->unknown002(RELOAD_BDAT_UNKNOWN_0, GfDataBdat::getReloadCount());
  GfDataBdat::releaseBdatInfo();
  fw::BdatManager::reloadBdat(0);
  GfDataBdat::setupBdatInfo();
  GfDataUtil::refreshBdatParam();
  GfEvent::get()->unknown002(RELOAD_BDAT_UNKNOWN_1, GfDataBdat::getReloadCount());
  return true;
}

GF_SCOM_HANDLE *SCOM_RELOAD_BDAT::create() {
#line 1078
  SCOM_RELOAD_BDAT *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_RELOAD_BDAT(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_RELOAD_TEXT::exec(const fw::UpdateInfo &) {
  GfEvent::get()->unknown002(RELOAD_BDAT_UNKNOWN_0, GfDataBdat::getReloadCount());
  GfDataBdat::releaseBdatInfo();
  fw::BdatManager::reloadBdat(1);
  ui::UIUtil::initBdatFP();
  GfDataBdat::setupBdatInfo();
  GfDataUtil::refreshBdatParam();
  ui::UIManager::get()->reloadText();
  GfEvent::get()->unknown002(RELOAD_BDAT_UNKNOWN_1, GfDataBdat::getReloadCount());
  return true;
}

GF_SCOM_HANDLE *SCOM_RELOAD_TEXT::create(fw::LangType type) {
  if (fw::LangUtil::getLangType() == type) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  fw::LangUtil::setLangType(type);
#line 1120
  SCOM_RELOAD_TEXT *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_RELOAD_TEXT(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_STOP_LAYER::exec(const fw::UpdateInfo &) {
  GfGameUtil::changeStopLayer(m_GF_OBJ_HANDLE, unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_STOP_LAYER::create(GF_OBJ_HANDLE *target, bool stop) {
#line 1136
  SCOM_STOP_LAYER *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_STOP_LAYER(GfReqSmallCom::get()->allocate(), target, stop);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_SET_IDEA_POINT_FOR_DEBUG::exec(const fw::UpdateInfo &) {
  GfGameUtil::setIdeaPointForDebug(unknown20, unknown24, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_IDEA_POINT_FOR_DEBUG::create(u32 driver, u32 idea, int point) {
  if (point != 0) {
#line 394
    SCOM_SET_IDEA_POINT_FOR_DEBUG *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_SET_IDEA_POINT_FOR_DEBUG(GfReqSmallCom::get()->allocate(), driver, idea, point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_BATTLE_BGM::exec(const fw::UpdateInfo &) { return true; }

GF_SCOM_HANDLE *SCOM_BATTLE_BGM::create(u32 bgm) {
  GfFieldBgm::get()->setRscBattleBgmID(bgm);
#line 3473
  SCOM_BATTLE_BGM *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_BATTLE_BGM(GfReqSmallCom::get()->allocate(), bgm);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_COLI_CHAR_VALID::exec(const fw::UpdateInfo &) {
  GfObjAcc acc(m_GF_OBJ_HANDLE);
  acc.setCollisionChar(unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_COLI_CHAR_VALID::create(GF_OBJ_HANDLE *target, bool isEnable) {
#line 1151
  SCOM_COLI_CHAR_VALID *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_COLI_CHAR_VALID(GfReqSmallCom::get()->allocate(), target, isEnable);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_CREATE_GMK_SET::exec(const fw::UpdateInfo &) {
  GfFieldGimmick::createGmkSet(unknown1c);
  GfAutoTalkManager::get()->create();
  return true;
}

GF_SCOM_HANDLE *SCOM_CREATE_GMK_SET::create(u32 gimmickSet) {
#line 1226
  SCOM_CREATE_GMK_SET *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_CREATE_GMK_SET(GfReqSmallCom::get()->allocate(), gimmickSet);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_GMK_SET::exec(const fw::UpdateInfo &) {
  GfFieldGimmick::disposeGmkSet(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_GMK_SET::create(u32 gimmickSet) {
#line 1210
  SCOM_DESTROY_GMK_SET *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_DESTROY_GMK_SET(GfReqSmallCom::get()->allocate(), gimmickSet);
  return GfReqSmallCom::addRequest(command);
}

SCOM_FIELD_SKILL::SCOM_FIELD_SKILL(GF_SCOM_HANDLE *handle, u32 fieldSkill, u32 blade) : SCOM(handle, SCOM_TYPE_UNKNOWN_55, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(fieldSkill), unknown20(blade) {}

bool SCOM_FIELD_SKILL::exec(const fw::UpdateInfo &) {
  if (unknown20 == 0) {
    if (!GfGameManager::isControlFree()) {
      return false;
    }
    for (u32 partyId = 0; partyId < PARTY_UNKNOWN_3; partyId++) {
      DataParamAcc acc(OBJECT_TYPE_PC, GfGameParty::getDriverBdatId(partyId), GIMMICK_TYPE_UNKNOWN_0);
      if (acc.isValid()) {
        int setBladeNum = GfDataDriver::getMaxSetBladeNum(acc.getValidDriverId());
        for (int slot = 0; slot < setBladeNum; slot++) {
          u32 blade = acc.getBlade(slot, false);
          if (blade != 0) {
            GfQuestUtil::incFieldSkillTask(blade, unknown1c);
          }
        }
      }
    }
  } else {
    GfQuestUtil::incFieldSkillTask(unknown20, unknown1c);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_FIELD_SKILL::create(u32 fieldSkill) {
  if (fieldSkill != 0) {
#line 3324
    SCOM_FIELD_SKILL *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_SKILL(GfReqSmallCom::get()->allocate(), fieldSkill, 0);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_SKILL::createWithBlade(u32 fieldSkill, u32 blade) {
  if (fieldSkill != 0) {
#line 3331
    SCOM_FIELD_SKILL *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_SKILL(GfReqSmallCom::get()->allocate(), fieldSkill, blade);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_REBUILD::exec(const fw::UpdateInfo &) {
  GfObjUtil::rebuild(m_GF_OBJ_HANDLE);
  return true;
}

GF_SCOM_HANDLE *SCOM_REBUILD::create(GF_OBJ_HANDLE *target) {
#line 3402
  SCOM_REBUILD *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_REBUILD(GfReqSmallCom::get()->allocate(), target);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_CHANGE_RIDE::create(GF_OBJ_HANDLE *driver, bool isRide) {
#line 3459
  SCOM_CHANGE_RIDE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_CHANGE_RIDE(GfReqSmallCom::get()->allocate(), driver, isRide);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ADD_MERCENARIES_POINT::exec(const fw::UpdateInfo &) {
  GfGameMercenaries::addPoint(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_MERCENARIES_POINT::create(u32 point) {
  if (point != 0) {
#line 446
    SCOM_ADD_MERCENARIES_POINT *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_MERCENARIES_POINT(GfReqSmallCom::get()->allocate(), point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_SET_MERCENARIES_LEVEL::exec(const fw::UpdateInfo &) {
  GfGameMercenaries::setLevel(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_MERCENARIES_LEVEL::create(u32 level) {
#line 460
  SCOM_SET_MERCENARIES_LEVEL *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_SET_MERCENARIES_LEVEL(GfReqSmallCom::get()->allocate(), level);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_EXEC_MOUNT::exec(const fw::UpdateInfo &) {
  GfMountManager::execMount(m_GF_OBJ_HANDLE, GFATTACH_UNKNOWN_0, unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_MOUNT::create(GF_OBJ_HANDLE *target, OPTMNT mountType) {
#line 1165
  SCOM_EXEC_MOUNT *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_EXEC_MOUNT(GfReqSmallCom::get()->allocate(), target, mountType);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_RESET_MOUNT::exec(const fw::UpdateInfo &) {
  GfMountManager::resetMount(m_GF_OBJ_HANDLE, GFATTACH_UNKNOWN_0, unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_RESET_MOUNT::create(GF_OBJ_HANDLE *target, OPTMNT mountType) {
#line 1178
  SCOM_RESET_MOUNT *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_RESET_MOUNT(GfReqSmallCom::get()->allocate(), target, mountType);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_VALID_LOCAL_SPEED::exec(const fw::UpdateInfo &) {
  GfGameUtil::changeStopLayer(m_GF_OBJ_HANDLE, unknown2c);
  if (unknown28 >= 0.0f) {
    GfGameSpeed::setLayerSpeed(unknown003, unknown28);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_VALID_LOCAL_SPEED::create(GF_OBJ_HANDLE *target, bool stop, f32 speed) {
#line 1195
  SCOM_VALID_LOCAL_SPEED *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_VALID_LOCAL_SPEED(GfReqSmallCom::get()->allocate(), target, stop, speed);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_LOADING::exec(const fw::UpdateInfo &) {
  if (GfMenuFade::isInitialized()) {
    GfMenuFade::setLoading(unknown1c, unknown20);
    return true;
  }
  return false;
}

GF_SCOM_HANDLE *SCOM_LOADING::create(u32 type, bool isDisp) {
#line 991
  SCOM_LOADING *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_LOADING(GfReqSmallCom::get()->allocate(), type, isDisp);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_STOP_BATTLE::exec(const fw::UpdateInfo &) {
  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr) {
    if (!GfGameManager::isBattle()) {
      scene->setForceStopBattle(false);
      return true;
    }
    scene->setForceStopBattle(true);
  }
  return false;
}

GF_SCOM_HANDLE *SCOM_STOP_BATTLE::create() {
#line 4237
  SCOM_STOP_BATTLE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_STOP_BATTLE(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ADD_ETHER::exec(const fw::UpdateInfo &) {
  GfGameUtil::addEther(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_ETHER::create(int ether) {
  GfGameUtil::addEther(ether);
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

int SCOM_ACHIEV_INC::s_countSalvageShop;

SCOM_ACHIEV_INC::SCOM_ACHIEV_INC(GF_SCOM_HANDLE *handle, u32 stats, int count, u32 blade) : SCOM(handle, SCOM_TYPE_UNKNOWN_55, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(stats), unknown20(count) {
  if (stats == 0x22) {
    s_countSalvageShop++;
  }
  if (blade != 0) {
    unknown28.push_back(blade);
  }
}

bool SCOM_ACHIEV_INC::exec(const fw::UpdateInfo &) {
  GfAchievManager *manager = GfAchievManager::get();
  if (manager != nullptr) {
    if (GfDataAchievement::isWaitControllFreeStats(unknown1c)) {
      if (!GfGameManager::isControlFree()) {
        return false;
      }
      if (unknown1c == 0x22) {
        if (s_countSalvageShop == 0) {
          return true;
        }
        s_countSalvageShop = 0;
        manager->incAchiev(0x22, 1);
        return true;
      }
    }
    if (unknown28.size() == 0) {
      manager->incAchiev(unknown1c, unknown20);
    } else {
      manager->incAchievWithBlade(unknown1c, unknown20, unknown28);
    }
  }
  return true;
}

void SCOM_ACHIEV_INC::create(u32 stats, int count, u32 blade) {
#line 2784
  SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), stats, count, blade);
  GfReqSmallCom::addRequestParallel(command);
}

void SCOM_ACHIEV_INC::createParty(u32 stats, int count) {
#line 2790
  SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), stats, count, 0);
  GfDataBlade::getListPartyAll(command->unknown28);
  GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_ACHIEV_INC::createCurrentBlade(GF_OBJ_HANDLE *handle, u32 stats, int count) {
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  GF_SCOM_HANDLE *scom = reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  if (blade != 0 && !GfDataBlade::isDummyBlade(blade)) {
#line 2810
    SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), stats, count, blade);
    scom = GfReqSmallCom::addRequestParallel(command);
  }
  return scom;
}

void SCOM_ACHIEV_INC::addTotalCount(u32 stats, u32 count) { GfDataAchievement::addTotalCount(stats, count); }

GF_SCOM_HANDLE *SCOM_ACHIEV_INC::createBladeArts(GF_OBJ_HANDLE *handle, u32 arts) {
  DataParamAcc acc(handle);
  GF_SCOM_HANDLE *scom = reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  if (acc.isValid()) {
    u32 stats;
    if (acc.getBladeArts(0, false) == arts) {
      stats = 0x5d;
    } else if (acc.getBladeArts(1, false) == arts) {
      stats = 0x5e;
    } else if (acc.getBladeArts(2, false) == arts) {
      stats = 0x5f;
    } else {
      return scom;
    }
#line 2856
    SCOM_ACHIEV_INC *total = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), 0x62, 1, acc.getBlade(-1, false));
    GfReqSmallCom::addRequestParallel(total);
#line 2859
    SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), stats, 1, acc.getBlade(-1, false));
    scom = GfReqSmallCom::addRequestParallel(command);
  }
  return scom;
}

GF_SCOM_HANDLE *SCOM_ACHIEV_INC::createBladeArtsSp(GF_OBJ_HANDLE *handle, u32 arts) {
  GF_SCOM_HANDLE *scom = reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  if (arts != 0) {
    DataParamAcc acc(handle);
    if (acc.isValid() && (acc.getBladeArtsEx(false) == arts || acc.getBladeArtsEx2(false) == arts)) {
#line 2877
      SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), 0x60, 1, acc.getBlade(-1, false));
      scom = GfReqSmallCom::addRequestParallel(command);
    }
  }
  return scom;
}

GF_SCOM_HANDLE *SCOM_ACHIEV_INC::createBladeNArts(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
  GF_SCOM_HANDLE *scom = reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  if (acc.isValid()) {
#line 2889
    SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), 0x61, 1, acc.getBlade(-1, false));
    scom = GfReqSmallCom::addRequestParallel(command);
  }
  return scom;
}

void SCOM_ACHIEV_INC::createElementalCombo(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x7c, 1);
  create(0x7c, 1, 0);
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x7d, 1, blade);
  }
}

void SCOM_ACHIEV_INC::createElementalComboFinish(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x7e, 1);
  create(0x7e, 1, 0);
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x7f, 1, blade);
  }
}

// Inferred role: counts a combo for the party and each party blade; original name unknown.
static void unknown009(u32 stats) {
  SCOM_ACHIEV_INC::addTotalCount(stats - 1, 1);
  SCOM_ACHIEV_INC::create(stats - 1, 1, 0);
  mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> blades;
  GfDataBlade::getListParty(blades);
  u16 *end = blades.end();
  for (u16 *it = blades.begin(); it != end; ++it) {
    SCOM_ACHIEV_INC::create(stats, 1, *it);
  }
}

void SCOM_ACHIEV_INC::createFightCombo(GF_OBJ_HANDLE *) { unknown009(0x79); }

void SCOM_ACHIEV_INC::createFightComboFinish(GF_OBJ_HANDLE *) { unknown009(0x7b); }

void SCOM_ACHIEV_INC::createChainAttack(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x80, 1);
  create(0x80, 1, 0);
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x81, 1, blade);
  }
}

void SCOM_ACHIEV_INC::createButtonChallenge() {
  GF_OBJ_HANDLE *leader = GfGameManager::getPartyLeaderDriver();
  addTotalCount(0x82, 1);
  create(0x82, 1, 0);
  DataParamAcc acc(leader);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x83, 1, blade);
  }
}

void SCOM_ACHIEV_INC::createHelp(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x84, 1);
  create(0x84, 1, 0);
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x85, 1, blade);
  }
}

void SCOM_ACHIEV_INC::createPotGet() {
  GF_OBJ_HANDLE *leader = GfGameManager::getPartyLeaderDriver();
  addTotalCount(0x86, 1);
  create(0x86, 1, 0);
  DataParamAcc acc(leader);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x87, 1, blade);
  }
}

void SCOM_ACHIEV_INC::createAvoid(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x88, 1);
  create(0x88, 1, 0);
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x89, 1, blade);
  }
}

void SCOM_ACHIEV_INC::createGuard(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x8a, 1);
  create(0x8a, 1, 0);
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x8b, 1, blade);
  }
}

void SCOM_ACHIEV_INC::createBladeChange(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x8c, 1);
  create(0x8c, 1, 0);
  DataParamAcc acc(handle);
  create(0x8d, 1, acc.getValidBdatId());
}

void SCOM_ACHIEV_INC::createRecover(GF_OBJ_HANDLE *handle, u32 value) {
  addTotalCount(0x94, value);
  create(0x94, value, 0);
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x95, value, blade);
  }
}

void SCOM_ACHIEV_INC::createBackAttack(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  if (blade != 0) {
    create(0x96, 1, blade);
  }
}

void SCOM_ACHIEV_INC::createDamageMax(GF_OBJ_HANDLE *handle, u32 damage) {
  addTotalCount(0x92, damage);
  create(0x92, damage, 0);
  DataParamAcc acc(handle);
  u32 type = acc.getObjType();
  u32 blade = 0;
  if (type == OBJECT_TYPE_BLADE) {
    blade = acc.getValidBdatId();
  } else if (type == OBJECT_TYPE_PC) {
    blade = acc.getBlade(-1, false);
  }
  if (blade != 0) {
    create(0x93, damage, blade);
  }
}

void SCOM_ACHIEV_INC::createDamageAdd(GF_OBJ_HANDLE *handle, u32 damage) {
  addTotalCount(0x8e, damage);
  create(0x8e, damage, 0);
  DataParamAcc acc(handle);
  u32 type = acc.getObjType();
  u32 blade = 0;
  if (type == OBJECT_TYPE_BLADE) {
    blade = acc.getValidBdatId();
  } else if (type == OBJECT_TYPE_PC) {
    blade = acc.getBlade(-1, false);
  }
  if (blade != 0) {
    create(0x8f, damage, blade);
  }
}

void SCOM_ACHIEV_INC::createDamageGet(GF_OBJ_HANDLE *handle, u32 damage) {
  addTotalCount(0x90, damage);
  create(0x90, damage, 0);
  DataParamAcc acc(handle);
  create(0x91, damage, acc.getBlade(-1, false));
}

void SCOM_ACHIEV_INC::createCriticalHit(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x72, 1);
  create(0x72, 1, 0);
  DataParamAcc acc(handle);
  create(0x73, 1, acc.getBlade(-1, false));
}

void SCOM_ACHIEV_INC::createCriticalGet(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x74, 1);
  create(0x74, 1, 0);
  DataParamAcc acc(handle);
  create(0x75, 1, acc.getBlade(-1, false));
}

void SCOM_ACHIEV_INC::createKizuna(GF_OBJ_HANDLE *handle) {
  addTotalCount(0x76, 1);
  create(0x76, 1, 0);
  DataParamAcc acc(handle);
  create(0x77, 1, acc.getBlade(-1, false));
}

void SCOM_ACHIEV_INC::createKillEnemy(GF_OBJ_HANDLE *handle) {
  addTotalCount(99, 1);
  create(99, 1, 0);
  DataParamAcc acc(handle);
  create(100, 1, acc.getBlade(-1, false));
}

// Inferred role: item and stats counted once the item is owned; original type name unknown.
struct unknown010 {
  u16 unknown00; // Inferred role: item; original member name unknown.
  u16 unknown02; // Inferred role: stats; original member name unknown.
};

static const unknown010 unknown011[4] = {{45005, 0x97}, {45006, 0x98}, {45007, 0x99}, {45008, 0x9a}};

// Inferred role: tells whether a blade of the party, other than the given one, satisfies the condition; original name unknown.
static bool unknown012(bool (*condition)(DataParamAcc &, int), int excludeBlade, int value) {
  for (u32 partyId = 0; partyId < 3; partyId++) {
    DataParamAcc driverAcc(GfGameParty::getHandleDriver(partyId));
    if (driverAcc.isValid()) {
      for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(driverAcc.getValidDriverId()); slot++) {
        int blade = driverAcc.getBlade(slot, false);
        if (blade == 0 || blade != excludeBlade) {
          bool isMatch = false;
          {
            DataParamAcc bladeAcc(OBJECT_TYPE_BLADE, driverAcc.getBlade(slot, false), GIMMICK_TYPE_UNKNOWN_0);
            if (bladeAcc.isValid()) {
              isMatch = condition(bladeAcc, value);
            }
          }
          if (isMatch) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

// Inferred role: male blade; original name unknown.
static bool unknown013(DataParamAcc &acc, int) { return acc.getGender() == 1; }

// Inferred role: female blade; original name unknown.
static bool unknown014(DataParamAcc &acc, int) { return acc.getGender() == 2; }

// Inferred role: blade that is not a quest race 2 blade; original name unknown.
static bool unknown015(DataParamAcc &acc, int) { return acc.getQuestRace() != 2; }

// Inferred role: blade with the given weapon type; original name unknown.
static bool unknown016(DataParamAcc &acc, int weaponType) { return acc.getWeaponType(-1, false) == weaponType; }

// Inferred role: blade with the given id; original name unknown.
static bool unknown017(DataParamAcc &acc, int blade) { return acc.getValidBdatId() == blade; }

void SCOM_ACHIEV_INC::createBattle() {
  addTotalCount(0x65, 1);
  create(0x65, 1, 0);
  for (u32 i = 0; i < 4; i++) {
    if (GfItemUtil::getItemBoxCount(unknown011[i].unknown00) != 0) {
      u32 stats = unknown011[i].unknown02;
      addTotalCount(stats, 1);
      create(stats, 1, 0);
    }
  }
  DataParamAcc leaderAcc(GfGameManager::getPartyLeaderDriver());
  for (u32 partyId = 0; partyId < 3; partyId++) {
    DataParamAcc acc(GfGameParty::getHandleDriver(partyId));
    if (acc.isValid()) {
      create(0x66, 1, acc.getBlade(-1, false));
      if (unknown012(unknown013, leaderAcc.getBlade(-1, false), 0)) {
        create(0x67, 1, acc.getBlade(-1, false));
      }
      if (unknown012(unknown014, leaderAcc.getBlade(-1, false), 0)) {
        create(0x68, 1, acc.getBlade(-1, false));
      }
      if (unknown012(unknown015, leaderAcc.getBlade(-1, false), 0)) {
        create(0x69, 1, acc.getBlade(-1, false));
      }
      for (int weaponType = 10; weaponType != 0x11; weaponType++) {
        if (unknown012(unknown016, leaderAcc.getBlade(-1, false), weaponType)) {
          create(weaponType + 0x60, 1, acc.getBlade(-1, false));
        }
      }
      if (unknown012(unknown017, leaderAcc.getBlade(-1, false), 0x3e9)) {
        create(0x71, 1, acc.getBlade(-1, false));
      }
    }
  }
}

void SCOM_ACHIEV_INC::createBladeCreate() {
  addTotalCount(0x31, 1);
  create(0x31, 1, 0);
  mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> blades;
  GfDataBlade::getListPartyAll(blades);
  GfAchievManager *manager = GfAchievManager::get();
  if (manager != nullptr) {
    manager->incAchievWithBlade(0x32, 1, blades);
  }
}

void SCOM_ACHIEV_INC::createCrystal() {
  mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> blades;
  GfDataBlade::getListPartyAll(blades);
  GfAchievManager *manager = GfAchievManager::get();
  if (manager != nullptr) {
    manager->incAchievWithBlade(0x43, 1, blades);
  }
}

GAME_VOICE_HANDLE *SCOM_SALVAGE_VOICE::create(GF_OBJ_HANDLE *handle, CV_SALVAGE voice) { return GfSalvageVoice::playVoice(handle, voice); }

GAME_VOICE_HANDLE *SCOM_SALVAGE_VOICE::createResult(GF_OBJ_HANDLE *handle, CV_SALVAGE_RESULT voice) { return GfSalvageVoice::playResultVoice(handle, voice); }

bool SCOM_SALVAGE_VOICE::isPlayEnd(GAME_VOICE_HANDLE *voice) { return GfGameVoice::getResult(voice) != CV_RESULT_UNKNOWN_2; }

bool SCOM_FIELD_VOICE::isStopVoice() const { return unknownd2 && GfGameManager::isPlayEvent(); }

bool SCOM_FIELD_VOICE::exec(const fw::UpdateInfo &info) {
  if (unknownd0) {
    if (!GfGameManager::isControlFree()) {
      return false;
    }
    unknownd0 = false;
    unknownd1 = true;
  }
  if (unknownd1 && !GfGameManager::isControlFree()) {
    return true;
  }

  unknown001 &voice = unknown20.front();
  switch (voice.unknown18) {
  case CV_RESULT_UNKNOWN_0:
    voice.unknown10 -= info.unknown04;
    if (voice.unknown10 > 0.0f) {
      return false;
    }
    if (!isStopVoice()) {
      voice.m_GAME_VOICE_HANDLE = GfFieldVoice::playVoice(voice.m_paramObj, voice.unknown14, voice.unknown1c);
      if (voice.m_GAME_VOICE_HANDLE != nullptr) {
        voice.unknown18 = CV_RESULT_UNKNOWN_2;
        return false;
      }
    } else {
      voice.m_GAME_VOICE_HANDLE = nullptr;
    }
    voice.unknown18 = CV_RESULT_UNKNOWN_3;
    break;
  case CV_RESULT_UNKNOWN_2:
    if (isStopVoice() && voice.m_GAME_VOICE_HANDLE != nullptr) {
      GfGameVoice::playStop(voice.m_GAME_VOICE_HANDLE);
      voice.m_GAME_VOICE_HANDLE = nullptr;
    }
    voice.unknown18 = GfGameVoice::getResult(voice.m_GAME_VOICE_HANDLE);
    if (voice.unknown18 == CV_RESULT_UNKNOWN_2) {
      return false;
    }
    break;
  }
  if (voice.unknown18 >= CV_RESULT_UNKNOWN_3) {
    unknown20.pop_front();
    if (unknown20.empty()) {
      return true;
    }
  }
  return false;
}

// Inferred role: picks a random party member with a valid driver and blade, or -1; original name unknown.
static u32 unknown005() {
  mm::mtl::FixedVector<u16, 16> members;
  for (u32 i = 0; i < 3; i++) {
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(i);
    GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(i, -1);
    if (GfGameObj::isValidGameObj(driver, true, nullptr) && GfGameObj::isValidGameObj(blade, true, nullptr)) {
      members.push_back(i);
    }
  }
  if (members.size() == 0) {
    return 0xffffffff;
  }
  return members[ml::mtRand(members.size())];
}

// Inferred role: picks a random driver of the party, or 0; original name unknown.
static u32 unknown006() {
  mm::mtl::FixedVector<u16, 16> drivers;
  for (u32 i = 0; i < 5; i++) {
    u32 driver = GfDataParty::getDriver(i);
    if (driver != 0) {
      drivers.push_back(driver);
    }
  }
  if (drivers.size() == 0) {
    return 0;
  }
  return drivers[ml::mtRand(drivers.size())];
}

// Inferred role: voice names of the driver kizuna voices, three per driver; original name unknown.
static const char *const unknown007[6][3] = {
    {"01200201", "01420601", "01980201"},
    {"02490101", "02750101", "02410602"},
    {"06470101", "06470104", "06910103"},
    {"03980201", "03490202", "03870101"},
    {"04490101", "04980201", "04320102"},
    {"05490101", "05980201", "05980101"},
};

void SCOM_FIELD_VOICE::create(CV_FIELD voice, CV_PRIO priority) {
  ParamObj object = {GfGameManager::getControlMover(), 0, 0};
  GfFieldVoice::playVoice(object, voice, priority);
}

void SCOM_FIELD_VOICE::create(const ParamObj &paramObj, CV_FIELD voice, CV_PRIO priority) {
  ParamObj object = paramObj;
  if (paramObj.m_GF_OBJ_HANDLE == unknown020 && paramObj.unknown0c == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  GfFieldVoice::playVoice(object, voice, priority);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createJump(const ParamObj &paramObj) {
  if (GfGameManager::getControlMover() == paramObj.m_GF_OBJ_HANDLE && GfGameManager::isControlFree()) {
    SCOM_ACHIEV_INC::addTotalCount(2, 1);
    SCOM_ACHIEV_INC::create(2, 1, 0);
    if (ml::mtRandf1() < 0.4f) {
      return nullptr;
    }
    ParamObj object = paramObj;
    if (paramObj.m_GF_OBJ_HANDLE == unknown020 && paramObj.unknown0c == 0) {
      object = ParamObj{GfGameManager::getControlMover(), 0, 0};
    }
    return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_0, CV_PRIO_UNKNOWN_1);
  }
  return nullptr;
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createHighLanding(const ParamObj &paramObj) {
  if (GfGameManager::getControlMover() == paramObj.m_GF_OBJ_HANDLE) {
    ParamObj object = paramObj;
    if (paramObj.m_GF_OBJ_HANDLE == unknown020 && paramObj.unknown0c == 0) {
      object = ParamObj{GfGameManager::getControlMover(), 0, 0};
    }
    return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_2, CV_PRIO_UNKNOWN_1);
  }
  return nullptr;
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createFallDead(const ParamObj &paramObj) {
  if (!GfGameManager::isEvent(false)) {
    ParamObj object = paramObj;
    if (paramObj.m_GF_OBJ_HANDLE == unknown020 && paramObj.unknown0c == 0) {
      object = ParamObj{GfGameManager::getControlMover(), 0, 0};
    }
    return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_1, CV_PRIO_UNKNOWN_4);
  }
  return nullptr;
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createLandmark() {
  if (!GfGameManager::isBattle()) {
    GfGameScene *scene = GfGameScene::get();
    if (scene == nullptr || static_cast<u32>(scene->unknown624) >= 60) {
      u32 party = unknown005();
      if (party != 0xffffffff) {
        GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(party);
        GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(party, -1);
        if (DataParamAcc(driver).getHp() != 0) {
#line 3675
          SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
          if (command != nullptr) {
            ParamObj driverObject = {driver, 0, 0};
            command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_5, CV_PRIO_UNKNOWN_1);
            ParamObj bladeObject = {blade, 0, 0};
            command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_5, CV_PRIO_UNKNOWN_3);
            return GfReqSmallCom::addRequestParallel(command);
          }
        }
      }
    }
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createUnexplored() {
  if (!GfGameManager::isBattle()) {
    GfGameScene *scene = GfGameScene::get();
    if (scene == nullptr || static_cast<u32>(scene->unknown624) >= 60) {
      u32 party = unknown005();
      if (party != 0xffffffff) {
        GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(party);
        GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(party, -1);
        u32 hp = DataParamAcc(driver).getHp();
        if (hp != 0 && GfGameObj::isValidGameObj(driver, true, nullptr)) {
#line 3713
          SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
          if (command != nullptr) {
            ParamObj driverObject = {driver, 0, 0};
            command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_6, CV_PRIO_UNKNOWN_1);
            ParamObj bladeObject = {blade, 0, 0};
            command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_6, CV_PRIO_UNKNOWN_3);
            return GfReqSmallCom::addRequestParallel(command);
          }
        }
      }
    }
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createLevelup(const ParamObj &paramObj) {
  int party = GfObjUtil::getPartyID(paramObj.m_GF_OBJ_HANDLE);
  if (party != -1) {
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(party);
    if (driver != unknown020) {
      u32 hp;
      {
        DataParamAcc acc(driver);
        hp = acc.getHp();
      }
      if (hp == 0) {
        return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
      }
    }
  }
#line 3739
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), !GfGameManager::isTalking());
  if (command != nullptr) {
    ParamObj object = paramObj;
    command->unknown002(object, 0.0f, CV_FIELD_UNKNOWN_8, CV_PRIO_UNKNOWN_3);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createExitInn() {
  u32 party = unknown005();
  if (party != 0xffffffff) {
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(party);
    GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(party, -1);
    u32 hp = DataParamAcc(driver).getHp();
    if (hp != 0 && GfGameObj::isValidGameObj(blade, true, nullptr)) {
#line 3766
      SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
      if (command != nullptr) {
        ParamObj bladeObject = {blade, 0, 0};
        command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_9, CV_PRIO_UNKNOWN_1);
        ParamObj driverObject = {driver, 0, 0};
        command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_9, CV_PRIO_UNKNOWN_1);
        command->unknownd0 = true;
        return GfReqSmallCom::addRequestParallel(command);
      }
    }
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createBladeSkill(u32 blade) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
  u32 creator = GfDataBlade::getCreator(blade);
  GF_SCOM_HANDLE *handle = reinterpret_cast<GF_SCOM_HANDLE *>(-1);
#line 3784
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
  if (command != nullptr) {
    ParamObj bladeObject = {unknown020, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_10, CV_PRIO_UNKNOWN_1);
    ParamObj creatorObject = {unknown020, OBJECT_TYPE_PC, creator};
    command->unknown002(creatorObject, 0.0f, CV_FIELD_UNKNOWN_10, CV_PRIO_UNKNOWN_1);
    handle = GfReqSmallCom::addRequestParallel(command);
  }
  return handle;
}

void SCOM_FIELD_VOICE::createPartyIn(u32 id) {
  u32 type = OBJECT_TYPE_BLADE;
  if (id <= 1000) {
    type = OBJECT_TYPE_PC;
  }
  ParamObj object = {unknown020, type, id};
  if (id == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_11, CV_PRIO_UNKNOWN_1);
}

void SCOM_FIELD_VOICE::createPartyOut(u32 id) {
  u32 type = OBJECT_TYPE_BLADE;
  if (id <= 1000) {
    type = OBJECT_TYPE_PC;
  }
  ParamObj object = {unknown020, type, id};
  if (id == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_12, CV_PRIO_UNKNOWN_1);
}

void SCOM_FIELD_VOICE::createMercenariesIn(u32 blade) {
  ParamObj object = {unknown020, OBJECT_TYPE_BLADE, blade};
  if (blade == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_13, CV_PRIO_UNKNOWN_1);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createMercenariesLeader(u32 blade) {
  ParamObj object = {unknown020, OBJECT_TYPE_BLADE, blade};
  if (blade == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_14, CV_PRIO_UNKNOWN_1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createMercenariesStart(u32 blade) {
  u32 driver = unknown006();
#line 3844
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
  if (command != nullptr) {
    ParamObj bladeObject = {unknown020, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_15, CV_PRIO_UNKNOWN_1);
    if (driver != 0) {
      ParamObj driverObject = {unknown020, OBJECT_TYPE_PC, driver};
      command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_15, CV_PRIO_UNKNOWN_1);
    }
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createMercenariesEnd(u32 blade) {
  u32 driver = unknown006();
#line 3861
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
  if (command != nullptr) {
    ParamObj bladeObject = {unknown020, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_16, CV_PRIO_UNKNOWN_1);
    if (driver != 0) {
      ParamObj driverObject = {unknown020, OBJECT_TYPE_PC, driver};
      command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_16, CV_PRIO_UNKNOWN_1);
    }
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createMercenariesResult(u32 blade) {
  u32 driver = unknown006();
#line 3878
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
  if (command != nullptr) {
    ParamObj bladeObject = {unknown020, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_17, CV_PRIO_UNKNOWN_1);
    if (driver != 0) {
      ParamObj driverObject = {unknown020, OBJECT_TYPE_PC, driver};
      command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_17, CV_PRIO_UNKNOWN_1);
    }
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createReleaseBlade(u32 blade) {
  ParamObj object = {unknown020, OBJECT_TYPE_BLADE, blade};
  if (blade == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_18, CV_PRIO_UNKNOWN_1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createSkipTravel(bool isStart) {
  CV_FIELD voice = CV_FIELD_UNKNOWN_19;
  if (!isStart) {
    voice = CV_FIELD_UNKNOWN_20;
  }
  u32 party = unknown005();
  if (party != 0xffffffff) {
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(party);
    GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(party, -1);
#line 3909
    SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
    if (command != nullptr) {
      ParamObj driverObject = {driver, 0, 0};
      command->unknown002(driverObject, 0.0f, voice, CV_PRIO_UNKNOWN_1);
      ParamObj bladeObject = {blade, 0, 0};
      command->unknown002(bladeObject, 0.0f, voice, CV_PRIO_UNKNOWN_1);
      GfReqSmallCom::addRequestParallel(command);
    }
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createRestart(CV_FIELD voice) {
  u32 party = unknown005();
  if (party != 0xffffffff) {
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(party);
    GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(party, -1);
    u32 hp = DataParamAcc(driver).getHp();
    if (hp != 0 && GfGameObj::isValidGameObj(driver, true, nullptr)) {
#line 3937
      SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
      if (command != nullptr) {
        ParamObj driverObject = {driver, 0, 0};
        command->unknown002(driverObject, 0.5f, voice, CV_PRIO_UNKNOWN_1);
        ParamObj bladeObject = {blade, 0, 0};
        command->unknown002(bladeObject, 0.5f, voice, CV_PRIO_UNKNOWN_1);
        return GfReqSmallCom::addRequestParallel(command);
      }
    }
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createEnemy(CV_FIELD voice) {
  u32 party = unknown005();
  if (party == 0xffffffff) {
    return nullptr;
  }
  ParamObj object = {GfGameParty::getHandleDriver(party), 0, 0};
  if (object.m_GF_OBJ_HANDLE == unknown020) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  return GfFieldVoice::playVoice(object, voice, CV_PRIO_UNKNOWN_1);
}

void SCOM_FIELD_VOICE::createAchievement(u32 blade, u32 achievement) {
  ParamObj object = {unknown020, OBJECT_TYPE_BLADE, blade};
  if (achievement == 9) {
    GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_26, 0, 0, CV_PRIO_UNKNOWN_1);
  } else {
    GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_25, achievement / 3, achievement % 3, CV_PRIO_UNKNOWN_1);
  }
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createAchievementAll(u32 blade) {
  u32 driver = GfDataBlade::getSetDriver(blade);
  if (driver == 0) {
    driver = GfDataBlade::getCreator(blade);
  }
#line 3982
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
  if (command != nullptr) {
    ParamObj bladeObject = {unknown020, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_27, CV_PRIO_UNKNOWN_1);
    if (driver != 0) {
      ParamObj driverObject = {unknown020, OBJECT_TYPE_PC, driver};
      command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_27, CV_PRIO_UNKNOWN_1);
    }
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_FIELD_VOICE::createEngage(u32 blade) {
  ParamObj object = {unknown020, OBJECT_TYPE_BLADE, blade};
  GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_36, 0, 0, CV_PRIO_UNKNOWN_1);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createFavorite(u32 id, FAVORITE favorite) {
  DataParamAcc acc(GfDataBlade::isBladeID(id) ? OBJECT_TYPE_BLADE : OBJECT_TYPE_PC, id, GIMMICK_TYPE_UNKNOWN_0);
  if (!acc.isValid()) {
    return nullptr;
  }
  u32 type = acc.getObjType();
  ParamObj object = {unknown020, type, id};
  if (acc.getObjType() == OBJECT_TYPE_BLADE && GfDataBlade::isCommonBlade(id)) {
    u32 middle = 2;
    switch (favorite) {
    case FAVORITE_UNKNOWN_0:
    case FAVORITE_UNKNOWN_1:
      middle = 0;
      break;
    case FAVORITE_UNKNOWN_2:
    case FAVORITE_UNKNOWN_3:
      middle = 2;
      break;
    }
    u32 category = FAVORITE_CATEGORY_UNKNOWN_20;
    switch (favorite) {
    case FAVORITE_UNKNOWN_2:
    case FAVORITE_UNKNOWN_3: {
      u32 item = GfDataBlade::getFavorite(id, favorite);
      // The game drops the result (bl at 0x71005d04d8) and falls through to the category read.
      GfBdatItem::get()->getFavoriteCategory(item);
    }
    case FAVORITE_UNKNOWN_0:
    case FAVORITE_UNKNOWN_1:
      category = GfDataBlade::getFavorite(id, favorite);
      break;
    }
    u32 variation = GfDataItem::isFavoriteCategoryFood(category) ? 0 : 1;
    switch (favorite) {
    case FAVORITE_UNKNOWN_2:
    case FAVORITE_UNKNOWN_3:
      return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_29, middle, variation, CV_PRIO_UNKNOWN_1);
    case FAVORITE_UNKNOWN_0:
    case FAVORITE_UNKNOWN_1:
      return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_29, variation, middle, CV_PRIO_UNKNOWN_1);
    }
  } else if (favorite >= FAVORITE_UNKNOWN_2 && favorite <= FAVORITE_UNKNOWN_3) {
    return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_29, 2, favorite - FAVORITE_UNKNOWN_2, CV_PRIO_UNKNOWN_1);
  } else if (favorite >= FAVORITE_UNKNOWN_0 && favorite <= FAVORITE_UNKNOWN_1) {
    return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_29, favorite, 0, CV_PRIO_UNKNOWN_1);
  }
  return nullptr;
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createBadWeather() {
  if (!GfGameManager::isBattle()) {
    u32 party = unknown005();
    if (party != 0xffffffff) {
      GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(party);
      GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(party, -1);
      u32 hp = DataParamAcc(driver).getHp();
      if (hp != 0 && GfGameObj::isValidGameObj(blade, true, nullptr)) {
#line 4106
        SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
        if (command != nullptr) {
          ParamObj bladeObject = {blade, 0, 0};
          command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_30, CV_PRIO_UNKNOWN_1);
          ParamObj driverObject = {driver, 0, 0};
          command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_30, CV_PRIO_UNKNOWN_1);
          return GfReqSmallCom::addRequestParallel(command);
        }
      }
    }
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createTime(CV_FIELD voice) {
  if (!GfGameManager::isBattle()) {
    u32 party = unknown005();
    if (party != 0xffffffff) {
      GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(party);
      GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(party, -1);
      u32 hp = DataParamAcc(driver).getHp();
      if (hp != 0 && GfGameObj::isValidGameObj(driver, true, nullptr)) {
#line 4137
        SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
        if (command != nullptr) {
          ParamObj driverObject = {driver, 0, 0};
          command->unknown002(driverObject, 0.0f, voice, CV_PRIO_UNKNOWN_1);
          ParamObj bladeObject = {blade, 0, 0};
          command->unknown002(bladeObject, 0.0f, voice, CV_PRIO_UNKNOWN_1);
          return GfReqSmallCom::addRequestParallel(command);
        }
      }
    }
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_FIELD_VOICE::createQuest(CV_FIELD voice) {
  ParamObj object = {GfGameManager::getPartyLeaderDriver(), 0, 0};
  GfFieldVoice::playVoice(object, voice, CV_PRIO_UNKNOWN_1);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createFieldSkillStart(u32 blade, u32 skill) {
  const char *voice = GfDataBlade::getFieldSkillVoice(blade, skill);
  if (voice == nullptr) {
    return nullptr;
  }
  ParamObj object = {unknown020, OBJECT_TYPE_BLADE, blade};
  return GfGameVoice::playVoice(object, voice, CV_PRIO_UNKNOWN_1);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createFieldSkillClear(u32 skill) {
  QuestListAcc *questList = QuestListAcc::get();
  DataParamAcc acc(GfGameManager::getPartyLeaderDriver());
  u32 category = questList->getFLD_FieldSkillSettingSuccessVoiceCategory(skill);
  const char *voice = GfDataField::getFieldSkillVoice(acc.getValidDriverId(), category);
  GAME_VOICE_HANDLE *handle = nullptr;
  if (voice != nullptr) {
    handle = GfGameVoice::playVoice(GfGameManager::getPartyLeaderDriver(), voice, CV_PRIO_UNKNOWN_1);
  }
  return handle;
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createFieldSkillMiss(u32 skill) {
  QuestListAcc *questList = QuestListAcc::get();
  DataParamAcc acc(GfGameManager::getPartyLeaderDriver());
  u32 category = questList->getFLD_FieldSkillSettingMissVoiceCategory(skill);
  const char *voice = GfDataField::getFieldSkillVoice(acc.getValidDriverId(), category);
  GAME_VOICE_HANDLE *handle = nullptr;
  if (voice != nullptr) {
    handle = GfGameVoice::playVoice(GfGameManager::getPartyLeaderDriver(), voice, CV_PRIO_UNKNOWN_1);
  }
  return handle;
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createDriverKizuna(u32 driver) {
  if (driver - 1 > 5) {
    return nullptr;
  }
  int variation = ml::mtRand(3);
  return GfGameVoice::playVoice(OBJECT_TYPE_PC, driver, unknown007[driver - 1][variation], CV_PRIO_UNKNOWN_3);
}

bool GfReqSmallCom::isValid(GF_SCOM_HANDLE *handle) {
  if (handle != reinterpret_cast<GF_SCOM_HANDLE *>(-1)) {
    for (mm::mtl::FixedList<SCOM *, 1024>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
      if ((*it)->m_GF_SCOM_HANDLE == handle) {
        return true;
      }
    }
    for (mm::mtl::FixedList<SCOM *, 1024>::iterator it = unknown4828.begin(); it != unknown4828.end(); ++it) {
      if ((*it)->m_GF_SCOM_HANDLE == handle) {
        return true;
      }
    }
  }
  return false;
}

bool GfReqSmallCom::isExistCommand() {
  GfReqSmallCom *smallCom = get();
  if (smallCom->unknown08.size() != 0) {
    return true;
  }

  return smallCom->unknown4828.size() != 0;
}

bool GfReqSmallCom::isExistCommandWithoutParallel() { return get()->unknown08.size() != 0; }

bool GfReqSmallCom::isExistCommand(SCOM_TYPE type) {
  GfReqSmallCom *smallCom = get();
  for (mm::mtl::FixedList<SCOM *, 1024>::iterator it = smallCom->unknown08.begin(); it != smallCom->unknown08.end(); ++it) {
    if ((*it)->unknown18 == type) {
      return true;
    }
  }
  return false;
}

bool GfReqSmallCom::update(const fw::UpdateInfo &info, u16 priority) {
  for (mm::mtl::FixedList<SCOM *, 1024>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    if ((*it)->unknown10 == priority) {
      if ((*it)->exec(info)) {
        if (*it != nullptr) {
          delete *it;
          *it = nullptr;
        }
        unknown08.erase(it);
      }
      return false;
    }
  }
  return true;
}

void GfReqSmallCom::update(const fw::UpdateInfo &info) {
  unknownd870 = true;
  if (update(info, 0)) {
    if (update(info, 1)) {
      update(info, 2);
    }
  }
  updateParallel(info);
  for (mm::mtl::FixedList<SCOM *, 1024>::iterator it = unknown9048.begin(); it != unknown9048.end(); ++it) {
    unknown4828.push_back(*it);
  }
  unknown9048.clear();
  unknownd870 = false;
}

// Inferred role: names of the SCOM types, indexed by SCOM_TYPE (0x71011a0c30); original name unknown.
static const char *const unknown190[] = {
    "DESTROY_GAME_OBJ",
    "ADD_MONEY",
    "ADD_COIN",
    "ADD_ETHER",
    "ADD_EXP",
    "EXEC_LVUP",
    "MAXIMUM_HEAL",
    "ADD_WP",
    "ADD_SP",
    "ADD_IDEA",
    "ADD_IDEA_POINT",
    "ADD_DEVELOP",
    "LEVELUP_DEVELOP",
    "ADD_ITEM",
    "REMOVE_ITEM",
    "STOP_BATTLE",
    "WARP_POS",
    "OBJ_WARP_POS",
    "OBJ_COLI",
    "INTERVAL_SPEED",
    "GAME_SPEED",
    "DESTROY_GAME_OBJP",
    "CREATE_PARTY_OBJ",
    "DESTROY_PARTY_OBJ",
    "DESTROY_FIELD_OBJ",
    "DESTROY_MAP_OBJ",
    "CREATE_MAP_OBJ",
    "FADE",
    "LOADING",
    "SCRIPT",
    "RELOAD_BDAT",
    "RELOAD_TEXT",
    "CHANGE_LAYER",
    "COLI_CHAR_VALID",
    "ATTACH_WEAPON",
    "DETACH_WEAPON",
    "EXEC_MOUNT",
    "VALID_LOCAL_SPEED",
    "DESTROY_GMK_SET",
    "CREATE_GMK_SET",
    "OBJ_ALPHA",
    "QUEST_ORDER",
    "QUEST_REACH",
    "QUEST_GIMMICK",
    "QUEST_TALK",
    "QUEST_EVENT",
    "ACCESS_TARGET",
    "TARGET_UI",
    "SET_FLAG",
    "SET_CAMTYPE",
    "CHAR_DEAD",
    "CHAR_DMG",
    "CHANGE_BLADE",
    "PARTY_ADD",
    "EXEC_DRIVER_ARTS_LVUP",
    "ACHIEV_INC",
    "FIELD_SKILL",
    "PARTY_LEADER",
    "REBUILD",
    "ADD_MERCENARIES_POINT",
    "INC_MERCENARIES_LEVEL",
    "CHANGE_RIDE",
    "BATTLE_BGM",
    "FIELD_VOICE",
    "ADD_TRUST",
    "SET_TRUST",
    "ZONE",
    "OBJ_VFADE",
    "ITEM_USE",
    "ENBOOK_IN_BATTLE",
    "OBJ_VFADE_OFF",
    "ENBOOK_BOSS_TIME",
    "ENBOOK_DEFEAT_ENEMY",
    "ENBOOK_DEAD_PLAYER",
    "FSKILLMAX_FOR_DEBUG",
    "POPUP",
    "HOMURI",
    "DEAD_PARTICLE",
    "CURRENT_BLADE",
    "BC_PARTICLE",
    "MISSION_COMPLETE",
    "SET_BLADE",
    "NIA_BLADE",
};

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Draws the name of one command and returns the next row; its user is GfReqSmallCom::debugCommandDisp (0x71005d3f70). With the row as an `s16 y` local of the caller (`drawFont(0x100, y, ...);
// y += 18;`, also 47 instructions) InstCombine moves the 16 bit extension of the loop carried value to the loop header, before the node assertion (0x71005d3fd0), and the registers differ;
// the game extends the int row at the call (sxth w22 at 0x71005d3fec, after the assertion), which an inlined function taking an `s16` row gives.
static int drawCommandName(s16 y, const char *name) {
  fw::debug::drawFont(0x100, y, name);
  return y + 18;
}

void GfReqSmallCom::debugCommandDisp() {
  int y = GfInfo::m_nScreenH / 2;
  for (mm::mtl::FixedList<SCOM *, 1024>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    y = drawCommandName(y, unknown190[(*it)->unknown18]);
  }
}

GF_SCOM_HANDLE *SCOM_ADD_ITEM::create(u32 item, int num) {
  if (item != 0 && num != 0) {
#line 602
    SCOM_ADD_ITEM *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_ITEM(GfReqSmallCom::get()->allocate(), item, num, false);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_ITEM::createForBattle(u32 item, int num) {
  if (item != 0 && num != 0) {
#line 609
    SCOM_ADD_ITEM *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_ADD_ITEM(GfReqSmallCom::get()->allocate(), item, num, true);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_HOMURI_PARTS::create(u32 partyId, bool isVisible, f32 time) {
#line 4572
  SCOM_HOMURI_PARTS *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_HOMURI_PARTS(GfReqSmallCom::get()->allocate(), partyId, isVisible, time);
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_SCRIPT::exec(const fw::UpdateInfo &) {
  if (unknown20.empty()) {
    GfScriptManager::destroyScript(unknown1c);
    return true;
  }
  if (unknown44 == 0) {
    GfScriptManager::loadScript(unknown1c, unknown20.c_str());
    unknown44 = 1;
  }
  if (unknown44 == 1) {
    if (GfScriptManager::isScriptLoadError(unknown1c)) {
      return true;
    }
    if (!GfScriptManager::isScriptWaitStart(unknown1c)) {
      return false;
    }
    GfScriptManager::startScript(unknown1c);
    if (!unknown48) {
      return true;
    }
    unknown44 = 2;
  }
  if (unknown44 == 2 && GfScriptManager::isScriptActive(unknown1c)) {
    return false;
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_SCRIPT::create(u32 slot, const char *script, bool isWait) {
  mm::mtl::FixStr<32> name;
  if (script != nullptr) {
    name = util::getNoPathExtName(script).c_str();
  }
#line 1047
  SCOM_SCRIPT *command = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SCOM_SCRIPT(GfReqSmallCom::get()->allocate(), slot, name, isWait);
  return GfReqSmallCom::addRequestParallel(command);
}

} // namespace gf

template mm::mtl::FixedList<gf::SCOM *, 1024>::iterator mm::mtl::FixedList<gf::SCOM *, 1024>::erase(mm::mtl::FixedList<gf::SCOM *, 1024>::iterator);

template mm::mtl::PtrSingleton<gf::GfReqSmallCom>::~PtrSingleton();

template mm::mtl::PtrSingleton<gf::SCOM_PARTY_ADD>::~PtrSingleton();
