#pragma once
#include <stddef.h>

#include "dr/dr_mdo_setup.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
struct Col3;
} // namespace mm

namespace ml {
class DrMdoSmlShadowObj;
struct MdsMatCharMkTexTbl;

class DrMdoCtl : public DrMdoSetup {
public:
  DrMdoCtl(int viewNum);
  void setMatrix(const mm::Mat44 &matrix);
  void setOffsetPos(const mm::Vec3 &position);
  const mm::Mat44 &getMatrix() const;
  void setFrameSpd(f32 speed) { m_frameSpd = speed; }

  u8 _38[0x40 - 0x38];
  mm::Col3 *m_avatarMapColors;
  const MdsMatCharMkTexTbl *m_charMkTextures;
  u8 _50[0x58 - 0x50];
  DrMdoSmlShadowObj *m_smlShadow;
  u8 _60[0x70 - 0x60];
  mm::Mat44 m_matrix;
  u8 _b0[0xd0 - 0xb0];
  f32 m_alphas[2];
  f32 m_bloom;
  f32 m_frameSpd;
  f32 m_alpha;
  u8 _e4[0xe8 - 0xe4];
  f32 m_scale;
  u8 _ec[0xf0 - 0xec];
  bool m_isGpuRender;
  u8 _f1[0xfc - 0xf1];
  u32 m_drawFlags;
  u32 m_alphaFlags;
  u8 _104[0x110 - 0x104];
  mm::Vec3 m_aabbMax;
  mm::Vec3 m_aabbMin;
  mm::Vec3 m_center;
  u8 _140[0x160 - 0x140];
  f32 m_length;
  u8 _164[0x16a - 0x164];
  u8 m_charMkTextureCount;
  u8 _16b[0x180 - 0x16b];
  s16 m_nodeMax;
  u8 _182[0x190 - 0x182];
};

static_assert(offsetof(DrMdoCtl, m_avatarMapColors) == 0x40, "");
static_assert(offsetof(DrMdoCtl, m_charMkTextures) == 0x48, "");
static_assert(offsetof(DrMdoCtl, m_smlShadow) == 0x58, "");
static_assert(offsetof(DrMdoCtl, m_matrix) == 0x70, "");
static_assert(offsetof(DrMdoCtl, m_alphas) == 0xd0, "");
static_assert(offsetof(DrMdoCtl, m_bloom) == 0xd8, "");
static_assert(offsetof(DrMdoCtl, m_frameSpd) == 0xdc, "");
static_assert(offsetof(DrMdoCtl, m_alpha) == 0xe0, "");
static_assert(offsetof(DrMdoCtl, m_scale) == 0xe8, "");
static_assert(offsetof(DrMdoCtl, m_isGpuRender) == 0xf0, "");
static_assert(offsetof(DrMdoCtl, m_drawFlags) == 0xfc, "");
static_assert(offsetof(DrMdoCtl, m_alphaFlags) == 0x100, "");
static_assert(offsetof(DrMdoCtl, m_aabbMax) == 0x110, "");
static_assert(offsetof(DrMdoCtl, m_aabbMin) == 0x120, "");
static_assert(offsetof(DrMdoCtl, m_center) == 0x130, "");
static_assert(offsetof(DrMdoCtl, m_length) == 0x160, "");
static_assert(offsetof(DrMdoCtl, m_charMkTextureCount) == 0x16a, "");
static_assert(offsetof(DrMdoCtl, m_nodeMax) == 0x180, "");

} // namespace ml
