#pragma once
#include <stddef.h>

#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObjTopFont;

class LayerObjSortFont : public LayerSortObj {
public:
  void finalRender() override;

  LayerObjTopFont *unknown10; // Inferred role: object to render; original member name unknown.
};

static_assert(offsetof(LayerObjSortFont, unknown10) == 0x10, "");

} // namespace layer
