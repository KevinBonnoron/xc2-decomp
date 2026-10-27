#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace layer {

class LayerManager;
class LayerSortObj;

class LayerSortMan {
public:
  ~LayerSortMan();
  void set2DSpace(LayerSortObj *object, u32 index);
  void stock2DObj(LayerSortObj *object, s32 index);
  void stock3DObj(LayerSortObj *object, s32 index);
  void begin(const mm::Vec3 &position);
  void end();
  void alphaRender();
  void lastRender();
  void finalRender();

  LayerManager *unknown00;  // Inferred role: layer manager; original member name unknown.
  void *unknown08;          // Inferred role: allocated buffer; original member name unknown.
  LayerSortObj **unknown10; // Inferred role: 2d first objects; original member name unknown.
  LayerSortObj **unknown18; // Inferred role: 2d last objects; original member name unknown.
  LayerSortObj **unknown20; // Inferred role: 3d first objects; original member name unknown.
  LayerSortObj **unknown28; // Inferred role: 3d last objects; original member name unknown.
  u32 *unknown30;           // Inferred role: 2d used bits; original member name unknown.
  u32 *unknown38;           // Inferred role: 3d used bits; original member name unknown.
  LayerSortObj *unknown40;  // Inferred role: first sorted object; original member name unknown.
  LayerSortObj *unknown48;  // Inferred role: last sorted object; original member name unknown.
  mm::Vec3 unknown50;       // Inferred role: camera position; original member name unknown.
  f32 unknown60;            // Inferred role: unknown60; original member name unknown.
  f32 unknown64;            // Inferred role: far depth; original member name unknown.
  f32 unknown68;            // Inferred role: depth curve exponent; original member name unknown.
  u32 unknown6c;            // Inferred role: 2d slot count; original member name unknown.
  u32 unknown70;            // Inferred role: 3d slot count; original member name unknown.
  s32 unknown74;            // Inferred role: 2d used bits size; original member name unknown.
  s32 unknown78;            // Inferred role: 3d used bits size; original member name unknown.
};

static_assert(offsetof(LayerSortMan, unknown08) == 0x08, "");
static_assert(offsetof(LayerSortMan, unknown30) == 0x30, "");
static_assert(offsetof(LayerSortMan, unknown40) == 0x40, "");
static_assert(offsetof(LayerSortMan, unknown50) == 0x50, "");
static_assert(offsetof(LayerSortMan, unknown60) == 0x60, "");
static_assert(offsetof(LayerSortMan, unknown6c) == 0x6c, "");
static_assert(offsetof(LayerSortMan, unknown78) == 0x78, "");

} // namespace layer
