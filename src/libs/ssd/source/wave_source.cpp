#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_text.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {
enum Result : long;

WaveSource::WaveSource()
    : Object(ObjectType::WAVE_SOURCE), unknown18(false), unknown19(false), unknown1a(0), unknown1c(0), unknown20(0), unknown24(0), unknown28(0), unknown2c(48000.0f), unknown30(0),
      unknown34(static_cast<unknown001>(0)), unknown35(0), unknown38(0), unknown3c(0), unknown40(0), unknown44(0), unknown48(0), unknown4c(0), unknown4e(0), unknown50(false), unknown6c(0),
      unknown70(nullptr), unknown78(0), unknown80(nullptr), unknown88(0), unknown90(nullptr), unknown98(nullptr) {}

WaveSource::~WaveSource() { Quit(); }

Result WaveSource::Quit() {
  unknown80 = nullptr;
  unknown88 = 0;
  unknown70 = nullptr;
  unknown78 = 0;
  if (unknown98 != nullptr) {
    static_cast<SystemCore *>(SoundCore::instance_)->FreeAudioDataBuffer(unknown98);
    unknown98 = nullptr;
  }
  m_string.FreeImpl();
  return static_cast<Result>(0);
}

u64 WaveSource::TimeToSample(f32 time) const {
  f32 sample = unknown2c * time;
  if (unknown34 == unknown001_3) {
    sample = (sample * 8.0f) / 14.0f;
  }
  return static_cast<u64>(sample);
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

Result WaveSource::InitWithFile(const TextRef &name) {
  unknown19 = true;
  static_cast<TextRef &>(m_string).Set(name);
  unknown70 = nullptr;
  unknown78 = 0;
  return static_cast<Result>(0);
}

u64 WaveSource::SampleToPosition(u32 sample) const {
  u64 position = sample;
  if (unknown34 == unknown001_3) {
    return position * 16 / 28;
  }
  return unknown40 * position;
}

void WaveSource::SetName(const TextRef &text) { static_cast<TextRef &>(m_string).Set(text); }

} // namespace ssd
