#include "event/se_manager.h"

#include <stddef.h>

#include "event/skip_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/dev_graph.h"
#include "mm_mtl/singleton.h"

namespace event {

SeManager::SeManager() : unknown10(0), unknown14(0) {}

void SeManager::clear() {
  for (u32 i = 0; i < SE_COUNT; i++) {
    unknown18[i].clear();
  }
  unknown5318.clear();
  gf::GfGameEvent::destroySe();
  unknown14 = 0;
}

void SeManager::render() {
  if ((unknown10 & DISP_FLAG_DISP) == 0 || unknown5318.empty()) {
    return;
  }
  int x = ml::DevGraph::getRootWidth() - 340;
  for (u32 i = 0; i < SE_COUNT; i++) {
    if (unknown18[i].isPlay()) {
      unknown18[i].draw(i, x, 230 + i * 70);
    }
  }
}

void SeManager::load(const char *name) {
  gf::GfGameEvent::createSe(name);
  unknown14++;
}

bool SeManager::isLoading() const {
  if (unknown14 == 0) {
    return false;
  }
  return !gf::GfGameEvent::isLoadedSe();
}

void SeManager::pause(bool isPause) {
  for (SeObj **it = unknown5318.begin(); it != unknown5318.end(); ++it) {
    (*it)->pause(isPause);
  }
}

void SeManager::play(int index, const char *name, f32 life, f32 fadeIn, f32 fadeOut, f32 volume) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() || *name == '\0') {
    return;
  }
  SeObj *obj = &unknown18[index];
  obj->play(name, life, fadeIn, fadeOut, volume);
  int found = -1;
  for (size_t i = 0; i < unknown5318.size(); i++) {
    if (unknown5318[i] == obj) {
      found = i;
      break;
    }
  }
  if (found < 0) {
    unknown5318.push_back(obj);
  }
}

void SeManager::changeVolume(int index, f32 volume, f32 frame) {
  if (unknown18[index].isPlay()) {
    unknown18[index].changeVolume(volume, frame);
  }
}

void SeManager::pan(int index, f32 pan, f32 frame, CV_TYPE cv) {
  if (unknown18[index].isPlay()) {
    unknown18[index].pan(pan, frame, cv);
  }
}

void SeManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown10 |= DISP_FLAG_DISP;
  } else {
    unknown10 &= ~DISP_FLAG_DISP;
  }
}

bool SeManager::isDisp() const { return (unknown10 & DISP_FLAG_DISP) != 0; }

void SeManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  default:
    break;
  }
}

} // namespace event
