#include "gf/object/component/env_sensor/gf_com_env_sensor.h"

#include <float.h>
#include <math.h>

#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "framework/coli/coli_object.h"
#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_transform.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {

namespace {

// Inferred role: ground index of each foot, in the order of the bone indices unknown2b0 (1.0.0: 0x7100f73d78), shared by flushFoot and flushFakeFoot; original name unknown.
const GfEnvProperty::GROUND_INDEX unknown002[6] = {GfEnvProperty::GROUND_INDEX_UNKNOWN_1,
                                                   GfEnvProperty::GROUND_INDEX_UNKNOWN_2,
                                                   GfEnvProperty::GROUND_INDEX_UNKNOWN_3,
                                                   GfEnvProperty::GROUND_INDEX_UNKNOWN_4,
                                                   GfEnvProperty::GROUND_INDEX_UNKNOWN_5,
                                                   GfEnvProperty::GROUND_INDEX_UNKNOWN_6};

} // namespace

GfComEnvSensor::GfComEnvSensor() : unknown2bc(0xffff), unknown2d8(nullptr), unknown2e0(), unknown2e8(), unknown360(nullptr), unknown368(nullptr) {
  for (u32 i = 0; i < 6; i++) {
    unknown2b0[i] = 0xffff;
  }
  for (u32 i = 0; i < 6; i++) {
    unknown2c0[i] = 0;
  }
  m_envListener.m_comEnvSensor = this;
}

bool GfComEnvSensor::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_UNKNOWN_16777219) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  return false;
}

void GfComEnvSensor::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

GfComEnvSensor::~GfComEnvSensor() {}

void GfComEnvSensor::cleanup() {
  unknown360.reset();
  fw::SensorManager *manager = fw::SensorManager::get();
  if (manager != nullptr) {
    if (unknown2f0.unknown30) {
      manager->removeUpdaterBeforeGame(getLayer(), unknown2f0);
    }
    if (unknown328.unknown30) {
      manager->removeUpdaterAfterAnimation(getLayer(), unknown328);
    }
  }
}

void GfComEnvSensor::changeLayer(u32 oldLayer, u32 newLayer) {
  fw::SensorManager *manager = fw::SensorManager::get();
  if (manager == nullptr) {
    return;
  }

  if (unknown2f0.unknown30) {
    manager->removeUpdaterBeforeGame(oldLayer, unknown2f0);
    manager->addUpdaterBeforeGame(newLayer, unknown2f0);
  }
  if (unknown328.unknown30) {
    manager->removeUpdaterAfterAnimation(oldLayer, unknown328);
    manager->addUpdaterAfterAnimation(newLayer, unknown328);
  }
}

void GfComEnvSensor::setEnableSensor(bool isEnable) {
  if (isEnable) {
    if (!unknown2f0.unknown30) {
      fw::SensorManager *manager = fw::SensorManager::get();
      if (manager != nullptr) {
        manager->addUpdaterBeforeGame(getLayer(), unknown2f0);
      }
    }
  } else if (unknown2f0.unknown30) {
    fw::SensorManager *manager = fw::SensorManager::get();
    if (manager != nullptr) {
      manager->removeUpdaterBeforeGame(getLayer(), unknown2f0);
    }
  }
}

void GfComEnvSensor::flushEnv(const fw::Transform &transform) {
  m_envSensor.check(transform, unknown2e0);
  GfComProperty *property = unknown08->getComponent<GfComProperty>();
  if (property != nullptr) {
    GfEnvProperty *env = property->unknown28.get();
    if (env != nullptr) {
      bool isEnable = true;
      GfComCollider *collider = unknown08->getComponent<GfComCollider>();
      if (collider != nullptr) {
        fw::ColiObject *coli = collider->unknown18[0];
        if (coli != nullptr) {
          isEnable = coli->testAttribute(fw::COLI_ATRR_UNKNOWN_0);
        }
      }
      m_envSensor.writeBackProperty(isEnable, env);
    }
  }
  if (unknown360) {
    unknown360->update(static_cast<GfObj *>(unknown08)->unknownf8);
  }
}

void GfComEnvSensor::resolveTransform() {
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  if (transform->unknown10->m_referenceFrame != nullptr) {
    transform->unknown10->invalidateWorld();
  }
  transform->unknown10->syncWorldTransform();
}

const fw::Transform &GfComEnvSensor::getTransform() {
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  return transform->unknown10->unknown40;
}

void GfComEnvSensor::flushRoot() {
  resolveTransform();
  flushEnv(getTransform());
}

// Evidence (1.0.0: 0x710051bdb0): the same prologue and foot loop as flushFoot, but without the root-relative branch. When ground sample 0 is not valid (flag bit 1) the six foot bits
// (2..7) are cleared at once (`and w8, w8, #0xffffff03`: the loop over the GROUND_INDEX table folds into one mask). Otherwise the segment from `foot + (0, up, 0)` to `foot - (0, down, 0)`
// is clipped against the plane of sample 0 (the same distance tests, FLT_EPSILON guard and `start + direction * ratio` as fw::PlaneRayCaster::castRay, 1.0.0: 0x71001808f8): when it
// crosses, the foot sample is a copy of sample 0 (the 28 byte tail through the stack, 0x710051c034-0x710051c068) with the crossing point as position, otherwise the valid bit is cleared.
void GfComEnvSensor::flushFakeFoot() {
  anm::Pose *pose = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX])->unknown30;
  if (pose == nullptr) {
    return;
  }
  resolveTransform();
  flushRootAfterMovement();
  const unknown001 *param = unknown2e8.get<unknown001>();
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  const fw::Transform &world = transform->unknown10->unknown40;
  GfComProperty *property = unknown08->getComponent<GfComProperty>();
  if (property == nullptr) {
    return;
  }
  GfEnvProperty *env = property->unknown28.get();
  if (env == nullptr) {
    return;
  }
  if (!env->unknown003(GfEnvProperty::GROUND_INDEX_UNKNOWN_0)) {
    for (u32 i = 0; i < 6; i++) {
      env->unknown2d0 &= ~(1 << (unknown002[i] + 1));
    }
    return;
  }
  const GfEnvProperty::unknown002 &ground = env->unknown00[GfEnvProperty::GROUND_INDEX_UNKNOWN_0];
  for (u32 i = 0; i < 6; i++) {
    if (unknown2b0[i] == 0xffff) {
      continue;
    }
    const mm::Vec4 &bone = pose->getBoneModelSpace(unknown2b0[i]).unknown00;
    mm::Vec3 foot(bone.x, bone.y, bone.z);
    mm::unknown010(world.unknown10, foot);
    foot += world.unknown00;
    mm::Vec3 start = foot + mm::Vec3(0.0f, param->unknown04, 0.0f);
    mm::Vec3 end = foot + mm::Vec3(0.0f, -param->unknown08, 0.0f);
    const mm::Plane &plane = ground.unknown10;
    f32 startDistance = plane.normal.x * start.x + plane.normal.y * start.y + plane.normal.z * start.z + plane.distance;
    f32 endDistance = plane.normal.x * end.x + plane.normal.y * end.y + plane.normal.z * end.z + plane.distance;
    if (startDistance >= 0.0f && endDistance <= 0.0f) {
      GfEnvProperty::unknown002 sample = ground;
      mm::Vec3 direction = end - start;
      f32 slope = fabsf(direction.x * plane.normal.x + direction.y * plane.normal.y + direction.z * plane.normal.z);
      f32 ratio = slope > FLT_EPSILON ? fabsf(startDistance) / slope : 0.0f;
      sample.unknown00 = start + direction * ratio;
      GfEnvProperty::GROUND_INDEX index = unknown002[i];
      env->unknown2d0 |= 1 << (index + 1);
      env->unknown00[index] = sample;
    } else {
      GfEnvProperty::GROUND_INDEX index = unknown002[i];
      env->unknown2d0 &= ~(1 << (index + 1));
    }
  }
}

void GfComEnvSensor::flushRootAfterMovement() {
  if (unknown2bc == -1) {
    return;
  }
  anm::Pose *pose = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX])->unknown30;
  if (pose == nullptr) {
    return;
  }
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  const fw::Transform &world = transform->unknown10->unknown40;
  GfComProperty *property = unknown08->getComponent<GfComProperty>();
  if (property == nullptr) {
    return;
  }
  GfEnvProperty *env = property->unknown28.get();
  if (env == nullptr) {
    return;
  }
  // Ruling 8: the rotation of the bone position by the world rotation is written out as in GfComSound::flush (1.0.0: 0x710051c674-0x710051c74c: the loads of the bone position and of the
  // quaternion, the four temporaries, the three stored components). The call forms are measured and do not match: `mm::unknown010(q, position)` (in place) has 36 differing lines and
  // `world.unknown10.rotate(position)` 9 (operands of products and sums swapped, same size). The bone position is a copy (`const mm::Vec4 v`): through a reference the loads
  // come in another order and 53 lines differ in operand order and scheduling (the result declared before or after the copy makes no difference here); the quaternion stays a reference
  // (a copy: 24 lines).
  const mm::Vec4 v = pose->getBoneModelSpace(unknown2bc).unknown00;
  const mm::Quat &q = world.unknown10;
  mm::Vec3 position;
  f32 tx = v.z * q.y - v.y * q.z + v.x * q.w;
  f32 ty = v.x * q.z - v.z * q.x + v.y * q.w;
  f32 tz = v.y * q.x - v.x * q.y + v.z * q.w;
  f32 tw = -v.x * q.x - v.y * q.y - v.z * q.z;
  position.x = -(q.z * ty) + q.y * tz - q.x * tw + q.w * tx;
  position.y = -(q.x * tz) + q.z * tx - q.y * tw + q.w * ty;
  position.z = -(q.y * tx) + q.x * ty - q.z * tw + q.w * tz;
  position += world.unknown00;
  // The game (0x710051c764) never sets x0 for this call: flushGroundSingle, defined in this file, never reads `this` (ruling 6), so the object the original called it on cannot be
  // checked; `this` is the most plausible one.
  const unknown001 *param = static_cast<const unknown001 *>(unknown2e8.unknown00->param);
  flushGroundSingle(env, position, param->unknown0c, param->unknown10, GfEnvProperty::GROUND_INDEX_UNKNOWN_7);
}

bool GfComEnvSensor::flushGroundSingle(GfEnvProperty *property, const mm::Vec3 &position, f32 up, f32 down, GfEnvProperty::GROUND_INDEX index) {
  mm::Vec3 start = position + mm::Vec3(0.0f, up, 0.0f);
  mm::Vec3 end = position + mm::Vec3(0.0f, -down, 0.0f);
  fw::ColiCheckConfig config;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown10 = 1;
  config.unknown04 = 0xfffffffa;
  config.unknown00 = 9;
  fw::TColiCheckResult<256> result;
  fw::ColiCheck::testLine(result, start, end, config);
  if (result.getCount() == 0) {
    return false;
  }
  GfEnvProperty::unknown002 ground;
  ground.unknown00 = result.getPosition(0);
  ground.unknown10.set(result.getPosition(0), result.getNormal(0));
  ground.unknown30 = result.getMaterial(0).unknown04;
  ground.unknown34 = result.getMaterial(0).unknown00;
  // The game (1.0.0: 0x710051c77c) keeps four ldr b + ucvtf. Through material.unknown18[0] the first load keeps the 4-byte alignment of the member and GVN widens the four loads
  // into one word load (ldr w + ubfx); through a u8 pointer every load has alignment 1 and stays a byte load.
  const u8 *color = result.getMaterial(0).unknown18;
  ground.unknown38.r = color[0];
  ground.unknown38.g = color[1];
  ground.unknown38.b = color[2];
  ground.unknown38.a = color[3];
  ground.unknown48 = 0;
  property->unknown2d0 |= 1 << (index + 1);
  property->unknown00[index] = ground;
  return true;
}

const mm::mtl::RTTI *GfComEnvSensor::getRTTI() const { return &m_rtti; }

} // namespace gf

template void mm::mtl::UniquePtr<gf::GfEnemySensor>::_safe_bool_helper::safe_bool_function() const;
template void mm::mtl::Delegate<void()>::memberFuncInvoker<gf::GfComEnvSensor>(const mm::mtl::Delegate<void()> *);
