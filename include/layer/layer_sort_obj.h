#pragma once
#include <stddef.h>

namespace layer {

class LayerObj;

class LayerSortObj {
public:
  LayerSortObj(LayerObj *obj) : m_layerObj(obj) { m_layerSortObj = nullptr; }
  virtual ~LayerSortObj() {}
  virtual void alphaRender() {}
  virtual void lastRender() {}
  virtual void finalRender() = 0;

  LayerSortObj *m_layerSortObj; // Inferred role: next object; original member name unknown.
  // Held by the base: the inlined Top constructors store it before the sort object vtable.
  LayerObj *m_layerObj; // Inferred role: object to render; original member name unknown.
};

static_assert(offsetof(LayerSortObj, m_layerSortObj) == 0x08, "");
static_assert(offsetof(LayerSortObj, m_layerObj) == 0x10, "");

} // namespace layer
