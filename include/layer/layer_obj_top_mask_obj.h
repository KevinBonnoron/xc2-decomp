#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_obj.h"
#include "layer/layer_view_port.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerTextureObj;
struct LayerResViewPortInfo;

class LayerObjTopMaskObj : public LayerObj {
public:
  LayerObjTopMaskObj(const void *data);
  ~LayerObjTopMaskObj() override;
  void createWorkBuffer(const void *data);
  void releaseWorkBuffer();
  const grlib::CGLibTextureBuffer &getTexture() const;
  void resourceInit() override;
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;

  LayerResViewPortInfo *m_layerResViewPortInfo; // Inferred role: view port, cleared by the constructor like the other Top objects; original member name unknown.
  LayerViewPort m_layerViewPort;                // Inferred role: view port; original member name unknown.
  u8 _268[0x290 - 0x268];
  grlib::CGLibDblUniformBlock m_cGLibDblUniformBlock; // Inferred role: uniform block; original member name unknown.
  LayerTextureObj *m_layerTextureObj;                 // Inferred role: mask texture; original member name unknown.
  u16 unknown2d0;                                     // Inferred role: icon num; original member name unknown.
  u16 unknown2d2;                                     // Inferred role: icon max; original member name unknown.
};

static_assert(offsetof(LayerObjTopMaskObj, m_layerResViewPortInfo) == 0x250, "");
static_assert(offsetof(LayerObjTopMaskObj, m_layerViewPort) == 0x258, "");
static_assert(offsetof(LayerObjTopMaskObj, m_layerViewPort.unknown0c) == 0x264, "");
static_assert(offsetof(LayerObjTopMaskObj, m_cGLibDblUniformBlock) == 0x290, "");
static_assert(offsetof(LayerObjTopMaskObj, m_layerTextureObj) == 0x2c8, "");
static_assert(offsetof(LayerObjTopMaskObj, unknown2d0) == 0x2d0, "");

} // namespace layer
