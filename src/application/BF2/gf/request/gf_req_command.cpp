#include "gf/request/gf_req_command.h"

#include "battle/utility_battle.h"
#include "fw/fw_update_info.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_fobj_manager.h"
#include "gf/game/gf_game_save.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/map/gf_map_manager.h"
#include "gf/request/gf_req_manager.h"
#include "gf/script/gf_script_manager.h"
#include "ml/time_count.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"

namespace gf {

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

u32 GfReqCommand::reqSave(SAVESLOT slot) {
#line 68
  unknown001 *param = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) unknown001();
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
  unknown001 *param = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) unknown001();
  param->unknown00 = SAVESLOT_NONE;
  return GfReqManager::addCommand(param, execSaveOption);
}

void GfReqCommand::execSaveOption(const GfReqParam *param) {
  GfGameSave save(static_cast<const unknown001 *>(param)->unknown00);
  save.execOptionSaveWithMicroThread();
}

u32 GfReqCommand::reqSoloParty(u32 driver) {
#line 95
  unknown002 *param = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) unknown002();
  param->unknown00 = driver;
  return GfReqManager::addCommand(param, execSoloParty);
}

void GfReqCommand::reqPartyBlade(u32 blade, u32 driver) {
#line 104
  unknown003 *param = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) unknown003();
  param->unknown00 = blade;
  param->unknown04 = driver;
  GfReqManager::addCommand(param, execPartyBlade);
}

void GfReqCommand::reqChangeAttribute(u32 objectType, u32 blade, u32 attribute) {
#line 113
  unknown004 *param = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) unknown004();
  param->unknown00 = objectType;
  param->unknown04 = blade;
  param->unknown08 = attribute;
  GfReqManager::addCommand(param, execChangeAttributeForDebug);
}

void GfReqCommand::execChangeAttributeForDebug(const GfReqParam *) {}

u32 GfReqCommand::reqWaitEvent(f32 time, GF_OBJ_HANDLE *handle) {
#line 125
  unknown005 *param = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) unknown005;
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
    if (!GfPause::isPause(PAUSE_BIT_FIELD_TIME)) {
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
  unknown006 *param = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) unknown006;
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
  unknown007 *param = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) unknown007;
  param->unknown00 = isTool;
  GfReqManager::addCommand(param, execToolMode);
}

void GfReqCommand::execToolMode(const GfReqParam *param) {
  if (static_cast<const unknown007 *>(param)->unknown00) {
    GfManager::setExec(EXEC_STATE_TOOL);
  } else {
    GfManager::setExec(EXEC_STATE_DEBUG);
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
  unknown008 *param = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) unknown008;
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

u32 GfReqCommand::reqDebugPartyNum(u32) { return 0xffffffff; }

void GfReqCommand::execPartyNumForDebug(const GfReqParam *) {}

u32 GfReqCommand::reqDebugPartyInBlade(bool) { return 0xffffffff; }

void GfReqCommand::execPartyInBladeForDebug(const GfReqParam *) {}

} // namespace gf
