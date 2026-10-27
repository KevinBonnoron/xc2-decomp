#include "ssd/ssd_sound_core.h"
#include "types.h"

namespace ssd {
enum Result : long;

Result SystemCorePlatform::InitEffect(u8 bus, SoundEffecter *effecter) {
  if (bus < 2) {
    if (effecter->unknown18 == SoundEffecter::unknown001_0) {
      return InitDelayEffect(bus, static_cast<SoundDelayEffecter *>(effecter));
    }
    if (effecter->unknown18 == SoundEffecter::unknown001_1) {
      return InitI3dl2ReverbEffect(bus, static_cast<SoundI3dl2ReverbEffecter *>(effecter));
    }
  }
  return static_cast<Result>(-1);
}

int SystemCorePlatform::GetBusNumberFormEffecter(SoundEffecter *effecter) {
  if (unknown1f0[0].unknown10 == effecter) {
    return 0;
  }
  if (unknown1f0[1].unknown10 == effecter) {
    return 1;
  }
  return -1;
}

void SystemCorePlatform::UpdateEffectVolume(SoundEffecter *effecter) {
  int bus = GetBusNumberFormEffecter(effecter);
  if (bus >= 0) {
    unknown1f0[bus].unknown08 = effecter->unknown1c;
  }
}

void SystemCorePlatform::UpdateEffectParam(SoundEffecter *effecter) {}

} // namespace ssd
