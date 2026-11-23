#include "gf/object/component/enemy/gf_com_property_enemy.h"

#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {

GfComPropertyEnemy::GfComPropertyEnemy() : unknown60(mm::Vec3::zero), unknown70(mm::Quat::identity), unknown80(mm::Vec3::zero), unknown90(mm::Quat::identity) {}

GfComPropertyEnemy::~GfComPropertyEnemy() {}

void GfComPropertyEnemy::writeBack() {
  unknown60 = unknown80;
  unknown70 = unknown90;
}

void GfComPropertyEnemy::flush() {
  m_battleProperty.Update(*this);
  const fw::Transform &transform = unknown08->getComponent<GfComTransform>()->unknown001()->unknown40;
  unknown80 = transform.unknown00;
  unknown90 = transform.unknown10;
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Gets the env sensor component of an object. Single user: GfComPropertyEnemy::getWaterHeight (1.0.0: 0x710051ad18, 44 instructions), which keeps the null test of the component (cbz x21 at
// 0x710051ad40, joining at the flag load at 0x710051ad68). Forms tried without the helper: the component read directly after getComponent<GfComEnvSensor>() gives 43 instructions (test dropped),
// as does `&component->m_envSensor`. The cause is written at UpdatableObject::getComponent. isFieldDeadCondMatched (0x710051ae64, not matched yet) reads the component the same way at 0x710051af58:
// if it matches with this helper, it has two users and becomes unknownNNN.
static GfComEnvSensor *getEnvSensorComponent(fw::UpdatableObject *object) { return object->getComponent<GfComEnvSensor>(); }

bool GfComPropertyEnemy::getWaterHeight(f32 &height) const {
  GfComEnvSensor *envSensor = getEnvSensorComponent(unknown08);
  if (!envSensor->m_envSensor.unknown24_1) {
    return false;
  }
  GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
  if (acc.getObj() == nullptr) {
    return false;
  }
  height = envSensor->m_envSensor.m_verticalData.unknown70.unknown00 - acc.getWorldTransformNoSync().unknown00.y;
  return true;
}

void GfComPropertyEnemy::cleanup() { m_battleProperty.Finalize(*this); }

f32 GfComPropertyEnemy::getChestHeight() const {
  DataParamAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
  f32 height = acc.getChestHeight() * 0.01f;
  GfObjSetupEnemy *setup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30);
  return height * setup->unknown40;
}

const mm::mtl::RTTI *GfComPropertyEnemy::getRTTI() const { return &m_rtti; }

} // namespace gf
