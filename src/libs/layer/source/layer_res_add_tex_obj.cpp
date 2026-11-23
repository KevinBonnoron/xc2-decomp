#include "layer/layer_res_add_tex_obj.h"

#include "layer/layer_texture_obj.h"

namespace layer {

LayerResAddTexObj::LayerResAddTexObj(const void *data, u32 index) : unknown00(nullptr), unknown08(nullptr), unknown10(data), m_layerTextureObj(nullptr) {
  unknown22 = 0;
  unknown20 = index;
}

LayerResAddTexObj::LayerResAddTexObj(grlib::CGLibTextureBuffer *texture, u32 index) {
  unknown00 = nullptr;
  unknown08 = nullptr;
  unknown22 = 0x400;
  unknown20 = index;
  unknown10_texture = texture;
  m_layerTextureObj = nullptr;
}

LayerResAddTexObj::~LayerResAddTexObj() { release(); }

void LayerResAddTexObj::release() {
  if (m_layerTextureObj != nullptr) {
    m_layerTextureObj->release();
    m_layerTextureObj = nullptr;
  }
}

grlib::CGLibTextureBuffer *LayerResAddTexObj::getTexObj(u32 index) {
  if (unknown22 & 0x400) {
    return unknown10_texture;
  }
  return m_layerTextureObj->getTexture(index);
}

} // namespace layer
