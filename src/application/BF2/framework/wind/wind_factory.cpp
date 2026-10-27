#include "framework/wind/wind_factory.h"

#include <float.h>

#include "framework/memory/framework_memory.h"
#include "framework/reference_frame.h"
#include "framework/wind/wind_impluse.h"
#include "framework/wind/wind_probe.h"

namespace fw {

WindProbe *WindFactory::createProbe(u32 group, f32 radius, mm::mtl::IntrusivePtr<ReferenceFrame> frame, bool isFollowFrame) {
#line 28
  WindProbe *probe = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) WindProbe(group, radius, frame, isFollowFrame);
  probe->addRef();
  return probe;
}

void WindFactory::generateImpluse(const mm::Vec3 &position, f32 radius, f32 param3, f32 param4, f32 param5) {
  if (param5 > FLT_EPSILON) {
#line 46
    WindImpluse *impluse = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) WindImpluse(position, radius, param3, param4, param5);
    impluse->addRef();
  }
}

mm::mtl::IntrusivePtr<DynamicWindResource> WindFactory::createWindResource(const mm::Vec3 &min, const mm::Vec3 &max) {
#line 60
  DynamicWindResource *resource = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) DynamicWindResource();
  resource->unknown10.unknown00 = min;
  resource->unknown10.unknown10 = max;
  return resource;
}

} // namespace fw
