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
    FLAG_UNKNOWN_4 = 0x10, // Inferred role: render; original name unknown.
    FLAG_UNKNOWN_7 = 0x80, // Inferred role: pause; original name unknown.
  };

  DrGpuCheckObj(int type, bool isWorld);
  ~DrGpuCheckObj() override;
  void release() override;
  bool isRender() const override;
  void setPause(bool isPause) override;
  u32 isDeleteCall() const override;
  void setPos(const mm::Vec3 &position, f32 radius) override;
  void setWorldPos(const mm::Vec3 &position, f32 radius) override;
  bool update() override;
  void render() override;

  DrGpuCheckObj *unknown08; // Inferred role: previous object; original member name unknown.
  DrGpuCheckObj *unknown10; // Inferred role: next object; original member name unknown.
  s32 unknown18;            // Inferred role: type; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  grlib::CGLibOcclusionQuery unknown20; // Inferred role: query; original member name unknown.
  u32 unknown38;                        // Inferred role: unknown; original member name unknown.
  u32 unknown3c;                        // Inferred role: flags; original member name unknown.
  unknown001 unknown40[2];              // Inferred role: positions per buffer; original member name unknown.
  unknown001 unknown60;                 // Inferred role: current position; original member name unknown.
  s32 unknown70;                        // Inferred role: unknown; original member name unknown.
  u8 _74[0x80 - 0x74];
};

static_assert(offsetof(DrGpuCheckObj, unknown18) == 0x18, "");
static_assert(offsetof(DrGpuCheckObj, unknown20) == 0x20, "");
static_assert(offsetof(DrGpuCheckObj, unknown3c) == 0x3c, "");
static_assert(offsetof(DrGpuCheckObj, unknown40) == 0x40, "");
static_assert(offsetof(DrGpuCheckObj, unknown60) == 0x60, "");
static_assert(offsetof(DrGpuCheckObj, unknown70) == 0x70, "");
static_assert(offsetof(DrGpuCheckObj, unknown08) == 0x08, "");
static_assert(offsetof(DrGpuCheckObj, unknown10) == 0x10, "");
static_assert(sizeof(DrGpuCheckObj) == 0x80, "");

} // namespace ml
