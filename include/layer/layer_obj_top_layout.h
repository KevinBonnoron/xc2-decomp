#pragma once
#include <stddef.h>

#include "layer/layer_obj_layout.h"
#include "layer/layer_obj_sort_layout.h"

namespace layer {

class LayerObjTopLayout : public LayerObjLayout {
public:
  LayerObjTopLayout(const void *data);
  LayerObjTopLayout();
  ~LayerObjTopLayout() override;
  void workLayoutCreate(const void *data);
  void finalRender();

  LayerObjSortLayout unknown400; // Inferred role: sort object; original member name unknown.
};

static_assert(offsetof(LayerObjTopLayout, unknown400) == 0x400, "");
static_assert(sizeof(LayerObjTopLayout) == 0x420, "");

} // namespace layer
