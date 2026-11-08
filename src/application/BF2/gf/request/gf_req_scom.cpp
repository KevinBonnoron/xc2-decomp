#include "gf/request/gf_req_scom.h"

#include <math.h>

#include "framework/lang_util.h"
#include "fw/fw_bdat_manager.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_data_field.h"
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
#include "gf/map/gf_map_manager.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/object/gf_menu_obj_popup.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/scom/gf_scom_enbook.h"
#include "gf/scom/gf_scom_fade.h"
#include "gf/scom/gf_scom_obj.h"
#include "gf/util/gf_item_util.h"
#include "gmk/gmk_manager.h"
#include "ml/rand.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "ui/ui_manager.h"
#include "ui/ui_util.h"

namespace gf {

static const u32 unknown001 = 4; // Inferred role: object attribute bit cleared when destroying a game object; original name unknown.
static const u32 unknown002 = 4; // Inferred role: game speed layer set by the speed command; original name unknown.
static const u32 unknown003 = 1; // Inferred role: game speed layer set by the local speed command; original name unknown.

SCOM::SCOM(GF_SCOM_HANDLE *handle, SCOM_TYPE type, SCOM_EXEC exec, u16 unknown10) : unknown08(handle), unknown10(unknown10), unknown14(exec), unknown18(type) {}

GF_OBJ_HANDLE *SCOM::getObjHandle() const { return INVALID_HANDLE; }

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
  return scom->unknown08;
}

GF_SCOM_HANDLE *GfReqSmallCom::addRequestParallel(SCOM *scom) {
  GfReqSmallCom *smallCom = get();
  if (!smallCom->unknownd870) {
    smallCom->unknown4828.push_back(scom);
  } else {
    smallCom->unknown9048.push_back(scom);
  }
  return scom->unknown08;
}

bool SCOM_ENBOOK_IN_BATTLE::exec(const fw::UpdateInfo &) {
  GfDataEnBook::setAttackFlag(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_IN_BATTLE::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4274
  SCOM_ENBOOK_IN_BATTLE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_IN_BATTLE(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_BOSS_TIME::exec(const fw::UpdateInfo &) {
  GfDataEnBook::setClearNamedTime(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_BOSS_TIME::create(GF_OBJ_HANDLE *handle, u32 time) {
  DataParamAcc acc(handle);
#line 4289
  SCOM_ENBOOK_BOSS_TIME *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_BOSS_TIME(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0, time);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_DEFEAT_ENEMY::exec(const fw::UpdateInfo &) {
  GfDataEnBook::incDefeatNum(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_DEFEAT_ENEMY::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4304
  SCOM_ENBOOK_DEFEAT_ENEMY *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEFEAT_ENEMY(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_DEAD_PLAYER::exec(const fw::UpdateInfo &) {
  GfDataEnBook::incDeadNum(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_DEAD_PLAYER::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4319
  SCOM_ENBOOK_DEAD_PLAYER *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEAD_PLAYER(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
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
    SCOM_MISSION_COMPLETE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_MISSION_COMPLETE(GfReqSmallCom::get()->allocate(), mission);
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
    SCOM_ADD_TRUST *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_TRUST(GfReqSmallCom::get()->allocate(), blade, point);
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
    SCOM_SET_TRUST_FOR_DEBUG *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SET_TRUST_FOR_DEBUG(GfReqSmallCom::get()->allocate(), blade, point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_TARGET_UI::exec(const fw::UpdateInfo &) {
  GfGameManager::setTargetUI(unknown20);
  return true;
}

void SCOM_TARGET_UI::create(GF_OBJ_HANDLE *target) {
#line 1942
  SCOM_TARGET_UI *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_TARGET_UI(GfReqSmallCom::get()->allocate(), target);
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_REFRESH_COMPASS::SCOM_REFRESH_COMPASS(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown28(3) {}

GF_SCOM_HANDLE *SCOM_REFRESH_COMPASS::create() {
  if (get() == nullptr) {
#line 4841
    SCOM_REFRESH_COMPASS *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_REFRESH_COMPASS(GfReqSmallCom::get()->allocate());
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
  SCOM_FSKILLMAX_FOR_DEBUG *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FSKILLMAX_FOR_DEBUG(GfReqSmallCom::get()->allocate());
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_SOLO_REX::SCOM_SOLO_REX(GF_SCOM_HANDLE *handle, bool isSolo) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(isSolo) {}

bool SCOM_SOLO_REX::exec(const fw::UpdateInfo &) {
  for (u32 i = 0; i < BLADE_COUNT; i++) {
    u32 blade = GfDataBlade::getBladeID(i);
    if (blade == 0) {
      continue;
    }
    u32 creator = GfDataBlade::getCreator(blade);
    if (creator == 0 || creator == DRIVER_REX) {
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
  SCOM_SOLO_REX *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SOLO_REX(GfReqSmallCom::get()->allocate(), isSolo);
  return GfReqSmallCom::addRequest(command);
}

SCOM_CURRENT_BLADE::SCOM_CURRENT_BLADE(GF_SCOM_HANDLE *handle, u32 blade) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(blade) {}

bool SCOM_CURRENT_BLADE::exec(const fw::UpdateInfo &) {
  int slot = GfDataBlade::getDriverSetID(unknown1c);
  u32 driver = GfDataBlade::getSetDriver(unknown1c);
  if (slot >= 0 && slot < static_cast<int>(SET_BLADE_NUM_MAX) && driver != 0) {
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
  SCOM_CURRENT_BLADE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_CURRENT_BLADE(GfReqSmallCom::get()->allocate(), blade);
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
  SCOM_ZONE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ZONE(GfReqSmallCom::get()->allocate(), map);
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
  SCOM_LEVELUP_DEVELOP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_LEVELUP_DEVELOP(GfReqSmallCom::get()->allocate());
  GfReqSmallCom::addRequestParallel(command);
}

// Inferred helper: quaternion of the Euler angles; original name unknown. Evidence: inlined in both SCOM_OBJ_WARP_POS::create overloads taking a position and a rotation.
static inline mm::Quat unknown004(mm::Vec3 rotation) {
  f32 sinX = sinf(rotation.x * 0.5f);
  f32 cosX = cosf(rotation.x * 0.5f);
  f32 sinY = sinf(rotation.y * 0.5f);
  f32 cosY = cosf(rotation.y * 0.5f);
  f32 sinZ = sinf(rotation.z * 0.5f);
  f32 cosZ = cosf(rotation.z * 0.5f);
  mm::Quat quat;
  quat.x = sinX * cosY * cosZ + cosX * sinY * sinZ;
  quat.y = cosX * sinY * cosZ - sinX * cosY * sinZ;
  quat.z = cosX * cosY * sinZ - sinX * sinY * cosZ;
  quat.w = cosX * cosY * cosZ + sinX * sinY * sinZ;
  return quat;
}

GF_SCOM_HANDLE *SCOM_OBJ_WARP_POS::create(GF_OBJ_HANDLE *handle, const mm::Vec3 &position, const mm::Vec3 &rotation, bool isFollow) {
  fw::Transform transform;
  transform.unknown00 = position;
  transform.unknown10 = unknown004(rotation);
#line 629
  SCOM_OBJ_WARP_POS *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(GfReqSmallCom::get()->allocate(), handle, transform, isFollow);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_OBJ_WARP_POS::create(const mm::Vec3 &position, const mm::Vec3 &rotation, bool isFollow) {
  fw::Transform transform;
  transform.unknown00 = position;
  transform.unknown10 = unknown004(rotation);
#line 637
  SCOM_OBJ_WARP_POS *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(GfReqSmallCom::get()->allocate(), GfGameManager::getControlMover(), transform, isFollow);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_OBJ_WARP_POS::create(GF_OBJ_HANDLE *handle, const fw::Transform &transform, bool isFollow) {
#line 642
  SCOM_OBJ_WARP_POS *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(GfReqSmallCom::get()->allocate(), handle, transform, isFollow);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_OBJ_WARP_POS::create(const fw::Transform &transform, bool isFollow) {
#line 647
  SCOM_OBJ_WARP_POS *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(GfReqSmallCom::get()->allocate(), GfGameManager::getControlMover(), transform, isFollow);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_GAME_OBJ::exec(const fw::UpdateInfo &) {
  GfGameObj::destroyGameObjWithAttribute(unknown20, unknown28, unknown2c);
  return true;
}

void SCOM_DESTROY_GAME_OBJ::create(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute) {
  GfObjAcc acc(handle);
  acc.setFlag(OBJ_FLAG_UI_HIDDEN, true);
  acc.setAttribute(acc.getAttribute() & ~unknown001);
#line 692
  SCOM_DESTROY_GAME_OBJ *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_GAME_OBJ(GfReqSmallCom::get()->allocate(), handle, fadeTime, attribute);
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_OBJ_VFADE_OFF::SCOM_OBJ_VFADE_OFF(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_67, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}

bool SCOM_OBJ_VFADE_OFF::exec(const fw::UpdateInfo &) {
  GfObjUtil::setVolumeFadeUserFlag(unknown20, false);
  return true;
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE_OFF::create(GF_OBJ_HANDLE *handle) {
  if (handle != INVALID_HANDLE) {
#line 1305
    SCOM_OBJ_VFADE_OFF *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE_OFF(GfReqSmallCom::get()->allocate(), handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_WP::exec(const fw::UpdateInfo &) {
  if (unknown30 == unknown004_3) {
    GfGameUtil::addWpForObject(unknown20_int, unknown2c, unknown28);
    return true;
  }
  GfObjAcc acc(unknown20);
  u32 driverId = acc.getType() == OBJECT_TYPE_DRIVER ? acc.getDriverId() : 0;
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
    SCOM_ADD_WP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_WP(GfReqSmallCom::get()->allocate(), INVALID_HANDLE, weaponPoint, weaponType, unknown004_0);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_WP::createForReserve(int weaponPoint) {
  if (weaponPoint != 0) {
#line 313
    SCOM_ADD_WP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_WP(GfReqSmallCom::get()->allocate(), INVALID_HANDLE, weaponPoint, 0, unknown004_2);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_WP::createForObject(GF_OBJ_HANDLE *handle, int weaponPoint, u32 weaponType) {
  if (weaponPoint != 0) {
#line 320
    SCOM_ADD_WP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_WP(GfReqSmallCom::get()->allocate(), handle, weaponPoint, weaponType, unknown004_1);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_WP::createForBdatid(int driver, int weaponPoint, u32 weaponType) {
  if (weaponPoint != 0) {
#line 327
    SCOM_ADD_WP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_WP(GfReqSmallCom::get()->allocate(), driver, weaponPoint, weaponType, unknown004_3);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_SP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::addSP(driverId, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_SP::create(GF_OBJ_HANDLE *handle, int skillPoint) {
  if (skillPoint != 0) {
#line 348
    SCOM_ADD_SP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_SP(GfReqSmallCom::get()->allocate(), skillPoint, 0, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_SP::create(u32 driver, int skillPoint) {
  if (skillPoint != 0) {
#line 353
    SCOM_ADD_SP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_SP(GfReqSmallCom::get()->allocate(), skillPoint, driver, INVALID_HANDLE);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_IDEA::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::addIdeaPoint(driverId, unknown24, unknown1c);
  return true;
}

bool SCOM_EXEC_DRIVER_ARTS_LVUP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::execDriverArtsLevelUp(driverId, unknown24, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_DRIVER_ARTS_LVUP::create(u32 level, u32 arts, GF_OBJ_HANDLE *handle) {
  if (level != 0) {
#line 265
    SCOM_EXEC_DRIVER_ARTS_LVUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_DRIVER_ARTS_LVUP(GfReqSmallCom::get()->allocate(), level, 0, arts, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_EXEC_DRIVER_ARTS_LVUP::create(u32 level, u32 arts, u32 driver) {
  if (level != 0) {
#line 270
    SCOM_EXEC_DRIVER_ARTS_LVUP *command =
        new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_DRIVER_ARTS_LVUP(GfReqSmallCom::get()->allocate(), level, driver, arts, INVALID_HANDLE);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_EXEC_LVUP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::execLevelUp(driverId, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_LVUP::create(u32 level, GF_OBJ_HANDLE *handle) {
  if (level != 0) {
#line 238
    SCOM_EXEC_LVUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_LVUP(GfReqSmallCom::get()->allocate(), level, 0, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_EXEC_LVUP::create(u32 level, u32 driver) {
  if (level != 0) {
#line 243
    SCOM_EXEC_LVUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_LVUP(GfReqSmallCom::get()->allocate(), level, driver, INVALID_HANDLE);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

SCOM_OBJ_ALPHA::SCOM_OBJ_ALPHA(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time, f32 alpha)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_40, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(time), unknown2c(0.0f), unknown30(alpha), unknown34(-1.0f) {}

bool SCOM_OBJ_ALPHA::exec(const fw::UpdateInfo &info) {
  GfObjAcc acc(unknown20);
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
  if (handle != INVALID_HANDLE) {
#line 1268
    SCOM_OBJ_ALPHA *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_ALPHA(GfReqSmallCom::get()->allocate(), handle, time, alpha);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_OBJ_ALPHA::createWeapon(GF_OBJ_HANDLE *handle, f32 time, f32 alpha) {
  if (handle != INVALID_HANDLE) {
    GfWeapon *weapon = GfMountManager::getAppendHandles(handle, GFATTACH_WEAPON);
    if (weapon != nullptr) {
      for (u32 i = 0; i < 10; i++) {
        GF_OBJ_HANDLE *target = weapon->getCurrentHandles()[i];
        if (target != INVALID_HANDLE) {
#line 1282
          SCOM_OBJ_ALPHA *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_ALPHA(GfReqSmallCom::get()->allocate(), target, time, alpha);
          GfReqSmallCom::addRequestParallel(command);
        }
      }
    }
  }
}

bool SCOM_ADD_EXP::exec(const fw::UpdateInfo &) {
  u32 driver = unknown20;
  if (driver == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driver = 0;
    } else {
      GfObjAcc acc(unknown28);
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
    SCOM_ADD_EXP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_EXP(GfReqSmallCom::get()->allocate(), exp, 0, handle, false);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_EXP::createBattleExp(u32 exp, u32 driver) {
  if (exp != 0) {
#line 209
    SCOM_ADD_EXP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_EXP(GfReqSmallCom::get()->allocate(), exp, driver, INVALID_HANDLE, false);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_EXP::createInnExp(u32 exp) {
  if (exp != 0) {
#line 214
    SCOM_ADD_EXP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_EXP(GfReqSmallCom::get()->allocate(), exp, 0, INVALID_HANDLE, true);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

SCOM_POPUP::SCOM_POPUP(GF_SCOM_HANDLE *handle, GfMenuObjPopup::OpenParam &param) : SCOM(handle, SCOM_TYPE_UNKNOWN_75, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(param) {}

bool SCOM_POPUP::exec(const fw::UpdateInfo &) {
  if (unknown1c.unknown00 == GfMenuObjPopup::unknown005_7 && GfGameManager::isBusyBladeCreateEvent()) {
    return false;
  }
  GfMenuObjPopup::open(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_POPUP::createQuest(QuestID quest) {
  if (!GfGameManager::isStartGame()) {
    if (QuestListAcc::get()->getListVisible(quest) != 0) {
      GfMenuObjPopup::OpenParam param = {};
      param.unknown00 = GfMenuObjPopup::unknown005_9;
      param.unknown04 = quest.unknown00;
#line 4407
      SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
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
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createMercenaryAdd(u32 mission) {
  if (mission != 0 && !GfGameManager::isStartGame()) {
    GfMenuObjPopup::OpenParam param = {};
    param.unknown00 = GfMenuObjPopup::unknown005_7;
    param.unknown04 = GfDataMercenaries::getMissionMapID(mission);
#line 4433
    SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
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
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createAffinity(u32 blade, u32 driver, u32 trustRank) {
  if (GfGameManager::isStartGame()) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_5, blade, driver, trustRank};
#line 4458
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createAchievement(u32 blade, u32 achievement, u32 level) {
  GfGameManager::isStartGame();
  if (GfMenuObjUtil::getMenuCondition(15) && !GfGameUtil::setupSaveAchievementPopup(blade, achievement, level)) {
    GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_4, blade, achievement, level};
#line 4476
    SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
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
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createPouch(u32 driver, u32 item, u32 unknown3) {
  bool isStart = GfGameManager::isStartGame();
  if (driver != 0 && !isStart) {
    GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_2, driver, item, unknown3};
#line 4503
    SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
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
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_POPUP::createCrystalOK(u32 item) {
  if (GfGameManager::isStartGame()) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  GfMenuObjPopup::OpenParam param = {GfMenuObjPopup::unknown005_10, item, 0, 0};
#line 4529
  SCOM_POPUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_POPUP(GfReqSmallCom::get()->allocate(), param);
  return GfReqSmallCom::addRequestParallel(command);
}

SCOM_BC_PARTICLE::SCOM_BC_PARTICLE(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_77, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(0), unknown30(time), unknown34(time) {
  DataParamAcc acc(target);
  unknown2c = acc.getAttribute(-1, false);
  if (acc.getObjType() == OBJECT_TYPE_BLADE && acc.isValid() && acc.getBdatId() == 0x3f1) {
    unknown2c = 0x11;
  }
}

bool SCOM_BC_PARTICLE::exec(const fw::UpdateInfo &info) {
  GfObjAcc acc(unknown20);
  if (acc.getObj() != nullptr) {
    u32 attribute = unknown2c;
    switch (unknown28) {
    case 0:
      unknown28 = 1;
      GfObjUtil::setDeadParticle(unknown20, true, attribute, acc.getAlpha());
      return false;
    case 1:
      if (unknown30 > 0.0f) {
        f32 remain = unknown30 - info.unknown04;
        if (remain <= 0.0f) {
          remain = 0.0f;
        }
        unknown30 = remain;
        f32 ratio = remain / unknown34;
        GfObjUtil::setDeadParticle(unknown20, ratio > 0.0f, attribute, ratio);
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
  SCOM_BC_PARTICLE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_BC_PARTICLE(GfReqSmallCom::get()->allocate(), handle, time);
  return GfReqSmallCom::addRequestParallel(command);
}

SCOM_DEAD_PARTICLE::SCOM_DEAD_PARTICLE(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, u32 attribute, f32 time)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_77, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(0), unknown2c(attribute), unknown30(time), unknown34(time) {}

bool SCOM_DEAD_PARTICLE::exec(const fw::UpdateInfo &info) {
  GfObjAcc acc(unknown20);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return true;
  }
  GfComAsm *comAsm = obj->getComponent<GfComAsm>();
  switch (unknown28) {
  case 0:
    if (comAsm != nullptr && !comAsm->isEnd(ANIM_LAYER_BASE) && !comAsm->isLoop(ANIM_LAYER_BASE)) {
      return false;
    }
    unknown28 = 1;
    GfObjUtil::setDeadParticle(unknown20, true, unknown2c, acc.getAlpha());
    GfObjUtil::setDeadParticle(GfMountManager::getHandle(unknown20, GFATTACH_WEAPON, OPTMNT_BLADE), true, unknown2c, 1.0f);
    return false;
  case 1:
    if (unknown30 > 0.0f) {
      f32 remain = unknown30 - info.unknown04;
      if (remain <= 0.0f) {
        remain = 0.0f;
      }
      unknown30 = remain;
      f32 ratio = remain / unknown34;
      GF_OBJ_HANDLE *blade = GfMountManager::getHandle(unknown20, GFATTACH_WEAPON, OPTMNT_BLADE);
      GfObjUtil::setDeadParticle(unknown20, ratio > 0.0f, unknown2c, ratio);
      GfObjUtil::setDeadParticle(blade, ratio > 0.0f, unknown2c, ratio);
    }
    DataParamAcc param(unknown20);
    if (param.getHp() != 0) {
      GF_OBJ_HANDLE *blade = GfMountManager::getHandle(unknown20, GFATTACH_WEAPON, OPTMNT_BLADE);
      GfObjUtil::setDeadParticle(unknown20, false, unknown2c, acc.getAlpha());
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
  SCOM_DEAD_PARTICLE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DEAD_PARTICLE(GfReqSmallCom::get()->allocate(), handle, attribute, time);
  return GfReqSmallCom::addRequestParallel(command);
}

mm::mtl::FixedQueue<SCOM_PARTY_ADD::unknown002, 16> SCOM_PARTY_ADD::s_info;

void SCOM_PARTY_ADD::addBlade(u32 blade, u32 driver, int slot) {
  if (blade == 0) {
    return;
  }
  unknown002 info = {GfDataBlade::getActBlade2CommonBlade(blade), driver, slot, true, false, false, unknown001_1};
  s_info.push(info);
  create();
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
  DataParamAcc acc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
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
  if (driver == DRIVER_NIA) {
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
        DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, DRIVER_REX, GIMMICK_TYPE_NONE);
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
  SCOM_EXEC_CURRENT_BLADE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_CURRENT_BLADE(GfReqSmallCom::get()->allocate(), blade);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_PARTY_LEADER::exec(const fw::UpdateInfo &) {
  if (unknown1c == OBJECT_TYPE_BLADE) {
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
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
  SCOM_PARTY_LEADER *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_PARTY_LEADER(GfReqSmallCom::get()->allocate(), objectType, leader);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_SET_BLADE::exec(const fw::UpdateInfo &) {
  RQ_SETUP_PARTY info;
  GfGameParty::getCurrentPartyInfo(info);
  u32 partyId = GfDataParty::getDriverPartyID(unknown1c.unknown00);
  RQ_SETUP_PARTY::Member &member = info.unknown00[partyId];
  member.unknown12 = true;
  member.unknown08 = unknown1c.unknown04;
  member.unknown04 = -1;
  u32 current = unknown1c.unknown02;
  u32 blade = GfDataDriver::getBlade(member.unknown00, -1);
  for (int slot = 0; slot < 5; slot++) {
    if (unknown1c.unknown04[slot] == unknown1c.unknown02) {
      member.unknown04 = slot;
      break;
    }
  }
  if (member.unknown04 < 0) {
    for (int slot = 0; slot < 5; slot++) {
      if (unknown1c.unknown04[slot] == blade) {
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
      info.unknownc8 = OBJECT_TYPE_DRIVER;
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
  SCOM_SET_BLADE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SET_BLADE(GfReqSmallCom::get()->allocate(), info);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_NIA_BLADE::exec(const fw::UpdateInfo &) {
  if (!unknown1c) {
    RQ_SETUP_PARTY info;
    GfGameParty::getCurrentPartyInfo(info);
    if (GfDataBlade::getSetDriver(BLADE_UNKNOWN_1011) == DRIVER_REX) {
      GfDataDriver::unsetBlade(BLADE_UNKNOWN_1011);
    }
    if (GfDataDriver::isActivateUnuse(DRIVER_NIA)) {
      GfDataDriver::setActivateReserver(DRIVER_NIA, PARTY_ID_NONE);
    }
    if (GfDataBlade::isActivateUnuse(BLADE_UNKNOWN_1011)) {
      return true;
    }
    GfDataDriver::equipDriverBladeFromReserverBlade(DRIVER_NIA);
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
    for (u32 index = PARTY_MEMBER_NUM; index < 5; index++) {
      RQ_SETUP_PARTY::Member &member = info.unknown00[index];
      if (member.unknown00 == 0) {
        member.unknown00 = DRIVER_NIA;
        for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(DRIVER_NIA); slot++) {
          member.unknown08[slot] = GfDataDriver::getBlade(DRIVER_NIA, slot);
        }
        isSet = true;
        break;
      }
    }
    if (!isSet) {
      for (u32 index = 0; index < PARTY_MEMBER_NUM; index++) {
        RQ_SETUP_PARTY::Member &member = info.unknown00[index];
        if (member.unknown00 == 0) {
          member.unknown00 = DRIVER_NIA;
          for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(DRIVER_NIA); slot++) {
            member.unknown08[slot] = GfDataDriver::getBlade(DRIVER_NIA, slot);
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
    if (GfDataDriver::isActivateUnuse(DRIVER_NIA)) {
      return true;
    }
    for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(DRIVER_NIA); slot++) {
      u32 blade = GfDataDriver::getBlade(DRIVER_NIA, slot);
      if (blade != 0) {
        GfDataDriver::unsetBlade(blade);
      }
    }
    GfDataDriver::setActivateUnuse(DRIVER_NIA);
    for (u32 index = 0; index < 10; index++) {
      RQ_SETUP_PARTY::Member &member = info.unknown00[index];
      if (member.unknown00 == DRIVER_NIA) {
        member.unknown00 = 0;
        for (u32 slot = 0; slot < SET_BLADE_NUM_MAX; slot++) {
          member.unknown08[slot] = 0;
        }
      }
      member.unknown12 = true;
    }
    if (info.unknown00[0].unknown00 == 0 && info.unknown00[1].unknown00 == 0 && info.unknown00[2].unknown00 == 0) {
      for (u32 index = PARTY_MEMBER_NUM; index < 10; index++) {
        if (info.unknown00[index].unknown00 == DRIVER_REX) {
          info.unknown00[0] = info.unknown00[index];
          info.unknown00[0].unknown12 = true;
          info.unknown00[index].clear();
        }
      }
    }
    info.unknownc8 = OBJECT_TYPE_DRIVER;
    info.unknowncc = 0;
    info.unknowne0 = position;
    GfReqCommand::reqChangeParty(info);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_NIA_BLADE::create(bool isBlade) {
#line 2730
  SCOM_NIA_BLADE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_NIA_BLADE(GfReqSmallCom::get()->allocate(), isBlade);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_QUEST_REACH::checkEventScequence() const {
  if (!GfGameManager::isInnerState(GF_STATE_EVENT)) {
    return true;
  }
  if (GfGameEvent::get() != nullptr && GfGameEvent::get()->unknown1914 >= GfGameEvent::PLAY_STATE_PLAY) {
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
  SCOM_QUEST_REACH *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(GfReqSmallCom::get()->allocate(), unknown001_1, landmark);
  GfReqSmallCom::addRequestParallel(command);
  createArriveLandmark(landmark);
}

void SCOM_QUEST_REACH::createArriveLandmark(u32 landmark) {
#line 1730
  SCOM_QUEST_REACH *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(GfReqSmallCom::get()->allocate(), unknown001_2, landmark);
  GfReqSmallCom::addRequestParallel(command);
}

void SCOM_QUEST_REACH::createArrivePlace(u32 place) {
#line 1736
  SCOM_QUEST_REACH *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(GfReqSmallCom::get()->allocate(), unknown001_3, place);
  GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createDoor(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_DOOR, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1780
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_DOOR, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createElevator(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_ELEVATOR, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1799
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_ELEVATOR, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createJump(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_JUMP, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1818
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_JUMP, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createMapGimmick(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_MAP_GIMMICK, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1837
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_MAP_GIMMICK, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createWarp(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_WARP, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1855
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_WARP, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createSalvage(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_SALVAGE, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1874
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_SALVAGE, gimmick, delay);
  return GfReqSmallCom::addRequest(command);
}

GF_SCOM_HANDLE *SCOM_QUEST_GIMMICK::createTresure(u32 gimmick, f32 delay) {
  if (delay > 0.0f) {
    GfPlayFactory::createGimmickTaskComplete(gmk::GMK_TYPE_TBOX, gimmick, delay);
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
#line 1893
  SCOM_QUEST_GIMMICK *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(GfReqSmallCom::get()->allocate(), gmk::GMK_TYPE_TBOX, gimmick, delay);
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
    SCOM_ADD_MONEY *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_MONEY(GfReqSmallCom::get()->allocate(), money);
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
    SCOM_ADD_COIN *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_COIN(GfReqSmallCom::get()->allocate(), coin);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_MAXIMUM_HEAL::exec(const fw::UpdateInfo &) {
  GfObj *obj = GfObjUtil::getObj(unknown20);
  if (obj != nullptr) {
    DataParamAcc acc(unknown20);
    {
      MsgObjectMaxHp message(acc.getHpMax(false));
      obj->sendMessage(obj, message);
    }
    {
      MsgObjectHealHp message(0, HEAL_TYPE_FULL);
      obj->sendMessage(obj, message);
    }
  }
  return true;
}

void SCOM_MAXIMUM_HEAL::create(GF_OBJ_HANDLE *handle) {
#line 162
  SCOM_MAXIMUM_HEAL *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_MAXIMUM_HEAL(GfReqSmallCom::get()->allocate(), handle);
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ADD_DEVELOP::exec(const fw::UpdateInfo &) {
  GfGameUtil::addDevelopPoint(unknown20, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_DEVELOP::create(u32 nation, u32 point) {
  if (nation != 0 && point != 0) {
#line 409
    SCOM_ADD_DEVELOP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_DEVELOP(GfReqSmallCom::get()->allocate(), nation, point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_ADD_DEVELOP::createGmk(u32 fieldZone, u32 point) { create(GfDataMap::getFieldZoneId(fieldZone), point); }

bool SCOM_ACCESS_TARGET::exec(const fw::UpdateInfo &) {
  GfGameManager::setAccessTarget(unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_ACCESS_TARGET::create(GF_OBJ_HANDLE *target) {
#line 1925
  SCOM_ACCESS_TARGET *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ACCESS_TARGET(GfReqSmallCom::get()->allocate(), target);
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
  SCOM_SET_FLAG *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SET_FLAG(GfReqSmallCom::get()->allocate(), size, index, value);
  return GfReqSmallCom::addRequest(command);
}

SCOM_CHAR_DEAD::SCOM_CHAR_DEAD(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, const MsgObjectNotifyDead &message)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_50, SCOM_EXEC_UNKNOWN_0, 1), unknown28(DEAD_TYPE_UNKNOWN_1, nullptr) {
  unknown20 = target;
  unknown28 = message;
  unknown28.unknown10 = nullptr;
}

bool SCOM_CHAR_DEAD::exec(const fw::UpdateInfo &) {
  GfObjAcc acc(unknown20);
  GfObjAcc killerAcc(unknown28.unknown18);
  if (unknown20 != unknown28.unknown18) {
    GfGameParty::getPartyId(unknown20);
  }
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    if (!GfGameManager::isPlayerDeadSequence()) {
      GfQuestTask::incSuppressEnemy(acc.getEnArrangeId());
      GfGameUtil::incEnemySuppress(acc.getEnArrangeId());
    }
    if (GfGameScene::get() != nullptr) {
      GfGameScene::get()->setEnemyDead(unknown20);
    }
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_CHAR_DEAD::create(GF_OBJ_HANDLE *target, const MsgObjectNotifyDead &message) {
  GfObjAcc acc(target);
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    if (message.unknown08 == DEAD_TYPE_EMERGENCY_ESCAPE) {
      DataParamAcc paramAcc(target);
      if (paramAcc.getHp() == 0) {
        return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
      }
      SCOM_DESTROY_GAME_OBJ::create(target, 0.5f, 0);
    }
    SCOM_ACHIEV_INC::createKillEnemy(message.unknown18);
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
    damage.unknown10 = message.unknown18;
    GfGameScene::get()->addDamage(target, damage);
  }
  GfGameObj::addCharDeadMessage(target, message);
#line 2163
  SCOM_CHAR_DEAD *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_CHAR_DEAD(GfReqSmallCom::get()->allocate(), target, message);
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
  SCOM_GAME_SPEED *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_GAME_SPEED(GfReqSmallCom::get()->allocate(), speed);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_INTERVAL_SPEED::exec(const fw::UpdateInfo &) {
  GfGameSpeed::setIntervalSpeed(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_INTERVAL_SPEED::create(f32 speed, f32 time) {
#line 661
  SCOM_INTERVAL_SPEED *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_INTERVAL_SPEED(GfReqSmallCom::get()->allocate(), speed, time);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_SET_CAMTYPE::exec(const fw::UpdateInfo &) {
  GfGameCamera::setCameraControlType(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_CAMTYPE::create(int type) {
#line 1996
  SCOM_SET_CAMTYPE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SET_CAMTYPE(GfReqSmallCom::get()->allocate(), type);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_QUEST_EVENT::exec(const fw::UpdateInfo &) {
  GfQuestTask::completeEventTask(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_QUEST_EVENT::create(u32 event) {
#line 1908
  SCOM_QUEST_EVENT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_EVENT(GfReqSmallCom::get()->allocate(), event);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_QUEST_ORDER::exec(const fw::UpdateInfo &) {
  GfQuestManager::openOrder(unknown1c, false);
  return true;
}

GF_SCOM_HANDLE *SCOM_QUEST_ORDER::create(QuestID quest) {
#line 1688
  SCOM_QUEST_ORDER *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_ORDER(GfReqSmallCom::get()->allocate(), quest);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ITEM_USE::exec(const fw::UpdateInfo &) {
  GfQuestTask::completeItemUseTask(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_ITEM_USE::create(u32 item, u32 count) {
#line 1751
  SCOM_ITEM_USE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ITEM_USE(GfReqSmallCom::get()->allocate(), item, count);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_PARTY_OBJ::exec(const fw::UpdateInfo &) {
  if (!unknown1c) {
    unknown1c = true;
    GfGameUnit::destroyParty(unknown20, &unknown1c0);
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
  SCOM_DESTROY_PARTY_OBJ *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_PARTY_OBJ(GfReqSmallCom::get()->allocate(), info);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_FIELD_OBJ::exec(const fw::UpdateInfo &) {
  GfFieldManager::destroyObj();
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_FIELD_OBJ::create() {
#line 898
  SCOM_DESTROY_FIELD_OBJ *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_FIELD_OBJ(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_MAP_OBJ::exec(const fw::UpdateInfo &) {
  GfMapManager::destroyObj();
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_MAP_OBJ::create() {
#line 914
  SCOM_DESTROY_MAP_OBJ *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_MAP_OBJ(GfReqSmallCom::get()->allocate());
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
  SCOM_CREATE_MAP_OBJ *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_CREATE_MAP_OBJ(GfReqSmallCom::get()->allocate(), mapJump, map);
  return GfReqSmallCom::addRequest(command);
}

SCOM_FADE::unknown001 SCOM_FADE::s_fades[GfMenuFade::FADE_COUNT];
GF_SCOM_HANDLE *SCOM_FADE::s_hCreatedReq = reinterpret_cast<GF_SCOM_HANDLE *>(-1);

bool SCOM_FADE::exec(const fw::UpdateInfo &) {
  if (!GfMenuFade::isInitialized()) {
    return false;
  }
  for (u32 i = 0; i < GfMenuFade::FADE_COUNT; i++) {
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
    SCOM_FADE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FADE(GfReqSmallCom::get()->allocate());
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
  GfEvent::get()->unknown002(RELOAD_BDAT_ALL, GfDataBdat::getReloadCount());
  return true;
}

GF_SCOM_HANDLE *SCOM_RELOAD_BDAT::create() {
#line 1078
  SCOM_RELOAD_BDAT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_RELOAD_BDAT(GfReqSmallCom::get()->allocate());
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
  GfEvent::get()->unknown002(RELOAD_BDAT_ALL, GfDataBdat::getReloadCount());
  return true;
}

GF_SCOM_HANDLE *SCOM_RELOAD_TEXT::create(fw::LangType type) {
  if (fw::LangUtil::getLangType() == type) {
    return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  }
  fw::LangUtil::setLangType(type);
#line 1120
  SCOM_RELOAD_TEXT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_RELOAD_TEXT(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_STOP_LAYER::exec(const fw::UpdateInfo &) {
  GfGameUtil::changeStopLayer(unknown20, unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_STOP_LAYER::create(GF_OBJ_HANDLE *target, bool stop) {
#line 1136
  SCOM_STOP_LAYER *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_STOP_LAYER(GfReqSmallCom::get()->allocate(), target, stop);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_SET_IDEA_POINT_FOR_DEBUG::exec(const fw::UpdateInfo &) {
  GfGameUtil::setIdeaPointForDebug(unknown20, unknown24, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_IDEA_POINT_FOR_DEBUG::create(u32 driver, u32 idea, int point) {
  if (point != 0) {
#line 394
    SCOM_SET_IDEA_POINT_FOR_DEBUG *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SET_IDEA_POINT_FOR_DEBUG(GfReqSmallCom::get()->allocate(), driver, idea, point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_BATTLE_BGM::exec(const fw::UpdateInfo &) { return true; }

GF_SCOM_HANDLE *SCOM_BATTLE_BGM::create(u32 bgm) {
  GfFieldBgm::get()->setRscBattleBgmID(bgm);
#line 3473
  SCOM_BATTLE_BGM *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_BATTLE_BGM(GfReqSmallCom::get()->allocate(), bgm);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_COLI_CHAR_VALID::exec(const fw::UpdateInfo &) {
  GfObjAcc acc(unknown20);
  acc.setCollisionChar(unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_COLI_CHAR_VALID::create(GF_OBJ_HANDLE *target, bool isEnable) {
#line 1151
  SCOM_COLI_CHAR_VALID *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_COLI_CHAR_VALID(GfReqSmallCom::get()->allocate(), target, isEnable);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_CREATE_GMK_SET::exec(const fw::UpdateInfo &) {
  GfFieldGimmick::createGmkSet(unknown1c);
  GfAutoTalkManager::get()->create();
  return true;
}

GF_SCOM_HANDLE *SCOM_CREATE_GMK_SET::create(u32 gimmickSet) {
#line 1226
  SCOM_CREATE_GMK_SET *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_CREATE_GMK_SET(GfReqSmallCom::get()->allocate(), gimmickSet);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_GMK_SET::exec(const fw::UpdateInfo &) {
  GfFieldGimmick::disposeGmkSet(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_GMK_SET::create(u32 gimmickSet) {
#line 1210
  SCOM_DESTROY_GMK_SET *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_GMK_SET(GfReqSmallCom::get()->allocate(), gimmickSet);
  return GfReqSmallCom::addRequest(command);
}

SCOM_FIELD_SKILL::SCOM_FIELD_SKILL(GF_SCOM_HANDLE *handle, u32 fieldSkill, u32 blade) : SCOM(handle, SCOM_TYPE_UNKNOWN_55, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(fieldSkill), unknown20(blade) {}

bool SCOM_FIELD_SKILL::exec(const fw::UpdateInfo &) {
  if (unknown20 == 0) {
    if (!GfGameManager::isControlFree()) {
      return false;
    }
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
      DataParamAcc acc(OBJECT_TYPE_DRIVER, GfGameParty::getDriverBdatId(partyId), GIMMICK_TYPE_NONE);
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
    SCOM_FIELD_SKILL *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_SKILL(GfReqSmallCom::get()->allocate(), fieldSkill, 0);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_SKILL::createWithBlade(u32 fieldSkill, u32 blade) {
  if (fieldSkill != 0) {
#line 3331
    SCOM_FIELD_SKILL *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_SKILL(GfReqSmallCom::get()->allocate(), fieldSkill, blade);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_REBUILD::exec(const fw::UpdateInfo &) {
  GfObjUtil::rebuild(unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_REBUILD::create(GF_OBJ_HANDLE *target) {
#line 3402
  SCOM_REBUILD *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_REBUILD(GfReqSmallCom::get()->allocate(), target);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ADD_MERCENARIES_POINT::exec(const fw::UpdateInfo &) {
  GfGameMercenaries::addPoint(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_MERCENARIES_POINT::create(u32 point) {
  if (point != 0) {
#line 446
    SCOM_ADD_MERCENARIES_POINT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_MERCENARIES_POINT(GfReqSmallCom::get()->allocate(), point);
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
  SCOM_SET_MERCENARIES_LEVEL *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SET_MERCENARIES_LEVEL(GfReqSmallCom::get()->allocate(), level);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_EXEC_MOUNT::exec(const fw::UpdateInfo &) {
  GfMountManager::execMount(unknown20, GFATTACH_WEAPON, unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_MOUNT::create(GF_OBJ_HANDLE *target, OPTMNT mountType) {
#line 1165
  SCOM_EXEC_MOUNT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_MOUNT(GfReqSmallCom::get()->allocate(), target, mountType);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_RESET_MOUNT::exec(const fw::UpdateInfo &) {
  GfMountManager::resetMount(unknown20, GFATTACH_WEAPON, unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_RESET_MOUNT::create(GF_OBJ_HANDLE *target, OPTMNT mountType) {
#line 1178
  SCOM_RESET_MOUNT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_RESET_MOUNT(GfReqSmallCom::get()->allocate(), target, mountType);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_VALID_LOCAL_SPEED::exec(const fw::UpdateInfo &) {
  GfGameUtil::changeStopLayer(unknown20, unknown2c);
  if (unknown28 >= 0.0f) {
    GfGameSpeed::setLayerSpeed(unknown003, unknown28);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_VALID_LOCAL_SPEED::create(GF_OBJ_HANDLE *target, bool stop, f32 speed) {
#line 1195
  SCOM_VALID_LOCAL_SPEED *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_VALID_LOCAL_SPEED(GfReqSmallCom::get()->allocate(), target, stop, speed);
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
  SCOM_LOADING *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_LOADING(GfReqSmallCom::get()->allocate(), type, isDisp);
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
  SCOM_STOP_BATTLE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_STOP_BATTLE(GfReqSmallCom::get()->allocate());
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
  SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), stats, count, blade);
  GfReqSmallCom::addRequestParallel(command);
}

void SCOM_ACHIEV_INC::createParty(u32 stats, int count) {
#line 2790
  SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), stats, count, 0);
  GfDataBlade::getListPartyAll(command->unknown28);
  GfReqSmallCom::addRequestParallel(command);
}

GF_SCOM_HANDLE *SCOM_ACHIEV_INC::createCurrentBlade(GF_OBJ_HANDLE *handle, u32 stats, int count) {
  DataParamAcc acc(handle);
  u32 blade = acc.getBlade(-1, false);
  GF_SCOM_HANDLE *scom = reinterpret_cast<GF_SCOM_HANDLE *>(-1);
  if (blade != 0 && !GfDataBlade::isDummyBlade(blade)) {
#line 2810
    SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), stats, count, blade);
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
    SCOM_ACHIEV_INC *total = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), 0x62, 1, acc.getBlade(-1, false));
    GfReqSmallCom::addRequestParallel(total);
#line 2859
    SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), stats, 1, acc.getBlade(-1, false));
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
      SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), 0x60, 1, acc.getBlade(-1, false));
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
    SCOM_ACHIEV_INC *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::get()->allocate(), 0x61, 1, acc.getBlade(-1, false));
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
  mm::mtl::FixedVector<u16, BLADE_COUNT> blades;
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
  } else if (type == OBJECT_TYPE_DRIVER) {
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
  } else if (type == OBJECT_TYPE_DRIVER) {
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
            DataParamAcc bladeAcc(OBJECT_TYPE_BLADE, driverAcc.getBlade(slot, false), GIMMICK_TYPE_NONE);
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
  mm::mtl::FixedVector<u16, BLADE_COUNT> blades;
  GfDataBlade::getListPartyAll(blades);
  GfAchievManager *manager = GfAchievManager::get();
  if (manager != nullptr) {
    manager->incAchievWithBlade(0x32, 1, blades);
  }
}

void SCOM_ACHIEV_INC::createCrystal() {
  mm::mtl::FixedVector<u16, BLADE_COUNT> blades;
  GfDataBlade::getListPartyAll(blades);
  GfAchievManager *manager = GfAchievManager::get();
  if (manager != nullptr) {
    manager->incAchievWithBlade(0x43, 1, blades);
  }
}

GAME_VOICE_HANDLE *SCOM_SALVAGE_VOICE::create(GF_OBJ_HANDLE *handle, CV_SALVAGE voice) { return GfSalvageVoice::playVoice(handle, voice); }

GAME_VOICE_HANDLE *SCOM_SALVAGE_VOICE::createResult(GF_OBJ_HANDLE *handle, CV_SALVAGE_RESULT voice) { return GfSalvageVoice::playResultVoice(handle, voice); }

bool SCOM_SALVAGE_VOICE::isPlayEnd(GAME_VOICE_HANDLE *voice) { return GfGameVoice::getResult(voice) != VOICE_RESULT_PLAY; }

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
  case VOICE_RESULT_UNKNOWN_0:
    voice.unknown10 -= info.unknown04;
    if (voice.unknown10 > 0.0f) {
      return false;
    }
    if (!isStopVoice()) {
      voice.unknown20 = GfFieldVoice::playVoice(voice.unknown00, voice.unknown14, voice.unknown1c);
      if (voice.unknown20 != nullptr) {
        voice.unknown18 = VOICE_RESULT_PLAY;
        return false;
      }
    } else {
      voice.unknown20 = nullptr;
    }
    voice.unknown18 = VOICE_RESULT_UNKNOWN_3;
    break;
  case VOICE_RESULT_PLAY:
    if (isStopVoice() && voice.unknown20 != nullptr) {
      GfGameVoice::playStop(voice.unknown20);
      voice.unknown20 = nullptr;
    }
    voice.unknown18 = GfGameVoice::getResult(voice.unknown20);
    if (voice.unknown18 == VOICE_RESULT_PLAY) {
      return false;
    }
    break;
  }
  if (voice.unknown18 >= VOICE_RESULT_UNKNOWN_3) {
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
  if (paramObj.unknown00 == INVALID_HANDLE && paramObj.unknown0c == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  GfFieldVoice::playVoice(object, voice, priority);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createJump(const ParamObj &paramObj) {
  if (GfGameManager::getControlMover() == paramObj.unknown00 && GfGameManager::isControlFree()) {
    SCOM_ACHIEV_INC::addTotalCount(2, 1);
    SCOM_ACHIEV_INC::create(2, 1, 0);
    if (ml::mtRandf1() < 0.4f) {
      return nullptr;
    }
    ParamObj object = paramObj;
    if (paramObj.unknown00 == INVALID_HANDLE && paramObj.unknown0c == 0) {
      object = ParamObj{GfGameManager::getControlMover(), 0, 0};
    }
    return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_0, CV_PRIO_UNKNOWN_1);
  }
  return nullptr;
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createHighLanding(const ParamObj &paramObj) {
  if (GfGameManager::getControlMover() == paramObj.unknown00) {
    ParamObj object = paramObj;
    if (paramObj.unknown00 == INVALID_HANDLE && paramObj.unknown0c == 0) {
      object = ParamObj{GfGameManager::getControlMover(), 0, 0};
    }
    return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_2, CV_PRIO_UNKNOWN_1);
  }
  return nullptr;
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createFallDead(const ParamObj &paramObj) {
  if (!GfGameManager::isEvent(false)) {
    ParamObj object = paramObj;
    if (paramObj.unknown00 == INVALID_HANDLE && paramObj.unknown0c == 0) {
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
          SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
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
          SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
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
  int party = GfObjUtil::getPartyID(paramObj.unknown00);
  if (party != -1) {
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(party);
    if (driver != INVALID_HANDLE) {
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
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), !GfGameManager::isTalking());
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
      SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
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
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  u32 creator = GfDataBlade::getCreator(blade);
  GF_SCOM_HANDLE *handle = reinterpret_cast<GF_SCOM_HANDLE *>(-1);
#line 3784
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
  if (command != nullptr) {
    ParamObj bladeObject = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_10, CV_PRIO_UNKNOWN_1);
    ParamObj creatorObject = {INVALID_HANDLE, OBJECT_TYPE_DRIVER, creator};
    command->unknown002(creatorObject, 0.0f, CV_FIELD_UNKNOWN_10, CV_PRIO_UNKNOWN_1);
    handle = GfReqSmallCom::addRequestParallel(command);
  }
  return handle;
}

void SCOM_FIELD_VOICE::createPartyIn(u32 id) {
  u32 type = OBJECT_TYPE_BLADE;
  if (id <= 1000) {
    type = OBJECT_TYPE_DRIVER;
  }
  ParamObj object = {INVALID_HANDLE, type, id};
  if (id == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_11, CV_PRIO_UNKNOWN_1);
}

void SCOM_FIELD_VOICE::createPartyOut(u32 id) {
  u32 type = OBJECT_TYPE_BLADE;
  if (id <= 1000) {
    type = OBJECT_TYPE_DRIVER;
  }
  ParamObj object = {INVALID_HANDLE, type, id};
  if (id == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_12, CV_PRIO_UNKNOWN_1);
}

void SCOM_FIELD_VOICE::createMercenariesIn(u32 blade) {
  ParamObj object = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
  if (blade == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_13, CV_PRIO_UNKNOWN_1);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createMercenariesLeader(u32 blade) {
  ParamObj object = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
  if (blade == 0) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  return GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_14, CV_PRIO_UNKNOWN_1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createMercenariesStart(u32 blade) {
  u32 driver = unknown006();
#line 3844
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
  if (command != nullptr) {
    ParamObj bladeObject = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_15, CV_PRIO_UNKNOWN_1);
    if (driver != 0) {
      ParamObj driverObject = {INVALID_HANDLE, OBJECT_TYPE_DRIVER, driver};
      command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_15, CV_PRIO_UNKNOWN_1);
    }
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createMercenariesEnd(u32 blade) {
  u32 driver = unknown006();
#line 3861
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
  if (command != nullptr) {
    ParamObj bladeObject = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_16, CV_PRIO_UNKNOWN_1);
    if (driver != 0) {
      ParamObj driverObject = {INVALID_HANDLE, OBJECT_TYPE_DRIVER, driver};
      command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_16, CV_PRIO_UNKNOWN_1);
    }
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_FIELD_VOICE::createMercenariesResult(u32 blade) {
  u32 driver = unknown006();
#line 3878
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
  if (command != nullptr) {
    ParamObj bladeObject = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_17, CV_PRIO_UNKNOWN_1);
    if (driver != 0) {
      ParamObj driverObject = {INVALID_HANDLE, OBJECT_TYPE_DRIVER, driver};
      command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_17, CV_PRIO_UNKNOWN_1);
    }
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GAME_VOICE_HANDLE *SCOM_FIELD_VOICE::createReleaseBlade(u32 blade) {
  ParamObj object = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
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
    SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
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
      SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
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
  if (object.unknown00 == INVALID_HANDLE) {
    object = ParamObj{GfGameManager::getControlMover(), 0, 0};
  }
  return GfFieldVoice::playVoice(object, voice, CV_PRIO_UNKNOWN_1);
}

void SCOM_FIELD_VOICE::createAchievement(u32 blade, u32 achievement) {
  ParamObj object = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
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
  SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), false);
  if (command != nullptr) {
    ParamObj bladeObject = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
    command->unknown002(bladeObject, 0.0f, CV_FIELD_UNKNOWN_27, CV_PRIO_UNKNOWN_1);
    if (driver != 0) {
      ParamObj driverObject = {INVALID_HANDLE, OBJECT_TYPE_DRIVER, driver};
      command->unknown002(driverObject, 0.0f, CV_FIELD_UNKNOWN_27, CV_PRIO_UNKNOWN_1);
    }
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_FIELD_VOICE::createEngage(u32 blade) {
  ParamObj object = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
  GfFieldVoice::playVoice(object, CV_FIELD_UNKNOWN_36, 0, 0, CV_PRIO_UNKNOWN_1);
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
        SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
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
        SCOM_FIELD_VOICE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(GfReqSmallCom::get()->allocate(), true);
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
  ParamObj object = {INVALID_HANDLE, OBJECT_TYPE_BLADE, blade};
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
  return GfGameVoice::playVoice(OBJECT_TYPE_DRIVER, driver, unknown007[driver - 1][variation], CV_PRIO_UNKNOWN_3);
}

bool GfReqSmallCom::isValid(GF_SCOM_HANDLE *handle) {
  if (handle != reinterpret_cast<GF_SCOM_HANDLE *>(-1)) {
    for (mm::mtl::FixedList<SCOM *, 1024>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
      if ((*it)->unknown08 == handle) {
        return true;
      }
    }
    for (mm::mtl::FixedList<SCOM *, 1024>::iterator it = unknown4828.begin(); it != unknown4828.end(); ++it) {
      if ((*it)->unknown08 == handle) {
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

} // namespace gf

template mm::mtl::FixedList<gf::SCOM *, 1024>::iterator mm::mtl::FixedList<gf::SCOM *, 1024>::erase(mm::mtl::FixedList<gf::SCOM *, 1024>::iterator);

template mm::mtl::PtrSingleton<gf::GfReqSmallCom>::~PtrSingleton();

template mm::mtl::PtrSingleton<gf::SCOM_PARTY_ADD>::~PtrSingleton();
