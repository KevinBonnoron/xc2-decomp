#pragma once
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace wnd {

struct ResWind {
  mm::Vec3 min;
  mm::Vec3 max;
  u8 _20[0x30 - 0x20];
};

static_assert(sizeof(ResWind) == 0x30, "");

} // namespace wnd

namespace fw {

class DynamicWindResource : public mm::mtl::ReferenceObject {
public:
  DynamicWindResource();
  ~DynamicWindResource();

  wnd::ResWind resWind;
};

static_assert(sizeof(DynamicWindResource) == 0x40, "");

class WindFactory {
public:
  static mm::mtl::IntrusivePtr<DynamicWindResource> createWindResource(const mm::Vec3 &min, const mm::Vec3 &max);
};

} // namespace fw
