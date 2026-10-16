#include "event/voice_player.h"

#include <stddef.h>

#include "event/extend.h"
#include "event/skip_manager.h"
#include "event/voice_util.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace event {

const f32 VoicePlayer::TO_SEC = 1.0f / 30.0f;
const f32 VoicePlayer::TO_FR = 30.0f;

VoicePlayer::VoicePlayer() : flags(0), waitingHandle(0), delay(0.0f), handle(0), event(nullptr) {}

void VoicePlayer::clear() {
  stop(10.0f);
  clearPreload();
  flags = 0;
}

void VoicePlayer::stop(f32 frame) {
  handle = 0;
  for (size_t i = 0; i < plays.size(); i++) {
    fw::SoundManager::get()->pause(plays[i].handle, false, 0.0f);
    fw::SoundManager::get()->stopVoice(plays[i].handle, frame * TO_SEC);
  }
  plays.clear();
  clr();
}

void VoicePlayer::clearPreload() {
  stopWaiting();
  keys.clear();
}

void VoicePlayer::stopWaiting() {
  if (waitingHandle != 0) {
    fw::SoundManager::get()->stopVoice(waitingHandle, 0.0f);
    waitingHandle = 0;
  }
  waitingPath = "";
}

void VoicePlayer::draw() {
  if (handle == 0 && waitingHandle == 0) {
    return;
  }
  int width = ml::DevGraph::getRootWidth();
  fw::debug::drawSquare2D(mm::Rect<int>(width - 330, 160, 320, 60), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(width - 330, 160, 320, 60), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(width - 325, 165, "VOICE");
  int x = width - 320;
  if (handle != 0) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(x, 180, "now");
    fw::debug::drawFont(x + 45, 180, mm::mtl::Singleton<Extend>::getPtr()->filename(path.c_str()));
    if ((flags & FLAG_DELAY) != 0) {
      fw::debug::drawFont(x + 230, 180, "delay");
    }
    if (fw::SoundManager::get()->isPreparing(handle)) {
      fw::debug::drawFont(x + 230, 180, "preparing");
    } else {
      fw::debug::drawFont(x + 230, 180, "%d / %d", static_cast<int>(getPlayFrame()), static_cast<int>(getTotalFrame()));
    }
  }
  if (waitingHandle != 0) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(x, 195, "next");
    fw::debug::drawFont(x + 45, 195, mm::mtl::Singleton<Extend>::getPtr()->filename(waitingPath.c_str()));
    if (fw::SoundManager::get()->isPreparing(waitingHandle)) {
      fw::debug::drawFont(x + 230, 195, "preparing");
    }
  }
  int y = 230;
  for (u32 i = 0; i < plays.size(); i++) {
    f32 time = 0.0f;
    bool isTime = fw::SoundManager::get()->getPlayTime(plays[i].handle, time);
    u32 playHandle = plays[i].handle;
    const char *name = mm::mtl::Singleton<Extend>::getPtr()->filename(plays[i].path.c_str());
    fw::debug::drawFont(x - 370,
                        y,
                        "%d %s time=%.2f(%d) valid=%d pause=%d preparing=%d prepared=%d %s",
                        playHandle,
                        name,
                        time,
                        isTime,
                        fw::SoundManager::get()->isValid(plays[i].handle),
                        fw::SoundManager::get()->isPause(plays[i].handle),
                        fw::SoundManager::get()->isPreparing(plays[i].handle),
                        fw::SoundManager::get()->isPrepared(plays[i].handle),
                        plays[i].retakeCount != 0 ? "RETAKE" : "");
    y += 20;
  }
}

f32 VoicePlayer::getPlayFrame() const {
  if (handle != 0) {
    f32 time;
    if (fw::SoundManager::get()->getPlayTime(handle, time)) {
      return time * TO_FR;
    }
  }
  return 0.0f;
}

f32 VoicePlayer::getTotalFrame() const {
  if (handle != 0) {
    f32 time;
    if (fw::SoundManager::get()->getTotalTime(handle, time)) {
      return time * TO_FR;
    }
  }
  return 0.0f;
}

void VoicePlayer::setMultipleMode(bool isMultipleMode) {
  if (isMultipleMode) {
    flags |= FLAG_MULTIPLE_MODE;
  } else {
    flags &= ~FLAG_MULTIPLE_MODE;
  }
}

void VoicePlayer::preload(f32 frame, const char *path) {
  while (keys.size() >= static_cast<int>(KEY_COUNT)) {
    keys.erase(keys.begin());
  }
  keys.push_back(Key(frame, path));
}

bool VoicePlayer::play(const char *path, f32 delay, IVoiceEvent *event) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return false;
  }
  bool isPause = (flags & FLAG_PAUSE) != 0;
  if ((flags & FLAG_MULTIPLE_MODE) == 0) {
    stop(10.0f);
  } else {
    clr();
  }
  if (__builtin_strcmp(waitingPath.c_str(), path) == 0) {
    if (waitingHandle != 0) {
      fw::SoundManager::get()->isPreparing(waitingHandle);
      handle = waitingHandle;
      this->path = waitingPath;
      if (delay <= 0.0f) {
        fw::SoundManager::get()->startVoice(handle);
        flags &= ~FLAG_DELAY;
      } else {
        flags |= FLAG_DELAY;
        this->delay = delay;
      }
    }
    waitingPath = "";
    waitingHandle = 0;
  } else {
    if (delay <= 0.0f) {
      handle = VoiceUtil::playVoice(path, 1.0f, false);
      this->path = path;
      flags &= ~FLAG_DELAY;
    } else {
      handle = 0;
      this->path = path;
      flags |= FLAG_DELAY;
      this->delay = delay;
    }
    stopWaiting();
  }
  while (plays.size() >= plays.capacity()) {
    fw::SoundManager::get()->stopVoice(plays.front().handle, 10.0f * TO_SEC);
    plays.erase(plays.begin());
  }
  if (handle != 0) {
    plays.push_back(Play(handle, path));
  }
  if (isPause) {
    fw::SoundManager::get()->pause(handle, true, 0.0f);
  }
  this->event = event;
  return handle != 0;
}

void VoicePlayer::clr() {
  path = "";
  event = nullptr;
  delay = 0.0f;
  flags &= ~(FLAG_DELAY | FLAG_STARTED | FLAG_START_FAILED);
}

void VoicePlayer::pause(bool isPause) {
  if (isPause == ((flags & FLAG_PAUSE) != 0)) {
    return;
  }
  for (size_t i = 0; i < plays.size(); i++) {
    f32 time = 0.0f;
    f32 totalTime = 0.0f;
    bool isPlayTime = fw::SoundManager::get()->getPlayTime(plays[i].handle, time);
    bool isTotalTime = fw::SoundManager::get()->getTotalTime(handle, totalTime);
    if (isPlayTime && isTotalTime && totalTime > 0.0f && time > 0.0f && totalTime - 0.5f <= time) {
      fw::SoundManager::get()->pause(plays[i].handle, false, 0.0f);
      fw::SoundManager::get()->stopVoice(plays[i].handle, 0.0f);
    } else {
      fw::SoundManager::get()->pause(plays[i].handle, isPause, 0.0f);
    }
  }
  if (isPause) {
    flags |= FLAG_PAUSE;
  } else {
    flags &= ~FLAG_PAUSE;
  }
}

void VoicePlayer::startWaiting(const char *path) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return;
  }
  if (__builtin_strcmp(waitingPath.c_str(), path) == 0) {
    return;
  }
  stopWaiting();
  waitingPath = path;
  waitingHandle = VoiceUtil::playVoice(path, 1.0f, true);
}

bool VoicePlayer::isPlay() const { return handle != 0; }

const char *VoicePlayer::getPath() const { return handle != 0 ? path.c_str() : ""; }

} // namespace event
