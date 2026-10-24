#include "gf/object/component/gf_com_wind.h"

#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "framework/wind/wind_factory.h"
#include "framework/wind/wind_probe.h"
#include "gf/object/component/gf_com_transform.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace gf {

GfComWind::GfComWind() : unknown10(nullptr) {}

void GfComWind::setup(const SetupInfo &info) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = transform->unknown18.get() == nullptr ? transform->unknown10 : transform->unknown18;
  unknown10 = fw::WindFactory::createProbe(info.group, info.radius, frame, info.isFollowFrame);
}

void GfComWind::cleanup() { mm::mtl::safeRelease(unknown10); }

const mm::mtl::RTTI *GfComWind::getRTTI() const { return &m_rtti; }

void GfComWind::changeLayer(u32 oldLayer, u32 newLayer) {}

} // namespace gf
