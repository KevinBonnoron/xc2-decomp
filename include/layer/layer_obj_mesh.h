#pragma once
#include <stddef.h>

#include "layer/layer_obj_place.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
} // namespace grlib

namespace layer {

struct LayerResColor;
struct LayerResMatrix;
struct LayerResNode;
struct LyrMeshData;

struct LayerArgMdlRenInf {
  u32 *unknown00;                         // Inferred role: icon entry state cursor; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown08; // Inferred role: uniform block of the icon entry; original member name unknown.
  const LayerResNode *m_layerResNode;     // Inferred role: mesh node (LayerObjTopDef::updateParams stores an element of a 0x38 stride array); original member name unknown.
  const LayerResMatrix *m_layerResMatrix; // Inferred role: parent matrix; original member name unknown.
  const LayerResColor *m_layerResColor;   // Inferred role: parent color; original member name unknown.
  const LyrMeshData *m_lyrMeshData;       // Inferred role: mesh entry; original member name unknown.
  f32 *unknown30;                         // Inferred role: uniform buffer cursor; original member name unknown.
};

static_assert(offsetof(LayerArgMdlRenInf, unknown08) == 0x08, "");
static_assert(offsetof(LayerArgMdlRenInf, m_layerResNode) == 0x10, "");
static_assert(offsetof(LayerArgMdlRenInf, m_layerResMatrix) == 0x18, "");
static_assert(offsetof(LayerArgMdlRenInf, m_layerResColor) == 0x20, "");
static_assert(offsetof(LayerArgMdlRenInf, m_lyrMeshData) == 0x28, "");
static_assert(offsetof(LayerArgMdlRenInf, unknown30) == 0x30, "");

// Evidence: the vtable holds LayerActDef::updatePartsAction; LayerObjTopDef calls the LayerObjPlace, LayerObjMesh and
// LayerObjDraw functions on itself, so the three classes form one inheritance chain (order inferred).
class LayerObjMesh : public LayerObjPlace {
public:
  LayerObjMesh();
  void updateMeshUniformBlock(LayerArgMdlRenInf &info);
  f32 getWinSclW(const LayerResMatrix &matrix) const;
  f32 getWinSclH(const LayerResMatrix &matrix) const;
  void call_uniform_def(LayerArgMdlRenInf &info);
  void call_uniform_icon(LayerArgMdlRenInf &info);
  void call_uniform_number(LayerArgMdlRenInf &info);
  void call_uniform_uvscl(LayerArgMdlRenInf &info);
  void call_uniform_noImage(LayerArgMdlRenInf &info);
  void call_uniform_win_ga_X(LayerArgMdlRenInf &info);
  void call_uniform_win_ga_Y(LayerArgMdlRenInf &info);
  void call_uniform_win_height(LayerArgMdlRenInf &info);
  void call_uniform_win_sclga_X(LayerArgMdlRenInf &info);
  void call_uniform_win_sclga_Y(LayerArgMdlRenInf &info);
  void call_uniform_win_sclheight(LayerArgMdlRenInf &info);
  void call_uniform_hdr(LayerArgMdlRenInf &info);
  void setUniformWinGaX(LayerArgMdlRenInf &info, bool isScale);
  void setUniformWinGaY(LayerArgMdlRenInf &info, bool isScale);
  void setUniformWinHeight(LayerArgMdlRenInf &info, bool isScale);
};

} // namespace layer
