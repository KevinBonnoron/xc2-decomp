#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrResMdoVtxMeshObj {
public:
  void setActive(bool isActive, u32 index);
  void alpRender();
  u32 setup(const u8 *, u8 *);
  u32 calcWorkSize(const u8 *);

  u8 _000[0x0e0 - 0x000];
  mm::Vec3 unknowne0; // Inferred role: init vector; original member name unknown.
  mm::Vec3 unknownf0; // Inferred role: add vector; original member name unknown.
};

static_assert(offsetof(DrResMdoVtxMeshObj, unknowne0) == 0x0e0, "");
static_assert(offsetof(DrResMdoVtxMeshObj, unknownf0) == 0x0f0, "");

} // namespace ml
