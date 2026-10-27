#pragma once
#include <stddef.h>

#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObjTopTexObj;

class LayerObjSortTexObj : public LayerSortObj {
public:
  void finalRender() override;

  LayerObjTopTexObj *unknown10; // Inferred role: object to render; original member name unknown.
};

static_assert(offsetof(LayerObjSortTexObj, unknown10) == 0x10, "");

} // namespace layer
