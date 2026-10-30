#pragma once
#include <stddef.h>

#include "layer/layer_acc_obj_base.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace grlib {
class CGLibDblUniformBlock;
} // namespace grlib

namespace layer {

struct LayerResMatrix;
struct LayerResColor;
struct LyrLayoutPosData;

enum LayerUniType {
  LAYER_UNI_TYPE_UNKNOWN_9 = 9,
  LAYER_UNI_TYPE_UNKNOWN_10 = 10,
};

struct LayerBasePos {
  f32 unknown00; // Inferred role: pos x; original member name unknown.
  f32 unknown04; // Inferred role: pos y; original member name unknown.
  f32 unknown08; // Inferred role: rot; original member name unknown.
  f32 unknown0c; // Inferred role: scl x; original member name unknown.
  f32 unknown10; // Inferred role: scl y; original member name unknown.
  f32 unknown14; // Inferred role: anchor x; original member name unknown.
  f32 unknown18; // Inferred role: anchor y; original member name unknown.
};

static_assert(offsetof(LayerBasePos, unknown00) == 0x00, "");
static_assert(offsetof(LayerBasePos, unknown18) == 0x18, "");
static_assert(sizeof(LayerBasePos) == 0x1c, "");

struct LayerResRenderInfo {
  u8 _00[0x08];
  f32 unknown08; // Inferred role: width; original member name unknown.
  f32 unknown0c; // Inferred role: height; original member name unknown.
  s16 unknown10; // Inferred role: pixel x; original member name unknown.
  s16 unknown12; // Inferred role: pixel y; original member name unknown.
  s16 unknown14; // Inferred role: pixel width; original member name unknown.
  s16 unknown16; // Inferred role: pixel height; original member name unknown.
};

static_assert(offsetof(LayerResRenderInfo, unknown08) == 0x08, "");
static_assert(offsetof(LayerResRenderInfo, unknown16) == 0x16, "");

class LayerObjUtil {
public:
  static void releaseWorldMatrixUniform(grlib::CGLibDblUniformBlock *&uniform);
  static void calcLayerColor(LayerResColor &result, const LayerResColor &base, const LayerResColor &parent);
  static void updateUnitUniformBlock(f32 *uniform);
  static void updateMatrixUniformBlock(f32 *uniform, const LayerResMatrix *matrix);
  static void updateColorUniformBlock(f32 *uniform, const LayerResColor &color);
  static u32 getUniformBlockAligment(u32 size);
  static void calcPos_Pixel_Up(f32 *pos, const LayerBasePos &base);
  static void calcPos_Correction_Up(f32 *pos, const LayerBasePos &base);
  static void calcPos_Pixel_Down(f32 *pos, const LayerBasePos &base);
  static void calcPos_Correction_Down(f32 *pos, const LayerBasePos &base);
  static void calcScl_Correction_Up(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void calcSwfScl_Correction_Up(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void updatePosMatrixUniformBlock(f32 *uniform, const LayerResMatrix *matrix, const LayerResMatrix &parent, f32 depth, bool flag);
  static void calcLayerInvertMatrix(mm::Vec3 &pos, mm::Vec3 &scl, const LayerResMatrix &matrix);
  static void calcScl_Pixel_Up(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void calcSwfScl_Pixel_Up(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void calcMdlPos_Center_Up(f32 *pos, f32 *size, const f32 *scl, const LayerBasePos &base);
  static void calcMdlPos_Center_Down(f32 *pos, f32 *size, const f32 *scl, const LayerBasePos &base);
  static void calcMdlPos_Center_Center(f32 *pos, f32 *size, const f32 *scl, const LayerBasePos &base);
  static void calcLayerMatrix(LayerResMatrix &result, const LayerResMatrix &base, const LayerResMatrix &parent);
  static void calcLayerScaleMatrix(LayerResMatrix &result, const LayerBasePos &base, f32 x, f32 y);
  static u32 getUniformBlockSizeAlOff(LayerUniType type);
  static u32 getUniformBlockSize(LayerUniType type);
  static void calcPosData_Pixel_Up(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y);
  static void calcPosData_Correction_Up(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y);
  static void getLayoutInfo(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y);

  static const u16 UNIFORM_BLOCK_SIZE[];
  static void (*s_CallDataPos[])(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y);
};

} // namespace layer
