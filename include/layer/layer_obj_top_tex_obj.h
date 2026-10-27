#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_sort_tex_obj.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerObjTopTexObj : public LayerObj {
public:
  ~LayerObjTopTexObj() override;
  void createWorkBuffer();
  void releaseWorkBuffer();
  void finalRender();

  u8 _250[0x258 - 0x250];
  LayerObjSortTexObj unknown258;               // Inferred role: sort object; original member name unknown.
  const grlib::CGLibTextureBuffer *unknown270; // Inferred role: texture; original member name unknown.
  grlib::CGLibDblUniformBlock unknown278;      // Inferred role: uniform block; original member name unknown.
};

static_assert(offsetof(LayerObjTopTexObj, unknown258) == 0x258, "");
static_assert(offsetof(LayerObjTopTexObj, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjTopTexObj, unknown278) == 0x278, "");

} // namespace layer
