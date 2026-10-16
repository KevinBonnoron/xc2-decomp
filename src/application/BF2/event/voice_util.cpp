#include "event/voice_util.h"

#include "framework/sound/sound_manager.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace event {

static constexpr fw::SoundCategory SOUND_CATEGORY_EVENT_VOICE = static_cast<fw::SoundCategory>(11);

u32 VoiceUtil::playVoice(const char *path, f32 volume, bool isPrepare) {
  u32 handle = fw::SoundManager::get()->playVoice(path, volume, isPrepare, SOUND_CATEGORY_EVENT_VOICE);
  if (!isPrepare) {
    fw::SoundManager::get()->pause(handle, false, 0.0f);
  }
  return handle;
}

} // namespace event
