#pragma once
#include <stddef.h>

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

  u8 _250[0x2e8 - 0x250];
  grlib::CGLibTextureBuffer *unknown2e8; // Inferred role: texture; original member name unknown.
  u8 _2f0[0x740 - 0x2f0];
  u32 unknown740; // Inferred role: width; original member name unknown.
  u32 unknown744; // Inferred role: height; original member name unknown.
};

static_assert(offsetof(LayerObjTopMemObj, unknown2e8) == 0x2e8, "");
static_assert(offsetof(LayerObjTopMemObj, unknown740) == 0x740, "");

} // namespace layer
