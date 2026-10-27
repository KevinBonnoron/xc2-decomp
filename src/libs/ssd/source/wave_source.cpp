#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_text.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {
enum Result : long;

Result WaveSource::Quit() {
  unknown80 = nullptr;
  unknown88 = 0;
  unknown70 = nullptr;
  unknown78 = 0;
  if (unknown98 != nullptr) {
    static_cast<SystemCore *>(SoundCore::instance_)->FreeAudioDataBuffer(unknown98);
    unknown98 = nullptr;
  }
  unknowna0.FreeImpl();
  return static_cast<Result>(0);
}

const WaveSource::unknown002 *WaveSource::GetAdpcmHeader(int index) const {
  if (unknown90 != nullptr) {
    return &unknown90[index];
  }
  return nullptr;
}

u8 *WaveSource::GetDataAddress(int index) const {
  u32 offset = 0;
  if (unknown34 == unknown001_3) {
    offset = unknown70->unknown60[index];
  }
  return unknown80 + offset;
}

u32 WaveSource::GetDataSize() const {
  if (unknown34 == unknown001_3) {
    return unknown70->unknown34;
  }
  return unknown24;
}

u64 WaveSource::TimeToSample(f32 time) const {
  f32 sample = unknown2c * time;
  if (unknown34 == unknown001_3) {
    sample = (sample * 8.0f) / 14.0f;
  }
  return static_cast<u64>(sample);
}

} // namespace ssd
