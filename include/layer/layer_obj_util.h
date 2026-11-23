#pragma once
#include <stddef.h>

#include "layer/layer_acc_obj_base.h"
#include "mm_math/mm_pnt.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace grlib {
class CGLibDblUniformBlock;
} // namespace grlib

namespace layer {

struct LayerRenderView;
struct LayerResMatrix;
struct LayerResColor;
struct LayerResUvParam;
struct LayerResNode;
struct LayerResViewPortInfo;
struct LayerViewPort;
struct LyrLayoutPosData;

enum LayerUniType {
  LAYER_UNI_TYPE_UNKNOWN_5 = 5,
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
  f32 unknown00;     // Inferred role: scale x; original member name unknown.
  f32 unknown04;     // Inferred role: scale y; original member name unknown.
  f32 unknown08;     // Inferred role: width; original member name unknown.
  f32 unknown0c;     // Inferred role: height; original member name unknown.
  s16 m_pixelX;      // Inferred role: pixel x; named after the game accessor layer::LayerAccObjBase::getPixelX.
  s16 m_pixelY;      // Inferred role: pixel y; named after the game accessor layer::LayerAccObjBase::getPixelY.
  s16 m_pixelWidth;  // Inferred role: pixel width; named after the game accessor layer::LayerAccObjBase::getPixelWidth.
  s16 m_pixelHeight; // Inferred role: pixel height; named after the game accessor layer::LayerAccObjBase::getPixelHeight.
  u8 m_centerType;   // Inferred role: center type, index of LayerObjUtil::s_CallMdl; named after the game accessor layer::LayerAccObjBase::getCenterType.
};

static_assert(offsetof(LayerResRenderInfo, unknown00) == 0x00, "");
static_assert(offsetof(LayerResRenderInfo, unknown04) == 0x04, "");
static_assert(offsetof(LayerResRenderInfo, unknown08) == 0x08, "");
static_assert(offsetof(LayerResRenderInfo, m_pixelHeight) == 0x16, "");
static_assert(offsetof(LayerResRenderInfo, m_centerType) == 0x18, "");
static_assert(sizeof(LayerResRenderInfo) == 0x1c, "");

// Evidence: LayerObjUtil::calcDispInfo raises 0x00 and 0x04 and lowers 0x08 and 0x0c to the screen corners of an object;
// LayerObj::LayerObj and the applyParams overrides write 0x08 as one 8-byte copy and 0x00 and 0x04 one by one.
struct LayerResDispInfo {
  // Inferred helper: empties the bounds before calcDispInfo grows them; original name unknown.
  void unknown001() {
    unknown00 = unknown04 = -100000.0f;
    unknown08.x = unknown08.y = 100000.0f;
  }

  f32 unknown00;          // Inferred role: max x; original member name unknown.
  f32 unknown04;          // Inferred role: max y; original member name unknown.
  mm::Pnt<f32> unknown08; // Inferred role: min x and y; original member name unknown.
};

static_assert(offsetof(LayerResDispInfo, unknown08) == 0x08, "");
static_assert(sizeof(LayerResDispInfo) == 0x10, "");

class LayerObjUtil {
public:
  static void calcDispInfo(LayerResDispInfo &disp, const LayerResMatrix &matrix, const LayerResRenderInfo &info);
  static void calcLayoutDispInfo(LayerResDispInfo &disp, const LayerResMatrix &matrix, const LayerResRenderInfo &info);
  static void calcLayerRenderView(LayerRenderView &result, LayerResViewPortInfo &viewPort, grlib::CGLibDblUniformBlock *&uniform, const LayerViewPort &port, const LayerRenderView *view,
                                  const LayerResMatrix *matrix);
  static void releaseWorldMatrixUniform(grlib::CGLibDblUniformBlock *&uniform);
  static void calcLayerColor(LayerResColor &result, const LayerResColor &base, const LayerResColor &parent);
  static void updateUnitUniformBlock(f32 *uniform);
  static void updateMatrixUniformBlock(f32 *uniform, const LayerResMatrix *matrix);
  static void updateUvCalcUniformBlock(f32 *uniform, const LayerResUvParam &param, u32 flags);
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
  static void calcPlaceNode(LayerResNode *node, const LayerResNode *parent);
  static void calcLayerScaleMatrix(LayerResMatrix &result, const LayerBasePos &base, f32 x, f32 y);
  static void calcMatrixToZBuffPos(f32 &depth, f32 &param, const mm::Mat44 &matrix);
  static void createWorldMatrixUniform(grlib::CGLibDblUniformBlock *&uniform, const mm::Mat44 &matrix, f32 depth);
  static u32 getUniformBlockSizeAlOff(LayerUniType type);
  static u32 getUniformBlockSize(LayerUniType type);
  static void calcPosData_Pixel_Up(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y);
  static void calcPosData_Correction_Up(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y);
  static void getLayoutInfo(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y);
  static void calcLayer3DSpaceTransRotScaleMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void calcLayerRotMatrix(LayerResMatrix &result, const LayerBasePos &base, f32 x, f32 y);
  static void calcLayerTransRotScaleMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void calcLayerTransRotScaleFontMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void calcLayerTransRotScaleLaoutMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void calcLayerTransRotScaleSWFMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void calcLayer3DSpaceTransRotScaleFontMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void calcLayer3DSpaceTransRotScaleMatrix(LayerResMatrix &result, const LayerBasePos &base);

  static const u16 UNIFORM_BLOCK_SIZE[];
  static void (*s_CallDataPos[])(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y);
  static void (*s_CallScl[])(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info);
  static void (*s_CallPos[])(f32 *pos, const LayerBasePos &base);
  static void (*s_CallMdl[])(f32 *pos, f32 *size, const f32 *scl, const LayerBasePos &base);
  static void (*s_CallSwfScl[])(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info);
};

} // namespace layer
