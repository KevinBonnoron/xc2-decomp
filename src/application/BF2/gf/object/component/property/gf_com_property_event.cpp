#include "gf/object/component/property/gf_com_property_event.h"

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/gf_com_transform.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {

GfComPropertyEvent::GfComPropertyEvent() : m_moveSpeed(0.0f) {}

void GfComPropertyEvent::setup(const SetupInfo &info) {}

void GfComPropertyEvent::cleanup() {}

void GfComPropertyEvent::setMoveSpeed(f32 speed) { m_moveSpeed = speed; }

f32 GfComPropertyEvent::getMoveSpeed() const { return m_moveSpeed; }

bool GfComPropertyEvent::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_UNKNOWN_16777286) {
    procMsgObjectGetVelocity(sender, static_cast<MsgObjectGetVelocity &>(message));
    return true;
  }
  return GfComProperty::recieveMessage(sender, message);
}

void GfComPropertyEvent::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  if (transform != nullptr) {
    message.unknown10 = transform->getRotation().rotate(mm::Vec3::unitZ) * m_moveSpeed;
  }
}

const mm::mtl::RTTI *GfComPropertyEvent::getRTTI() const { return &m_rtti; }

} // namespace gf
