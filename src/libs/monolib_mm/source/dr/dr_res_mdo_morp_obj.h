#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResMdoMorpObj {
public:
  // Inferred role: resource header holding the offset of the morph table; original type name unknown.
  struct unknown001 {
    u8 _00[0x80];
    u32 unknown80; // Inferred role: offset of the morph table; original member name unknown.
  };

  // Inferred role: morph table; original type name unknown.
  struct unknown002 {
    u8 _00[4];
    s32 unknown04; // Inferred role: morph count; original member name unknown.
  };

  // Inferred role: morph parameter description; original type name unknown.
  struct unknown003 {
    u8 _00[0x08];
    u32 unknown08; // Inferred role: parameter type in the low 16 bits and parameter index in the high 16 bits; original member name unknown.
  };

  // Inferred role: morph entry; original type name unknown.
  struct unknown004 {
    f32 unknown00; // Inferred role: current parameter; original member name unknown.
    f32 unknown04; // Inferred role: previous parameter; original member name unknown.
    u8 _08[0x18 - 0x08];
    const unknown003 *unknown18; // Inferred role: parameter description; original member name unknown.
  };

  DrResMdoMorpObj();
  ~DrResMdoMorpObj();
  static u32 calcWorkSize(const u8 *resource);
  static void release(DrResMdoMorpObj *&morpObj);

  u8 unknown00; // Inferred role: state; original member name unknown.
  u8 unknown01; // Inferred role: state; original member name unknown.
  u8 unknown02; // Inferred role: flag; original member name unknown.
  u8 _03[0x08 - 0x03];
  unknown004 *unknown08; // Inferred role: morph array; original member name unknown.
  u32 unknown10;         // Inferred role: morph count; original member name unknown.
  u8 _14[0x18 - 0x14];
};

static_assert(sizeof(DrResMdoMorpObj::unknown004) == 0x20, "");
static_assert(offsetof(DrResMdoMorpObj::unknown003, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoMorpObj, unknown01) == 0x01, "");
static_assert(offsetof(DrResMdoMorpObj, unknown02) == 0x02, "");
static_assert(offsetof(DrResMdoMorpObj, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoMorpObj, unknown10) == 0x10, "");
static_assert(sizeof(DrResMdoMorpObj) == 0x18, "");

} // namespace ml
