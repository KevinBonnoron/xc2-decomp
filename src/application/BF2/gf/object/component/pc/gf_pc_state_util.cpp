#include "gf/object/component/pc/gf_pc_state_util.h"

#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/game/gf_game_ride.h"
#include "gf/game/gf_game_target.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace pc {

void StateUtil::resetCamera() { GfGamePlayerCamera::resetCamera(); }

bool StateUtil::isManualCamera() { return GfGamePlayerCamera::isManualCamera(); }

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

EnviromentSensor::GroundInfo *StateUtil::getGroundInfo(GfComBehaviorPc &behavior) {
  EnviromentSensor *sensor = behavior.unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
  return sensor->unknown24_0 ? &sensor->unknown30 : nullptr;
}

EnviromentSensor::unknown003 *StateUtil::getClimbWallInfo(GfComBehaviorPc &behavior) {
  EnviromentSensor *sensor = behavior.unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
  EnviromentSensor::unknown003 *info = &sensor->unknown30.unknown180;
  if (!sensor->unknown24_6 || !info->unknown24_4) {
    info = nullptr;
  }

  return info;
}

EnviromentSensor::GroundInfo *StateUtil::getClimbEndGroundInfo(GfComBehaviorPc &behavior) {
  EnviromentSensor *sensor = behavior.unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
  return sensor->unknown25_0 ? &sensor->unknown1f0 : nullptr;
}

EnviromentSensor::unknown004 *StateUtil::getDescendWallInfo(GfComBehaviorPc &behavior) {
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

} // namespace pc
} // namespace gf
