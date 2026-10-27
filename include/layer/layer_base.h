#pragma once
#include <stddef.h>

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
  virtual ~LayerBase() {}
  virtual void release();

  LayerBase *unknown08; // Inferred role: previous node; original member name unknown.
  LayerBase *unknown10; // Inferred role: next node; original member name unknown.
  int unknown18;        // Inferred role: type; original member name unknown.
};

static_assert(offsetof(LayerBase, unknown08) == 0x08, "");
static_assert(offsetof(LayerBase, unknown10) == 0x10, "");
static_assert(offsetof(LayerBase, unknown18) == 0x18, "");

} // namespace layer
