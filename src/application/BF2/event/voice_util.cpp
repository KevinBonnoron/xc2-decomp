#include "event/voice_util.h"

#include "framework/sound/sound_manager.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace event {

static constexpr fw::SoundCategory SOUND_CATEGORY_UNKNOWN_11 = static_cast<fw::SoundCategory>(11); // Inferred role: sound category event voice; original name unknown.

u32 VoiceUtil::playVoice(const char *path, f32 volume, bool isPrepare) {
  u32 handle = fw::SoundManager::get()->playVoice(path, volume, isPrepare, SOUND_CATEGORY_UNKNOWN_11);
  if (!isPrepare) {
    fw::SoundManager::get()->pause(handle, false, 0.0f);
  }
  return handle;
}

} // namespace event
