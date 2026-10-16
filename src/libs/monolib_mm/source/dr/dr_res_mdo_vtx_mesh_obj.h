#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrResMdoVtxMeshObj {
public:
  void setActive(bool isActive, u32 index);

  u8 _000[0x0e0 - 0x000];
  mm::Vec3 m_initVector;
  mm::Vec3 m_addVector;
};

static_assert(offsetof(DrResMdoVtxMeshObj, m_initVector) == 0x0e0, "");
static_assert(offsetof(DrResMdoVtxMeshObj, m_addVector) == 0x0f0, "");

} // namespace ml
