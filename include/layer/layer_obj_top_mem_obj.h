#pragma once
#include <stddef.h>

#include "grlib/cglib_one_uniform_block.h"
#include "layer/layer_obj.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerObjTopMemObj : public LayerObj {
public:
  void *getBuffer();
  void updateBufer();
  void setRender(bool render);
  bool isRender() const;

  u8 _250[0x270 - 0x250];
  u32 unknown270; // Inferred role: flags; original member name unknown.
  u8 _274[0x2e8 - 0x274];
  grlib::CGLibTextureBuffer *unknown2e8; // Inferred role: texture; original member name unknown.
  u8 _2f0[0x6a0 - 0x2f0];
  grlib::CGLibOneUniformBlock unknown6a0[2]; // Inferred role: uniform blocks; original member name unknown.
  grlib::CGLibOneUniformBlock unknown6f0[2]; // Inferred role: uniform blocks; original member name unknown.
  u32 unknown740;                            // Inferred role: width; original member name unknown.
  u32 unknown744;                            // Inferred role: height; original member name unknown.
};

static_assert(offsetof(LayerObjTopMemObj, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjTopMemObj, unknown2e8) == 0x2e8, "");
static_assert(offsetof(LayerObjTopMemObj, unknown6a0) == 0x6a0, "");
static_assert(offsetof(LayerObjTopMemObj, unknown6f0) == 0x6f0, "");
static_assert(offsetof(LayerObjTopMemObj, unknown740) == 0x740, "");

} // namespace layer
