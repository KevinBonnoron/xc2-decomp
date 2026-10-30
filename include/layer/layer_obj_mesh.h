#pragma once
#include <stddef.h>

#include "layer/layer_obj_work.h"
#include "types.h"

namespace layer {

struct LayerResMatrix;
struct LayerResNode;

struct LayerArgMdlRenInf {
  u8 _00[0x10];
  const LayerResNode *unknown10;   // Inferred role: mesh node (LayerObjTopDef::updateParams stores an element of a 0x38 stride array); original member name unknown.
  const LayerResMatrix *unknown18; // Inferred role: parent matrix; original member name unknown.
  u8 _20[0x30 - 0x20];
  f32 *unknown30; // Inferred role: uniform buffer cursor; original member name unknown.
};

static_assert(offsetof(LayerArgMdlRenInf, unknown10) == 0x10, "");
static_assert(offsetof(LayerArgMdlRenInf, unknown18) == 0x18, "");
static_assert(offsetof(LayerArgMdlRenInf, unknown30) == 0x30, "");

class LayerObjMesh : public LayerObjWork {
public:
  f32 getWinSclW(const LayerResMatrix &matrix) const;
  f32 getWinSclH(const LayerResMatrix &matrix) const;
  void call_uniform_noImage(LayerArgMdlRenInf &info);
  void call_uniform_win_ga_X(LayerArgMdlRenInf &info);
  void call_uniform_win_ga_Y(LayerArgMdlRenInf &info);
  void call_uniform_win_height(LayerArgMdlRenInf &info);
  void call_uniform_win_sclga_X(LayerArgMdlRenInf &info);
  void call_uniform_win_sclga_Y(LayerArgMdlRenInf &info);
  void call_uniform_win_sclheight(LayerArgMdlRenInf &info);
  void setUniformWinGaX(LayerArgMdlRenInf &info, bool isScale);
  void setUniformWinGaY(LayerArgMdlRenInf &info, bool isScale);
  void setUniformWinHeight(LayerArgMdlRenInf &info, bool isScale);
};

} // namespace layer
