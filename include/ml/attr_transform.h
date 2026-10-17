#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class AttrTransform {
public:
  enum Flag {
    FLAG_MATRIX = 1 << 0,
    FLAG_QUAT = 1 << 1,
  };

  AttrTransform() : m_flags(0) {}
  void update();
  void clear();

  mm::Vec3 m_pos;
  u8 _10[0x20 - 0x10];
  mm::Vec3 m_scl;
  mm::Mat44 m_matrix;
  mm::Mat44 m_worldMatrix;
  u8 _b0[0xf0 - 0xb0];
  mm::Vec3 m_rot;
  u8 _100[0x110 - 0x100];
  mm::Quat m_quat;
  u8 _120[0x130 - 0x120];
  u32 m_flags;
};

static_assert(offsetof(AttrTransform, m_scl) == 0x20, "");
static_assert(offsetof(AttrTransform, m_matrix) == 0x30, "");
static_assert(offsetof(AttrTransform, m_worldMatrix) == 0x70, "");
static_assert(offsetof(AttrTransform, m_rot) == 0xf0, "");
static_assert(offsetof(AttrTransform, m_quat) == 0x110, "");
static_assert(offsetof(AttrTransform, m_flags) == 0x130, "");
static_assert(sizeof(AttrTransform) == 0x140, "");

} // namespace ml
