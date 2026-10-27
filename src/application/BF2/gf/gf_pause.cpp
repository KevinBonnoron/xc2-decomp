#include "gf/gf_pause.h"

namespace gf {

bool GfPause::isInitialized() {
  GfPause *pause = get();
  if (pause != nullptr) {
    return pause->unknowne64;
  }
  return false;
}

bool GfPause::isPause(u32 pauseBits) { return (get()->unknowne58 & pauseBits) == pauseBits; }

u64 GfPause::createPauseHandleByIndex(u32 index) {
  u32 serial = unknowne60;
  unknowne60 = serial + 1;
  if (serial >= 0x3ffffff) {
    serial++;
    unknowne60 = serial + 1;
  }
  return (index & 0x3f) | (serial << 6);
}

} // namespace gf
