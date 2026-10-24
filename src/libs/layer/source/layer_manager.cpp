#include "layer/layer_manager.h"
#include "layer/layer_mem_handle_allocator.h"
#include "mtl/mem_manager.h"

#include "dr/dr_draw_work_info.h"
#include "layer/layer_font_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_rce_manager.h"
#include "layer/layer_shd_manager.h"

namespace layer {

LayerMemHandleAllocator::LayerMemHandleAllocator() {}

LayerMemHandleAllocator::LayerMemHandleAllocator(mtl::ALLOC_HANDLE handle) : m_handle(handle) {}

void LayerMemHandleAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { m_handle = handle; }

mtl::ALLOC_HANDLE LayerMemHandleAllocator::getMemHandle() const { return m_handle; }

void *LayerMemHandleAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(m_handle, size, alignment, false, "no name", 0); }

void LayerMemHandleAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

void LayerManager::beginFastSetup() {
  m_flags |= 1;
  m_shdManager->readShader();
  m_setupFunc = &LayerManager::loadWait;
}

void LayerManager::tail() {
  s_nDebIdx = s_nDebIdx == 0;
  s_nStkIdx = s_nDebIdx == 0;
  s_nTriIdx = s_nTriIdx > 1 ? 0 : s_nTriIdx + 1;
}

f32 LayerManager::getScreenDivWidth() const { return m_shdManager->m_screenDivWidth; }

f32 LayerManager::getScreenDivHeight() const { return m_shdManager->m_screenDivHeight; }

f32 LayerManager::getScreenCalcSclWidth() const { return m_shdManager->m_screenCalcSclWidth; }

f32 LayerManager::getScreenCalcSclHeight() const { return m_shdManager->m_screenCalcSclHeight; }

f32 LayerManager::getScreenCalcPosWidth() const { return m_shdManager->m_screenCalcPosWidth; }

f32 LayerManager::getScreenCalcPosHeight() const { return m_shdManager->m_screenCalcPosHeight; }

f32 LayerManager::getScreenRatioHeight() const { return m_shdManager->m_screenRatioHeight; }

void LayerManager::begin() { (this->*m_setupFunc)(); }

void LayerManager::end() {
  if (!(m_flags & 1)) {
    m_objManager->end();
  }
}

void LayerManager::apply(const ml::IDrDrawWorkInfo *info) {
  if (!(m_flags & 1) && info->unknown560 == 0) {
    m_objManager->apply(info);
  }
}

void LayerManager::finalRender(const ml::IDrDrawWorkInfo *info) {
  if (!(m_flags & 1) && info->unknown560 == 0) {
    m_shdManager->beginShader(info);
    m_objManager->finalRender(info);
    m_shdManager->endShader(info);
  }
}

void LayerManager::loadWait() {
  m_flags |= 1;
  if (m_shdManager->setupUpdate()) {
    m_flags &= ~1;
    m_fontManager->update();
    m_rceManager->update();
    m_objManager->begin();
    m_setupFunc = &LayerManager::defSetup;
  }
}

void LayerManager::defSetup() {
  m_flags &= ~1;
  m_fontManager->update();
  m_rceManager->update();
  m_objManager->begin();
}

void LayerManager::reLoadShd() { m_flags |= 1; }

} // namespace layer
