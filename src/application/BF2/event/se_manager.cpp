#include "event/se_manager.h"

#include <stddef.h>

#include "event/skip_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/dev_graph.h"
#include "mm_mtl/singleton.h"

namespace event {

SeManager::SeManager() : dispFlags(0), loadCount(0) {}

void SeManager::clear() {
  for (u32 i = 0; i < SE_COUNT; i++) {
    objs[i].clear();
  }
  playList.clear();
  gf::GfGameEvent::destroySe();
  loadCount = 0;
}

void SeManager::render() {
  if ((dispFlags & DISP_FLAG_DISP) == 0 || playList.empty()) {
    return;
  }
  int x = ml::DevGraph::getRootWidth() - 340;
  for (u32 i = 0; i < SE_COUNT; i++) {
    if (objs[i].isPlay()) {
      objs[i].draw(i, x, 230 + i * 70);
    }
  }
}

void SeManager::load(const char *name) {
  gf::GfGameEvent::createSe(name);
  loadCount++;
}

bool SeManager::isLoading() const {
  if (loadCount == 0) {
    return false;
  }
  return !gf::GfGameEvent::isLoadedSe();
}

void SeManager::pause(bool isPause) {
  for (SeObj **it = playList.begin(); it != playList.end(); ++it) {
    (*it)->pause(isPause);
  }
}

void SeManager::play(int index, const char *name, f32 life, f32 fadeIn, f32 fadeOut, f32 volume) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() || *name == '\0') {
    return;
  }
  SeObj *obj = &objs[index];
  obj->play(name, life, fadeIn, fadeOut, volume);
  int found = -1;
  for (size_t i = 0; i < playList.size(); i++) {
    if (playList[i] == obj) {
      found = i;
      break;
    }
  }
  if (found < 0) {
    playList.push_back(obj);
  }
}

void SeManager::changeVolume(int index, f32 volume, f32 frame) {
  if (objs[index].isPlay()) {
    objs[index].changeVolume(volume, frame);
  }
}

void SeManager::pan(int index, f32 pan, f32 frame, CV_TYPE cv) {
  if (objs[index].isPlay()) {
    objs[index].pan(pan, frame, cv);
  }
}

void SeManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool SeManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

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
