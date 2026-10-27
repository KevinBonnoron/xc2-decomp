#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_obj.h"
#include "mm_math/mm_rect.h"
#include "types.h"

namespace layer {

class LayerTextureObj;

class LayerObjTopMaskObj : public LayerObj {
public:
  LayerObjTopMaskObj(const void *data);
  ~LayerObjTopMaskObj() override;
  void createWorkBuffer(const void *data);
  void releaseWorkBuffer();
  void resourceInit() override;
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;

  u8 _250[0x258 - 0x250];
  mm::Rect<f32> unknown258; // Inferred role: view port; original member name unknown.
  u8 _268[0x290 - 0x268];
  grlib::CGLibDblUniformBlock unknown290; // Inferred role: uniform block; original member name unknown.
  LayerTextureObj *unknown2c8;            // Inferred role: mask texture; original member name unknown.
  u16 unknown2d0;                         // Inferred role: icon num; original member name unknown.
  u16 unknown2d2;                         // Inferred role: icon max; original member name unknown.
};

static_assert(offsetof(LayerObjTopMaskObj, unknown258) == 0x258, "");
static_assert(offsetof(LayerObjTopMaskObj, unknown258.height) == 0x264, "");
static_assert(offsetof(LayerObjTopMaskObj, unknown290) == 0x290, "");
static_assert(offsetof(LayerObjTopMaskObj, unknown2c8) == 0x2c8, "");
static_assert(offsetof(LayerObjTopMaskObj, unknown2d0) == 0x2d0, "");

} // namespace layer
