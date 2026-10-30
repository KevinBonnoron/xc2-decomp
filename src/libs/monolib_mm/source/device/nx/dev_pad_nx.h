#pragma once
#include <stddef.h>

#include "ml/dev_pad.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace ml {
class WorkObj;

class DevPadNx : public DevPad {
public:
  class Impl {
  public:
    void release();

    u8 _0000[0x0024];
    u32 unknown24[4]; // Inferred role: npad ids of the pads; original member name unknown.
    u8 _0034[0x4540 - 0x0034];
    s32 unknown4540; // Inferred role: pad index; original member name unknown.
    s32 unknown4544; // Inferred role: user select pad id; original member name unknown.
  };

  DevPadNx(const char *name, WorkObj *parent);
  static void setUserSelectControllerID(u32 id);
  bool isLocalConnect(int padNo) const override;
  u32 getLocalStyle(int padNo) const override;
  int getLocalUserSelectPadID() const override;
  u32 getLocalBtn(int padNo) const override;
  f32 getLocalALX(int padNo) const override;
  f32 getLocalALY(int padNo) const override;
  f32 getLocalARX(int padNo) const override;
  f32 getLocalARY(int padNo) const override;
  void updateDevice(f32 time) override;
  bool createDevice() override;
  void releaseDevice() override;

  mm::mtl::UniquePtr<Impl> unknown548; // Inferred role: implementation; original member name unknown.
};

static_assert(offsetof(DevPadNx::Impl, unknown24) == 0x0024, "");
static_assert(offsetof(DevPadNx::Impl, unknown4540) == 0x4540, "");
static_assert(offsetof(DevPadNx::Impl, unknown4544) == 0x4544, "");
static_assert(offsetof(DevPadNx, unknown548) == 0x548, "");

} // namespace ml
