#include "layer/layer_obj_top_tex_obj.h"

#include "grlib/cglib_texture_buffer.h"

namespace layer {

LayerObjTopTexObj::~LayerObjTopTexObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopTexObj::createWorkBuffer() {
  unknown278.setup(0x80);
  u32 width = 0x40;
  u32 height = 0x40;
  if (unknown270->isInitialized()) {
    width = unknown270->getWidth();
    height = unknown270->getHeight();
  }
  f32 sclY = static_cast<f32>(height) / static_cast<f32>(width);
  unknown188 = 1.0f;
  unknown18c = sclY;
  f32 sclX = 1.0f;
  if (width <= height) {
    sclY = 1.0f;
    sclX = static_cast<f32>(width) / static_cast<f32>(height);
  }
  unknown180 = sclX;
  unknown184 = sclY;
  unknown190 = 0;
  unknown192 = 0;
  unknown194 = width;
  unknown196 = height;
}

void LayerObjTopTexObj::releaseWorkBuffer() { unknown278.release(); }

} // namespace layer
