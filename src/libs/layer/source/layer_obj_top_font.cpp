#include "layer/layer_obj_top_font.h"

namespace layer {

LayerObjTopFont::~LayerObjTopFont() {
  baseRelease();
  workRelease();
}

void LayerObjTopFont::alphaRender() {}

void LayerObjTopFont::lastRender() {}

} // namespace layer
