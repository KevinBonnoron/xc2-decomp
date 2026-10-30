#pragma once
#include <stddef.h>

namespace layer {

class LayerObj;

class LayerSortObj {
public:
  LayerSortObj(LayerObj *obj) : unknown10(obj) { unknown08 = nullptr; }
  virtual ~LayerSortObj() {}
  virtual void alphaRender() {}
  virtual void lastRender() {}
  virtual void finalRender() = 0;

  LayerSortObj *unknown08; // Inferred role: next object; original member name unknown.
  // Held by the base: the inlined Top constructors store it before the sort object vtable.
  LayerObj *unknown10; // Inferred role: object to render; original member name unknown.
};

static_assert(offsetof(LayerSortObj, unknown08) == 0x08, "");
static_assert(offsetof(LayerSortObj, unknown10) == 0x10, "");

} // namespace layer
