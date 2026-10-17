#include "event/rand_manager.h"

#include "event/debug_manager.h"
#include "event/frame_manager.h"
#include "event/rand_calc.h"

namespace event {

RandManager::RandManager() : flags(0) {}

void RandManager::clear() {
  player.clear();
  flags = 0;
}

void RandManager::update() {
  if ((flags & FLAG_PLAY) != 0) {
    player.update();
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
    if ((flags & FLAG_PLAY) == 0) {
      int talk = RandCalc::calc(id);
      if (talk < 1) {
        return true;
      }
      player.play(talk, (flags & FLAG_WARP) != 0);
      flags |= FLAG_PLAY;
    }
    bool isPlaying = player.isPlaying();
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
