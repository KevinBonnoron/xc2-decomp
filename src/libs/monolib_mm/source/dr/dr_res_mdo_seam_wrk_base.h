#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoSeamWrkBaseVertex;
struct MdoWrkMatRes;

class DrResMdoSeamWrkBase {
public:
  void beginBaseMapRenderList();
  void callShadowCacheBaseUpdate(u64 mask);
  void beginRender();
  void endRender();
  void selectVertex(int index);

  u8 _00[0x08 - 0x00];
  DrResMdoSeamWrkBase *unknown08; // Inferred role: next object; original member name unknown.
  u8 _10[0x68 - 0x10];
  MdoWrkMatRes *unknown68; // Inferred role: material work; original member name unknown.
  u8 _70[0x78 - 0x70];
  DrResMdoSeamWrkBaseVertex *unknown78; // Inferred role: vertices; original member name unknown.
  u8 _80[0x8c - 0x80];
  u32 unknown8c; // Inferred role: render count; original member name unknown.
  u32 unknown90; // Inferred role: render count; original member name unknown.
  u32 unknown94; // Inferred role: render count; original member name unknown.
  u64 unknown98; // Inferred role: shadow cache update mask; original member name unknown.
  u8 _a0[0xf0 - 0xa0];
  u8 **unknownf0; // Inferred role: shadow bit tables; original member name unknown.
  u32 unknownf8;  // Inferred role: shadow bit table size; original member name unknown.
  u8 _fc[0x110 - 0xfc];
  u8 *unknown110; // Inferred role: render lists; original member name unknown.
  u8 _118[0x170 - 0x118];
  s32 unknown170; // Inferred role: render list num; original member name unknown.
  s32 unknown174; // Inferred role: render list size; original member name unknown.
  s16 unknown178; // Inferred role: selected vertex; original member name unknown.
  u8 _17a[0x180 - 0x17a];
};

static_assert(offsetof(DrResMdoSeamWrkBase, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown78) == 0x78, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown8c) == 0x8c, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown98) == 0x98, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknownf0) == 0xf0, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown110) == 0x110, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown170) == 0x170, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown178) == 0x178, "");
static_assert(sizeof(DrResMdoSeamWrkBase) == 0x180, "");

} // namespace ml
