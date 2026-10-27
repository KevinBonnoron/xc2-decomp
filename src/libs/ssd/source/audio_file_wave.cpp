#include <stddef.h>

#include "ssd/ssd_audio_file.h"
#include "ssd/ssd_buffer.h"
#include "ssd/ssd_io_stream.h"
#include "types.h"

namespace ssd {

struct unknown003 {
  AudioChunk unknown00; // Inferred role: RIFF chunk header; original member name unknown.
  u16 unknown08;        // Inferred role: wave format tag; original member name unknown.
  u16 unknown0a;        // Inferred role: channel count; original member name unknown.
  u32 unknown0c;        // Inferred role: sample rate; original member name unknown.
  u8 _10[0x16 - 0x10];
  u16 unknown16; // Inferred role: bits per sample; original member name unknown.
  u8 _18[0x24 - 0x18];
  u32 unknown24; // Inferred role: loop count; original member name unknown.
  u8 _28[0x34 - 0x28];
  u32 unknown34; // Inferred role: loop start; original member name unknown.
  u32 unknown38; // Inferred role: loop end; original member name unknown.
  u8 _3c[0x220 - 0x3c];
};

static_assert(offsetof(unknown003, unknown08) == 0x8, "");
static_assert(offsetof(unknown003, unknown16) == 0x16, "");
static_assert(offsetof(unknown003, unknown24) == 0x24, "");
static_assert(offsetof(unknown003, unknown38) == 0x38, "");
static_assert(sizeof(unknown003) == 0x220, "");

struct unknown005 {
  AudioChunk unknown00; // Inferred role: RIFF chunk header; original member name unknown.
  u16 unknown08;        // Inferred role: wave format tag; original member name unknown.
  u16 unknown0a;        // Inferred role: channel count; original member name unknown.
  u32 unknown0c;        // Inferred role: sample rate; original member name unknown.
  u32 unknown10;        // Inferred role: bytes per second; original member name unknown.
  u16 unknown14;        // Inferred role: block align; original member name unknown.
  u16 unknown16;        // Inferred role: bits per sample; original member name unknown.
};

static_assert(sizeof(unknown005) == 0x18, "");

struct unknown004 {
  u32 unknown00; // Inferred role: RIFF tag; original member name unknown.
  u32 unknown04; // Inferred role: file size minus 8; original member name unknown.
  u32 unknown08; // Inferred role: WAVE tag; original member name unknown.
};

Result AudioFileWave::Open(IoStreamBase *stream) {
  unknown08 = stream;
  return static_cast<Result>(0);
}

Result AudioFileWave::Close() {
  if (unknown1b) {
    u64 size;
    unknown08->GetSize(&size);
    unknown08->Seek(IoStreamBase::SEEK_MODE_BEGIN, 0, nullptr);
    unknown004 header;
    header.unknown00 = 0x46464952;
    header.unknown04 = static_cast<u32>(size) - 8;
    header.unknown08 = 0x45564157;
    unknown08->Write(0xc, &header, nullptr);
  }
  AudioFileBase::Close();
  return static_cast<Result>(0);
}

void AudioFileWave::SetPositionBySample(u64 sample) {
  u64 position = unknown20 + sample;
  unknown08->Seek(IoStreamBase::SEEK_MODE_BEGIN, position, nullptr);
}

void AudioFileWave::ReadWaveSound(AudioChunk *chunk) {
  u64 position;
  unknown08->GetPosition(&position);
  u64 size = chunk->unknown04;
  unknown20 = position;
  unknown24 = size;
  u64 skip = size + (size & 1);
  unknown08->Seek(IoStreamBase::SEEK_MODE_CURRENT, skip, nullptr);
}

void AudioFileWave::ReadWaveLoopPosition(AudioChunk *chunk) {
  unknown003 *buffer = static_cast<unknown003 *>(unknown10);
  if (buffer != nullptr) {
    unknown08->Read(chunk->unknown04, &buffer->unknown08, nullptr);
    if (buffer->unknown24 != 0) {
      u32 start = buffer->unknown34;
      u32 end = buffer->unknown38;
      unknown4c = 1;
      unknown4e = 2;
      unknown44 = start;
      unknown48 = end;
      unknown50 = start != end;
    }
  }
}

Result AudioFileWave::PreSave() {
  unknown004 header;
  header.unknown00 = 0x46464952;
  header.unknown04 = 0;
  header.unknown08 = 0x45564157;
  unknown08->Write(0xc, &header, nullptr);
  unknown005 format;
  format.unknown00.unknown00 = 0x20746d66;
  format.unknown00.unknown04 = 0x10;
  format.unknown08 = 1;
  format.unknown0a = unknown35;
  format.unknown0c = static_cast<u32>(unknown2c);
  format.unknown10 = unknown40 * format.unknown0c;
  format.unknown14 = unknown40;
  format.unknown16 = unknown38;
  unknown08->Write(0x18, &format, nullptr);
  if (unknown50) {
    unknown003 loop;
    ClearMemory8(&loop, 0x44);
    loop.unknown00.unknown00 = 0x6c706d73;
    loop.unknown00.unknown04 = 0x3c;
    loop.unknown24 = 1;
    loop.unknown34 = unknown44;
    loop.unknown38 = unknown48;
    unknown08->Write(0x44, &loop, nullptr);
  }
  return static_cast<Result>(0);
}

Result AudioFileWave::SaveAudioData(const s16 *data, int count) {
  u32 size = unknown40 * count;
  AudioChunk chunk;
  chunk.unknown00 = 0x61746164;
  chunk.unknown04 = size;
  unknown08->Write(8, &chunk, nullptr);
  u64 position;
  unknown08->GetPosition(&position);
  unknown20 = position;
  WriteBySamples(data, count);
  return static_cast<Result>(0);
}

} // namespace ssd
