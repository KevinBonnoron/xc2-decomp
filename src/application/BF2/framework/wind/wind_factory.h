#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace wnd {

struct ResWind {
  ResWind() : unknown20(0), unknown28(0) {}

  mm::Vec3 unknown00; // Inferred role: min; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: max; original member name unknown.
  u64 unknown20;      // Role and original member name unknown.
  u32 unknown28;      // Role and original member name unknown.
  u8 _2c[0x30 - 0x2c];
};

static_assert(offsetof(ResWind, unknown20) == 0x20, "");
static_assert(offsetof(ResWind, unknown28) == 0x28, "");
static_assert(sizeof(ResWind) == 0x30, "");

} // namespace wnd

namespace fw {

class ReferenceFrame;
class WindProbe;

class DynamicWindResource : public mm::mtl::ReferenceObject {
public:
  DynamicWindResource();
  ~DynamicWindResource();

  wnd::ResWind unknown10; // Inferred role: res wind; original member name unknown.
};

static_assert(sizeof(DynamicWindResource) == 0x40, "");

class WindFactory {
public:
  static void generateImpluse(const mm::Vec3 &position, f32 radius, f32 param3, f32 param4, f32 param5);
  static WindProbe *createProbe(u32 group, f32 radius, mm::mtl::IntrusivePtr<ReferenceFrame> frame, bool isFollowFrame);
  static mm::mtl::IntrusivePtr<DynamicWindResource> createWindResource(const mm::Vec3 &min, const mm::Vec3 &max);
};

} // namespace fw
