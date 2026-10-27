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

  DrResMdoMorpObj();
  ~DrResMdoMorpObj();
  static u32 calcWorkSize(const u8 *resource);
  static void release(DrResMdoMorpObj *&morpObj);

  u16 unknown00; // Inferred role: state; original member name unknown.
  u8 unknown02;  // Inferred role: flag; original member name unknown.
  u8 _03[0x08 - 0x03];
  void *unknown08; // Inferred role: morph array; original member name unknown.
  u32 unknown10;   // Inferred role: morph count; original member name unknown.
  u8 _14[0x18 - 0x14];
};

static_assert(offsetof(DrResMdoMorpObj, unknown02) == 0x02, "");
static_assert(offsetof(DrResMdoMorpObj, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoMorpObj, unknown10) == 0x10, "");
static_assert(sizeof(DrResMdoMorpObj) == 0x18, "");

} // namespace ml
