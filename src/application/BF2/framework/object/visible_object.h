#pragma once
#include <stddef.h>

#include "framework/reference_frame.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class VisibleObject : public mm::mtl::ReferenceObject {
public:
  struct SetupInfo {
    u32 layer;
  };

  static VisibleObject *create(const SetupInfo &info, mm::mtl::IAllocator *allocator);
  void changeLayer(u32 layer);
  bool isRender() const;

  u8 _10[0x28 - 0x10];
  mm::mtl::IntrusivePtr<ReferenceFrame> referenceFrame;
};

static_assert(offsetof(VisibleObject, referenceFrame) == 0x28, "");

} // namespace fw
