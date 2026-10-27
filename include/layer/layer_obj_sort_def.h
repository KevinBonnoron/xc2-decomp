#pragma once
#include <stddef.h>

#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObjTopDef;

class LayerObjSortDef : public LayerSortObj {
public:
  void finalRender() override;

  LayerObjTopDef *unknown10; // Inferred role: object to render; original member name unknown.
};

static_assert(offsetof(LayerObjSortDef, unknown10) == 0x10, "");

} // namespace layer
