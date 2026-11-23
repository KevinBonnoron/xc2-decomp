#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_sort_tex_obj.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

struct LayerResViewPortInfo;

class LayerObjTopTexObj : public LayerObj {
public:
  LayerObjTopTexObj(const grlib::CGLibTextureBuffer *texture);
  ~LayerObjTopTexObj() override;
  void createWorkBuffer();
  void releaseWorkBuffer();
  void finalRender();
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;
  void applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) override;

  LayerResViewPortInfo *m_layerResViewPortInfo;       // Inferred role: view port; original member name unknown.
  LayerObjSortTexObj m_layerObjSortTexObj;            // Inferred role: sort object; original member name unknown.
  const grlib::CGLibTextureBuffer *unknown270;        // Inferred role: texture; original member name unknown.
  grlib::CGLibDblUniformBlock m_cGLibDblUniformBlock; // Inferred role: uniform block; original member name unknown.
};

static_assert(offsetof(LayerObjTopTexObj, m_layerResViewPortInfo) == 0x250, "");
static_assert(offsetof(LayerObjTopTexObj, m_layerObjSortTexObj) == 0x258, "");
static_assert(offsetof(LayerObjTopTexObj, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjTopTexObj, m_cGLibDblUniformBlock) == 0x278, "");

} // namespace layer
