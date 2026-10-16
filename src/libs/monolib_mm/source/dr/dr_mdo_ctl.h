#pragma once
#include <stddef.h>

#include "dr/dr_mdo_mat.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
struct Col3;
} // namespace mm

namespace ml {

class DrMdoCtl : public DrMdoMat {
public:
  const mm::Mat44 &getMatrix() const;

  u8 _38[0x40 - 0x38];
  mm::Col3 *m_avatarMapColors;
  u8 _48[0x70 - 0x48];
  mm::Mat44 m_matrix;
  u8 _b0[0xd8 - 0xb0];
  f32 m_bloom;
  f32 m_frameSpd;
  u8 _e0[0x110 - 0xe0];
  mm::Vec3 m_aabbMax;
  mm::Vec3 m_aabbMin;
  mm::Vec3 m_center;
  u8 _140[0x160 - 0x140];
  f32 m_length;
};

static_assert(offsetof(DrMdoCtl, m_avatarMapColors) == 0x40, "");
static_assert(offsetof(DrMdoCtl, m_matrix) == 0x70, "");
static_assert(offsetof(DrMdoCtl, m_bloom) == 0xd8, "");
static_assert(offsetof(DrMdoCtl, m_frameSpd) == 0xdc, "");
static_assert(offsetof(DrMdoCtl, m_aabbMax) == 0x110, "");
static_assert(offsetof(DrMdoCtl, m_aabbMin) == 0x120, "");
static_assert(offsetof(DrMdoCtl, m_center) == 0x130, "");
static_assert(offsetof(DrMdoCtl, m_length) == 0x160, "");

} // namespace ml
