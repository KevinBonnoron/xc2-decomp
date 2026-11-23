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

LayerMemHandleAllocator::LayerMemHandleAllocator(mtl::ALLOC_HANDLE handle) : m_memHandle(handle) {}

void LayerMemHandleAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { m_memHandle = handle; }

mtl::ALLOC_HANDLE LayerMemHandleAllocator::getMemHandle() const { return m_memHandle; }

void *LayerMemHandleAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(m_memHandle, size, alignment, false, "no name", 0); }

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
  m_frameRate = 30.0f;
  unknown80 = 0.033333335f;
  m_screenPosWidth = 1.0f;
  m_screenPosHeight = 1.0f;
  unknown90 = 1.0f;
  m_screenSclHeight = 1.0f;
  unknown98 = 0.003125f;
  u32 restSize = size - 0x190000;
  u32 gxSize = restSize / 5 + (-(restSize / 5) & 0xff);
  u32 workSize = restSize - gxSize;
  unknown28 = mtl::MemManager::create(unknown20, workSize, "LayerWork", true);
  unknown2c = mtl::MemManager::create(unknown20, gxSize, "LayerGx", true);
  unknown30.setMemHandle(unknown28);
  unknown40.setMemHandle(unknown2c);
  m_layerMemHandleAllocator.setMemHandle(unknown28);
  m_layerShdManager = new (unknown28) LayerShdManager(this);
  m_layerObjManager = new (unknown28) LayerObjManager(this);
  m_layerFontManager = new (unknown28) LayerFontManager(this);
  m_layerRceManager = new (unknown28) LayerRceManager(this);
  unknown78 = 1;
  if (unknown50->unknown38 != nullptr) {
    unknown50->unknown38->setCallBack(this);
  }
  s_nDebIdx = 0;
  s_nStkIdx = 1;
  s_nTriIdx = 0;
  m_coordinate = LAYER_COORDINATE_PIXEL;
  m_fontBorderWeight = 1.0f;
}

LayerManager::~LayerManager() {
  if (unknown50->unknown38 != nullptr) {
    unknown50->unknown38->releaseCallBack(this);
  }
  if (m_layerObjManager != nullptr) {
    delete m_layerObjManager;
    m_layerObjManager = nullptr;
  }
  if (m_layerFontManager != nullptr) {
    delete m_layerFontManager;
    m_layerFontManager = nullptr;
  }
  if (m_layerRceManager != nullptr) {
    delete m_layerRceManager;
    m_layerRceManager = nullptr;
  }
  if (m_layerShdManager != nullptr) {
    delete m_layerShdManager;
    m_layerShdManager = nullptr;
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
  m_layerShdManager->readShader();
  unknown10 = &LayerManager::loadWait;
}

void LayerManager::tail() {
  s_nDebIdx = s_nDebIdx == 0;
  s_nStkIdx = s_nDebIdx == 0;
  s_nTriIdx = s_nTriIdx > 1 ? 0 : s_nTriIdx + 1;
}

f32 LayerManager::getScreenDivWidth() const { return m_layerShdManager->m_screenDivWidth; }

f32 LayerManager::getScreenDivHeight() const { return m_layerShdManager->m_screenDivHeight; }

f32 LayerManager::getScreenCalcSclWidth() const { return m_layerShdManager->m_screenCalcSclWidth; }

f32 LayerManager::getScreenCalcSclHeight() const { return m_layerShdManager->m_screenCalcSclHeight; }

f32 LayerManager::getScreenCalcPosWidth() const { return m_layerShdManager->m_screenCalcPosWidth; }

f32 LayerManager::getScreenCalcPosHeight() const { return m_layerShdManager->m_screenCalcPosHeight; }

f32 LayerManager::getScreenRatioHeight() const { return m_layerShdManager->m_screenRatioHeight; }

void LayerManager::begin() { (this->*unknown10)(); }

void LayerManager::end() {
  if (!(unknown78 & 1)) {
    m_layerObjManager->end();
  }
}

void LayerManager::apply(const ml::IDrDrawWorkInfo *info) {
  if (!(unknown78 & 1) && info->unknown560 == 0) {
    m_layerObjManager->apply(info);
  }
}

void LayerManager::finalRender(const ml::IDrDrawWorkInfo *info) {
  if (!(unknown78 & 1) && info->unknown560 == 0) {
    m_layerShdManager->beginShader(info);
    m_layerObjManager->finalRender(info);
    m_layerShdManager->endShader(info);
  }
}

void LayerManager::loadWait() {
  unknown78 |= 1;
  if (m_layerShdManager->setupUpdate()) {
    unknown78 &= ~1;
    m_layerFontManager->update();
    m_layerRceManager->update();
    m_layerObjManager->begin();
    unknown10 = &LayerManager::defSetup;
  }
}

void LayerManager::defSetup() {
  unknown78 &= ~1;
  m_layerFontManager->update();
  m_layerRceManager->update();
  m_layerObjManager->begin();
}

void LayerManager::reLoadShd() { unknown78 |= 1; }

void LayerManager::opacityRender(const ml::IDrDrawWorkInfo *info) {}

void LayerManager::alphaRender(const ml::IDrDrawWorkInfo *info) {}

void LayerManager::lastRender(const ml::IDrDrawWorkInfo *info) {}

} // namespace layer

// The game builds the tag parser in the layer manager's unit: LayerManager and LayerTag functions alternate in one contiguous range with no other unit
// between (LayerManager 0x71008f9d9c to 0x71008fa520, LayerStr/LayerTag 0x71008fa530 to 0x71008fb2c4, then the LayerManager render callbacks
// opacityRender to lastRender 0x71008fb2f8 to 0x71008fb300).
#include "layer_tag.cpp"
