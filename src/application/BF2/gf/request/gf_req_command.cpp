#include "gf/request/gf_req_command.h"

#include "battle/utility_battle.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_fobj_manager.h"
#include "gf/game/gf_game_load.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_ride.h"
#include "gf/game/gf_game_save.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/map/gf_map_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_manager.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_fade.h"
#include "gf/script/gf_script_manager.h"
#include "ml/time_count.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {
struct SDataOption;
struct SDataSave;

// Inferred role: parameter of the save requests; original type name unknown.
struct unknown001 : GfReqParam {
  SAVESLOT unknown00; // Inferred role: save slot; original member name unknown.
};

// Inferred role: parameter of the solo party request; original type name unknown.
struct unknown002 : GfReqParam {
  u32 unknown00; // Inferred role: driver; original member name unknown.
};

// Inferred role: parameter of the party blade request; original type name unknown.
struct unknown003 : GfReqParam {
  u32 unknown00; // Inferred role: blade; original member name unknown.
  u32 unknown04; // Inferred role: driver; original member name unknown.
};

// Inferred role: parameter of the change attribute request; original type name unknown.
struct unknown004 : GfReqParam {
  u32 unknown00; // Inferred role: object type; original member name unknown.
  u32 unknown04; // Inferred role: blade; original member name unknown.
  u32 unknown08; // Inferred role: attribute; original member name unknown.
};

// Inferred role: parameter of the wait event request; original type name unknown.
struct unknown005 : GfReqParam {
  f32 unknown00;            // Inferred role: time; original member name unknown.
  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
};

// Inferred role: parameter of the rebuild party weapon request; original type name unknown.
struct unknown014 : GfReqParam {
  u32 unknown00; // Inferred role: party; original member name unknown.
  int unknown04; // Inferred role: blade slot; original member name unknown.
};

// Inferred role: parameter of the player pause request; original type name unknown.
struct unknown006 : GfReqParam {
  f32 unknown00; // Inferred role: time; original member name unknown.
};

// Inferred role: parameter of the tool mode request; original type name unknown.
struct unknown007 : GfReqParam {
  bool unknown00; // Inferred role: tool mode; original member name unknown.
};

// Inferred role: parameter of the start script request; original type name unknown.
struct unknown008 : GfReqParam {
  mm::mtl::FixStr<32> unknown00; // Inferred role: script name; original member name unknown.
  u32 unknown24;                 // Inferred role: script slot; original member name unknown.
  bool unknown28;                // Inferred role: start; original member name unknown.
};

// Inferred role: parameter of the load request; original type name unknown.
struct unknown010 : GfReqParam {
  SAVESLOT unknown00;     // Inferred role: save slot; original member name unknown.
  SDataSave *unknown08;   // Inferred role: game data to load; original member name unknown.
  SDataOption *unknown10; // Inferred role: option data to load; original member name unknown.
};

// Inferred role: parameter of the change blade with blade set request; original type name unknown.
struct unknown011 : GfReqParam {
  u32 unknown00;  // Inferred role: party; original member name unknown.
  int unknown04;  // Inferred role: blade set; original member name unknown.
  bool unknown08; // Inferred role: force; original member name unknown.
};

// Inferred role: parameter of the change blade with blade request; original type name unknown.
struct unknown012 : GfReqParam {
  u32 unknown00; // Inferred role: party; original member name unknown.
  u32 unknown04; // Inferred role: blade; original member name unknown.
};

void GfMapjumpInfo::setupForSaveData(u32 mapjumpId, const mm::Vec3 &position, const mm::Vec3 &rotation, bool isStartChapterSave) {
  unknown00 = mapjumpId;
  unknown100 = true;
  f32 rotY = rotation.y;
  GfPartyPosInfo::unknown004 &pos = unknown40.unknown00[0];
  pos.unknown00.x = position.x;
  pos.unknown00.y = position.y;
  pos.unknown00.z = position.z;
  pos.unknown10 = rotY;
  pos.unknown14 = true;
  unknown101 = isStartChapterSave;
  unknown108 = 1;
}

RQ_SETUP_BLADE::RQ_SETUP_BLADE() : unknown00(0), unknown02(0) {
  for (u32 slot = 0; slot < 5; slot++) {
    unknown04[slot] = 0;
  }
}

void RQ_SETUP_PARTY::getAllBlade(mm::mtl::FixedVector<u32, 16> &blades) const {
  for (u32 index = 0; index < 10; index++) {
    const Member &member = unknown00[index];
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(member.unknown00);
    for (int slot = 0; slot < setBladeNum; slot++) {
      if (member.unknown08[slot] != 0) {
        blades.push_back(member.unknown08[slot]);
      }
    }
  }
}

// Inferred role: replaces an act blade by its common blade, copying the save data when the common one is not set up; original name unknown.
static u32 unknown009(u32 blade) {
  u32 commonBlade = GfDataBlade::getActBlade2CommonBlade(blade);
  if (commonBlade != blade) {
    SDataBlade &commonData = GfDataBlade::getSDataBlade(commonBlade);
    if (commonData.unknown06 == 0) {
      commonData = GfDataBlade::getSDataBlade(blade);
      commonData.unknown06 = commonBlade;
    }
    blade = commonBlade;
  }
  return blade;
}

void RQ_SETUP_PARTY::replaceActBlade() {
  if (unknownc8 == OBJECT_TYPE_BLADE) {
    unknowncc = unknown009(unknowncc);
  }
  if (unknownd0 == OBJECT_TYPE_BLADE) {
    unknownd4 = unknown009(unknownd4);
  }
  for (u32 index = 0; index < 10; index++) {
    u16 *blade = &unknown00[index].unknown08[0];
    for (u32 slot = 0; slot < 5; slot++, blade++) {
      *blade = unknown009(*blade);
    }
  }
}

u32 GfReqCommand::reqSave(SAVESLOT slot) {
#line 68
  unknown001 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown001();
  param->unknown00 = slot;
  return GfReqManager::addCommand(param, execSave);
}

void GfReqCommand::execSave(const GfReqParam *param) {
  GfGameSave save(static_cast<const unknown001 *>(param)->unknown00);
  save.execGameSaveWithMicroThread();
  save.execOptionSaveWithMicroThread();
}

u32 GfReqCommand::reqSaveOption() {
#line 76
  unknown001 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown001();
  param->unknown00 = SAVESLOT_UNKNOWN_FFFFFFFF;
  return GfReqManager::addCommand(param, execSaveOption);
}

void GfReqCommand::execSaveOption(const GfReqParam *param) {
  GfGameSave save(static_cast<const unknown001 *>(param)->unknown00);
  save.execOptionSaveWithMicroThread();
}

void GfReqCommand::reqLoad(SAVESLOT slot, SDataSave *saveData, SDataOption *optionData) {
#line 85
  unknown010 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown010;
  param->unknown00 = slot;
  param->unknown08 = saveData;
  param->unknown10 = optionData;
  GfReqManager::addCommand(param, execLoad);
}

void GfReqCommand::execLoad(const GfReqParam *param) {
  const unknown010 *load = static_cast<const unknown010 *>(param);
  GfGameLoad gameLoad(load->unknown00);
  gameLoad.execGameLoadWithMicroThread(*load->unknown08);
  if (load->unknown10 != nullptr) {
    gameLoad.execOptionLoadWithMicroThread(*load->unknown10);
  }
}

u32 GfReqCommand::reqSoloParty(u32 driver) {
#line 95
  unknown002 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown002();
  param->unknown00 = driver;
  return GfReqManager::addCommand(param, execSoloParty);
}

void GfReqCommand::reqPartyBlade(u32 blade, u32 driver) {
#line 104
  unknown003 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown003();
  param->unknown00 = blade;
  param->unknown04 = driver;
  GfReqManager::addCommand(param, execPartyBlade);
}

u32 GfReqCommand::reqRebuildPartyWeapon(u32 blade) {
#line 140
  unknown014 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown014;
  u32 partyId = GfGameParty::getPartyId(OBJECT_TYPE_BLADE, blade);
  if (partyId == PARTY_UNKNOWN_4294967295) {
    return 0xffffffff;
  }
  DataParamAcc acc(GfGameParty::getHandleDriver(partyId));
  int bladeNum = GfDataDriver::getMaxSetBladeNum(acc.getValidDriverId());
  int bladeSlot = -1;
  for (int slot = 0; slot < bladeNum; slot++) {
    if (acc.getBlade(slot, false) == blade) {
      bladeSlot = slot;
      break;
    }
  }
  if (bladeSlot < 0) {
    return 0xffffffff;
  }
  param->unknown00 = partyId;
  param->unknown04 = bladeSlot;
  return GfReqManager::addCommand(param, execRebuildPartyWeapon);
}

void GfReqCommand::reqChangeAttribute(u32 objectType, u32 blade, u32 attribute) {
#line 113
  unknown004 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown004();
  param->unknown00 = objectType;
  param->unknown04 = blade;
  param->unknown08 = attribute;
  GfReqManager::addCommand(param, execChangeAttributeForDebug);
}

void GfReqCommand::execChangeAttributeForDebug(const GfReqParam *) {}

u32 GfReqCommand::reqWaitEvent(f32 time, GF_OBJ_HANDLE *handle) {
#line 125
  unknown005 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown005;
  param->unknown00 = time;
  param->unknown08 = handle;
  return GfReqManager::addCommand(param, execWaitEvent);
}

void GfReqCommand::execWaitEvent(const GfReqParam *param) {
  ml::TimeCount timer;
  timer.start();
  while (!btl::Utility::IsEnableEventStart()) {
    GfSleep(1);
    if (timer.getSecLap() > 15.0f) {
      break;
    }
  }
  f32 remain = static_cast<const unknown005 *>(param)->unknown00 - 0.5f - timer.getSecLap();
  while (remain > 0.0f) {
    if (!GfPause::isPause(PAUSE_BIT_UNKNOWN_4)) {
      remain -= GfReqManager::getUpdateInfo()->unknown04;
    }
    GfSleep(1);
  }
  f32 elapsed = 0.0f;
  do {
    elapsed += GfReqManager::getUpdateInfo()->unknown04;
    if (elapsed > 1.5f) {
      elapsed = 1.5f;
    }
    GfFobjManager::get()->unknown907c = elapsed / 1.5f * 40.0f;
    GfFobjManager::get()->unknown9080 = true;
    GfSleep(1);
  } while (elapsed < 1.5f);
  GfFobjManager::get()->unknown907c = 1000.0f;
  GfFobjManager::get()->unknown9080 = false;
  GfSleep(1);
  GfFobjManager::get()->unknown907c = 0.0f;
  GfFobjManager::get()->unknown9080 = false;
}

u32 GfReqCommand::reqPlayerPause(f32 time) {
  if (GfReqManager::isExistCommand(execPlayerPause)) {
    return 0xffffffff;
  }
#line 804
  unknown006 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown006;
  param->unknown00 = time;
  return GfReqManager::addCommand(param, execPlayerPause);
}

void GfReqCommand::execPlayerPause(const GfReqParam *param) {
  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr) {
    f32 time = static_cast<const unknown006 *>(param)->unknown00;
    u32 pause = scene->createPlayerPause();
    while (time > 0.0f) {
      time -= GfReqManager::getUpdateInfo()->unknown04;
      GfSleep(1);
    }
    scene->destroyPlayerPause(pause);
  }
}

void GfReqCommand::reqToolMode(bool isTool) {
#line 835
  unknown007 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown007;
  param->unknown00 = isTool;
  GfReqManager::addCommand(param, execToolMode);
}

void GfReqCommand::execToolMode(const GfReqParam *param) {
  if (static_cast<const unknown007 *>(param)->unknown00) {
    GfManager::setExec(EXEC_STATE_UNKNOWN_4);
  } else {
    GfManager::setExec(EXEC_STATE_UNKNOWN_0);
  }
  u32 mapjumpId = GfMapManager::getMapJumpID();
  if (mapjumpId == 0) {
    mapjumpId = 1;
  }
  GfMapjumpInfo info(mapjumpId);
  GfPlayFactory::createMapjump(info);
}

void GfReqCommand::reqStartScript(u32 slot, const char *name, bool isStart) {
#line 861
  unknown008 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown008;
  param->unknown00 = name;
  param->unknown28 = isStart;
  param->unknown24 = slot;
  GfReqManager::addCommand(param, execStartScript);
}

void GfReqCommand::execStartScript(const GfReqParam *param) {
  const unknown008 *script = static_cast<const unknown008 *>(param);
  GfScriptManager::loadScript(script->unknown24, script->unknown00.c_str());
  if (script->unknown28) {
    GfScriptManager::startScript(script->unknown24);
  }
}

// Inferred role: replaces the blade of a party member by another blade set; original name unknown.
static void unknown013(u32 partyId, int bladeSet) {
  if (GfGameParty::getBladeSetId(partyId, -1) == bladeSet) {
    return;
  }
  GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(partyId);
  if (!GfObjUtil::isValid(driver)) {
    return;
  }
  GF_OBJ_HANDLE *newBlade = GfGameParty::getHandleBlade(partyId, bladeSet);
  if (!GfObjUtil::isValid(newBlade)) {
    return;
  }
  if (GfGameRide::testRideOn() && GfGameParty::getPartyId(GfGameParty::getLeader()) == partyId) {
    GfGameRide::setRideOn(false);
  }
  GF_OBJ_HANDLE *oldBlade = GfGameParty::getHandleBlade(partyId, -1);
  GfObjUtil::getMountHandle(driver, GFATTACH_UNKNOWN_0);
  {
    GfObjAcc oldAcc(oldBlade);
    GfObjAcc newAcc(newBlade);
    if (oldAcc.isRebuild() || newAcc.isRebuild()) {
      GfSleep(1);
    }
  }
  GfObjUtil::copyTransformToSetup(oldBlade, newBlade);
  GfGameObj::setupLeaveGameObj(oldBlade, 0.5f);
  GfGameObj::setupLeaveGameObjMount(oldBlade, GFATTACH_UNKNOWN_0, 0.5f);
  GfGameUtil::setBladeSelect(driver, bladeSet);
  GfSelectBlade::resetStartBattleSetId(partyId);
  GfObjSetupBlade *bladeSetup = GfObjUtil::getObjSetup<GfObjSetupBlade>(newBlade);
  if (bladeSetup != nullptr) {
    bladeSetup->unknown70 = false;
  }
  GfGameMount *mount = GfMountManager::getMount(GfObjUtil::getMountHandle(newBlade, GFATTACH_UNKNOWN_0));
  if (mount != nullptr) {
    for (u32 index = 0; index < HANDLE_UNKNOWN_10; index++) {
      GF_OBJ_HANDLE *handle = mount->unknown18->getCurrentHandles()[index];
      if (handle != unknown020) {
        GfObjSetupWeapon *weaponSetup = GfObjUtil::getObjSetup<GfObjSetupWeapon>(handle);
        if (weaponSetup != nullptr) {
          weaponSetup->unknown70 = false;
        }
      }
    }
  }
  GfGameObj::enterStayObject(newBlade);
  GfGameObj::enterStayObjectMount(newBlade, GFATTACH_UNKNOWN_0);
  GfGameObj::setupEnterGameObj(newBlade, 0.5f);
  GfGameObj::setupEnterGameObjMount(newBlade, GFATTACH_UNKNOWN_0, 0.5f);
  GfObjAcc acc(newBlade);
  acc.setAlphaNormal(1.0f);
  GfMountManager::setAlphaMount(newBlade, GFATTACH_UNKNOWN_0, 1.0f);
  GfSelectBlade::resetDefaultBladeForDebug(driver);
  while (!GfGameObj::isValidGameObj(newBlade, false, nullptr)) {
    GfSleep(1);
  }
}

u32 GfReqCommand::reqChangeBladeWithSetId(u32 partyId, int bladeSet, bool isForce) {
#line 221
  unknown011 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown011;
  param->unknown00 = partyId;
  param->unknown04 = bladeSet;
  param->unknown08 = isForce;
  return GfReqManager::addCommand(param, execChangeBladeWithSetId);
}

void GfReqCommand::execChangeBladeWithSetId(const GfReqParam *param) {
  const unknown011 *change = static_cast<const unknown011 *>(param);
  if (!change->unknown08) {
    f32 time = 0.0f;
    while (GfReqSmallCom::isExistCommandWithoutParallel()) {
      GfSleep(1);
      time += GfReqManager::getUpdateInfo()->unknown04;
      if (time >= 10.0f) {
        break;
      }
    }
  }
  unknown013(change->unknown00, change->unknown04);
}

void GfReqCommand::reqChangeBladeWithBladeId(u32 partyId, u32 blade) {
#line 232
  unknown012 *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) unknown012;
  param->unknown00 = partyId;
  param->unknown04 = blade;
  GfReqManager::addCommand(param, execChangeBladeWithBladeId);
}

void GfReqCommand::execChangeBladeWithBladeId(const GfReqParam *param) {
  const unknown012 *change = static_cast<const unknown012 *>(param);
  while (GfReqSmallCom::isExistCommandWithoutParallel()) {
    GfSleep(1);
  }
  GfSleep(30);
  int bladeSet = GfDataBlade::getDriverSetID(change->unknown04);
  unknown013(change->unknown00, bladeSet);
}

u32 GfReqCommand::reqChangeParty(const RQ_SETUP_PARTY_DRIVER &info) {
  RQ_SETUP_PARTY party;
  for (u32 index = 0; index < 10; index++) {
    u32 driver = info.unknown00[index];
    party.unknown00[index].unknown00 = driver;
    if (driver != 0) {
      DataParamAcc acc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
      party.unknown00[index].unknown04 = acc.getBladeSet(false);
      int bladeNum = GfDataDriver::getMaxSetBladeNum(driver);
      for (int slot = 0; slot < bladeNum; slot++) {
        party.unknown00[index].unknown08[slot] = acc.getBlade(slot, false);
      }
    }
  }
  party.unknowncc = info.unknown14;
  party.unknownc8 = OBJECT_TYPE_PC;
  return reqChangeParty(party);
}

u32 GfReqCommand::reqDestroyGf() {
#line 756
  GfReqParam *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfReqParam;
  u32 handle = GfReqManager::addCommand(param, execDestroyGf);
  GfReqManager::terminateCommand();
  return handle;
}

void GfReqCommand::execDestroyGf(const GfReqParam *) {
  SCOM_FADE::create(1, 30, mm::Col4::black);
  GfSleep(30);
  RQ_SETUP_PARTY party;
  SCOM_DESTROY_PARTY_OBJ::create(party);
  while (GfGameParty::isExistObj()) {
    GfSleep(1);
  }
  GfObjManager *objManager = GfObjManager::get();
  if (objManager != nullptr) {
    for (int layer = 12; layer >= 0; layer--) {
      objManager->destroyLayerObj(layer);
      while (objManager->isExistLayerObj(layer)) {
        GfSleep(1);
      }
    }
    objManager = GfObjManager::get();
    if (objManager != nullptr) {
      objManager->destroyAllObj(false);
      while (objManager->isExistGfObj(false)) {
        GfSleep(1);
      }
    }
  }
}

u32 GfReqCommand::reqDebugPartyNum(u32) { return 0xffffffff; }

void GfReqCommand::execPartyNumForDebug(const GfReqParam *) {}

u32 GfReqCommand::reqDebugPartyInBlade(bool) { return 0xffffffff; }

void GfReqCommand::execPartyInBladeForDebug(const GfReqParam *) {}

} // namespace gf
