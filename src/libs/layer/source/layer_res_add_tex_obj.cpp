#include "layer/layer_res_add_tex_obj.h"

#include "layer/layer_texture_obj.h"

namespace layer {

LayerResAddTexObj::LayerResAddTexObj(const void *data, u32 index) : unknown00(nullptr), unknown08(nullptr), unknown10(data), unknown18(nullptr) {
  unknown22 = 0;
  unknown20 = index;
}

LayerResAddTexObj::LayerResAddTexObj(grlib::CGLibTextureBuffer *texture, u32 index) {
  unknown00 = nullptr;
  unknown08 = nullptr;
  unknown22 = 0x400;
  unknown20 = index;
  unknown10_texture = texture;
  unknown18 = nullptr;
}

LayerResAddTexObj::~LayerResAddTexObj() { release(); }

void LayerResAddTexObj::release() {
  if (unknown18 != nullptr) {
    unknown18->release();
    unknown18 = nullptr;
  }
}

grlib::CGLibTextureBuffer *LayerResAddTexObj::getTexObj(u32 index) {
  if (unknown22 & 0x400) {
    return unknown10_texture;
  }
  return unknown18->getTexture(index);
}

} // namespace layer
