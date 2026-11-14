#include "gf/object/component/pc/gf_com_property_pc.h"

#include <math.h>

#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/pc/gf_pc_agent.h" // IWYU pragma: keep
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "mm_math/mm_quat.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h" // IWYU pragma: keep

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {

GfComPropertyPc::GfComPropertyPc()
    : unknown38(0xffffffff), unknown3c(0), unknown40(0.0f), unknown50(mm::Vec3::zero), unknown60(), unknown6c(), unknown80(mm::Vec3::zero), unknown90(0.0f), unknown94(0.0f), unknownc0(0.0f),
      unknownd0(mm::Vec3::zero), unknowne0(mm::Vec3::zero), unknownf0(0.0f), unknown100(mm::Vec3::zero), unknown110_0(false), unknown110_1(false), unknown110_2(false), unknown110_3(false),
      unknown110_4(false), unknown110_5(false), unknown110_6(false), unknown110_7(false), unknown111_0(false), unknown111_1(false), unknown111_2(false), unknown111_3(false), unknown111_4(false),
      unknown111_5(false), unknown111_6(false), unknown111_7(false), unknown112_0(false), unknown112_1(0), unknown113_2(false), unknown113_3(0), unknown113_7(false), unknown114(0), unknown118(0.0f),
      unknown11c(0.0f), unknown120(0), unknown150(0), unknown1c0(mm::Vec3::zero), unknown1d0(mm::Vec3::zero), unknown1e0(mm::Vec3::zero), unknown1f0(mm::Vec3::zero), unknown200(mm::Vec3::zero),
      unknown210(mm::Vec3::zero), unknown220(mm::Vec3::zero), unknown230(mm::Vec3::zero), unknown240(mm::Vec3::zero), unknown250(mm::Vec3::zero), unknown260(mm::Vec3::zero),
      unknown270(mm::Vec3::zero), unknown280(mm::Vec3::zero), unknown290(mm::Vec3::zero), unknown2a0(mm::Vec3::zero), unknown2b0(mm::Vec3::zero), unknown2c0(mm::Vec3::zero),
      unknown2d0(mm::Vec3::zero), unknown2e0(mm::Vec3::zero), unknown2f0(0.0f), unknown2f4(0.0f), unknown2f8(0.0f) {
  m_locomotion.unknown00 = mm::Vec3::zero;
  m_locomotion.unknown10 = mm::Quat::identity;
}

bool GfComPropertyPc::existInputXY() const {
  const pc::InputParam *param = static_cast<const pc::InputParam *>(unknown300->unknown10[0].param);
  bool exist = false;
  if (!(fabsf(unknown60.unknown00) < param->threshold) || !(fabsf(unknown60.unknown04) < param->threshold)) {
    exist = true;
  }

  return exist;
}

const mm::mtl::RTTI *GfComPropertyPc::getRTTI() const { return &m_rtti; }

f32 GfComPropertyPc::getGravity() const {
  if (!unknown110_3) {
    return 0.0f;
  }

  return -static_cast<const pc::MoveParam *>(unknown300->unknown10[1].param)->gravity;
}

const fw::Transform &GfComPropertyPc::getLocomotion() const {
  static const fw::Transform unknown014 = {mm::Vec3::zero, mm::Quat::identity}; // Inferred role: identity; original name unknown.
  const fw::Transform &locomotion = unknown110_2 ? m_locomotion : unknown014;
  return locomotion;
}

void GfComPropertyPc::setPadControl(bool padControl) {
  if (padControl) {
    unknown111_2 = true;
  } else {
    unknown111_2 = false;
  }

  resetParams();
  unknown310.resetStatus(*this);
}

void GfComPropertyPc::resetParams() {
  fw::ParamManager *manager = fw::ParamManager::get();
  unknown300 = manager->unknown408[13];
  if (unknown111_2) {
    unknown310.unknown08 = manager->unknown408[14];
  } else {
    unknown310.unknown08 = manager->unknown408[15];
  }
}

void GfComPropertyPc::cleanup() {
  unknown470.cleanup(*this);
  unknown310.cleanup(*this);
  unknown310.unknown08 = nullptr;
  unknown300 = nullptr;
  unknown38 = 0xffffffff;
  unknown3c = 0;
}

void GfComPropertyPc::writeBack() {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  transform->unknown10->unknown003() = unknown160;
  if (transform->unknown10->unknowna8 != nullptr) {
    transform->unknown10->syncLocalTransform();
  }
  if (transform->unknown18.get() != nullptr) {
    transform->unknown18->invalidateWorld();
    transform->unknown18->syncWorldTransform();
  }
  unknown180 = unknown1a0;
}

void GfComPropertyPc::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) { message.unknown10 = unknown80 + mm::Vec3::unitY * unknown90; }

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

bool GfComPropertyPc::testEnvSensorCheckFlags(EnviromentSensor::Flag flag) {
  EnviromentSensor *sensor = &mm::mtl::dynamicCast<GfComEnvSensor>(unknown08->unknown38[GfComEnvSensor::COMPONENT_INDEX])->unknown10;
  return (sensor->m_envSensorCheckFlags & flag) != 0;
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

template void mm::mtl::UniquePtr<gf::pc::Agent>::_safe_bool_helper::safe_bool_function() const;
