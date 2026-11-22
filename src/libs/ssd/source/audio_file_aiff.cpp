#include "ssd/ssd_audio_file.h"
#include "ssd/ssd_io_stream.h"
#include "types.h"

namespace ssd {

struct unknown003 {
  AudioChunk m_audioChunk; // Inferred role: chunk header converted to host order; original member name unknown.
  u32 unknown08;           // Inferred role: sound data offset; original member name unknown.
  u32 unknown0c;           // Inferred role: sound data block size; original member name unknown.
};

static_assert(sizeof(unknown003) == 0x10, "");

Result AudioFileAiff::Open(IoStreamBase *stream) {
  m_ioStreamBase = stream;
  return static_cast<Result>(0);
}

Result AudioFileAiff::Close() {
  m_ioStreamBase = nullptr;
  return static_cast<Result>(0);
}

void AudioFileAiff::SetPositionBySample(u64 sample) {}

void AudioFileAiff::ReadAiffSound(AudioChunk *chunk) {
  unknown003 sound;
  m_ioStreamBase->Read(8, &sound.unknown08, nullptr);
  sound.m_audioChunk.unknown00 = unknown004(chunk->unknown00);
  sound.m_audioChunk.unknown04 = unknown004(chunk->unknown04);
  u64 position;
  m_ioStreamBase->GetPosition(&position);
  u32 offset = position + sound.unknown08;
  u32 size = sound.m_audioChunk.unknown04 - 8;
  unknown20 = offset;
  unknown24 = size;
  m_ioStreamBase->Seek(IoStreamBase::SEEK_MODE_CURRENT, size, nullptr);
}

void AudioFileAiff::CheckAiffLoopPosition() {
  unknown50 = false;
  unknown44 = 0;
  unknown48 = unknown30;
  unknown4c = 0;
  unknown4e = 0;
  if (m_audioMarkerList.unknown002() != m_audioMarkerList.unknown003() && (unknown98.unknown02 != 0 || unknown98.unknown04 != 0)) {
    AudioMarker *begin = m_audioMarkerList.GetMarkerDataByID(unknown98.unknown02);
    if (begin != nullptr) {
      AudioMarker *end = m_audioMarkerList.GetMarkerDataByID(unknown98.unknown04);
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
