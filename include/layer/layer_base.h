#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

enum LayerObjType {
  LAYER_OBJ_TYPE_OBJ = 1,
  LAYER_OBJ_TYPE_FONT = 2,
  LAYER_OBJ_TYPE_MEM = 5,
};

class LayerBase {
public:
  virtual ~LayerBase();
  virtual void release();

  u8 _08[0x18 - 0x08];
  int type;
};

static_assert(offsetof(LayerBase, type) == 0x18, "");

} // namespace layer
