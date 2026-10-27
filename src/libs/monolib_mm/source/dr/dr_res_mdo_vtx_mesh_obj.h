#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibVtxVertex;
} // namespace grlib

namespace ml {
class DrResMdoVertex;

class DrResMdoVtxMeshObj {
public:
  void setActive(bool isActive, u32 index);
  void alpRender();
  u32 setup(const u8 *, u8 *);
  u32 calcWorkSize(const u8 *);
  void resourceInit(DrResMdoVertex *vertex);
  void releaseWork();
  bool isRender() const;

  grlib::CGLibVtxVertex *unknown00;       // Inferred role: vertex; original member name unknown.
  grlib::CGLibOneUniformBlock *unknown08; // Inferred role: uniform block; original member name unknown.
  grlib::CGLibOneUniformBlock unknown10;  // Inferred role: uniform block; original member name unknown.
  grlib::CGLibDblUniformBlock unknown38;  // Inferred role: uniform block; original member name unknown.
  u8 _70[0x74 - 0x70];
  u32 unknown74;   // Inferred role: flags; original member name unknown.
  void *unknown78; // Inferred role: work memory; original member name unknown.
  u32 unknown80;   // Inferred role: vertex count; original member name unknown.
  u8 _84[0x8c - 0x84];
  s32 unknown8c; // Inferred role: render count; original member name unknown.
  u8 _90[0x94 - 0x90];
  s32 unknown94; // Inferred role: render count; original member name unknown.
  u8 _98[0x0e0 - 0x098];
  mm::Vec3 unknowne0; // Inferred role: init vector; original member name unknown.
  mm::Vec3 unknownf0; // Inferred role: add vector; original member name unknown.
};

static_assert(offsetof(DrResMdoVtxMeshObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown74) == 0x74, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown78) == 0x78, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown80) == 0x80, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown8c) == 0x8c, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown94) == 0x94, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknowne0) == 0x0e0, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknownf0) == 0x0f0, "");

} // namespace ml
