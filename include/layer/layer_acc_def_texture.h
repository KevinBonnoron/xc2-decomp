#pragma once

namespace layer {

class LayerBase;

class LayerAccDefTexture {
public:
  LayerAccDefTexture(LayerBase *layer);
  void setTexutre(const void *data);

  LayerBase *layer;
};

} // namespace layer
