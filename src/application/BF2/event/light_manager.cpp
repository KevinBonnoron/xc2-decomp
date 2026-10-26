#include "event/light_manager.h"

#include "event/cam_interface.h"
#include "event/cam_manager.h"
#include "event/extend.h"
#include "event/light_evt.h"
#include "event/memory_manager.h"
#include "event/res_manager.h"
#include "ml/dev_graph.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

const char *LightManager::OFF_PATH = "event/offlgt/offlgt01";

bool LightManager::isStreamMode() const { return (unknown14 & FLAG_STREAM_MODE) != 0; }

LightManager::LightManager() : unknown10(0), unknown14(0), unknown38(nullptr) {
  for (u32 i = 0; i < OFFSCR_LIGHT_COUNT; i++) {
    unknown18[i] = nullptr;
  }
}

void LightManager::loadOffScrLight(u32 screenID) { mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->lgt(OFF_PATH), nullptr, false); }

void LightManager::loadResource(const char *name) {
  if ((unknown14 & FLAG_STREAM_MODE) == 0) {
    mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->lgt(name), nullptr, true);
  }
}

void LightManager::loadEvtLight(const char *name) {
  mm::mtl::FixStr<256> path;
  path.format("event/evtlgt/%s", name);
  mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->lgt(path.c_str()), nullptr, false);
}

void LightManager::playEvtLight(const char *name) {
  clearEvtLight();
  mm::mtl::FixStr<256> path;
  path.format("event/evtlgt/%s", name);
  void *adr = mm::mtl::Singleton<ResManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->lgt(path.c_str()), nullptr);
  if (adr != nullptr) {
    unknown38 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) LightEvt;
    unknown38->play(adr, path.c_str(), 0);
  }
}

void LightManager::playOffScrLight(u32 screenID) {
  if (screenID != 0 && unknown18[screenID] == nullptr) {
    void *adr = mm::mtl::Singleton<ResManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->lgt(OFF_PATH), nullptr);
    if (adr != nullptr) {
      LightEvt *light = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) LightEvt;
      unknown18[screenID] = light;
      light->play(adr, OFF_PATH, screenID);
    }
  }
}

void LightManager::clear() {
  clearEvtLight();
  clearOffScrLight();
  unknown14 = 0;
}

void LightManager::update() {
  for (u32 i = 1; i < OFFSCR_LIGHT_COUNT; i++) {
    if (unknown18[i] != nullptr && unknown18[i]->isPlaying()) {
      unknown18[i]->setPos(mm::mtl::Singleton<CamManager>::getPtr()->unknown001(i)->unknown40);
    }
  }
}

void LightManager::render() {
  if (!(unknown10 & DISP_FLAG_LIGHT)) {
    return;
  }
  int x = ml::DevGraph::getRootWidth() - 250;
  if (unknown38 != nullptr && unknown38->isPlaying()) {
    unknown38->render(x, 280);
  }
  for (u32 i = 1; i < OFFSCR_LIGHT_COUNT; i++) {
    if (unknown18[i] != nullptr && unknown18[i]->isPlaying()) {
      unknown18[i]->render(x, 280 + i * 50);
    }
  }
}

void LightManager::setStreamMode(bool isStreamMode) {
  if (isStreamMode) {
    unknown14 |= FLAG_STREAM_MODE;
  } else {
    unknown14 &= ~FLAG_STREAM_MODE;
  }
}

void LightManager::clearOffScrLight() {
  for (u32 i = 0; i < OFFSCR_LIGHT_COUNT; i++) {
    if (unknown18[i] != nullptr) {
      delete unknown18[i];
      unknown18[i] = nullptr;
    }
  }
}

void LightManager::clearEvtLight() {
  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }
}

void LightManager::setLightDisp(bool isDisp) {
  if (isDisp) {
    unknown10 |= DISP_FLAG_LIGHT;
  } else {
    unknown10 &= ~DISP_FLAG_LIGHT;
  }
}

bool LightManager::isLightDisp() const { return (unknown10 & DISP_FLAG_LIGHT) != 0; }

void LightManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  case MSG_TYPE_TAIL:
    update();
    break;
  default:
    break;
  }
}

} // namespace event
