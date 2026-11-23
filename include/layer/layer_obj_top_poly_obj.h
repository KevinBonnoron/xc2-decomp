#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_res_tex.h"
#include "layer/layer_obj_sort_poly_obj.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
class CGLibVtxIndex;
class CGLibVtxVertex;
} // namespace grlib

namespace layer {
struct LayerPolyVertex;
struct LayerResViewPortInfo;
struct LayerRenderView;

class LayerObjTopPolyObj : public LayerObj {
public:
  struct layPolyWork {
    grlib::CGLibVtxVertex *unknown00[2]; // Inferred role: vertex buffers; original member name unknown.
    grlib::CGLibVtxIndex *unknown10[2];  // Inferred role: index buffers; original member name unknown.
    void *unknown20[2];                  // Inferred role: vertex data; original member name unknown.
    void *unknown30[2];                  // Inferred role: index data; original member name unknown.
    u16 unknown40;                       // Inferred role: vertex num; original member name unknown.
    u16 unknown42;                       // Inferred role: index num; original member name unknown.
    u16 unknown44[2];                    // Inferred role: index start; original member name unknown.
    u16 unknown48[2];                    // Inferred role: index num; original member name unknown.
    u16 unknown4c;                       // Inferred role: current index start; original member name unknown.
    u16 unknown4e;                       // Inferred role: current index num; original member name unknown.
    u16 unknown50;                       // Inferred role: current vertex buffer; original member name unknown.
    u16 unknown52;                       // Inferred role: current index buffer; original member name unknown.
    u8 _54[0x58 - 0x54];
  };

  LayerObjTopPolyObj(u32 width, u32 height, u16 vertexNum, u16 indexNum, LayerPrimitiveType type);
  ~LayerObjTopPolyObj() override;
  void releasePoly(layPolyWork &work);
  void releaseWorkBuffer();
  void createWorkBuffer(u32 width, u32 height);
  void createVertex(u16 vertexNum, u16 indexNum, LayerPrimitiveType type);
  void updateVertexBuffer();
  void applyPartsSetup() override;
  void LockVertex();
  void setVertex(u32 index, const LayerPolyVertex &vertex);
  void UnlockVertex();
  void LockIndex();
  void setIndex(u32 index, u16 vertexIndex);
  void UnlockIndex();
  void setTexutre(const void *data);
  void setTexutre(grlib::CGLibTextureBuffer &texture);
  void resetTexutre();
  void setIndexInfo(u16 start, u16 num);
  void applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) override;
  void updateUniformBlock(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color);
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;
  void finalRender();

  u32 unknown250; // Inferred role: update flags; original member name unknown.
  u8 _254[0x258 - 0x254];
  LayerResViewPortInfo *m_layerResViewPortInfo;       // Inferred role: view port; original member name unknown.
  LayerObjSortPolyObj m_layerObjSortPolyObj;          // Inferred role: sort object; original member name unknown.
  grlib::CGLibTextureBuffer *unknown278;              // Inferred role: first additional texture; original member name unknown.
  grlib::CGLibDblUniformBlock m_cGLibDblUniformBlock; // Inferred role: uniform block; original member name unknown.
  LayerObjResTex m_layerObjResTex;                    // Inferred role: textures; original member name unknown.
  layPolyWork m_layPolyWork;                          // Inferred role: poly work; original member name unknown.
  void *m_index;                                      // Inferred role: locked buffer; named after the game accessor layer::LayerObjTopPolyObj::setIndex.
  u8 _360[0x368 - 0x360];
  void *unknown368; // Inferred role: allocated memory; original member name unknown.
};

static_assert(offsetof(LayerObjTopPolyObj, unknown250) == 0x250, "");
static_assert(offsetof(LayerObjTopPolyObj, m_layerResViewPortInfo) == 0x258, "");
static_assert(offsetof(LayerObjTopPolyObj, m_layerObjSortPolyObj) == 0x260, "");
static_assert(offsetof(LayerObjTopPolyObj, unknown278) == 0x278, "");
static_assert(offsetof(LayerObjTopPolyObj, m_cGLibDblUniformBlock) == 0x280, "");
static_assert(offsetof(LayerObjTopPolyObj, m_layerObjResTex) == 0x2b8, "");
static_assert(offsetof(LayerObjTopPolyObj, m_layPolyWork) == 0x300, "");
static_assert(offsetof(LayerObjTopPolyObj, m_index) == 0x358, "");
static_assert(offsetof(LayerObjTopPolyObj, unknown368) == 0x368, "");
static_assert(sizeof(LayerObjTopPolyObj::layPolyWork) == 0x58, "");
static_assert(sizeof(LayerObjTopPolyObj) == 0x370, "");

} // namespace layer
