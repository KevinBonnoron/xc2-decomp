#include "event/voice_one_shoter.h"

#include "framework/sound/sound_manager.h"

namespace event {

const f32 VoiceOneShoter::TO_SEC = 1.0f / 30.0f;

VoiceOneShoter::VoiceOneShoter() : flags(0) {}

void VoiceOneShoter::clear() { stop(10.0f); }

void VoiceOneShoter::stop(f32 frame) {
  for (u32 i = 0; i < handles.size(); i++) {
    fw::SoundManager::get()->pause(handles[i], false, 0.0f);
    fw::SoundManager::get()->stopVoice(handles[i], frame * TO_SEC);
  }
  handles.clear();
  flags = 0;
}

void VoiceOneShoter::pause(bool isPause) {
  if (isPause == ((flags & FLAG_PAUSE) != 0)) {
    return;
  }
  for (u32 i = 0; i < handles.size(); i++) {
    fw::SoundManager::get()->pause(handles[i], isPause, 0.0f);
  }
  if (isPause) {
    flags |= FLAG_PAUSE;
  } else {
    flags &= ~FLAG_PAUSE;
  }
}

} // namespace event
