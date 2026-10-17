#include "gf/object/component/animation/gf_com_animation.h"

namespace gf {

GfComAnimation::GfComAnimation() {}

GfComAnimation::~GfComAnimation() {}

const mm::mtl::RTTI *GfComAnimation::getRTTI() const { return &m_rtti; }

} // namespace gf
