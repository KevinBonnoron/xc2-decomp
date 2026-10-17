#pragma once

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrPixlToonGrad {
public:
  void render();
  const grlib::CGLibTextureBuffer &getGradTex() const;
  const grlib::CGLibTextureBuffer &getDarkGradTex() const;
};

} // namespace ml
