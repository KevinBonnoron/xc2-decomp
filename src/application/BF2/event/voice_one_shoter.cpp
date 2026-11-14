#include "event/voice_one_shoter.h"

#include "event/skip_manager.h"
#include "framework/sound/sound_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

const f32 VoiceOneShoter::TO_SEC = 1.0f / 30.0f;

VoiceOneShoter::VoiceOneShoter() : unknown08(0) {}

void VoiceOneShoter::clear() { stop(10.0f); }

void VoiceOneShoter::stop(f32 frame) {
  for (u32 i = 0; i < unknown10.size(); i++) {
    fw::SoundManager::get()->pause(unknown10[i], false, 0.0f);
    fw::SoundManager::get()->stopVoice(unknown10[i], frame * TO_SEC);
  }
  unknown10.clear();
  unknown08 = 0;
}

void VoiceOneShoter::pause(bool isPause) {
  if (isPause == ((unknown08 & FLAG_UNKNOWN_0) != 0)) {
    return;
  }
  for (u32 i = 0; i < unknown10.size(); i++) {
    fw::SoundManager::get()->pause(unknown10[i], isPause, 0.0f);
  }
  if (isPause) {
    unknown08 |= FLAG_UNKNOWN_0;
  } else {
    unknown08 &= ~FLAG_UNKNOWN_0;
  }
}

void VoiceOneShoter::update() {
  if (unknown10.size() != 0) {
    while (unknown10.size() != 0) {
      if (fw::SoundManager::get()->isPlaying(unknown10[0])) {
        break;
      }
      unknown10.erase(unknown10.begin());
    }
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
      clear();
    }
  }
}

} // namespace event
