#include "gf/game/gf_game_voice.h"

namespace gf {

bool GfGameVoice::isInitialized() {
  GfGameVoice *voice = get();
  if (voice != nullptr) {
    return voice->unknown08;
  }
  return false;
}

void GfGameVoice::applyHanaVoiceCondirtion(GfVoiceName &) {}

} // namespace gf
