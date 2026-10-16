#pragma once
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerBase;
class LayerObjWork;

class LayerAccDefTexture {
public:
  LayerAccDefTexture(LayerBase *layer);
  u32 getTextureMax() const;
  void setTexutre(const void *data);
  void setTexutre(grlib::CGLibTextureBuffer &texture);
  void resetTexutre();
  void resetAllTexutre();

  LayerObjWork *m_layer;
};

} // namespace layer
