#include "gf/camera/gf_camera_subview.h"

namespace gf {

SubViewCamera::~SubViewCamera() {}

void SubViewCamera::onActivate() {}

void SubViewCamera::update(const fw::UpdateInfo &) { setLookAt(unknownb0, unknownc0, 0.0f); }

const mm::mtl::RTTI *SubViewCamera::getRTTI() const { return &m_rtti; }

const char *SubViewCamera::getName() const { return "SubViewCamera"; }

} // namespace gf
