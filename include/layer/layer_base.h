#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

enum LAYER_TYPE {
  LAYER_OBJ_TYPE_OBJ = 1,
  LAYER_OBJ_TYPE_FONT = 2,
  LAYER_OBJ_TYPE_LAYOUT = 3,
  LAYER_OBJ_TYPE_TEX = 4,
  LAYER_OBJ_TYPE_MEM = 5,
  LAYER_OBJ_TYPE_POLY = 6,
  LAYER_OBJ_TYPE_MASK = 7,
  LAYER_OBJ_TYPE_FILTER = 8,
  LAYER_OBJ_TYPE_FONT_STYLE = 9,
  LAYER_OBJ_TYPE_FONT_RES = 10,
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
