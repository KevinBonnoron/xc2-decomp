#include "layer/layer_obj_util.h"

#include <math.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_acc_layout_binary.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_render_view.h"
#include "layer/layer_res_view_port_info.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_view_port.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"

namespace layer {

void LayerObjUtil::releaseWorldMatrixUniform(grlib::CGLibDblUniformBlock *&uniform) {
  if (uniform != nullptr) {
    delete uniform;
    uniform = nullptr;
  }
}

void LayerObjUtil::calcLayoutDispInfo(LayerResDispInfo &disp, const LayerResMatrix &matrix, const LayerResRenderInfo &info) {
  f32 right = info.m_pixelX + info.m_pixelWidth;
  f32 bottom = info.m_pixelY + info.m_pixelHeight;
  f32 left = info.m_pixelX;
  f32 top = info.m_pixelY;
  f32 rightX = right * matrix.unknown08 * LayerManager::get()->getScreenCalcSclWidth();
  f32 bottomX = bottom * matrix.unknown14 * LayerManager::get()->getScreenCalcSclWidth();
  f32 leftX = left * matrix.unknown08 * LayerManager::get()->getScreenCalcSclWidth();
  f32 topX = top * matrix.unknown14 * LayerManager::get()->getScreenCalcSclWidth();
  f32 rightY = right * matrix.unknown10 * LayerManager::get()->getScreenCalcSclHeight();
  f32 bottomY = bottom * matrix.unknown0c * LayerManager::get()->getScreenCalcSclHeight();
  f32 leftY = left * matrix.unknown10 * LayerManager::get()->getScreenCalcSclHeight();
  f32 topY = top * matrix.unknown0c * LayerManager::get()->getScreenCalcSclHeight();
  f32 x[4] = {rightX + bottomX + matrix.unknown00, leftX + topX + matrix.unknown00, bottomX + leftX + matrix.unknown00, rightX + topX + matrix.unknown00};
  f32 y[4] = {rightY + bottomY + matrix.unknown04, leftY + topY + matrix.unknown04, bottomY + leftY + matrix.unknown04, rightY + topY + matrix.unknown04};
  for (s32 i = 0; i < 4; i++) {
    if (disp.unknown00 < x[i]) {
      disp.unknown00 = x[i];
    }
    if (disp.unknown08.x > x[i]) {
      disp.unknown08.x = x[i];
    }
  }
  for (s32 i = 0; i < 4; i++) {
    if (disp.unknown04 < y[i]) {
      disp.unknown04 = y[i];
    }
    if (disp.unknown08.y > y[i]) {
      disp.unknown08.y = y[i];
    }
  }
}

void LayerObjUtil::calcLayerRenderView(LayerRenderView &result, LayerResViewPortInfo &viewPort, grlib::CGLibDblUniformBlock *&uniform, const LayerViewPort &port, const LayerRenderView *view,
                                       const LayerResMatrix *matrix) {
  LayerShdManager *shader = LayerManager::get()->m_layerShdManager;
  result = *view;
  f32 posX = matrix->unknown00 * shader->m_screenWidth;
  f32 posY = matrix->unknown04 * shader->m_screenHeight * (1.0f / shader->m_screenRatioHeight);
  viewPort.m_layerViewPort.unknown00 = posX + port.unknown00;
  viewPort.m_layerViewPort.unknown04 = posY + port.unknown04;
  viewPort.m_layerViewPort.unknown0c = port.unknown0c;
  viewPort.m_layerViewPort.unknown08 = port.unknown08;
  if (uniform == nullptr) {
    uniform = new (LayerManager::get()->unknown2c) grlib::CGLibDblUniformBlock();
    uniform->setup(0x40);
  }

  f32 *buff = static_cast<f32 *>(uniform->getBuff());
  f32 x = viewPort.m_layerViewPort.unknown00 * shader->unknown558 / shader->m_screenWidth;
  f32 y = shader->unknown558 * viewPort.m_layerViewPort.unknown04 / shader->m_screenHeight;
  f32 sclX = 1.0f / (shader->unknown558 * viewPort.m_layerViewPort.unknown08 / shader->m_screenWidth);
  f32 sclY = 1.0f / (shader->unknown558 * viewPort.m_layerViewPort.unknown0c / shader->m_screenHeight);
  buff[0] = sclX;
  buff[1] = sclY;
  buff[2] = sclX - 1.0f - x * 2.0f * sclX;
  buff[3] = -(sclY - 1.0f - y * 2.0f * sclY);
  uniform->updateData();
  viewPort.unknown18 = uniform;
  result.m_layerResViewPortInfo = &viewPort;
}

void LayerObjUtil::calcLayerColor(LayerResColor &result, const LayerResColor &base, const LayerResColor &parent) {
  result.m_mulCol.r = base.m_mulCol.r * parent.m_mulCol.r;
  result.m_mulCol.g = base.m_mulCol.g * parent.m_mulCol.g;
  result.m_mulCol.b = base.m_mulCol.b * parent.m_mulCol.b;
  result.m_mulCol.a = base.m_mulCol.a * parent.m_mulCol.a;
  result.m_addCol.r = base.m_addCol.r + parent.m_addCol.r;
  result.m_addCol.g = base.m_addCol.g + parent.m_addCol.g;
  result.m_addCol.b = base.m_addCol.b + parent.m_addCol.b;
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

void LayerObjUtil::updateUvCalcUniformBlock(f32 *uniform, const LayerResUvParam &param, u32 flags) {
  const unknown023 &uv = param.unknown00[2];
  f32 sclU = uv.unknown08;
  f32 sclV = uv.unknown0c;
  f32 offU = 0.0f;
  if (flags & 0x100000) {
    sclU = -sclU;
    offU = 1.0f;
  }
  f32 offV = 0.0f;
  if (flags & 0x200000) {
    sclV = -sclV;
    offV = 1.0f;
  }
  f32 u = offU + uv.unknown00.x;
  f32 v = offV + uv.unknown00.y;
  if (uv.unknown10 == 0.0f) {
    uniform[0] = sclU;
    uniform[1] = 0.0f;
    uniform[2] = 0.0f;
    uniform[3] = u;
    uniform[4] = 0.0f;
    uniform[5] = sclV;
    uniform[6] = 0.0f;
    uniform[7] = v;
  } else {
    f32 sinRot = sinf(uv.unknown10);
    f32 cosRot = cosf(uv.unknown10);
    f32 anchorX = sclU * 0.5f + u;
    f32 anchorY = sclV * 0.5f + v;
    f32 rotX = anchorX + (cosRot * -anchorX + sinRot * -anchorY);
    f32 rotY = anchorY + (-sinRot * -anchorX + cosRot * -anchorY);
    f32 x = u * cosRot + v * sinRot;
    f32 y = u * -sinRot + v * cosRot;
    uniform[0] = sclU * cosRot;
    uniform[1] = sclV * sinRot;
    uniform[2] = 0.0f;
    uniform[3] = x + rotX;
    uniform[4] = sclU * -sinRot;
    uniform[5] = sclV * cosRot;
    uniform[6] = 0.0f;
    uniform[7] = y + rotY;
  }
}

void LayerObjUtil::calcLayerInvertMatrix(mm::Vec3 &pos, mm::Vec3 &scl, const LayerResMatrix &matrix) {
  pos.x = matrix.unknown0c;
  pos.y = -matrix.unknown14;
  pos.z = matrix.unknown14 * matrix.unknown04 - matrix.unknown0c * matrix.unknown00;
  f32 inv = 1.0f / (matrix.unknown08 * pos.x + matrix.unknown10 * pos.y);
  scl.x = -matrix.unknown10;
  scl.y = matrix.unknown08;
  scl.z = -(matrix.unknown08 * matrix.unknown04 - matrix.unknown10 * matrix.unknown00);
  pos *= inv;
  scl *= inv;
}

void LayerObjUtil::updateColorUniformBlock(f32 *uniform, const LayerResColor &color) {
  uniform[0] = color.m_mulCol.r;
  uniform[1] = color.m_mulCol.g;
  uniform[2] = color.m_mulCol.b;
  uniform[3] = color.m_mulCol.a;
  uniform[4] = color.m_addCol.r;
  uniform[5] = color.m_addCol.g;
  uniform[6] = color.m_addCol.b;
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
  f32 pixelWidth = info.m_pixelWidth + info.m_pixelX;
  f32 width = LayerManager::get()->getScreenCalcSclWidth() * pixelWidth;
  f32 pixelHeight = info.m_pixelHeight + info.m_pixelY;
  f32 height = LayerManager::get()->getScreenCalcSclHeight() * pixelHeight;
  scl[0] = base.unknown0c * width;
  scl[1] = height * base.unknown10;
}

void LayerObjUtil::calcSwfScl_Pixel_Up(f32 *scl, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 width = info.m_pixelWidth + info.m_pixelX;
  f32 height = info.m_pixelHeight + info.m_pixelY;
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

void LayerObjUtil::calcPosData_Pixel_Up(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y) {
  info[2] = static_cast<f32>(data->unknown30 - data->unknown2c) / x;
  info[3] = static_cast<f32>(data->unknown32 - data->unknown2e) / y;
  s16 left = data->unknown2c;
  info[0] = left;
  s16 top = data->unknown2e;
  info[1] = top;
  f32 offset;
  if (type == LAYER_CENTER_TYPE_UNKNOWN_1) {
    offset = data->unknown32;
  } else if (type == LAYER_CENTER_TYPE_CENTER) {
    info[0] = left + static_cast<f32>(data->unknown30 - data->unknown2c) * 0.5f;
    offset = static_cast<f32>(data->unknown32 - data->unknown2e) * 0.5f;
  } else {
    return;
  }
  info[1] = top + offset;
}

void LayerObjUtil::calcPosData_Correction_Up(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y) {
  info[0] = data->unknown20;
  info[1] = data->unknown24;
  info[2] = data->unknown18;
  info[3] = data->unknown1c;
  if (type == LAYER_CENTER_TYPE_UNKNOWN_1) {
    f32 height = data->unknown1c;
    info[1] += height * LayerManager::get()->getScreenCalcPosHeight();
  } else if (type == LAYER_CENTER_TYPE_CENTER) {
    f32 width = data->unknown18;
    info[0] += width * 0.5f * LayerManager::get()->getScreenCalcPosWidth();
    f32 height = data->unknown1c;
    info[1] += height * 0.5f * LayerManager::get()->getScreenCalcPosHeight();
  }
}

u32 LayerObjUtil::getUniformBlockSizeAlOff(LayerUniType type) { return UNIFORM_BLOCK_SIZE[type]; }

u32 LayerObjUtil::getUniformBlockSize(LayerUniType type) { return getUniformBlockAligment(UNIFORM_BLOCK_SIZE[type]); }

void LayerObjUtil::getLayoutInfo(f32 *info, const LyrLayoutPosData *data, LayerCenterType type, f32 x, f32 y) { s_CallDataPos[LayerManager::get()->m_coordinate](info, data, type, x, y); }

void LayerObjUtil::calcLayer3DSpaceTransRotScaleMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 sinRot = sinf(base.unknown08);
  f32 cosRot = cosf(base.unknown08);
  f32 width = static_cast<f32>(info.m_pixelWidth + info.m_pixelX) * LayerManager::get()->unknown98;
  f32 height = static_cast<f32>(info.m_pixelHeight + info.m_pixelY) * LayerManager::get()->unknown98;
  f32 scl[2];
  scl[0] = width * base.unknown0c;
  scl[1] = base.unknown10 * height;
  f32 pos[2];
  pos[0] = base.unknown00 * LayerManager::get()->unknown98;
  pos[1] = base.unknown04 * LayerManager::get()->unknown98;
  f32 size[2];
  s_CallMdl[info.m_centerType](pos, size, scl, base);
  f32 x = size[0] + (cosRot * -size[0] + sinRot * -size[1]);
  f32 y = size[1] + (-sinRot * -size[0] + cosRot * -size[1]);
  result.unknown08 = cosRot * scl[0];
  result.unknown14 = sinRot * scl[1];
  result.unknown00 = x + pos[0];
  result.unknown10 = -(sinRot * scl[0]);
  result.unknown0c = cosRot * scl[1];
  result.unknown04 = y + pos[1];
}

void LayerObjUtil::calcLayerRotMatrix(LayerResMatrix &result, const LayerBasePos &base, f32 x, f32 y) {
  f32 sinRot = sinf(base.unknown08);
  f32 cosRot = cosf(base.unknown08);
  f32 anchorX = base.unknown14 * x;
  f32 anchorY = base.unknown18 * y;
  result.unknown08 = cosRot;
  result.unknown14 = sinRot;
  result.unknown10 = -sinRot;
  result.unknown0c = cosRot;
  result.unknown00 = anchorX + (cosRot * -anchorX + sinRot * -anchorY);
  result.unknown04 = anchorY + (-sinRot * -anchorX + cosRot * -anchorY);
}

void LayerObjUtil::calcLayerTransRotScaleMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 sinRot = sinf(base.unknown08);
  f32 cosRot = cosf(base.unknown08);
  f32 scl[2];
  s_CallScl[LayerManager::get()->m_coordinate](scl, base, info);
  f32 pos[2];
  s_CallPos[LayerManager::get()->m_coordinate](pos, base);
  f32 width = static_cast<f32>(info.m_pixelWidth + info.m_pixelX) * LayerManager::get()->getScreenCalcSclWidth();
  f32 height = static_cast<f32>(info.m_pixelHeight + info.m_pixelY) * LayerManager::get()->getScreenCalcSclHeight();
  pos[0] -= scl[0] * base.unknown14 - width * base.unknown14;
  pos[1] -= scl[1] * base.unknown18 - height * base.unknown18;
  f32 size[2];
  s_CallMdl[info.m_centerType](pos, size, scl, base);
  f32 x = size[0] + (cosRot * -size[0] + sinRot * -size[1]);
  f32 y = size[1] + (-sinRot * -size[0] + cosRot * -size[1]);
  result.unknown08 = cosRot * scl[0];
  result.unknown14 = sinRot * scl[1];
  result.unknown00 = x + pos[0];
  result.unknown10 = -(sinRot * scl[0]);
  result.unknown0c = cosRot * scl[1];
  result.unknown04 = y + pos[1];
}

void LayerObjUtil::calcLayerTransRotScaleFontMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 sinRot = sinf(base.unknown08);
  f32 cosRot = cosf(base.unknown08);
  f32 scl[2];
  s_CallScl[LayerManager::get()->m_coordinate](scl, base, info);
  f32 pos[2];
  s_CallPos[LayerManager::get()->m_coordinate](pos, base);
  f32 width = static_cast<f32>(info.m_pixelWidth + info.m_pixelX) * LayerManager::get()->getScreenCalcSclWidth();
  f32 height = static_cast<f32>(info.m_pixelHeight + info.m_pixelY) * LayerManager::get()->getScreenCalcSclHeight();
  pos[0] -= scl[0] * base.unknown14 - width * base.unknown14;
  pos[1] -= scl[1] * base.unknown18 - height * base.unknown18;
  f32 size[2];
  s_CallMdl[info.m_centerType](pos, size, scl, base);
  f32 x = size[0] + (cosRot * -size[0] + sinRot * -size[1]);
  f32 y = size[1] + (-sinRot * -size[0] + cosRot * -size[1]);
  result.unknown08 = cosRot * scl[0];
  result.unknown14 = sinRot * scl[1];
  result.unknown00 = x + pos[0];
  result.unknown10 = -(sinRot * scl[0]);
  result.unknown0c = cosRot * scl[1];
  result.unknown04 = y + pos[1];
}

void LayerObjUtil::calcLayerTransRotScaleLaoutMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 sinRot = sinf(base.unknown08);
  f32 cosRot = cosf(base.unknown08);
  f32 scl[2];
  s_CallScl[LayerManager::get()->m_coordinate](scl, base, info);
  f32 pos[2];
  s_CallPos[LayerManager::get()->m_coordinate](pos, base);
  f32 width = static_cast<f32>(info.m_pixelWidth + info.m_pixelX) * LayerManager::get()->getScreenCalcSclWidth();
  f32 height = static_cast<f32>(info.m_pixelHeight + info.m_pixelY) * LayerManager::get()->getScreenCalcSclHeight();
  pos[0] -= scl[0] * base.unknown14 - width * base.unknown14;
  pos[1] -= scl[1] * base.unknown18 - height * base.unknown18;
  f32 size[2];
  s_CallMdl[info.m_centerType](pos, size, scl, base);
  f32 x = size[0] + (cosRot * -size[0] + sinRot * -size[1]);
  f32 y = size[1] + (-sinRot * -size[0] + cosRot * -size[1]);
  result.unknown08 = cosRot * base.unknown0c;
  result.unknown14 = sinRot * base.unknown10;
  result.unknown00 = x + pos[0];
  result.unknown10 = -(sinRot * base.unknown0c);
  result.unknown0c = cosRot * base.unknown10;
  result.unknown04 = y + pos[1];
}

void LayerObjUtil::calcLayerTransRotScaleSWFMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 sinRot = sinf(base.unknown08);
  f32 cosRot = cosf(base.unknown08);
  f32 scl[2];
  s_CallSwfScl[LayerManager::get()->m_coordinate](scl, base, info);
  f32 pos[2];
  s_CallPos[LayerManager::get()->m_coordinate](pos, base);
  f32 width = static_cast<f32>(info.m_pixelWidth + info.m_pixelX) * LayerManager::get()->getScreenCalcSclWidth();
  f32 height = static_cast<f32>(info.m_pixelHeight + info.m_pixelY) * LayerManager::get()->getScreenCalcSclHeight();
  pos[0] -= scl[0] * base.unknown14 - width * base.unknown14;
  pos[1] -= scl[1] * base.unknown18 - height * base.unknown18;
  f32 mdlScl[2];
  s_CallScl[LayerManager::get()->m_coordinate](mdlScl, base, info);
  f32 size[2];
  s_CallMdl[info.m_centerType](pos, size, mdlScl, base);
  f32 x = size[0] + (cosRot * -size[0] + sinRot * -size[1]);
  f32 y = size[1] + (-sinRot * -size[0] + cosRot * -size[1]);
  result.unknown08 = cosRot * scl[0];
  result.unknown14 = sinRot * scl[1];
  result.unknown00 = x + pos[0];
  result.unknown10 = -(sinRot * scl[0]);
  result.unknown0c = cosRot * scl[1];
  result.unknown04 = y + pos[1];
}

void LayerObjUtil::calcLayer3DSpaceTransRotScaleFontMatrix(LayerResMatrix &result, const LayerBasePos &base, const LayerResRenderInfo &info) {
  f32 sinRot = sinf(base.unknown08);
  f32 cosRot = cosf(base.unknown08);
  f32 width = static_cast<f32>(info.m_pixelWidth + info.m_pixelX) * LayerManager::get()->unknown98;
  f32 height = static_cast<f32>(info.m_pixelHeight + info.m_pixelY) * LayerManager::get()->unknown98;
  // Inferred: the game fills four scale floats and only the first two reach the model position; the role of the copy is unknown.
  f32 scl[4];
  scl[0] = width * base.unknown0c;
  scl[1] = base.unknown10 * height;
  scl[2] = scl[0];
  scl[3] = scl[1];
  f32 pos[2];
  pos[0] = base.unknown00 * LayerManager::get()->unknown98;
  pos[1] = base.unknown04 * LayerManager::get()->unknown98;
  f32 size[2];
  s_CallMdl[info.m_centerType](pos, size, scl, base);
  f32 x = size[0] + (cosRot * -size[0] + sinRot * -size[1]);
  f32 y = size[1] + (-sinRot * -size[0] + cosRot * -size[1]);
  result.unknown08 = cosRot * scl[0];
  result.unknown14 = sinRot * scl[1];
  result.unknown00 = x + pos[0];
  result.unknown10 = -(sinRot * scl[0]);
  result.unknown0c = cosRot * scl[1];
  result.unknown04 = y + pos[1];
}

void LayerObjUtil::calcLayer3DSpaceTransRotScaleMatrix(LayerResMatrix &result, const LayerBasePos &base) {
  f32 sinRot = sinf(base.unknown08);
  f32 cosRot = cosf(base.unknown08);
  f32 size[2];
  size[0] = base.unknown14 * base.unknown0c;
  size[1] = base.unknown18 * base.unknown10;
  f32 x = size[0] + (cosRot * -size[0] + sinRot * -size[1]);
  f32 y = size[1] + (-sinRot * -size[0] + cosRot * -size[1]);
  f32 pos[2];
  pos[0] = base.unknown00 * LayerManager::get()->unknown98;
  pos[1] = base.unknown04 * LayerManager::get()->unknown98;
  result.unknown08 = cosRot * base.unknown0c;
  result.unknown14 = sinRot * base.unknown10;
  result.unknown00 = x + pos[0];
  result.unknown10 = -(sinRot * base.unknown0c);
  result.unknown0c = cosRot * base.unknown10;
  result.unknown04 = y + pos[1];
}

} // namespace layer
