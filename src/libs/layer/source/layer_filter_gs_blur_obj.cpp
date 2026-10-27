#include "layer/layer_filter_gs_blur_obj.h"

#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_shd_manager.h"

namespace layer {

LayerFilterGsBlurObj::LayerFilterGsBlurObj(u32 width, u32 height) {
  m_filterType = 1;
  unknown7e8 = 0.9f;
  unknown7ec = 0.9f;
  unknown7f0 = 0;
  unknown7f4 = 1;
  unknown7f8 = false;
  unknown7f9 = true;
  unknown7e0 = width;
  unknown7e4 = height;
}

LayerFilterGsBlurObj::~LayerFilterGsBlurObj() {}

void LayerFilterGsBlurObj::resourceInit() {
  unknown18.setTextureInfo(static_cast<f32>(unknown7e0), static_cast<f32>(unknown7e4), GRL_SURFACE_FORMAT_RGBA16F, false, 0);
  unknown3e0.setTextureInfo(static_cast<f32>(unknown7e0), static_cast<f32>(unknown7e4), GRL_SURFACE_FORMAT_RGBA16F, false, 0);
  unknown7a8.setup(LayerObjUtil::getUniformBlockSizeAlOff(LAYER_UNI_TYPE_UNKNOWN_9));
}

void LayerFilterGsBlurObj::render() {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  if (shader->unknown52c != 2) {
    LayerShdManager::s_CallBlend[2]();
    shader->unknown52c = 2;
  }
  shader->setupVertex(static_cast<LayerDefVertType>(3));
  shader->unknown4f0 = 7;
  if (!unknown7f8) {
    renderMain();
    for (u32 i = 0; i < unknown7f0; i++) {
      renderSub();
    }
  } else {
    if (unknown7f9) {
      unknown7f9 = false;
      renderMain();
      return;
    }
    if (unknown7f0 != 0 && unknown7f4 != 0) {
      u32 i = 0;
      do {
        renderSub();
        i++;
        unknown7f0--;
      } while (unknown7f0 != 0 && i < unknown7f4);
    }
  }
}

void LayerFilterGsBlurObj::renderMain() {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  unknown18.setRenderTarget();
  shader->unknown4f8 = 1;
  shader->setupShader(&unknown7a8);
  shader->setupTexture(*shader->getDefRenderTarget()->unknown70, static_cast<LayerSamplerType>(3), 0);
  shader->renderQuadsIndex();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  unknown3e0.setRenderTarget();
  shader->unknown4f8 = 2;
  shader->setupShader(&unknown7a8);
  shader->setupTexture(*unknown18.unknown70, static_cast<LayerSamplerType>(3), 0);
  shader->renderQuadsIndex();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
}

void LayerFilterGsBlurObj::renderSub() {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  unknown18.setRenderTarget();
  shader->unknown4f8 = 3;
  shader->setupShader(&unknown7a8);
  shader->setupTexture(*unknown3e0.unknown70, static_cast<LayerSamplerType>(3), 0);
  shader->renderQuadsIndex();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  unknown3e0.setRenderTarget();
  shader->unknown4f8 = 2;
  shader->setupShader(&unknown7a8);
  shader->setupTexture(*unknown18.unknown70, static_cast<LayerSamplerType>(3), 0);
  shader->renderQuadsIndex();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
}

grlib::CGLibTextureBuffer *LayerFilterGsBlurObj::getTexture() { return unknown3e0.unknown70; }

void LayerFilterGsBlurObj::setParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum) {
  unknown7e8 = 1.0f;
  unknown7ec = 1.0f;
  if (strength > 1.0f) {
    unknown7e8 = 1.0f / strength;
  }
  if (scale > 1.0f) {
    unknown7ec = 1.0f / scale;
  }
  if (sampleNum > 0x400) {
    unknown7f0 = 0x400;
  } else {
    unknown7f0 = sampleNum;
  }
  if (passNum != 0) {
    unknown7f4 = passNum;
  } else {
    unknown7f4 = 1;
  }
  unknown7f8 = isHalf;
  unknown7f9 = true;
}

} // namespace layer
