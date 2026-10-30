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
  ~LayerObjTopTexObj() override;
  void createWorkBuffer();
  void releaseWorkBuffer();
  void finalRender();

  LayerResViewPortInfo *unknown250;            // Inferred role: view port; original member name unknown.
  LayerObjSortTexObj unknown258;               // Inferred role: sort object; original member name unknown.
  const grlib::CGLibTextureBuffer *unknown270; // Inferred role: texture; original member name unknown.
  grlib::CGLibDblUniformBlock unknown278;      // Inferred role: uniform block; original member name unknown.
};

static_assert(offsetof(LayerObjTopTexObj, unknown250) == 0x250, "");
static_assert(offsetof(LayerObjTopTexObj, unknown258) == 0x258, "");
static_assert(offsetof(LayerObjTopTexObj, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjTopTexObj, unknown278) == 0x278, "");

} // namespace layer
