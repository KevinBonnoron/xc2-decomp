#include "gf/game/gf_game_voice.h"

namespace gf {

bool GfGameVoice::isInitialized() {
  GfGameVoice *voice = get();
  if (voice != nullptr) {
    return voice->unknown08;
  }
  return false;
}

GAME_VOICE_HANDLE *GfGameVoice::createHandle() {
  u64 handle = unknown110 + 1;
  if (handle == 0) {
    handle++;
  }
  unknown110 = handle;
  return reinterpret_cast<GAME_VOICE_HANDLE *>(handle);
}

void GfGameVoice::applyHanaVoiceCondirtion(GfVoiceName &) {}

} // namespace gf
