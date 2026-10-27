#pragma once
#include <stddef.h>

namespace layer {

class LayerSortObj {
public:
  virtual ~LayerSortObj() {}
  virtual void alphaRender() {}
  virtual void lastRender() {}
  virtual void finalRender() = 0;

  LayerSortObj *unknown08; // Inferred role: next object; original member name unknown.
};

static_assert(offsetof(LayerSortObj, unknown08) == 0x08, "");

} // namespace layer
