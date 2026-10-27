#pragma once
#include <stddef.h>

#include "framework/reference_frame.h" // IWYU pragma: keep
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ml {
class DrGpuCheckBase;
} // namespace ml

namespace fw {
class VisibleObject : public mm::mtl::ReferenceObject {
public:
  struct SetupInfo {
    u32 unknown00; // Inferred role: layer; original member name unknown.
  };

  static VisibleObject *create(const SetupInfo &info, mm::mtl::IAllocator *allocator);
  void changeLayer(u32 layer);
  void update();
  bool isRender() const;

  mm::mtl::IntrusiveListNodeBase unknown10; // Inferred role: layer list node; original member name unknown.
  u32 unknown20;                            // Inferred role: layer; original member name unknown.
  u8 _24[0x28 - 0x24];
  mm::mtl::IntrusivePtr<ReferenceFrame> unknown28; // Inferred role: reference frame; original member name unknown.
  ml::DrGpuCheckBase *unknown30;                   // Inferred role: gpu check; original member name unknown.
  u8 _38[0x40 - 0x38];
  mm::Vec3 unknown40; // Inferred role: position offset of the gpu check; original member name unknown.
};

static_assert(offsetof(VisibleObject, unknown10) == 0x10, "");
static_assert(offsetof(VisibleObject, unknown20) == 0x20, "");
static_assert(offsetof(VisibleObject, unknown28) == 0x28, "");
static_assert(offsetof(VisibleObject, unknown30) == 0x30, "");
static_assert(offsetof(VisibleObject, unknown40) == 0x40, "");

} // namespace fw
