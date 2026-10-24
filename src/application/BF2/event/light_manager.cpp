#include "event/light_manager.h"

#include "event/light_evt.h"
#include "ml/dev_graph.h"

namespace event {

bool LightManager::isStreamMode() const { return (unknown14 & FLAG_STREAM_MODE) != 0; }

LightManager::LightManager() : unknown10(0), unknown14(0), unknown38(nullptr) {
  for (u32 i = 0; i < OFFSCR_LIGHT_COUNT; i++) {
    unknown18[i] = nullptr;
  }
}

void LightManager::clear() {
  clearEvtLight();
  clearOffScrLight();
  unknown14 = 0;
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
