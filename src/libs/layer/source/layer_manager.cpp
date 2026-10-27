#include "layer/layer_manager.h"
#include "layer/layer_mem_handle_allocator.h"
#include "mtl/mem_manager.h"

#include "dr/dr_draw_work_info.h"
#include "layer/layer_font_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_rce_manager.h"
#include "layer/layer_shd_manager.h"
#include "ml/scn.h"
#include "scn/scn_render_dr_sys.h"

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

LayerManager::LayerManager(ml::Scn *scn, mtl::ALLOC_HANDLE handle, unsigned int size) : unknown50(scn) {
  unknown10 = &LayerManager::beginFastSetup;
  unknown20 = mtl::ALLOC_HANDLE();
  unknown24 = mtl::ALLOC_HANDLE();
  unknown28 = mtl::ALLOC_HANDLE();
  unknown2c = mtl::ALLOC_HANDLE();
  unknown20 = mtl::MemManager::create(handle, size + 0x1000, "LayerTop", false);
  unknown24 = mtl::MemManager::create(unknown20, 0x190000, "LayerData", false);
  unknown7c = 30.0f;
  unknown80 = 0.033333335f;
  unknown88 = 1.0f;
  unknown8c = 1.0f;
  unknown90 = 1.0f;
  unknown94 = 1.0f;
  unknown98 = 0.003125f;
  u32 restSize = size - 0x190000;
  u32 gxSize = restSize / 5 + (-(restSize / 5) & 0xff);
  u32 workSize = restSize - gxSize;
  unknown28 = mtl::MemManager::create(unknown20, workSize, "LayerWork", true);
  unknown2c = mtl::MemManager::create(unknown20, gxSize, "LayerGx", true);
  unknown30.setMemHandle(unknown28);
  unknown40.setMemHandle(unknown2c);
  unknowna0.setMemHandle(unknown28);
  unknown58 = new (unknown28) LayerShdManager(this);
  unknown60 = new (unknown28) LayerObjManager(this);
  unknown68 = new (unknown28) LayerFontManager(this);
  unknown70 = new (unknown28) LayerRceManager(this);
  unknown78 = 1;
  if (unknown50->unknown38 != nullptr) {
    unknown50->unknown38->setCallBack(this);
  }
  s_nDebIdx = 0;
  s_nStkIdx = 1;
  s_nTriIdx = 0;
  unknown9c = LAYER_COORDINATE_PIXEL;
  unknown84 = 1.0f;
}

LayerManager::~LayerManager() {
  if (unknown50->unknown38 != nullptr) {
    unknown50->unknown38->releaseCallBack(this);
  }
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }
  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
  if (unknown2c.isValid()) {
    mtl::MemManager::erase(unknown2c);
    unknown2c = mtl::ALLOC_HANDLE();
  }
  if (unknown28.isValid()) {
    mtl::MemManager::erase(unknown28);
    unknown28 = mtl::ALLOC_HANDLE();
  }
  if (unknown24.isValid()) {
    mtl::MemManager::erase(unknown24);
    unknown24 = mtl::ALLOC_HANDLE();
  }
  if (unknown20.isValid()) {
    mtl::MemManager::erase(unknown20);
    unknown20 = mtl::ALLOC_HANDLE();
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
