#pragma once
#include <stddef.h>

#include "layer/layer_obj.h"
#include "types.h"

namespace layer {

class LayerObjTopMaskObj : public LayerObj {
public:
  u8 _250[0x2d0 - 0x250];
  u16 unknown2d0; // Inferred role: icon num; original member name unknown.
  u16 unknown2d2; // Inferred role: icon max; original member name unknown.
};

static_assert(offsetof(LayerObjTopMaskObj, unknown2d0) == 0x2d0, "");

} // namespace layer
