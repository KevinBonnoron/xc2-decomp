#include "event/rand_manager.h"

#include "event/debug_manager.h"
#include "event/frame_manager.h"
#include "event/rand_calc.h"

namespace event {

RandManager::RandManager() : unknown10(0) {}

void RandManager::clear() {
  unknown18.clear();
  unknown10 = 0;
}

void RandManager::update() {
  if ((unknown10 & FLAG_PLAY) != 0) {
    unknown18.update();
  }
}

void RandManager::OnEventProc(MSG_TYPE type) {
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
  default:
    break;
  }
}

bool RandManager::play(int id) {
  if (!mm::mtl::Singleton<DebugManager>::getPtr()->isFailureSkip()) {
    if ((unknown10 & FLAG_PLAY) == 0) {
      int talk = RandCalc::calc(id);
      if (talk < 1) {
        return true;
      }
      unknown18.play(talk, (unknown10 & FLAG_WARP) != 0);
      unknown10 |= FLAG_PLAY;
    }
    bool isPlaying = unknown18.isPlaying();
    FrameManager *frameManager = mm::mtl::Singleton<FrameManager>::getPtr();
    if (isPlaying) {
      frameManager->pause(FrameManager::PAUSE_TYPE_RAND, true);
      return false;
    }
    frameManager->pause(FrameManager::PAUSE_TYPE_RAND, false);
    clear();
    return true;
  }
  return true;
}

} // namespace event
