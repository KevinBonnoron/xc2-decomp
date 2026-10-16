#pragma once
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
}

namespace layer {

class LayerBase;

enum LayerCoordinate {
  LAYER_COORDINATE_PIXEL = 0,
  LAYER_COORDINATE_NORMALIZED = 1,
};

class LayerAccManager {
public:
  LayerAccManager();
  f32 getScreenWidth() const;
  f32 getScreenHeight() const;
  LayerCoordinate getCoordinate() const;
  void setCoordinate(LayerCoordinate coordinate);
  LayerBase *createObj(const void *data);
  LayerBase *createMaskObj(const void *data);
  LayerBase *createTexObj(const grlib::CGLibTextureBuffer &texture);
};

} // namespace layer
