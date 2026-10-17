#include "ml/dev_graph.h"

#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_gpu_cache.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_polygon.h"
#include "ml/err_viewer.h"
#include "ml/work_obj.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"

namespace ml {

namespace dg {

s32 s_nVSync = -1;
s32 s_nVSyncOld = -1;
bool s_bIgnore;
DevGraphModeType s_eGraphMode;

} // namespace dg

f32 DevGraph::fontGetWidth(const char *text, FONT_STYLE style, f32 scale) {
  f32 width;
  DevGraph *graph = get();
  if (graph != nullptr) {
    width = graph->fontGetWidthSys(text, style, scale);
  }

  return width;
}

f32 DevGraph::fontGetHeight(FONT_STYLE style, f32 scale) {
  f32 height;
  DevGraph *graph = get();
  if (graph != nullptr) {
    height = graph->fontGetHeightSys(style, scale);
  }

  return height;
}

bool DevGraph::isIgnore() { return dg::s_bIgnore; }

void DevGraph::setIgnore(bool isIgnore) { dg::s_bIgnore = isIgnore; }

void DevGraph::setRenderMode(DevGraphModeType mode) { dg::s_eGraphMode = mode; }

DevGraphModeType DevGraph::getRenderMode() { return dg::s_eGraphMode; }

void DevGraph::grSetViewport(const mm::Rect<int> &viewport, int index) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->grSetViewportSys(viewport, index);
  }
}

void DevGraph::grSetScissor(const mm::Rect<int> &scissor) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->grSetScissorSys(scissor);
  }
}

void DevGraph::grClearScreen() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    grlib::CGLibColorCtl::clearMainFrameBuffer(graph->m_clearCol);
  }
}

void DevGraph::grSetClearCol(const mm::Col4 &color) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->m_clearCol = color;
    graph->m_clearDepth = 1.0f;
  }
}

void DevGraph::grSetDoubleSide(bool isDoubleSide) {
  if (get() != nullptr) {
    if (isDoubleSide) {
      grlib::CGLibPolygon::setCullingOff();
    } else {
      grlib::CGLibPolygon::setCullingBack();
    }
  }
}

void DevGraph::grSetZMode(bool isTest, bool isWrite) {
  if (get() != nullptr) {
    if (isTest) {
      grlib::CGLibDepthCtl::setDepthControl(true, isWrite, GRL_COMPARE_LEQUAL);
    } else {
      grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_ALWAYS);
    }
  }
}

void DevGraph::grSetAlphaBlend(bool isBlend) {
  if (get() != nullptr) {
    if (isBlend) {
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
    } else {
      grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
    }
  }
}

void DevGraph::grInitContext() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->grInitContextSys();
    get()->m_graphQue->flushViewport();
  }
}

void DevGraph::grFlushViewport() { get()->m_graphQue->flushViewport(); }

int DevGraph::getRootWidth() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    return graph->getRootWidthSys();
  }

  return 0;
}

int DevGraph::getRootHeight() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    return graph->getRootHeightSys();
  }

  return 0;
}

void DevGraph::setMemPoolMemHandle(mtl::ALLOC_HANDLE handle) { grlib::CGLibGPUCache::setMemPoolMemHandle(handle); }

void DevGraph::setMemPoolBuffer(void *buffer, u32 size) { grlib::CGLibGPUCache::setMemPoolBuffer(buffer, size); }

void DevGraph::releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle) { grlib::CGLibGPUCache::releaseMemPoolMemHandle(handle); }

void DevGraph::releaseMemPoolBuffer(void *buffer) { grlib::CGLibGPUCache::releaseMemPoolBuffer(buffer); }

void DevGraph::cmdOpenDisplayList(u32 size) { get()->cmdOpenDisplayListSys(size, false, false); }

void DevGraph::cmdCloseDisplayList() { get()->cmdCloseDisplayListSys(false); }

void DevGraph::cmdAddCreatedList(void *list, u32 size) { get()->cmdAddCreatedListSys(list, size); }

void DevGraph::cmdSuspendDisplayList(bool isSuspend, bool isFlush) { get()->cmdSuspendDisplayListSys(isSuspend, isFlush); }

void *DevGraph::cmdGetCurrentAdr() { return get()->cmdGetCurrentAdrSys(); }

u32 DevGraph::cmdGetRemainSize() { return get()->cmdGetRemainSizeSys(); }

void DevGraph::cmdExecDisplayList() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->cmdExecDisplayListSys();
  }
}

void DevGraph::cmdAddDisplayList(void *list, u32 size, u32 flags) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->cmdAddDisplayListSys(list, size, flags);
  }
}

bool DevGraph::cmdIsOpenDisplayList() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    return graph->cmdIsOpenDisplayListSys();
  }

  return false;
}

void DevGraph::pushRect(const mm::Rect<int> &viewport, const mm::Rect<int> &scissor, const mm::Rect<int> &renderRect, bool isFlush) {
  get()->m_graphQue->pushRect(viewport, scissor, renderRect, isFlush);
}

void DevGraph::popRect() { get()->m_graphQue->popRect(); }

void DevGraph::getPers(mm::Mat44 &matrix, f32 fovy, f32 near, f32 far) { get()->getPersSys(matrix, fovy, near, far); }

void DevGraph::getOrtho(mm::Mat44 &matrix) { get()->getOrthoSys(matrix); }

f32 DevGraph::getAspect() {
  DevGraph *graph = get();
  if (graph->m_renderH != 0 && graph->m_renderW != 0) {
    return static_cast<f32>(graph->m_renderW) / static_cast<f32>(graph->m_renderH);
  }

  return 1.0f;
}

const mm::Rect<int> &DevGraph::getViewport() { return get()->m_viewport; }

const mm::Rect<int> &DevGraph::getRenderPort() { return get()->m_renderPort; }

int DevGraph::getRenderW() { return get()->m_renderW; }

int DevGraph::getRenderH() { return get()->m_renderH; }

f32 DevGraph::getScreenScaleW() { return get()->getScreenScaleWSys(); }

f32 DevGraph::getVSyncSec() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    return graph->getVSyncSecSys();
  }

  return 0.0f;
}

int DevGraph::getVSync() { return dg::s_nVSync; }

void DevGraph::setEnableFrustum(bool isEnable) { get()->m_isEnableFrustum = isEnable; }

bool DevGraph::getEnableFrustum() { return get()->m_isEnableFrustum; }

void DevGraph::setFrustumPort(const mm::Rect<int> &port) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->m_frustumPort = port;
  }
}

const mm::Rect<int> &DevGraph::getFrustumPort() { return get()->m_frustumPort; }

void DevGraph::renderEnd() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    for (int i = 0; i < 4; i++) {
      if (graph->m_outerRenders[i] != nullptr) {
        graph->m_outerRenders[i]();
      }
    }

    graph->renderEndSys();
    if (grlib::CGLibManager::get() != nullptr) {
      grlib::CGLibManager::get()->end();
    }

    get()->cmdCloseDisplayListSys(false);
  }
}

void DevGraph::resetSize(s16 width, s16 height) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->resetSizeSys(width, height);
  }
}

f32 DevGraph::getCost() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    return graph->getCostSys();
  }

  return 0.0f;
}

DevGraphQue *DevGraph::getGraphQue() { return get()->m_graphQue; }

bool DevGraph::isInitialized() {
  DevGraph *graph = get();
  if (graph == nullptr) {
    return true;
  }

  if (graph->wkIsWaitException()) {
    return false;
  }

  return graph->wkIsActive();
}

void DevGraph::setVSync(int vsync) {
  dg::s_nVSyncOld = dg::s_nVSync;
  dg::s_nVSync = vsync;
}

void DevGraph::wkStandby() {
  WorkObj::wkStandby();
  ErrViewer::standby();
}

void DevGraph::wkUpdate() { ErrViewer::update(); }

void DevGraph::setFrameSpd(f32 speed) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->m_frameSpd = speed;
  }
}

void DevGraph::addOuterRender(void (*render)()) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    for (int i = 0; i < 4; i++) {
      if (graph->m_outerRenders[i] == nullptr) {
        graph->m_outerRenders[i] = render;
        return;
      }
    }
  }
}

void DevGraph::removeOuterRender(void (*render)()) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    for (int i = 0; i < 4; i++) {
      if (graph->m_outerRenders[i] == render) {
        graph->m_outerRenders[i] = nullptr;
        return;
      }
    }
  }
}

void DevGraph::createGraphDeveice() {
  if (grlib::CGLibManager::get() == nullptr) {
    new (WorkUtil::getWorkMem()) grlib::CGLibManager();
    grlib::CGLibManager::get()->deviceInit();
  }
}

void DevGraph::cmdAddDisplayListFast(void *list, u32 size, u32 flags) {}

void DevGraph::cmdExecDisplayListSys() {}

void DevGraph::cmdAddDisplayListSys(void *list, u32 size, u32 flags) {}

void DevGraph::cmdSetupDisplayListSys() {}

void DevGraph::cmdTermDisplayListSys() {}

void *DevGraph::cmdOpenDisplayListSys(u32 size, bool isSuspend, bool isFlush) { return nullptr; }

bool DevGraph::cmdCloseDisplayListSys(bool isFlush) { return false; }

void DevGraph::cmdAddCreatedListSys(void *list, u32 size) {}

void DevGraph::cmdSuspendDisplayListSys(bool isSuspend, bool isFlush) {}

void *DevGraph::cmdGetCurrentAdrSys() { return nullptr; }

u32 DevGraph::cmdGetRemainSizeSys() const { return 0; }

void *DevGraph::cmdAllocSys(u32 size, u32 alignment) { return nullptr; }

void *DevGraph::cmdAlignSys(u32 alignment) { return nullptr; }

void *DevGraph::cmdAddOfsSys(u32 offset) { return nullptr; }

bool DevGraph::cmdIsOpenDisplayListSys() const { return false; }

} // namespace ml
