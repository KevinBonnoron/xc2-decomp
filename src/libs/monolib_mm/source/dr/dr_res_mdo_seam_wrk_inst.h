#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResMdoSeamWrkInst {
public:
  // Inferred role: header of the instance map data; original type name unknown.
  struct unknown001 {
    u8 _00[0x2c];
    s32 unknown2c; // Inferred role: model index offset; original member name unknown.
  };

  void beginMdl();
  void linkReadMdl();
  void linkReadMdl(u32 index);
  u32 isSubMdl(u32 index);

  u8 _00[0x08 - 0x00];
  DrResMdoSeamWrkInst *unknown08; // Inferred role: next object; original member name unknown.
  u8 _10[0x20 - 0x10];
  const unknown001 *unknown20; // Inferred role: instance map header; original member name unknown.
  u8 _28[0x88 - 0x28];
  s16 unknown88; // Inferred role: read count; original member name unknown.
  u8 _8a[0xc8 - 0x8a];
  u32 *unknownc8;       // Inferred role: read model bit table; original member name unknown.
  const u32 *unknownd0; // Inferred role: sub model bit table; original member name unknown.
  u8 _d8[0x150 - 0xd8];
  u16 unknown150; // Inferred role: model info index; original member name unknown.
  u8 _152[0x1c0 - 0x152];
};

static_assert(offsetof(DrResMdoSeamWrkInst, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown88) == 0x88, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknownc8) == 0xc8, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknownd0) == 0xd0, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown150) == 0x150, "");
static_assert(sizeof(DrResMdoSeamWrkInst) == 0x1c0, "");

} // namespace ml
