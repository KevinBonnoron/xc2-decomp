#pragma once
#include <stddef.h>

#include "ml/dev_file_accessor.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

class DevFileNxTh : public DevFileAccessor, public mm::mtl::PtrSingleton<DevFileNxTh> {
public:
  // Inferred type: file channel; the original type name is unknown.
  struct unknown001 {
    u8 _000[0x10c];
    bool unknown10c; // Inferred role: used; original member name unknown.
    u8 _10d[0x1d8 - 0x10d];
  };

  bool initialize() override;
  u32 addressAlignment() override;
  bool rfIsUsedChannel(u32 channel) override;

  u8 _10[0x14 - 0x10];
  mtl::ALLOC_HANDLE unknown14; // Inferred role: memory; original member name unknown.
  s32 unknown18;               // Inferred role: state; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  mm::mtl::UniquePtr<unknown001> unknown20; // Inferred role: channels; original member name unknown.
};

static_assert(sizeof(DevFileNxTh::unknown001) == 0x1d8, "");
static_assert(offsetof(DevFileNxTh, unknown14) == 0x14, "");
static_assert(offsetof(DevFileNxTh, unknown20) == 0x20, "");

} // namespace ml
