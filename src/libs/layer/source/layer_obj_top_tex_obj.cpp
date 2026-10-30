#include "layer/layer_obj_top_tex_obj.h"

#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_manager.h"
#include "layer/layer_shd_manager.h"
#include "types.h"

namespace layer {

void LayerObjTopTexObj::finalRender() {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  if (!shader->unknown002(unknown248, unknown250)) {
    return;
  }
  shader->unknown003(LayerShdManager::s_resDefBlend[unknownc5]);
  shader->unknown004(this);
  shader->unknown4f2 = 1;
  shader->setSecTexture(unknown220[2]);
  shader->setupVertex(static_cast<LayerDefVertType>(1));
  shader->unknown4f0 = 1;
  shader->setupShader(&unknown278);
  shader->setupTexture(*unknown270, static_cast<LayerSamplerType>(unknownc6), 0);
  shader->renderQuadsIndex();
}

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
