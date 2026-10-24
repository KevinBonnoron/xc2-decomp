#include "event/voice_one_shoter.h"

#include "framework/sound/sound_manager.h"

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
  if (isPause == ((unknown08 & FLAG_PAUSE) != 0)) {
    return;
  }
  for (u32 i = 0; i < unknown10.size(); i++) {
    fw::SoundManager::get()->pause(unknown10[i], isPause, 0.0f);
  }
  if (isPause) {
    unknown08 |= FLAG_PAUSE;
  } else {
    unknown08 &= ~FLAG_PAUSE;
  }
}

} // namespace event
