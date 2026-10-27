#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec3_na.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ptlib {

// Inferred role: kind, start and length of a force; original name unknown.
struct unknown003 {
  s32 unknown00; // Inferred role: kind; original member name unknown.
  s16 unknown04; // Inferred role: start frame; original member name unknown.
  s16 unknown06; // Inferred role: life; original member name unknown.
};

static_assert(sizeof(unknown003) == 0x08, "");

struct alignas(16) AddForceParam {
  unknown003 unknown00; // Role and original member name unknown.
  mm::Vec3 unknown10;   // Role and original member name unknown.
  mm::Vec3 unknown20;   // Role and original member name unknown.
  f32 unknown30;        // Role and original member name unknown.
};

static_assert(offsetof(AddForceParam, unknown10) == 0x10, "");
static_assert(offsetof(AddForceParam, unknown20) == 0x20, "");
static_assert(offsetof(AddForceParam, unknown30) == 0x30, "");
static_assert(sizeof(AddForceParam) == 0x40, "");

namespace forcefield {

// Inferred role: force being applied to the particles; original name unknown.
struct unknown002 {
  s32 unknown00; // Inferred role: elapsed frames; original member name unknown.
  u8 _04[0x10 - 0x04];
  unknown003 unknown10; // Inferred role: kind, start and life; original member name unknown.
  u8 _18[0x20 - 0x18];
  mm::Vec3NA unknown20; // Inferred role: position; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  mm::Vec3NA unknown30; // Inferred role: direction; original member name unknown.
  u8 _3c[0x40 - 0x3c];
  f32 unknown40; // Inferred role: radius; original member name unknown.
  u8 _44[0x50 - 0x44];
};

static_assert(offsetof(unknown002, unknown10) == 0x10, "");
static_assert(offsetof(unknown002, unknown20) == 0x20, "");
static_assert(offsetof(unknown002, unknown30) == 0x30, "");
static_assert(offsetof(unknown002, unknown40) == 0x40, "");
static_assert(sizeof(unknown002) == 0x50, "");

class FfManager {
public:
  static FfManager *get();
  static FfManager *&getPtr();
  static void term();
  void initSub();
  void termSub();
  void update(f32 speed);
  void addForce(const AddForceParam &param);

  mm::mtl::FixedVector<unknown002 *, 128> unknown00; // Inferred role: forces; original member name unknown.
};

static_assert(sizeof(FfManager) == 0x408, "");

} // namespace forcefield
} // namespace ptlib
