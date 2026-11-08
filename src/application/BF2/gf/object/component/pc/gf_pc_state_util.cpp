#include "gf/object/component/pc/gf_pc_state_util.h"

#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/pad/pad_relay_util.h"
#include "fw/fw_pad.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/game/gf_game_ride.h"
#include "gf/game/gf_game_target.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/object/component/behavior/plugin/gf_foot_ik_controller_plugin.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_distance_achiev_plugin.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "ml/dev_pad.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_mtl/vector.h"

namespace gf {
namespace pc {

u32 StateUtil::getFwPadKey(const char *name) {
  u32 key = 0;
  for (u32 padIndex = 0; padIndex < 5; padIndex++) {
    if (fw::PadRelayUtil::getFwPadKey(padIndex, name, 0, 0, &key)) {
      break;
    }
  }
  return key;
}

void StateUtil::resetCamera() { GfGamePlayerCamera::resetCamera(); }

bool StateUtil::isManualCamera() { return GfGamePlayerCamera::isManualCamera(); }

GF_OBJ_HANDLE *StateUtil::getTarget(const GfComBehaviorPc &behavior) { return behavior.unknown08->getComponent<GfComProperty>()->unknown18.get()->handle; }

void StateUtil::setTargetLock(bool isLock) { GfGameTarget::lockTarget(isLock); }

bool StateUtil::isBattle(GfComBehaviorPc &behavior) {
  if (GfGameManager::get() != nullptr) {
    return GfGameManager::isBattle();
  }
  return false;
}

void StateUtil::setEnableAgentField(GfComBehaviorPc &behavior, bool isEnable) { behavior.setEnableAgentField(isEnable); }

void StateUtil::setEnableAgentBattle(GfComBehaviorPc &behavior, bool isEnable) { behavior.setEnableAgentBattle(isEnable); }

void StateUtil::setEnableGravity(GfComBehaviorPc &behavior, bool isEnable) {
  GfComPropertyPc *property = behavior.getProperty();
  if (isEnable) {
    property->unknown110_3 = true;
  } else {
    property->unknown110_3 = false;
  }
}

bool StateUtil::testEnableGravity(GfComBehaviorPc &behavior) { return behavior.getProperty()->unknown110_3; }

void StateUtil::setEnvSensor(GfComBehaviorPc &behavior, u32 flags, bool isEnable) { behavior.unknown08->getComponent<GfComPropertyPc>()->setEnvSensorCheckFlags(flags, isEnable); }

bool StateUtil::testEnvSensor(GfComBehaviorPc &behavior, EnviromentSensor::Flag flag) { return behavior.unknown08->getComponent<GfComPropertyPc>()->testEnvSensorCheckFlags(flag); }

void StateUtil::setEnableAttach(GfComBehaviorPc &behavior, bool isEnable) {
  Plugin *plugin = behavior.unknown10.unknown28[12];
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtil::setEnableTimer(GfComBehaviorPc &behavior, bool isEnable) {
  Plugin *plugin = behavior.unknown10.unknown28[8];
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtil::setFallDamageDisable(GfComBehaviorPc &behavior, bool isDisable) {
  FallDamagePlugin *plugin = behavior.unknown001<FallDamagePlugin>(7);
  if (plugin != nullptr) {
    plugin->unknown1c = isDisable;
  }
}

void StateUtil::setEnableDownIK(GfComBehaviorPc &behavior, bool isEnable) {
  FootIkControllerPlugin *plugin = behavior.unknown001<FootIkControllerPlugin>(3);
  if (plugin != nullptr) {
    plugin->unknown1e = isEnable;
  }
}

void StateUtil::setEnableHeadDetectForSwitcher(GfComBehaviorPc &behavior, bool isEnable) {
  FootIkControllerPlugin *plugin = behavior.unknown001<FootIkControllerPlugin>(3);
  if (plugin != nullptr && plugin->unknown1c) {
    GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
    if (isEnable) {
      property->unknown111_6 = true;
    } else {
      property->unknown111_6 = false;
    }
  }
}

void StateUtil::switchPlacementIK(GfComBehaviorPc &behavior, bool isOn) {
  FootIkControllerPlugin *plugin = behavior.unknown001<FootIkControllerPlugin>(3);
  if (plugin != nullptr) {
    plugin->switchMode(isOn ? FootIkControllerPlugin::MODE_UNKNOWN_2 : FootIkControllerPlugin::MODE_UNKNOWN_1);
  }
}

void StateUtil::setActivateTimer(GfComBehaviorPc &behavior, TimerPlugin::TYPE type, bool isActive) {
  TimerPlugin *plugin = behavior.unknown001<TimerPlugin>(8);
  if (plugin != nullptr) {
    plugin->setActivateTimer(type, isActive);
  }
}

const f32 *StateUtil::getActivateTimer(GfComBehaviorPc &behavior, TimerPlugin::TYPE type) {
  TimerPlugin *plugin = behavior.unknown001<TimerPlugin>(8);
  if (plugin == nullptr) {
    return nullptr;
  }
  if (!plugin->unknown0c[type].unknown00) {
    return nullptr;
  }
  return &plugin->unknown0c[type].unknown04;
}

void StateUtil::setLipSpeed(GfComBehaviorPc &behavior, f32 speed) {
  LipSyncPlugin *plugin = behavior.unknown001<LipSyncPlugin>(2);
  if (plugin != nullptr) {
    plugin->setSpeed(speed);
  }
}

void StateUtil::setEnableFallDistChecker(GfComBehaviorPc &behavior, bool isEnable) {
  FallDistanceAchievPlugin *plugin = behavior.unknown001<FallDistanceAchievPlugin>(21);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtil::setEnableFootStep(GfComBehaviorPc &behavior, bool isEnable) {
  FootStepPlugin *plugin = behavior.unknown001<FootStepPlugin>(0);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

EnviromentSensor::GroundInfo *StateUtil::getGroundInfo(GfComBehaviorPc &behavior) {
  EnviromentSensor *sensor = behavior.unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
  return sensor->unknown24_0 ? &sensor->unknown30 : nullptr;
}

EnviromentSensor::unknown003 *StateUtil::getClimbWallInfo(GfComBehaviorPc &behavior) {
  EnviromentSensor *sensor = behavior.unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
  EnviromentSensor::unknown003 *info = &sensor->unknown150.unknown60;
  if (!sensor->unknown24_6 || !info->unknown24_4) {
    info = nullptr;
  }

  return info;
}

EnviromentSensor::GroundInfo *StateUtil::getClimbEndGroundInfo(GfComBehaviorPc &behavior) {
  EnviromentSensor *sensor = behavior.unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
  return sensor->unknown25_0 ? &sensor->unknown1f0 : nullptr;
}

EnviromentSensor::unknown003 *StateUtil::getDescendWallInfo(GfComBehaviorPc &behavior) {
  EnviromentSensor *sensor = behavior.unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
  return sensor->unknown24_7 ? &sensor->unknown260 : nullptr;
}

EnviromentSensor::unknown001 *StateUtil::getWaterInfo(GfComBehaviorPc &behavior) {
  EnviromentSensor *sensor = behavior.unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
  return sensor->unknown24_1 ? &sensor->unknown30.unknown70 : nullptr;
}

EnviromentSensor::unknown002 *StateUtil::getDeadPlaneInfo(GfComBehaviorPc &behavior) {
  EnviromentSensor *sensor = behavior.unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
  return sensor->unknown24_2 ? &sensor->unknown30.unknownb0 : nullptr;
}

bool StateUtil::isOnSlideGround(GfComBehaviorPc &behavior) {
  GfComPropertyPc *property = mm::mtl::dynamicCast<GfComPropertyPc>(behavior.unknown08->unknown38[GfComPropertyPc::COMPONENT_INDEX]);
  if (!property->unknown110_4) {
    return false;
  }

  EnviromentSensor *sensor = property->getEnvSensor();
  if (!sensor->unknown24_0) {
    return false;
  }

  return (sensor->unknown30.unknown30 >> 5) & 1;
}

GF_OBJ_HANDLE *StateUtil::getBuddyHandle(GfComBehaviorPc &behavior) {
  u32 playerId = behavior.getProperty()->unknown38;
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  if (formation == nullptr) {
    return INVALID_HANDLE;
  }

  u32 buddyId = (playerId & 1) != 0 ? playerId - 1 : playerId + 1;
  return formation->unknown1a0[buddyId].unknown08;
}

void StateUtil::sendMessageToBuddy(GfComBehaviorPc &behavior, fw::Message &message) {
  GfObj *obj = GfObjUtil::getObj(getBuddyHandle(behavior));
  if (obj != nullptr) {
    static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message);
  }
}

void StateUtil::notifyDead(GfComBehaviorPc &behavior, MsgObjectNotifyDead &message, bool isBroadcast) {
  GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
  if (!property->unknown111_3) {
    property->unknown111_3 = true;
  }
  if (property->unknown111_2 && isBroadcast) {
    if (!property->unknown111_4) {
      property->unknown111_4 = true;
      GfPlayFactory::createPlayerDead(static_cast<GfPlayerDead>(message.unknown08));
    } else if (message.unknown08 == PLAYER_DEAD_UNKNOWN_4) {
      GfPlayFactory::createPlayerDead(PLAYER_DEAD_UNKNOWN_4);
    }
  }
}

void StateUtil::notifyRevival(GfComBehaviorPc &behavior, MsgObjectNotifyHealHp &message) { behavior.getProperty()->unknown111_3 = false; }

bool StateUtil::sendMessageToRider(GfComBehaviorPc &behavior, fw::Message &message) {
  if (GfGameRide::isVehicle(static_cast<GfObj *>(behavior.unknown08)->unknownf8)) {
    GfObj *obj = GfObjUtil::getObj(getBuddyHandle(behavior));
    if (obj != nullptr) {
      return static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message);
    }
  }
  return false;
}

void StateUtil::broadcastDriver(GfComBehaviorPc &behavior, fw::Message &message) {
  behavior.unknown08->getComponent<GfComPropertyPc>();
  for (u32 i = 0; i < 3; i++) {
    GF_OBJ_HANDLE *handle = GfGameParty::getHandleDriver(i);
    if (handle != static_cast<GfObj *>(behavior.unknown08)->unknownf8) {
      GfObj *obj = GfObjUtil::getObj(handle);
      if (obj != nullptr) {
        static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message);
      }
    }
  }
}

void StateUtil::broadcastBlade(GfComBehaviorPc &behavior, fw::Message &message) {
  behavior.unknown08->getComponent<GfComPropertyPc>();
  for (u32 i = 0; i < 3; i++) {
    GF_OBJ_HANDLE *handle = GfGameParty::getHandleBlade(i, -1);
    if (handle != static_cast<GfObj *>(behavior.unknown08)->unknownf8) {
      GfObj *obj = GfObjUtil::getObj(handle);
      if (obj != nullptr) {
        static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message);
      }
    }
  }
}

void StateUtil::broadcastPlayer(GfComBehaviorPc &behavior, fw::Message &message) {
  broadcastDriver(behavior, message);
  broadcastBlade(behavior, message);
}

void StateUtil::broadcastMainChar(GfComBehaviorPc &behavior, fw::Message &message) {
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  behavior.unknown08->getComponent<GfComPropertyPc>();
  for (u32 i = 0; i < GfGamePlayerFormation::PLAYER_NUM; i++) {
    if (formation->unknown1a0[i].unknown10 && formation->unknown1a0[i].unknown08 != static_cast<GfObj *>(behavior.unknown08)->unknownf8) {
      GfObj *obj = GfObjUtil::getObj(formation->unknown1a0[i].unknown08);
      if (obj != nullptr) {
        static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message);
      }
    }
  }
}

void StateUtil::broadcastDriverAll(GfComBehaviorPc &behavior, fw::Message &message) {
  behavior.unknown08->getComponent<GfComPropertyPc>();
  for (u32 i = 0; i < 3; i++) {
    GfObj *obj = GfObjUtil::getObj(GfGameParty::getHandleDriver(i));
    if (obj != nullptr) {
      static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message);
    }
  }
}

void StateUtil::broadcastBladeAll(GfComBehaviorPc &behavior, fw::Message &message) {
  behavior.unknown08->getComponent<GfComPropertyPc>();
  for (u32 i = 0; i < 3; i++) {
    GfObj *obj = GfObjUtil::getObj(GfGameParty::getHandleBlade(i, -1));
    if (obj != nullptr) {
      static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message);
    }
  }
}

void StateUtil::broadcastPlayerAll(GfComBehaviorPc &behavior, fw::Message &message) {
  broadcastDriverAll(behavior, message);
  broadcastBladeAll(behavior, message);
}

void StateUtil::sendMessageGfObj(GfComBehaviorPc &behavior, GF_OBJ_HANDLE *handle, fw::Message &message) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message);
  }
}

void StateUtil::playVibration(GfComBehaviorPc &behavior, fw::VibrationID id) {
  if (behavior.getProperty()->unknown111_2) {
    fw::PadManager::playVibration(ml::PadVibrationInfo(id));
  }
}

} // namespace pc
} // namespace gf
