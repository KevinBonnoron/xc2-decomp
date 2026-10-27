#include "layer/layer_shd_manager.h"

#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_texture.h"
#include "layer/layer_handle_allocator.h"
#include "layer/layer_res_sec_texture.h"
#include "layer/layer_vertex_obj.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {

void LayerShdManager::allRelease() { shaderRelease(); }

void LayerShdManager::setupMainRenderTarget() { grlib::CGLibState::setMainFrameBuffer(); }

void LayerShdManager::createResWork() { grlib::CGLibTexture::createTextureImagePtrs(unknown368, unknown10, unknown18, false, nullptr, true); }

void LayerShdManager::setSecTexture(LayerResSecTexture *secTexture) {
  if (secTexture != nullptr && secTexture->unknown14 > 0.0f) {
    unknown58 = secTexture->getTexture();
    unknown60 = &secTexture->unknown18;
    unknown4fc = 2;
  } else {
    unknown58 = nullptr;
    unknown4fc = 1;
  }
}

void LayerShdManager::setShaderMaskOff() {
  unknown358 = nullptr;
  unknown50 = nullptr;
  unknown4fa = 1;
}

void LayerShdManager::setDepthBufferCheckOn() {
  if (!unknown529) {
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
    unknown529 = true;
  }
  unknown4f4 = 1;
  unknown350 = nullptr;
}

void LayerShdManager::setDepthBufferCheckOff() {
  if (unknown529) {
    grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_LESS);
    unknown529 = false;
  }
  unknown4f4 = 1;
  unknown350 = nullptr;
}

void LayerShdManager::set3DSpaceMode(grlib::CGLibDblUniformBlock *uniform) {
  if (!unknown529) {
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
    unknown529 = true;
  }
  unknown4f4 = 2;
  unknown350 = uniform;
}

void LayerShdManager::setupTexture(const grlib::CGLibTextureBuffer &texture, LayerSamplerType type, u32 location) { grlib::CGLibCtlTexture::setTexture(texture, unknownc0[type], location); }

grlib::CGLibRenderTarget *LayerShdManager::getDefRenderTarget() {
  if (unknown360 != nullptr) {
    return unknown360;
  }
  return grlib::CGLibState::getMainRenderTarget();
}

void LayerShdManager::setupVertex(LayerVertexObj *vertex, u32 index) { vertex->setVertex(index); }

void LayerShdManager::setupVertex(LayerDefVertType type) { grlib::CGLibCtlVertex::setVertex(unknown238[type]); }

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxInstans &instance, u32 stride, u32 offset) { grlib::CGLibCtlVertex::setInstanceVertex(instance, stride, offset, 1, 1); }

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxOneInstans &instance, u32 stride, u32 offset) { grlib::CGLibCtlVertex::setInstanceVertex(instance, stride, offset, 1, 1); }

void LayerShdManager::renderQuadsIndex() { unknown300.drawIndex(); }

void LayerShdManager::renderInstaceQuadsIndex(u32 instanceCount) { unknown300.drawInsIndex(instanceCount); }

void LayerShdManager::renderLineQuadsIndex() { unknown328.drawIndex(); }

void LayerShdManager::setupBlendDef() {
  grlib::CGLibColorCtl::setBlendControl(
      GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendSwf() {
  grlib::CGLibColorCtl::setBlendControl(
      GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendNo() { grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY); }

void LayerShdManager::setupBlendAdd() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendAddSwf() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendSub() {
  grlib::CGLibColorCtl::setBlendControl(
      GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_SUBTRACT, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_SUBTRACT, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendSubSwf() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_SUBTRACT, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_SUBTRACT, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendMul() {
  grlib::CGLibColorCtl::setBlendControl(
      GRL_BLEND_FUNC_ZERO, GRL_BLEND_FUNC_SRC_COLOR, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ZERO, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::initFlowMap(u32 index) {}

void LayerShdManager::initGamma(u32 index) {}

LayerHandleAllocator::LayerHandleAllocator() {}

LayerHandleAllocator::LayerHandleAllocator(mtl::ALLOC_HANDLE handle) : unknown08(handle) {}

void LayerHandleAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { unknown08 = handle; }

mtl::ALLOC_HANDLE LayerHandleAllocator::getMemHandle() const { return unknown08; }

void *LayerHandleAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(unknown08, size, alignment, false, "no name", 0); }

void LayerHandleAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

} // namespace layer
