#include "layer/layer_obj_mesh.h"

#include <math.h>
#include <stdio.h>

#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtx_instans.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_shd_manager.h"

namespace layer {

// Inferred layout of a number character instance (stride 0x24 in LayerObjMesh::call_uniform_number); original type and member names unknown.
struct unknown022 {
  f32 unknown00[2]; // Inferred role: size; original member name unknown.
  f32 unknown08;    // Inferred role: x offset; original member name unknown.
  f32 unknown0c;    // Inferred role: y offset; original member name unknown.
  f32 unknown10[4]; // Inferred role: uv rect; original member name unknown.
  u32 unknown20;    // Inferred role: color; original member name unknown.
};

static_assert(sizeof(unknown022) == 0x24, "");

LayerObjMesh::LayerObjMesh() {}

f32 LayerObjMesh::getWinSclW(const LayerResMatrix &matrix) const { return sqrtf(matrix.unknown08 * matrix.unknown08 + matrix.unknown10 * matrix.unknown10); }

f32 LayerObjMesh::getWinSclH(const LayerResMatrix &matrix) const { return sqrtf(matrix.unknown0c * matrix.unknown0c + matrix.unknown14 * matrix.unknown14); }

void LayerObjMesh::call_uniform_def(LayerArgMdlRenInf &info) {
  LayerObjUtil::updatePosMatrixUniformBlock(info.unknown30, reinterpret_cast<const LayerResMatrix *>(info.m_layerResNode), *info.m_layerResMatrix, unknown1fc, (unknowna8 >> 11) & 0x1);
  info.unknown30 += 8;
  LayerObjUtil::updateUvCalcUniformBlock(info.unknown30, m_layerResUvParam, unknowna8);
  info.unknown30 += 8;
}

void LayerObjMesh::call_uniform_icon(LayerArgMdlRenInf &info) {
  LayerObjUtil::updatePosMatrixUniformBlock(info.unknown30, reinterpret_cast<const LayerResMatrix *>(info.m_layerResNode), *info.m_layerResMatrix, unknown1fc, (unknowna8 >> 11) & 0x1);
  info.unknown30 += 8;
  if (unknown2a4 >= unknown2a6) {
    unknown2a4 = unknown2a6 - 1;
  }
  f32 *uniform = info.unknown30;
  const unknown018 *icon = reinterpret_cast<const unknown018 *>(static_cast<const u8 *>(m_resData) + static_cast<const unknown013 *>(m_resData)->unknown2c);
  const unknown021 *uv = reinterpret_cast<const unknown021 *>(reinterpret_cast<const u8 *>(icon) + icon->unknown18) + unknown2a4;
  uniform[0] = uv->unknown00[0];
  uniform[1] = uv->unknown00[1];
  uniform[2] = 0.0f;
  uniform[3] = 0.0f;
  uniform[4] = uv->unknown08[0];
  uniform[5] = uv->unknown08[1];
  uniform[6] = uv->unknown08[2];
  uniform[7] = uv->unknown08[3];
  info.unknown30 += 8;
}

void LayerObjMesh::call_uniform_number(LayerArgMdlRenInf &info) {
  LayerObjUtil::updatePosMatrixUniformBlock(info.unknown30, reinterpret_cast<const LayerResMatrix *>(info.m_layerResNode), *info.m_layerResMatrix, unknown1fc, (unknowna8 >> 11) & 0x1);
  info.unknown30 += 8;
  unknown298->unknown78->unknown08 = 0;
  const unknown018 *icon = reinterpret_cast<const unknown018 *>(static_cast<const u8 *>(m_resData) + static_cast<const unknown013 *>(m_resData)->unknown2c);
  const unknown021 *uvs = reinterpret_cast<const unknown021 *>(reinterpret_cast<const u8 *>(icon) + icon->unknown18);
  char text[32];
  snprintf(text, sizeof(text), "%.2f", unknown2a0);
  unknown298->unknown78->unknown00->beginInstansBuff();
  unknown022 *instances = static_cast<unknown022 *>(unknown298->unknown78->unknown00->getNextInstansBuff());
  f32 width = 0.0f;
  u32 size = 0;
  for (s32 i = 0; i < 32; i++) {
    s32 index;
    if (text[i] == '.') {
      index = 11;
    } else if (text[i] >= '0' && text[i] <= '9') {
      index = text[i] - '0';
    } else {
      break;
    }
    const unknown021 *uv = &uvs[index];
    unknown022 *instance = &instances[i];
    width += uv->unknown00[0];
    instance->unknown00[0] = uv->unknown00[0];
    instance->unknown00[1] = uv->unknown00[1];
    instance->unknown08 = i * uv->unknown00[0];
    instance->unknown0c = 0.0f;
    instance->unknown10[0] = uv->unknown08[0];
    instance->unknown10[1] = uv->unknown08[1];
    instance->unknown10[2] = uv->unknown08[2];
    instance->unknown10[3] = uv->unknown08[3];
    instance->unknown20 = 0xffffffff;
    size += sizeof(unknown022);
    unknown298->unknown78->unknown08++;
  }
  unknown022 *instance = instances;
  for (u32 i = 0; i < unknown298->unknown78->unknown08; i++, instance++) {
    instance->unknown08 -= width;
  }
  unknown298->unknown78->unknown00->unknown08 += size;
  unknown298->unknown78->unknown00->updateInstansBuff();
}

void LayerObjMesh::call_uniform_uvscl(LayerArgMdlRenInf &info) {
  LayerObjUtil::updatePosMatrixUniformBlock(info.unknown30, reinterpret_cast<const LayerResMatrix *>(info.m_layerResNode), *info.m_layerResMatrix, unknown1fc, (unknowna8 >> 11) & 0x1);
  info.unknown30 += 8;
  LayerObjUtil::updateUvCalcUniformBlock(info.unknown30, m_layerResUvParam, unknowna8);
  info.unknown30 += 8;
}

void LayerObjMesh::call_uniform_noImage(LayerArgMdlRenInf &info) {
  // The game passes the mesh node itself where updatePosMatrixUniformBlock expects a matrix.
  LayerObjUtil::updatePosMatrixUniformBlock(info.unknown30, reinterpret_cast<const LayerResMatrix *>(info.m_layerResNode), *info.m_layerResMatrix, unknown1fc, (unknowna8 >> 11) & 0x1);
  info.unknown30 += 8;
}

void LayerObjMesh::call_uniform_win_ga_X(LayerArgMdlRenInf &info) { setUniformWinGaX(info, false); }

void LayerObjMesh::call_uniform_win_ga_Y(LayerArgMdlRenInf &info) { setUniformWinGaY(info, false); }

void LayerObjMesh::call_uniform_win_height(LayerArgMdlRenInf &info) { setUniformWinHeight(info, false); }

void LayerObjMesh::call_uniform_win_sclga_X(LayerArgMdlRenInf &info) { setUniformWinGaX(info, true); }

void LayerObjMesh::call_uniform_win_sclga_Y(LayerArgMdlRenInf &info) { setUniformWinGaY(info, true); }

void LayerObjMesh::call_uniform_win_sclheight(LayerArgMdlRenInf &info) { setUniformWinHeight(info, true); }

void LayerObjMesh::call_uniform_hdr(LayerArgMdlRenInf &info) {
  LayerObjUtil::updatePosMatrixUniformBlock(info.unknown30, reinterpret_cast<const LayerResMatrix *>(info.m_layerResNode), *info.m_layerResMatrix, unknown1fc, (unknowna8 >> 11) & 0x1);
  info.unknown30 += 8;
  LayerObjUtil::updateUvCalcUniformBlock(info.unknown30, m_layerResUvParam, unknowna8);
  info.unknown30 += 8;
  LayerShdManager *shader = LayerManager::get()->m_layerShdManager;
  f32 width = shader->unknown368.getWidth();
  f32 *uniform = info.unknown30;
  uniform[0] = (width - 1.0f) / width;
  uniform[1] = 1.0f / (width + width);
  uniform[2] = 0.0f;
  uniform[3] = 1.0f / shader->m_gamma;
  info.unknown30 += 4;
}

} // namespace layer
