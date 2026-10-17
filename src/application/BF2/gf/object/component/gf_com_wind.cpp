#include "gf/object/component/gf_com_wind.h"

#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "framework/wind/wind_factory.h"
#include "framework/wind/wind_probe.h"
#include "gf/object/component/gf_com_transform.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace gf {

GfComWind::GfComWind() : probe(nullptr) {}

void GfComWind::setup(const SetupInfo &info) {
  GfComTransform *transform = owner->getComponent<GfComTransform>();
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = transform->childFrame.get() == nullptr ? transform->frame : transform->childFrame;
  probe = fw::WindFactory::createProbe(info.group, info.radius, frame, info.isFollowFrame);
}

void GfComWind::cleanup() { mm::mtl::safeRelease(probe); }

const mm::mtl::RTTI *GfComWind::getRTTI() const { return &m_rtti; }

void GfComWind::changeLayer(u32 oldLayer, u32 newLayer) {}

} // namespace gf
