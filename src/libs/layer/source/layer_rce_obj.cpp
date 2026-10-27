#include "layer/layer_rce_obj.h"

namespace layer {

LayerRceObj::LayerRceObj(const void *data, const char *name) : unknown00(nullptr), unknown08(nullptr) {
  unknown10 = name;
  unknown28 = data;
}

LayerRceObj::~LayerRceObj() {}

void LayerRceObj::setRceData(const void *data, const char *name) {
  unknown10 = name;
  unknown28 = data;
}

} // namespace layer
