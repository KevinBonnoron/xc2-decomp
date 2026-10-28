#include "gf/object/component/env_sensor/gf_com_env_sensor.h"

#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "gf/object/component/gf_com_transform.h"
#include "mm_mtl/rtti.h"

namespace fw {
struct Transform;
} // namespace fw

namespace gf {

bool GfComEnvSensor::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_DEBUG_ACTIVATE_COMPONENT_WINDOW) {
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

void GfComEnvSensor::resolveTransform() {
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  if (transform->unknown10->unknowna8 != nullptr) {
    transform->unknown10->invalidateWorld();
  }
  transform->unknown10->syncWorldTransform();
}

const fw::Transform &GfComEnvSensor::getTransform() {
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  return transform->unknown10->unknown40;
}

const mm::mtl::RTTI *GfComEnvSensor::getRTTI() const { return &m_rtti; }

} // namespace gf

template void mm::mtl::UniquePtr<gf::GfEnemySensor>::_safe_bool_helper::safe_bool_function() const;
