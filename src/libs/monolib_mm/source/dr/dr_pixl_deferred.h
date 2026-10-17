#pragma once

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrPixlDeferred {
public:
  void displayUpdate();
  void lastDeferredRender();
  grlib::CGLibTextureBuffer *getShadowMapTexture() const;
};

} // namespace ml
