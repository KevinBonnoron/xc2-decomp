#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibVtxVertex;
} // namespace grlib

namespace ml {
class DrResMdoVertex;

class DrResMdoVtxMeshObj {
public:
  ~DrResMdoVtxMeshObj();
  static void release(DrResMdoVtxMeshObj *&obj);
  void update(const mm::Mat44 &matrix, f32 param2, f32 param3);
  void updateInit(const mm::Mat44 &matrix);
  void updateCount(f32 param);
  void updateUniform(const mm::Mat44 &matrix, f32 param2, f32 param3);
  void setActive(bool isActive, u32 index);
  void alpRender();
  void stmRender(bool isNode);
  u32 setup(const u8 *, u8 *);
  u32 calcWorkSize(const u8 *);
  void resourceInit(DrResMdoVertex *vertex);
  void releaseWork();
  bool isRender() const;

  grlib::CGLibVtxVertex *unknown00;       // Inferred role: vertex; original member name unknown.
  grlib::CGLibOneUniformBlock *unknown08; // Inferred role: uniform block; original member name unknown.
  grlib::CGLibOneUniformBlock unknown10;  // Inferred role: uniform block; original member name unknown.
  grlib::CGLibDblUniformBlock unknown38;  // Inferred role: uniform block; original member name unknown.
  bool unknown70;                         // Inferred role: vertex was activated; original member name unknown.
  u32 unknown74;                          // Inferred role: flags; original member name unknown.
  void *unknown78;                        // Inferred role: work memory; original member name unknown.
  u32 unknown80;                          // Inferred role: vertex count; original member name unknown.
  u32 unknown84;                          // Inferred role: capacity of the work memory; original member name unknown.
  u8 _88[0x8c - 0x88];
  s32 unknown8c; // Inferred role: render count; original member name unknown.
  u8 _90[0x94 - 0x90];
  s32 unknown94; // Inferred role: render count; original member name unknown.
  u8 _98[0xa0 - 0x98];
  mm::Mat44 unknowna0; // Inferred role: matrix; original member name unknown.
  mm::Vec3 unknowne0;  // Inferred role: init vector; original member name unknown.
  mm::Vec3 unknownf0;  // Inferred role: add vector; original member name unknown.
  f32 unknown100;      // Inferred role: life time; original member name unknown.
  f32 unknown104;      // Inferred role: scale divisor; original member name unknown.
  f32 unknown108;      // Inferred role: speed; original member name unknown.
  f32 unknown10c;      // Inferred role: gravity; original member name unknown.
  u32 unknown110;      // Inferred role: particle count limit; original member name unknown.
  mm::Col3 unknown114; // Inferred role: color; original member name unknown.
  f32 unknown120;      // Role and original member name unknown.
  f32 unknown124;      // Inferred role: ratio clamped to 0..1; original member name unknown.
  f32 unknown128;      // Inferred role: ratio clamped to 0..1; original member name unknown.
  f32 unknown12c;      // Role and original member name unknown.
  f32 unknown130;      // Inferred role: fade ratio; original member name unknown.
};

static_assert(offsetof(DrResMdoVtxMeshObj, unknown100) == 0x100, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown114) == 0x114, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown12c) == 0x12c, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown74) == 0x74, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown78) == 0x78, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown80) == 0x80, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown8c) == 0x8c, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown94) == 0x94, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknowne0) == 0x0e0, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknownf0) == 0x0f0, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown70) == 0x70, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown84) == 0x84, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknowna0) == 0x0a0, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknown130) == 0x130, "");
static_assert(sizeof(DrResMdoVtxMeshObj) == 0x140, "");

} // namespace ml
