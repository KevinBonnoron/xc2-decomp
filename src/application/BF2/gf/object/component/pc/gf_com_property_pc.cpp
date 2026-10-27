#include "gf/object/component/pc/gf_com_property_pc.h"

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {

void GfComPropertyPc::resetInput() {
  unknown60.unknown00 = 0.0f;
  unknown60.unknown04 = 0.0f;
  unknown60.unknown08.clear();
  unknown6c.unknown00 = 0.0f;
  unknown6c.unknown04 = 0.0f;
  unknown6c.unknown08.clear();
}

EnviromentSensor *GfComPropertyPc::getEnvSensor() const { return &unknown08->getComponent<GfComEnvSensor>()->unknown10; }

void GfComPropertyPc::setEnvSensorCheckFlags(u32 flags, bool isEnable) {
  EnviromentSensor *sensor = &unknown08->getComponent<GfComEnvSensor>()->unknown10;
  if (isEnable) {
    sensor->m_envSensorCheckFlags |= flags;
  } else {
    sensor->m_envSensorCheckFlags &= ~flags;
  }
}

void GfComPropertyPc::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

void GfComPropertyPc::procMsgPcFieldNotifyChangePlayerID(fw::MessageObject *object, MsgPcFieldNotifyChangePlayerID &message) { unknown38 = message.playerId; }

void GfComPropertyPc::procMsgPcFieldWarpCancel(fw::MessageObject *object, MsgPcFieldWarpCancel &message) { unknown113_2 = false; }

u32 getMode(GfComPropertyPc &property) {
  if (property.unknown111_1) {
    return 2;
  }

  if (property.unknown111_2) {
    return 0;
  }

  return 1;
}

} // namespace gf
