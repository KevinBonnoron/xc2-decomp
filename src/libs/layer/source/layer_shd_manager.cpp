#include "layer/layer_shd_manager.h"

#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_state.h"
#include "layer/layer_handle_allocator.h"
#include "layer/layer_vertex_obj.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {

void LayerShdManager::allRelease() { shaderRelease(); }

void LayerShdManager::setupMainRenderTarget() { grlib::CGLibState::setMainFrameBuffer(); }

void LayerShdManager::setShaderMaskOff() {
  m_viewPortUniform = nullptr;
  m_maskObj = nullptr;
  m_maskMode = 1;
}

void LayerShdManager::setDepthBufferCheckOn() {
  if (!m_isDepthCheck) {
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
    m_isDepthCheck = true;
  }
  m_depthMode = 1;
  m_3DSpaceUniform = nullptr;
}

void LayerShdManager::setDepthBufferCheckOff() {
  if (m_isDepthCheck) {
    grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_LESS);
    m_isDepthCheck = false;
  }
  m_depthMode = 1;
  m_3DSpaceUniform = nullptr;
}

void LayerShdManager::set3DSpaceMode(grlib::CGLibDblUniformBlock *uniform) {
  if (!m_isDepthCheck) {
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
    m_isDepthCheck = true;
  }
  m_depthMode = 2;
  m_3DSpaceUniform = uniform;
}

void LayerShdManager::setupTexture(const grlib::CGLibTextureBuffer &texture, LayerSamplerType type, u32 location) {
  grlib::CGLibCtlTexture::setTexture(texture, m_samplers[type], location);
}

grlib::CGLibRenderTarget *LayerShdManager::getDefRenderTarget() {
  if (m_defRenderTarget != nullptr) {
    return m_defRenderTarget;
  }
  return grlib::CGLibState::getMainRenderTarget();
}

void LayerShdManager::setupVertex(LayerVertexObj *vertex, u32 index) { vertex->setVertex(index); }

void LayerShdManager::setupVertex(LayerDefVertType type) { grlib::CGLibCtlVertex::setVertex(m_vertices[type]); }

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxInstans &instance, u32 stride, u32 offset) {
  grlib::CGLibCtlVertex::setInstanceVertex(instance, stride, offset, 1, 1);
}

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxOneInstans &instance, u32 stride, u32 offset) {
  grlib::CGLibCtlVertex::setInstanceVertex(instance, stride, offset, 1, 1);
}

void LayerShdManager::renderQuadsIndex() { m_quadsIndex.drawIndex(); }

void LayerShdManager::renderInstaceQuadsIndex(u32 instanceCount) { m_quadsIndex.drawInsIndex(instanceCount); }

void LayerShdManager::renderLineQuadsIndex() { m_lineQuadsIndex.drawIndex(); }

void LayerShdManager::setupBlendDef() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA,
                                        GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendSwf() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendNo() { grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY); }

void LayerShdManager::setupBlendAdd() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendAddSwf() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendSub() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_SUBTRACT,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_SUBTRACT,
                                        GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendSubSwf() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_SUBTRACT,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_SUBTRACT,
                                        GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendMul() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ZERO,
                                        GRL_BLEND_FUNC_SRC_COLOR,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_BLEND_FUNC_ZERO,
                                        GRL_BLEND_FUNC_SRC_ALPHA,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::initFlowMap(u32 index) {}

void LayerShdManager::initGamma(u32 index) {}

LayerHandleAllocator::LayerHandleAllocator() {}

LayerHandleAllocator::LayerHandleAllocator(mtl::ALLOC_HANDLE handle) : m_handle(handle) {}

void LayerHandleAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { m_handle = handle; }

mtl::ALLOC_HANDLE LayerHandleAllocator::getMemHandle() const { return m_handle; }

void *LayerHandleAllocator::allocate(size_t size, size_t alignment) {
  return mtl::MemManager::allocate(m_handle, size, alignment, false, "no name", 0);
}

void LayerHandleAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

} // namespace layer
