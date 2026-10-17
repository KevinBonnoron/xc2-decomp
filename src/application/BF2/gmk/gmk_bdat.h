#pragma once
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "types.h"
#include <stddef.h>

namespace fw {
class CommonResource;
}

namespace gmk {

constexpr int BDAT_TYPE_U8 = 1;
constexpr int BDAT_TYPE_U16 = 2;
constexpr int BDAT_TYPE_U32 = 3;
constexpr int BDAT_TYPE_S16 = 5;
constexpr int BDAT_TYPE_STRING = 7;
constexpr int BDAT_TYPE_F32 = 8;

inline f32 toBdatF32(unsigned long value) {
  union {
    unsigned long value;
    f32 valueF32;
  } bits;
  bits.value = value;
  return bits.valueF32;
}

class GmkBdat {
public:
  struct CreateInfo {
    CreateInfo() : bdatId(-1) {}

    bool isValid() const { return memory.isValid() && path.length() > 0 && bdatId >= 0; }

    mtl::ALLOC_HANDLE memory;
    mm::mtl::FixStr<256> path;
    int bdatId;
  };

  virtual ~GmkBdat() { dispose(); }

  bool isValid() const;
  bool create(const CreateInfo &info);
  void dispose();
  void update(f32 deltaTime);
  GmkBdat(const CreateInfo *info);
  void seqWaitResourceLoaded(f32 deltaTime);

  CreateInfo createInfo;
  fw::CommonResource *resource;
  void *data;
  void (GmkBdat::*seq)(f32);
};

static_assert(sizeof(GmkBdat::CreateInfo) == 0x10c, "");
static_assert(offsetof(GmkBdat, createInfo) == 0x8, "");
static_assert(offsetof(GmkBdat, resource) == 0x118, "");
static_assert(offsetof(GmkBdat, seq) == 0x128, "");
static_assert(sizeof(GmkBdat) == 0x138, "");

} // namespace gmk
