#pragma once
#include "layer/layer_obj_font.h"

namespace layer {

class LayerObjTopFont : public LayerObjFont {
public:
  ~LayerObjTopFont() override;
  void alphaRender();
  void lastRender();
  void finalRender();
};

} // namespace layer
