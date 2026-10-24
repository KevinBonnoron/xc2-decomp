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
    CreateInfo() : unknown108(-1) {}

    bool isValid() const { return unknown00.isValid() && unknown04.length() > 0 && unknown108 >= 0; }

    mtl::ALLOC_HANDLE unknown00;    // Inferred role: memory; original member name unknown.
    mm::mtl::FixStr<256> unknown04; // Inferred role: path; original member name unknown.
    int unknown108;                 // Inferred role: bdat id; original member name unknown.
  };

  virtual ~GmkBdat() { dispose(); }

  bool isValid() const;
  bool create(const CreateInfo &info);
  void dispose();
  void update(f32 deltaTime);
  GmkBdat(const CreateInfo *info);
  void seqWaitResourceLoaded(f32 deltaTime);

  CreateInfo unknown08;             // Inferred role: create info; original member name unknown.
  fw::CommonResource *unknown118;   // Inferred role: resource; original member name unknown.
  void *unknown120;                 // Inferred role: data; original member name unknown.
  void (GmkBdat::*unknown128)(f32); // Inferred role: seq; original member name unknown.
};

static_assert(sizeof(GmkBdat::CreateInfo) == 0x10c, "");
static_assert(offsetof(GmkBdat, unknown08) == 0x8, "");
static_assert(offsetof(GmkBdat, unknown118) == 0x118, "");
static_assert(offsetof(GmkBdat, unknown128) == 0x128, "");
static_assert(sizeof(GmkBdat) == 0x138, "");

} // namespace gmk
