#pragma once
#include <stddef.h>

#include "mm_mtl/reserved_bitflag.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

struct _IBLPrimHeader {
  u32 unknown00; // Inferred role: collision data offset; original member name unknown.
  u16 unknown04; // Inferred role: collision type; original member name unknown.
  u16 unknown06; // Inferred role: texture index; original member name unknown.
  u16 unknown08; // Inferred role: priority; original member name unknown.
  u8 _0a[0x18 - 0x0a];
};

static_assert(offsetof(_IBLPrimHeader, unknown04) == 0x04, "");
static_assert(offsetof(_IBLPrimHeader, unknown06) == 0x06, "");
static_assert(offsetof(_IBLPrimHeader, unknown08) == 0x08, "");
static_assert(sizeof(_IBLPrimHeader) == 0x18, "");

struct _EnvColiListTreeData {
  f32 unknown00[3]; // Inferred role: upper bound; original member name unknown.
  f32 unknown0c[3]; // Inferred role: lower bound; original member name unknown.
  u32 unknown18;    // Inferred role: child index list offset; original member name unknown.
  u32 unknown1c;    // Inferred role: primitive index list offset; original member name unknown.
  u16 unknown20;    // Inferred role: child num; original member name unknown.
  u16 unknown22;    // Inferred role: primitive num; original member name unknown.
};

static_assert(offsetof(_EnvColiListTreeData, unknown0c) == 0x0c, "");
static_assert(offsetof(_EnvColiListTreeData, unknown18) == 0x18, "");
static_assert(offsetof(_EnvColiListTreeData, unknown22) == 0x22, "");
static_assert(sizeof(_EnvColiListTreeData) == 0x24, "");

class DrIBLColiAcc {
public:
  typedef bool (DrIBLColiAcc::*COLITEST)(const u8 *data, const mm::Vec3 &position, f32 margin);

  DrIBLColiAcc(const void *data, mtl::ALLOC_HANDLE handle);
  ~DrIBLColiAcc();
  bool testColi(const mm::Vec3 &position, f32 margin, const _IBLPrimHeader *&result);
  bool testTreeColi(const _EnvColiListTreeData *tree, const mm::Vec3 &position, f32 margin, const _IBLPrimHeader *&result);
  void testTreeInvalidColi(const _EnvColiListTreeData *tree, const mm::Vec3 &position, f32 margin);
  bool envcoli_box(const u8 *data, const mm::Vec3 &position, f32 margin);
  bool envcoli_sphere(const u8 *data, const mm::Vec3 &position, f32 margin);
  bool envcoli_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin);
  bool envcoli_notrot_box(const u8 *data, const mm::Vec3 &position, f32 margin);
  bool envcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin);

  static COLITEST s_pColiTest[5];

  const u8 *unknown00;                   // Inferred role: data; original member name unknown.
  const _IBLPrimHeader *unknown08;       // Inferred role: primitives; original member name unknown.
  const _EnvColiListTreeData *unknown10; // Inferred role: collision tree; original member name unknown.
  const _EnvColiListTreeData *unknown18; // Inferred role: invalid collision tree; original member name unknown.
  u16 unknown20;                         // Inferred role: current priority; original member name unknown.
  u8 _22[0x28 - 0x22];
  mm::mtl::ReservedBitflag unknown28; // Inferred role: invalid textures; original member name unknown.
};

static_assert(offsetof(DrIBLColiAcc, unknown08) == 0x08, "");
static_assert(offsetof(DrIBLColiAcc, unknown10) == 0x10, "");
static_assert(offsetof(DrIBLColiAcc, unknown18) == 0x18, "");
static_assert(offsetof(DrIBLColiAcc, unknown20) == 0x20, "");
static_assert(offsetof(DrIBLColiAcc, unknown28) == 0x28, "");

} // namespace ml
