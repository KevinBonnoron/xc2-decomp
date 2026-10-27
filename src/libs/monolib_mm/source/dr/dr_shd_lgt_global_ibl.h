#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
} // namespace grlib

namespace ml {

class DrLightObjGlobalIBL;
class DrMan;
class DrShdLgtMan;

namespace _dr_shd_lgt_glb_ibl {
bool CompareByPriority(const DrLightObjGlobalIBL *a, const DrLightObjGlobalIBL *b);
} // namespace _dr_shd_lgt_glb_ibl

class DrShdLgtGlobalIBL {
public:
  // Inferred layout of the per view data; the original type name is unknown.
  struct unknown001 {
    u8 _0000[0x2c];
    s32 unknown2c; // Inferred role: light object count; original member name unknown.
    u8 _0030[0x340 - 0x30];
    mm::Mat44 unknown340[0x60]; // Inferred role: sh matrices; original member name unknown.
    u8 _1b40[0x2048 - 0x1b40];
    grlib::CGLibDblUniformBlock *unknown2048; // Inferred role: uniform block; original member name unknown.
    bool unknown2050;                         // Inferred role: reset color buffer request; original member name unknown.
    u8 _2051[0x2060 - 0x2051];
  };

  void update(int viewNum);
  void render(DrShdLgtMan *man);
  void resetColorBuff(int index);
  void delViewInfo(int viewNum);
  bool isEnable() const;
  void setUniformBlock(u32 index) const;
  void setStorageBuffer(u32 index) const;
  const mm::Mat44 &getSHMatrix(u32 row, u32 column) const;
  void updateUB_ShMatrixList(u8 *work, int viewNum);

  DrMan *unknown00;        // Inferred role: dr man; original member name unknown.
  unknown001 unknown10[4]; // Inferred role: per view data; original member name unknown.
};

static_assert(offsetof(DrShdLgtGlobalIBL, unknown10) == 0x10, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown001, unknown2c) == 0x2c, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown001, unknown340) == 0x340, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown001, unknown2048) == 0x2048, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown001, unknown2050) == 0x2050, "");
static_assert(sizeof(DrShdLgtGlobalIBL::unknown001) == 0x2060, "");

} // namespace ml
