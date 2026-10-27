#include "ssd/ssd_audio_file.h"
#include "ssd/ssd_io_stream.h"
#include "types.h"

namespace ssd {

struct unknown003 {
  AudioChunk unknown00; // Inferred role: chunk header converted to host order; original member name unknown.
  u32 unknown08;        // Inferred role: sound data offset; original member name unknown.
  u32 unknown0c;        // Inferred role: sound data block size; original member name unknown.
};

static_assert(sizeof(unknown003) == 0x10, "");

// Inferred role: 32 bit byte swap; original name unknown.
static u32 unknown004(u32 value) {
  value = (value & 0xff00ff00) >> 8 | (value & 0x00ff00ff) << 8;
  return value >> 16 | value << 16;
}

Result AudioFileAiff::Open(IoStreamBase *stream) {
  unknown08 = stream;
  return static_cast<Result>(0);
}

Result AudioFileAiff::Close() {
  unknown08 = nullptr;
  return static_cast<Result>(0);
}

void AudioFileAiff::SetPositionBySample(u64 sample) {}

void AudioFileAiff::ReadAiffSound(AudioChunk *chunk) {
  unknown003 sound;
  unknown08->Read(8, &sound.unknown08, nullptr);
  sound.unknown00.unknown00 = unknown004(chunk->unknown00);
  sound.unknown00.unknown04 = unknown004(chunk->unknown04);
  u64 position;
  unknown08->GetPosition(&position);
  u32 offset = position + sound.unknown08;
  u32 size = sound.unknown00.unknown04 - 8;
  unknown20 = offset;
  unknown24 = size;
  unknown08->Seek(IoStreamBase::SEEK_MODE_CURRENT, size, nullptr);
}

void AudioFileAiff::CheckAiffLoopPosition() {
  unknown50 = false;
  unknown44 = 0;
  unknown48 = unknown30;
  unknown4c = 0;
  unknown4e = 0;
  if (unknown70.unknown002() != unknown70.unknown003() && (unknown98.unknown02 != 0 || unknown98.unknown04 != 0)) {
    AudioMarker *begin = unknown70.GetMarkerDataByID(unknown98.unknown02);
    if (begin != nullptr) {
      AudioMarker *end = unknown70.GetMarkerDataByID(unknown98.unknown04);
      if (end != nullptr) {
        u32 start = begin->unknown1c;
        u32 stop = end->unknown1c;
        unknown44 = start;
        unknown48 = stop;
        unknown4c = unknown98.unknown02;
        unknown4e = unknown98.unknown04;
        unknown50 = true;
      }
    }
  }
}

} // namespace ssd
