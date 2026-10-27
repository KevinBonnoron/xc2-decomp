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

LayerMemHandleAllocator::LayerMemHandleAllocator(mtl::ALLOC_HANDLE handle) : unknown08(handle) {}

void LayerMemHandleAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { unknown08 = handle; }

mtl::ALLOC_HANDLE LayerMemHandleAllocator::getMemHandle() const { return unknown08; }

void *LayerMemHandleAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(unknown08, size, alignment, false, "no name", 0); }

void LayerMemHandleAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

void LayerManager::beginFastSetup() {
  unknown78 |= 1;
  unknown58->readShader();
  unknown10 = &LayerManager::loadWait;
}

void LayerManager::tail() {
  s_nDebIdx = s_nDebIdx == 0;
  s_nStkIdx = s_nDebIdx == 0;
  s_nTriIdx = s_nTriIdx > 1 ? 0 : s_nTriIdx + 1;
}

f32 LayerManager::getScreenDivWidth() const { return unknown58->unknown538; }

f32 LayerManager::getScreenDivHeight() const { return unknown58->unknown53c; }

f32 LayerManager::getScreenCalcSclWidth() const { return unknown58->unknown548; }

f32 LayerManager::getScreenCalcSclHeight() const { return unknown58->unknown54c; }

f32 LayerManager::getScreenCalcPosWidth() const { return unknown58->unknown540; }

f32 LayerManager::getScreenCalcPosHeight() const { return unknown58->unknown544; }

f32 LayerManager::getScreenRatioHeight() const { return unknown58->unknown574; }

void LayerManager::begin() { (this->*unknown10)(); }

void LayerManager::end() {
  if (!(unknown78 & 1)) {
    unknown60->end();
  }
}

void LayerManager::apply(const ml::IDrDrawWorkInfo *info) {
  if (!(unknown78 & 1) && info->unknown560 == 0) {
    unknown60->apply(info);
  }
}

void LayerManager::finalRender(const ml::IDrDrawWorkInfo *info) {
  if (!(unknown78 & 1) && info->unknown560 == 0) {
    unknown58->beginShader(info);
    unknown60->finalRender(info);
    unknown58->endShader(info);
  }
}

void LayerManager::loadWait() {
  unknown78 |= 1;
  if (unknown58->setupUpdate()) {
    unknown78 &= ~1;
    unknown68->update();
    unknown70->update();
    unknown60->begin();
    unknown10 = &LayerManager::defSetup;
  }
}

void LayerManager::defSetup() {
  unknown78 &= ~1;
  unknown68->update();
  unknown70->update();
  unknown60->begin();
}

void LayerManager::reLoadShd() { unknown78 |= 1; }

void LayerManager::opacityRender(const ml::IDrDrawWorkInfo *info) {}

void LayerManager::alphaRender(const ml::IDrDrawWorkInfo *info) {}

void LayerManager::lastRender(const ml::IDrDrawWorkInfo *info) {}

} // namespace layer
