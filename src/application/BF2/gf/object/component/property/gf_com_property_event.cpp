#include "gf/object/component/property/gf_com_property_event.h"

namespace gf {

GfComPropertyEvent::GfComPropertyEvent() : m_moveSpeed(0.0f) {}

void GfComPropertyEvent::setup(const SetupInfo &info) {}

void GfComPropertyEvent::cleanup() {}

void GfComPropertyEvent::setMoveSpeed(f32 speed) { m_moveSpeed = speed; }

f32 GfComPropertyEvent::getMoveSpeed() const { return m_moveSpeed; }

const mm::mtl::RTTI *GfComPropertyEvent::getRTTI() const { return &m_rtti; }

} // namespace gf
