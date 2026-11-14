#include "ml/dev_graph.h"

#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_gpu_cache.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_polygon.h"
#include "ml/cache_draw.h"
#include "ml/critical_section.h"
#include "ml/dev_graph_cb.h"
#include "ml/dev_pad.h"
#include "ml/err_viewer.h"
#include "ml/reslist.h"
#include "ml/win_proc_root.h"
#include "ml/win_view_root.h"
#include "ml/work_cpu.h"
#include "ml/work_obj.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"

namespace ml {

namespace dg {

s32 s_nVSync = -1;
s32 s_nVSyncOld = -1;
bool s_bIgnore;
DevGraphModeType s_eGraphMode;

CriticalSection &getCriticalSection() {
  static CriticalSection sect;
  return sect;
}

} // namespace dg

u32 DevGraph::fontGetWidth(const char *text, FONT_STYLE style, f32 scale) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    return graph->fontGetWidthSys(text, style, scale);
  }

  return 0;
}

u32 DevGraph::fontGetHeight(FONT_STYLE style, f32 scale) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    return graph->fontGetHeightSys(style, scale);
  }

  return 0;
}

bool DevGraph::isIgnore() { return dg::s_bIgnore; }

void DevGraph::fontDraw(s16 x, s16 y, f32 scaleX, f32 scaleY, const char *text, const mm::Col4 *color, const mm::Col4 *backColor, bool isShadow) {
  DevGraph *graph = get();
  if (graph != nullptr && graph->unknown228.height != 0 && graph->unknown228.width != 0) {
    if (backColor != nullptr && backColor->a > 0.0f) {
      DebDraw *draw = DebDraw::get(0xffffffff);
      draw->setZComp(false);
      draw->setZWrite(false);
      draw->setCol(*backColor);
      draw->renderRectFill(x, y, fontGetWidth(text, FONT_STYLE_UNKNOWN_0, scaleX), fontGetHeight(FONT_STYLE_UNKNOWN_0, scaleY));
    }
    get()->fontDrawSys(x, y, scaleX, scaleY, text, color, isShadow);
  }
}

DevGraph::DevGraph(const char *name, WorkObj *parent) : DevBase(name, parent, 8), m_enableFrustum(false), unknown314(RSTAT_UNKNOWN_2), unknown318(mm::Col4::black), unknown328(1.0f) {
  unknown1b8.create(16, WorkUtil::getWorkMem());
  unknown340 = nullptr;
  unknown338 = nullptr;
  m_graphQue = nullptr;
  unknown348 = 1.0f;
  for (int i = 0; i < 4; i++) {
    unknown350[i] = nullptr;
  }
}

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
    grlib::CGLibColorCtl::clearMainFrameBuffer(graph->unknown318);
  }
}

void DevGraph::grSetClearCol(const mm::Col4 &color) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->unknown318 = color;
    graph->unknown328 = 1.0f;
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

void *DevGraph::cmdAllocBuf(u32 size, u32 alignment) {
  GraphQue *que = get()->unknown338;
  u8 *buffer = que->unknown30 - size;
  if (reinterpret_cast<size_t>(buffer) % alignment != 0) {
    buffer -= reinterpret_cast<size_t>(buffer) % alignment;
  }
  que->unknown30 = buffer;
  return buffer;
}

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
  if (graph->unknown228.height != 0 && graph->unknown228.width != 0) {
    return static_cast<f32>(graph->unknown228.width) / static_cast<f32>(graph->unknown228.height);
  }

  return 1.0f;
}

const mm::Rect<int> &DevGraph::getViewport() { return get()->m_viewport; }

const mm::Rect<int> &DevGraph::getRenderPort() { return get()->m_renderPort; }

int DevGraph::getRenderW() { return get()->unknown228.width; }

int DevGraph::getRenderH() { return get()->unknown228.height; }

f32 DevGraph::getScreenScaleW() { return get()->getScreenScaleWSys(); }

f32 DevGraph::getVSyncSec() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    return graph->getVSyncSecSys();
  }

  return 0.0f;
}

int DevGraph::getVSync() { return dg::s_nVSync; }

f32 DevGraph::getFrameSyncSec() {
  if (dg::s_nVSync == 0) {
    return getVSyncSec() * 2.0f;
  }

  return getVSyncSec() * dg::s_nVSync;
}

f32 DevGraph::getMicro2FrameRatio(u32 micro) {
  if (get() == nullptr) {
    return 0.0f;
  }

  return static_cast<f32>(micro) * 0.000001f / getFrameSyncSec();
}

void DevGraph::setEnableFrustum(bool isEnable) { get()->m_enableFrustum = isEnable; }

bool DevGraph::getEnableFrustum() { return get()->m_enableFrustum; }

void DevGraph::setFrustumPort(const mm::Rect<int> &port) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->m_frustumPort = port;
  }
}

const mm::Rect<int> &DevGraph::getFrustumPort() { return get()->m_frustumPort; }

void DevGraph::renderBegin() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->cmdOpenDisplayListSys(0, false, false);
    if (grlib::CGLibManager::get() != nullptr) {
      grlib::CGLibManager::get()->begin();
    }
    DebDraw::setup();
    get()->renderBeginSys();
  }
}

void DevGraph::renderEnd() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    for (int i = 0; i < 4; i++) {
      if (graph->unknown350[i] != nullptr) {
        graph->unknown350[i]();
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

bool DevGraph::entryCb(DevGraphCB *callback) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->unknown1b8.push_back(callback);
  }

  return true;
}

bool DevGraph::removeCb(DevGraphCB *callback) {
  DevGraph *graph = get();
  if (graph == nullptr) {
    return false;
  }
  graph->unknown1b8.remove(callback);
  return true;
}

void DevGraph::renderSync() {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->renderSyncSys();
    DebDraw::swap();
  }
}

DevGraphQue::~DevGraphQue() {}

GraphQue *DevGraphQue::createQue(u32 size) {
  GraphQue *que = new (WorkUtil::getWorkMem()) GraphQue(this);
  que->unknown002(size);
  entryQue(que);
  return que;
}

bool DevGraphQue::entryQue(GraphQue *que) {
  unknown08.push_back(que);
  return true;
}

bool DevGraphQue::removeQue(GraphQue *que) {
  for (reslist<GraphQue *>::Node *node = unknown08.begin(); node != unknown08.end(); node = node->getNext()) {
    if (node->value == que) {
      delete que;
      unknown08.erase(node);
      break;
    }
  }

  return true;
}

void DevGraphQue::swap() {
  unknown00 = unknown00 == 0;
  for (reslist<GraphQue *>::Node *node = unknown08.begin(); node != unknown08.end(); node = node->getNext()) {
    node->value->unknown001();
  }
}

u32 DevGraphQue::getEven() { return unknown00; }

bool DevGraphQue::getOdd() { return unknown00 == 0; }

mm::Rect<int> &DevGraphQue::getViewport() { return unknown58.back(); }

mm::Rect<int> &DevGraphQue::getRenderRect() { return unknown478.back(); }

void DevGraph::cb(RCB type) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    for (reslist<DevGraphCB *>::Node *node = graph->unknown1b8.begin(); node != get()->unknown1b8.end(); node = node->getNext()) {
      DevGraphCB *callback = node->value;
      if (type == RCB_UNKNOWN_0) {
        callback->viBeginFrame();
      } else if (type == RCB_UNKNOWN_1) {
        callback->viBeforeDrawDone();
      } else if (type == RCB_UNKNOWN_2) {
        callback->viAfterDrawDone();
      } else if (type == RCB_UNKNOWN_3) {
        callback->viAfterSync();
      } else if (type == RCB_UNKNOWN_4) {
        callback->viAfterRenderCall();
      }
    }
  }
}

bool DevGraph::wkStandbyLogin() {
  if (!WorkCpu::isInitialized()) {
    return false;
  }
  m_graphQue = new (WorkUtil::getWorkMem()) DevGraphQue();
  unknown338 = m_graphQue->createQue(0x600000);
  if (grlib::CGLibManager::get() == nullptr) {
    new (WorkUtil::getWorkMem()) grlib::CGLibManager();
  }
  unknown1f8 = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
  m_viewport = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
  m_renderPort = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
  unknown228 = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
  m_frustumPort = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
  ErrViewer::create();
  return WorkObj::wkStandbyLogin();
}

bool DevGraph::wkStandbyLogout() {
  if (unknown60.size() != 0 || WinProcRoot::get() != nullptr || WinViewRoot::get() != nullptr || DevPad::get() != nullptr) {
    return false;
  }
  if (!ErrViewer::destroy()) {
    return false;
  }
  m_graphQue->removeQue(unknown338);
  unknown338 = nullptr;
  unknown340 = nullptr;
  if (m_graphQue != nullptr) {
    delete m_graphQue;
    m_graphQue = nullptr;
  }
  if (!grlib::CGLibManager::isReleaseOk()) {
    return true;
  }
  return WorkObj::wkStandbyLogout();
}

void DevGraph::setRenderState(RSTAT state) {
  CS lock(dg::getCriticalSection());
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->unknown314 = state;
  }
}

RSTAT DevGraph::getRenderState() {
  CS lock(dg::getCriticalSection());
  DevGraph *graph = get();
  if (graph == nullptr) {
    return RSTAT_UNKNOWN_2;
  }
  return graph->unknown314;
}

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

void DevGraph::wkTail() {
  cmdTermDisplayListSys();
  m_graphQue->swap();
  cmdSetupDisplayListSys();
  if (dg::s_nVSync != dg::s_nVSyncOld) {
    dg::s_nVSyncOld = dg::s_nVSync;
  }
  ErrViewer::tail();
  if (grlib::CGLibManager::get() != nullptr) {
    grlib::CGLibManager::get()->tail();
  }
}

void DevGraph::setFrameSpd(f32 speed) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    graph->unknown348 = speed;
  }
}

void DevGraph::addOuterRender(void (*render)()) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    for (int i = 0; i < 4; i++) {
      if (graph->unknown350[i] == nullptr) {
        graph->unknown350[i] = render;
        return;
      }
    }
  }
}

void DevGraph::removeOuterRender(void (*render)()) {
  DevGraph *graph = get();
  if (graph != nullptr) {
    for (int i = 0; i < 4; i++) {
      if (graph->unknown350[i] == render) {
        graph->unknown350[i] = nullptr;
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

class IDevFontInfo;

template class reslist<DevGraphCB *>;
template class reslist<GraphQue *>;
template class reslist<IDevFontInfo *>;

} // namespace ml
