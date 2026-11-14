#include "event/voice_player.h"

#include <stddef.h>

#include "event/extend.h"
#include "event/frame_manager.h"
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

static constexpr int STALL_UNKNOWN_19 = 19; // Inferred role: stall count that pauses a voice; original name unknown.
static constexpr int STALL_UNKNOWN_20 = 20; // Inferred role: stall count that resumes a voice; original name unknown.

VoicePlayer::VoicePlayer() : unknown08(0), unknown46c(0), unknown470(0.0f), unknown4b8(0), unknown4c0(nullptr) {}

void VoicePlayer::clear() {
  stop(10.0f);
  clearPreload();
  unknown08 = 0;
}

void VoicePlayer::stop(f32 frame) {
  unknown4b8 = 0;
  for (size_t i = 0; i < unknown2d0.size(); i++) {
    fw::SoundManager::get()->pause(unknown2d0[i].unknown00, false, 0.0f);
    fw::SoundManager::get()->stopVoice(unknown2d0[i].unknown00, frame * TO_SEC);
  }
  unknown2d0.clear();
  clr();
}

void VoicePlayer::clearPreload() {
  stopWaiting();
  unknown0c.clear();
}

void VoicePlayer::update() {
  if ((unknown08 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_3)) == FLAG_UNKNOWN_0) {
    unknown470 -= 1.0f;
    if (unknown470 < 0.0f) {
      unknown4b8 = VoiceUtil::playVoice(unknown474.c_str(), 1.0f, false);
      if (unknown4b8 != 0) {
        unknown2d0.push_back(Play(unknown4b8, unknown474.c_str()));
      }
      unknown08 &= ~FLAG_UNKNOWN_0;
    }
  }
  if (unknown4b8 != 0) {
    if ((unknown08 & (FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) == 0 && !fw::SoundManager::get()->isPreparing(unknown4b8)) {
      bool isPlaying = fw::SoundManager::get()->isPlaying(unknown4b8);
      if (unknown4c0 != nullptr) {
        unknown4c0->OnVoicePlay(unknown474.c_str(), isPlaying);
      }
      if (isPlaying) {
        unknown08 |= FLAG_UNKNOWN_1;
      }
      if (!isPlaying) {
        unknown08 |= FLAG_UNKNOWN_2;
      }
    }
    if (!fw::SoundManager::get()->isPlaying(unknown4b8) && !fw::SoundManager::get()->isPreparing(unknown4b8)) {
      fw::SoundManager::get()->pause(unknown4b8, false, 0.0f);
      fw::SoundManager::get()->stopVoice(unknown4b8, 0.0f);
      unknown4b8 = 0;
      unknown474 = "";
    }
    if ((unknown08 & FLAG_UNKNOWN_3) == 0) {
      for (size_t i = 0; i < unknown2d0.size(); i++) {
        if (fw::SoundManager::get()->isPlaying(unknown2d0[i].unknown00)) {
          f32 time = 0.0f;
          if (fw::SoundManager::get()->getPlayTime(unknown2d0[i].unknown00, time)) {
            if (unknown2d0[i].unknown48 != time) {
              unknown2d0[i].unknown4c = 0;
              unknown2d0[i].unknown48 = time;
            } else {
              unknown2d0[i].unknown4c++;
              if (unknown2d0[i].unknown4c == STALL_UNKNOWN_19) {
                fw::SoundManager::get()->pause(unknown2d0[i].unknown00, true, 0.0f);
              } else if (unknown2d0[i].unknown4c == STALL_UNKNOWN_20) {
                unknown2d0[i].unknown4c = 0;
                unknown2d0[i].unknown50++;
                fw::SoundManager::get()->pause(unknown2d0[i].unknown00, false, 0.0f);
              }
            }
          }
        }
      }
    }
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
      stop(10.0f);
    }
  }
  if (unknown46c != 0 && !fw::SoundManager::get()->isPlaying(unknown46c)) {
    unknown46c = 0;
  }
  while (!unknown2d0.empty()) {
    Play *play = unknown2d0.begin();
    if (fw::SoundManager::get()->isPlaying(play->unknown00)) {
      break;
    }
    fw::SoundManager::get()->pause(play->unknown00, false, 0.0f);
    fw::SoundManager::get()->stopVoice(play->unknown00, 0.0f);
    unknown2d0.erase(play);
  }
  if (unknown0c.size() > 0) {
    f32 frame = mm::mtl::Singleton<FrameManager>::getPtr()->getFrame();
    while (unknown0c.size() > 0 && unknown0c.begin()->unknown00 <= frame) {
      unknown0c.pop_front();
    }
  }
  if (unknown46c != 0 && mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    stopWaiting();
  }
}

void VoicePlayer::stopWaiting() {
  if (unknown46c != 0) {
    fw::SoundManager::get()->stopVoice(unknown46c, 0.0f);
    unknown46c = 0;
  }
  unknown428 = "";
}

void VoicePlayer::draw() {
  if (unknown4b8 == 0 && unknown46c == 0) {
    return;
  }
  int width = ml::DevGraph::getRootWidth();
  fw::debug::drawSquare2D(mm::Rect<int>(width - 330, 160, 320, 60), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(width - 330, 160, 320, 60), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(width - 325, 165, "VOICE");
  int x = width - 320;
  if (unknown4b8 != 0) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(x, 180, "now");
    fw::debug::drawFont(x + 45, 180, mm::mtl::Singleton<Extend>::getPtr()->filename(unknown474.c_str()));
    if ((unknown08 & FLAG_UNKNOWN_0) != 0) {
      fw::debug::drawFont(x + 230, 180, "delay");
    }
    if (fw::SoundManager::get()->isPreparing(unknown4b8)) {
      fw::debug::drawFont(x + 230, 180, "preparing");
    } else {
      fw::debug::drawFont(x + 230, 180, "%d / %d", static_cast<int>(getPlayFrame()), static_cast<int>(getTotalFrame()));
    }
  }
  if (unknown46c != 0) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(x, 195, "next");
    fw::debug::drawFont(x + 45, 195, mm::mtl::Singleton<Extend>::getPtr()->filename(unknown428.c_str()));
    if (fw::SoundManager::get()->isPreparing(unknown46c)) {
      fw::debug::drawFont(x + 230, 195, "preparing");
    }
  }
  int y = 230;
  for (u32 i = 0; i < unknown2d0.size(); i++) {
    f32 time = 0.0f;
    bool isTime = fw::SoundManager::get()->getPlayTime(unknown2d0[i].unknown00, time);
    u32 playHandle = unknown2d0[i].unknown00;
    const char *name = mm::mtl::Singleton<Extend>::getPtr()->filename(unknown2d0[i].unknown04.c_str());
    fw::debug::drawFont(x - 370,
                        y,
                        "%d %s time=%.2f(%d) valid=%d pause=%d preparing=%d prepared=%d %s",
                        playHandle,
                        name,
                        time,
                        isTime,
                        fw::SoundManager::get()->isValid(unknown2d0[i].unknown00),
                        fw::SoundManager::get()->isPause(unknown2d0[i].unknown00),
                        fw::SoundManager::get()->isPreparing(unknown2d0[i].unknown00),
                        fw::SoundManager::get()->isPrepared(unknown2d0[i].unknown00),
                        unknown2d0[i].unknown50 != 0 ? "RETAKE" : "");
    y += 20;
  }
}

f32 VoicePlayer::getPlayFrame() const {
  if (unknown4b8 != 0) {
    f32 time;
    if (fw::SoundManager::get()->getPlayTime(unknown4b8, time)) {
      return time * TO_FR;
    }
  }
  return 0.0f;
}

f32 VoicePlayer::getTotalFrame() const {
  if (unknown4b8 != 0) {
    f32 time;
    if (fw::SoundManager::get()->getTotalTime(unknown4b8, time)) {
      return time * TO_FR;
    }
  }
  return 0.0f;
}

void VoicePlayer::setMultipleMode(bool isMultipleMode) {
  if (isMultipleMode) {
    unknown08 |= FLAG_UNKNOWN_4;
  } else {
    unknown08 &= ~FLAG_UNKNOWN_4;
  }
}

void VoicePlayer::preload(f32 frame, const char *path) {
  while (unknown0c.size() >= static_cast<int>(KEY_UNKNOWN_8)) {
    unknown0c.erase(unknown0c.begin());
  }
  unknown0c.push_back(Key(frame, path));
}

bool VoicePlayer::play(const char *path, f32 delay, IVoiceEvent *event) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return false;
  }
  bool isPause = (unknown08 & FLAG_UNKNOWN_3) != 0;
  if ((unknown08 & FLAG_UNKNOWN_4) == 0) {
    stop(10.0f);
  } else {
    clr();
  }
  if (__builtin_strcmp(unknown428.c_str(), path) == 0) {
    if (unknown46c != 0) {
      fw::SoundManager::get()->isPreparing(unknown46c);
      unknown4b8 = unknown46c;
      this->unknown474 = unknown428;
      if (delay <= 0.0f) {
        fw::SoundManager::get()->startVoice(unknown4b8);
        unknown08 &= ~FLAG_UNKNOWN_0;
      } else {
        unknown08 |= FLAG_UNKNOWN_0;
        this->unknown470 = delay;
      }
    }
    unknown428 = "";
    unknown46c = 0;
  } else {
    if (delay <= 0.0f) {
      unknown4b8 = VoiceUtil::playVoice(path, 1.0f, false);
      this->unknown474 = path;
      unknown08 &= ~FLAG_UNKNOWN_0;
    } else {
      unknown4b8 = 0;
      this->unknown474 = path;
      unknown08 |= FLAG_UNKNOWN_0;
      this->unknown470 = delay;
    }
    stopWaiting();
  }
  while (unknown2d0.size() >= unknown2d0.capacity()) {
    fw::SoundManager::get()->stopVoice(unknown2d0.front().unknown00, 10.0f * TO_SEC);
    unknown2d0.erase(unknown2d0.begin());
  }
  if (unknown4b8 != 0) {
    unknown2d0.push_back(Play(unknown4b8, path));
  }
  if (isPause) {
    fw::SoundManager::get()->pause(unknown4b8, true, 0.0f);
  }
  this->unknown4c0 = event;
  return unknown4b8 != 0;
}

void VoicePlayer::clr() {
  unknown474 = "";
  unknown4c0 = nullptr;
  unknown470 = 0.0f;
  unknown08 &= ~(FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2);
}

void VoicePlayer::pause(bool isPause) {
  if (isPause == ((unknown08 & FLAG_UNKNOWN_3) != 0)) {
    return;
  }
  for (size_t i = 0; i < unknown2d0.size(); i++) {
    f32 time = 0.0f;
    f32 totalTime = 0.0f;
    bool isPlayTime = fw::SoundManager::get()->getPlayTime(unknown2d0[i].unknown00, time);
    bool isTotalTime = fw::SoundManager::get()->getTotalTime(unknown4b8, totalTime);
    if (isPlayTime && isTotalTime && totalTime > 0.0f && time > 0.0f && totalTime - 0.5f <= time) {
      fw::SoundManager::get()->pause(unknown2d0[i].unknown00, false, 0.0f);
      fw::SoundManager::get()->stopVoice(unknown2d0[i].unknown00, 0.0f);
    } else {
      fw::SoundManager::get()->pause(unknown2d0[i].unknown00, isPause, 0.0f);
    }
  }
  if (isPause) {
    unknown08 |= FLAG_UNKNOWN_3;
  } else {
    unknown08 &= ~FLAG_UNKNOWN_3;
  }
}

void VoicePlayer::startWaiting(const char *path) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return;
  }
  if (__builtin_strcmp(unknown428.c_str(), path) == 0) {
    return;
  }
  stopWaiting();
  unknown428 = path;
  unknown46c = VoiceUtil::playVoice(path, 1.0f, true);
}

bool VoicePlayer::isPlay() const { return unknown4b8 != 0; }

const char *VoicePlayer::getPath() const { return unknown4b8 != 0 ? unknown474.c_str() : ""; }

} // namespace event
