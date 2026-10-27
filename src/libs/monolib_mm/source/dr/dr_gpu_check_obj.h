#pragma once
#include <stddef.h>

#include "dr/dr_gpu_check_base.h"
#include "grlib/cglib_occlusion_query.h"
#include "types.h"

namespace ml {

// Evidence: member offsets and strides from DrGpuCheckObj::DrGpuCheckObj, setPos, setWorldPos and update.
class DrGpuCheckObj : public DrGpuCheckBase {
public:
  // Inferred type: position and radius; the original type name is unknown.
  struct unknown001 {
    f32 unknown00; // Inferred role: x; original member name unknown.
    f32 unknown04; // Inferred role: y; original member name unknown.
    f32 unknown08; // Inferred role: z; original member name unknown.
    f32 unknown0c; // Inferred role: radius; original member name unknown.
  };

  enum Flag {
    FLAG_RENDER = 0x10,
    FLAG_PAUSE = 0x80,
  };

  DrGpuCheckObj(int type, bool isWorld);
  ~DrGpuCheckObj() override;
  void release() override;
  bool isRender() const override;
  void setPause(bool isPause) override;
  u32 isDeleteCall() const override;

  void *unknown08; // Inferred role: unknown; original member name unknown.
  void *unknown10; // Inferred role: unknown; original member name unknown.
  s32 unknown18;   // Inferred role: type; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  grlib::CGLibOcclusionQuery unknown20; // Inferred role: query; original member name unknown.
  u32 unknown38;                        // Inferred role: unknown; original member name unknown.
  u32 unknown3c;                        // Inferred role: flags; original member name unknown.
  unknown001 unknown40[2];              // Inferred role: positions per buffer; original member name unknown.
  unknown001 unknown60;                 // Inferred role: current position; original member name unknown.
  s32 unknown70;                        // Inferred role: unknown; original member name unknown.
};

static_assert(offsetof(DrGpuCheckObj, unknown18) == 0x18, "");
static_assert(offsetof(DrGpuCheckObj, unknown20) == 0x20, "");
static_assert(offsetof(DrGpuCheckObj, unknown3c) == 0x3c, "");
static_assert(offsetof(DrGpuCheckObj, unknown40) == 0x40, "");
static_assert(offsetof(DrGpuCheckObj, unknown60) == 0x60, "");
static_assert(offsetof(DrGpuCheckObj, unknown70) == 0x70, "");

} // namespace ml
