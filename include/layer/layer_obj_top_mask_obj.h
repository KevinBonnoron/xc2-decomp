#pragma once
#include <stddef.h>

#include "layer/layer_obj.h"
#include "types.h"

namespace layer {

class LayerObjTopMaskObj : public LayerObj {
public:
  u8 _250[0x2d0 - 0x250];
  u16 m_iconNum;
  u16 m_iconMax;
};

static_assert(offsetof(LayerObjTopMaskObj, m_iconNum) == 0x2d0, "");

} // namespace layer
