#include "layer/layer_obj_util.h"

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"

namespace layer {

void LayerObjUtil::releaseWorldMatrixUniform(grlib::CGLibDblUniformBlock *&uniform) {
  if (uniform != nullptr) {
    delete uniform;
    uniform = nullptr;
  }
}

void LayerObjUtil::calcLayerColor(LayerResColor &result, const LayerResColor &base, const LayerResColor &parent) {
  result.unknown00.r = base.unknown00.r * parent.unknown00.r;
  result.unknown00.g = base.unknown00.g * parent.unknown00.g;
  result.unknown00.b = base.unknown00.b * parent.unknown00.b;
  result.unknown00.a = base.unknown00.a * parent.unknown00.a;
  result.unknown10.r = base.unknown10.r + parent.unknown10.r;
  result.unknown10.g = base.unknown10.g + parent.unknown10.g;
  result.unknown10.b = base.unknown10.b + parent.unknown10.b;
}

void LayerObjUtil::updateUnitUniformBlock(f32 *uniform) {
  uniform[0] = 1.0f;
  uniform[5] = 1.0f;
  uniform[7] = 0.0f;
  uniform[3] = 0.0f;
  uniform[4] = 0.0f;
  uniform[1] = 0.0f;
  uniform[2] = 0.0f;
}

void LayerObjUtil::updateMatrixUniformBlock(f32 *uniform, const LayerResMatrix *matrix) {
  uniform[0] = matrix->unknown08;
  uniform[1] = matrix->unknown14;
  uniform[3] = matrix->unknown00;
  uniform[4] = matrix->unknown10;
  uniform[5] = matrix->unknown0c;
  f32 y = matrix->unknown04;
  uniform[6] = 0.0f;
  uniform[7] = y;
  uniform[2] = 0.0f;
}

void LayerObjUtil::updateColorUniformBlock(f32 *uniform, const LayerResColor &color) {
  uniform[0] = color.unknown00.r;
  uniform[1] = color.unknown00.g;
  uniform[2] = color.unknown00.b;
  uniform[3] = color.unknown00.a;
  uniform[4] = color.unknown10.r;
  uniform[5] = color.unknown10.g;
  uniform[6] = color.unknown10.b;
  uniform[7] = 0.0f;
}

u32 LayerObjUtil::getUniformBlockAligment(u32 size) {
  u32 padding = 0;
  if (size & 0xff) {
    padding = 0x100 - (size & 0xff);
  }
  return padding + size;
}

void LayerObjUtil::calcPos_Pixel_Up(f32 *pos, const LayerBasePos &base) {
  pos[0] = base.unknown00 * LayerManager::get()->getScreenCalcPosWidth();
  pos[1] = base.unknown04 * LayerManager::get()->getScreenCalcPosHeight();
}

void LayerObjUtil::calcPos_Correction_Up(f32 *pos, const LayerBasePos &base) {
  pos[0] = base.unknown00 * LayerManager::get()->getScreenCalcPosWidth();
  pos[1] = base.unknown04 * LayerManager::get()->getScreenCalcPosHeight();
}

void LayerObjUtil::calcPos_Pixel_Down(f32 *pos, const LayerBasePos &base) {
  pos[0] = base.unknown00 * LayerManager::get()->getScreenCalcPosWidth();
  pos[1] = (LayerManager::get()->getScreenHeight() - base.unknown04) * LayerManager::get()->getScreenCalcPosHeight();
}

void LayerObjUtil::calcPos_Correction_Down(f32 *pos, const LayerBasePos &base) {
  pos[0] = base.unknown00 * LayerManager::get()->getScreenCalcPosWidth();
  pos[1] = (LayerManager::get()->getScreenRatioHeight() - base.unknown04) * LayerManager::get()->getScreenCalcPosHeight();
}

void LayerObjUtil::calcScl_Correction_Up(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 width = info.unknown08 * LayerManager::get()->getScreenCalcSclWidth();
  f32 height = info.unknown0c * LayerManager::get()->getScreenCalcSclHeight();
  scl[0] = width * base.unknown0c;
  scl[1] = height * base.unknown10;
}

void LayerObjUtil::calcSwfScl_Correction_Up(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 size;
  if (info.unknown08 > info.unknown0c) {
    size = info.unknown08;
  } else {
    size = info.unknown0c;
  }
  f32 width = size * LayerManager::get()->getScreenCalcSclWidth();
  f32 height = size * LayerManager::get()->getScreenCalcSclHeight();
  scl[0] = width * base.unknown0c;
  scl[1] = height * base.unknown10;
}

void LayerObjUtil::calcScl_Pixel_Up(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 pixelWidth = info.unknown14 + info.unknown10;
  f32 width = LayerManager::get()->getScreenCalcSclWidth() * pixelWidth;
  f32 pixelHeight = info.unknown16 + info.unknown12;
  f32 height = LayerManager::get()->getScreenCalcSclHeight() * pixelHeight;
  scl[0] = base.unknown0c * width;
  scl[1] = height * base.unknown10;
}

void LayerObjUtil::calcSwfScl_Pixel_Up(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 width = info.unknown14 + info.unknown10;
  f32 height = info.unknown16 + info.unknown12;
  f32 size = height;
  if (width > height) {
    size = width;
  }
  f32 sclWidth = LayerManager::get()->getScreenCalcSclWidth() * size;
  f32 sclHeight = LayerManager::get()->getScreenCalcSclHeight() * size;
  scl[0] = base.unknown0c * sclWidth;
  scl[1] = sclHeight * base.unknown10;
}

void LayerObjUtil::calcMdlPos_Center_Up(f32 *pos, f32 *size, const f32 *scl, const LayerBasePos &base) {
  size[0] = base.unknown14 * scl[0];
  size[1] = base.unknown18 * scl[1];
}

void LayerObjUtil::calcMdlPos_Center_Down(f32 *pos, f32 *size, const f32 *scl, const LayerBasePos &base) {
  size[0] = base.unknown14 * scl[0];
  size[1] = (base.unknown18 + 1.0f) * scl[1];
  pos[1] -= scl[1];
}

void LayerObjUtil::calcMdlPos_Center_Center(f32 *pos, f32 *size, const f32 *scl, const LayerBasePos &base) {
  size[0] = (base.unknown14 + 0.5f) * scl[0];
  size[1] = (base.unknown18 + 0.5f) * scl[1];
  pos[0] = pos[0] - scl[0] * 0.5f;
  pos[1] = pos[1] - scl[1] * 0.5f;
}

void LayerObjUtil::calcLayerMatrix(LayerResMatrix &result, const LayerResMatrix &base, const LayerResMatrix &parent) {
  result.unknown08 = base.unknown08 * parent.unknown08 + base.unknown10 * parent.unknown14;
  result.unknown14 = base.unknown14 * parent.unknown08 + base.unknown0c * parent.unknown14;
  result.unknown00 = base.unknown00 * parent.unknown08 + base.unknown04 * parent.unknown14 + parent.unknown00;
  result.unknown10 = base.unknown08 * parent.unknown10 + base.unknown10 * parent.unknown0c;
  result.unknown0c = base.unknown14 * parent.unknown10 + base.unknown0c * parent.unknown0c;
  result.unknown04 = base.unknown00 * parent.unknown10 + base.unknown04 * parent.unknown0c + parent.unknown04;
}

void LayerObjUtil::calcLayerScaleMatrix(LayerResMatrix &result, const LayerBasePos &base, f32 x, f32 y) {
  result.unknown08 = base.unknown0c;
  result.unknown10 = 0.0f;
  result.unknown14 = 0.0f;
  result.unknown00 = 0.0f;
  result.unknown0c = base.unknown10;
  result.unknown04 = 0.0f;
}

u32 LayerObjUtil::getUniformBlockSizeAlOff(LayerUniType type) { return UNIFORM_BLOCK_SIZE[type]; }

u32 LayerObjUtil::getUniformBlockSize(LayerUniType type) { return getUniformBlockAligment(UNIFORM_BLOCK_SIZE[type]); }

void LayerObjUtil::getLayoutInfo(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y) { s_CallDataPos[LayerManager::get()->unknown9c](info, data, type, x, y); }

} // namespace layer
