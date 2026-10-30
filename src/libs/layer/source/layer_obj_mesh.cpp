#include "layer/layer_obj_mesh.h"

#include <math.h>

#include "layer/layer_obj.h"
#include "layer/layer_obj_util.h"

namespace layer {

f32 LayerObjMesh::getWinSclW(const LayerResMatrix &matrix) const { return sqrtf(matrix.unknown08 * matrix.unknown08 + matrix.unknown10 * matrix.unknown10); }

f32 LayerObjMesh::getWinSclH(const LayerResMatrix &matrix) const { return sqrtf(matrix.unknown0c * matrix.unknown0c + matrix.unknown14 * matrix.unknown14); }

void LayerObjMesh::call_uniform_noImage(LayerArgMdlRenInf &info) {
  // The game passes the mesh node itself where updatePosMatrixUniformBlock expects a matrix.
  LayerObjUtil::updatePosMatrixUniformBlock(info.unknown30, reinterpret_cast<const LayerResMatrix *>(info.unknown10), *info.unknown18, unknown1fc, (unknowna8 >> 11) & 0x1);
  info.unknown30 += 8;
}

void LayerObjMesh::call_uniform_win_ga_X(LayerArgMdlRenInf &info) { setUniformWinGaX(info, false); }

void LayerObjMesh::call_uniform_win_ga_Y(LayerArgMdlRenInf &info) { setUniformWinGaY(info, false); }

void LayerObjMesh::call_uniform_win_height(LayerArgMdlRenInf &info) { setUniformWinHeight(info, false); }

void LayerObjMesh::call_uniform_win_sclga_X(LayerArgMdlRenInf &info) { setUniformWinGaX(info, true); }

void LayerObjMesh::call_uniform_win_sclga_Y(LayerArgMdlRenInf &info) { setUniformWinGaY(info, true); }

void LayerObjMesh::call_uniform_win_sclheight(LayerArgMdlRenInf &info) { setUniformWinHeight(info, true); }

} // namespace layer
