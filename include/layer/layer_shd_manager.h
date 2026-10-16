#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "types.h"

namespace layer {

class LayerShdManager {
public:
  virtual ~LayerShdManager();

  u8 _008[0x4a0 - 0x008];
  mm::Mat44 m_viewProjectionMatrix;
  u8 _4e0[0x530 - 0x4e0];
  f32 m_screenWidth;
  f32 m_screenHeight;
  u8 _538[0x550 - 0x538];
  f32 m_screenOrgWidth;
  f32 m_screenOrgHeight;
  u8 _558[0x578 - 0x558];
  f32 m_gamma;
};

static_assert(offsetof(LayerShdManager, m_viewProjectionMatrix) == 0x4a0, "");
static_assert(offsetof(LayerShdManager, m_screenWidth) == 0x530, "");
static_assert(offsetof(LayerShdManager, m_screenOrgWidth) == 0x550, "");
static_assert(offsetof(LayerShdManager, m_gamma) == 0x578, "");

} // namespace layer
