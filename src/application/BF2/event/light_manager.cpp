#include "event/light_manager.h"

#include "event/light_evt.h"
#include "ml/dev_graph.h"

namespace event {

LightManager::LightManager() : dispFlags(0), flags(0), mEvtLight(nullptr) {
  for (u32 i = 0; i < OFFSCR_LIGHT_COUNT; i++) {
    mOffScrLights[i] = nullptr;
  }
}

void LightManager::clear() {
  clearEvtLight();
  clearOffScrLight();
  flags = 0;
}

void LightManager::render() {
  if (!(dispFlags & DISP_FLAG_LIGHT)) {
    return;
  }
  int x = ml::DevGraph::getRootWidth() - 250;
  if (mEvtLight != nullptr && mEvtLight->isPlaying()) {
    mEvtLight->render(x, 280);
  }
  for (u32 i = 1; i < OFFSCR_LIGHT_COUNT; i++) {
    if (mOffScrLights[i] != nullptr && mOffScrLights[i]->isPlaying()) {
      mOffScrLights[i]->render(x, 280 + i * 50);
    }
  }
}

void LightManager::setStreamMode(bool isStreamMode) {
  if (isStreamMode) {
    flags |= FLAG_STREAM_MODE;
  } else {
    flags &= ~FLAG_STREAM_MODE;
  }
}

void LightManager::clearOffScrLight() {
  for (u32 i = 0; i < OFFSCR_LIGHT_COUNT; i++) {
    if (mOffScrLights[i] != nullptr) {
      delete mOffScrLights[i];
      mOffScrLights[i] = nullptr;
    }
  }
}

void LightManager::clearEvtLight() {
  if (mEvtLight != nullptr) {
    delete mEvtLight;
    mEvtLight = nullptr;
  }
}

void LightManager::setLightDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_LIGHT;
  } else {
    dispFlags &= ~DISP_FLAG_LIGHT;
  }
}

bool LightManager::isLightDisp() const { return (dispFlags & DISP_FLAG_LIGHT) != 0; }

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
