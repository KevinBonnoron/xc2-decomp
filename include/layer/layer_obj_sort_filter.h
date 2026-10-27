#pragma once
#include <stddef.h>

#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObjTopFilter;

class LayerObjSortFilter : public LayerSortObj {
public:
  void finalRender() override;

  LayerObjTopFilter *unknown10; // Inferred role: object to render; original member name unknown.
};

static_assert(offsetof(LayerObjSortFilter, unknown10) == 0x10, "");

} // namespace layer
