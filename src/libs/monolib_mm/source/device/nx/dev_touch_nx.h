#pragma once

#include <stddef.h>

#include "ml/dev_touch.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace ml {
class WorkObj;

class DevTouchNx : public DevTouch {
public:
  // The size comes from the allocation in the constructor; the members are unknown.
  class Impl {
  public:
    void update(DevTouchNx *touch);

    u64 unknown00[0x290 / 8]; // Inferred role: touch screen state, 8-byte aligned like the allocation; original member name unknown.
  };

  DevTouchNx(const char *name, WorkObj *parent);
  void updateDevice() override;
  bool createDevice() override;
  void releaseDevice() override;

  mm::mtl::UniquePtr<Impl> unknown7d0; // Inferred role: implementation; original member name unknown.
};

static_assert(sizeof(DevTouchNx::Impl) == 0x290, "");
static_assert(offsetof(DevTouchNx, unknown7d0) == 0x7d0, "");
static_assert(sizeof(DevTouchNx) == 0x7e0, "");

} // namespace ml
