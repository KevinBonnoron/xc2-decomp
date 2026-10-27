#pragma once
#include <stddef.h>

#include "ssd/ssd_behavior.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {
class IoStreamBase;

class AudioMarker : public List<AudioMarker>::Node {
public:
  u16 unknown18; // Inferred role: marker id; original member name unknown.
  u8 _1a[0x1c - 0x1a];
  u32 unknown1c;            // Inferred role: marker position; original member name unknown.
  TextFixed<256> unknown20; // Inferred role: marker name; original member name unknown.
};

static_assert(offsetof(AudioMarker, unknown20) == 0x20, "");
static_assert(sizeof(AudioMarker) == 0x248, "");

class AudioMarkerList : public List<AudioMarker> {
public:
  AudioMarker *GetMarkerDataByID(int id);
};

static_assert(sizeof(AudioMarkerList) == 0x28, "");

class AudioChunk {
public:
  u32 unknown00; // Inferred role: chunk tag; original member name unknown.
  u32 unknown04; // Inferred role: chunk size; original member name unknown.
};

static_assert(sizeof(AudioChunk) == 0x8, "");

class AudioFileBase {
public:
  AudioFileBase();

  virtual Result Open(IoStreamBase *stream);
  virtual Result Close();
  virtual Result PreLoad();
  virtual void SetPositionBySample(u64 sample);
  virtual Result PreSave();
  virtual Result SaveAudioData(const s16 *data, int count);
  virtual ~AudioFileBase();

  void DeleteReadBuffer();
  void NewReadBuffer(size_t size);
  int ReadBySamples(s16 *buffer, int count);
  int WriteBySamples(const s16 *buffer, int count);

  IoStreamBase *unknown08; // Inferred role: stream; original member name unknown.
  void *unknown10;         // Inferred role: read buffer; original member name unknown.
  bool unknown18;          // Inferred role: owns the read buffer; original member name unknown.
  bool unknown19;          // Inferred role: allocated by CreateFileBase; original member name unknown.
  bool unknown1a;          // Inferred role: owns the stream; original member name unknown.
  bool unknown1b;          // Inferred role: opened for saving; original member name unknown.
  u32 unknown1c;           // Inferred role: cleared by the constructor; original member name unknown.
  u32 unknown20;           // Inferred role: data offset; original member name unknown.
  u32 unknown24;           // Inferred role: data size; original member name unknown.
  u32 unknown28;           // Inferred role: cleared by the constructor; original member name unknown.
  f32 unknown2c;           // Inferred role: sample rate; original member name unknown.
  u32 unknown30;           // Inferred role: sample count; original member name unknown.
  u8 unknown34;            // Inferred role: format; original member name unknown.
  u8 unknown35;            // Inferred role: channel count; original member name unknown.
  u8 _36[0x38 - 0x36];
  u32 unknown38;  // Inferred role: bits per sample; original member name unknown.
  u32 unknown3c;  // Inferred role: cleared by the constructor; original member name unknown.
  u32 unknown40;  // Inferred role: sample size; original member name unknown.
  u32 unknown44;  // Inferred role: loop start; original member name unknown.
  u32 unknown48;  // Inferred role: loop end; original member name unknown.
  u16 unknown4c;  // Inferred role: cleared by the constructor; original member name unknown.
  u16 unknown4e;  // Inferred role: cleared by the constructor; original member name unknown.
  bool unknown50; // Inferred role: loop; original member name unknown.
  u8 _51[0x70 - 0x51];
  AudioMarkerList unknown70; // Inferred role: markers; original member name unknown.
};

static_assert(offsetof(AudioFileBase, unknown08) == 0x8, "");
static_assert(offsetof(AudioFileBase, unknown18) == 0x18, "");
static_assert(offsetof(AudioFileBase, unknown20) == 0x20, "");
static_assert(offsetof(AudioFileBase, unknown2c) == 0x2c, "");
static_assert(offsetof(AudioFileBase, unknown40) == 0x40, "");
static_assert(offsetof(AudioFileBase, unknown50) == 0x50, "");
static_assert(offsetof(AudioFileBase, unknown70) == 0x70, "");
static_assert(sizeof(AudioFileBase) == 0x98, "");

struct unknown001 {
  u16 unknown00; // Inferred role: sustain loop play mode; original member name unknown.
  u16 unknown02; // Inferred role: sustain loop begin marker id; original member name unknown.
  u16 unknown04; // Inferred role: sustain loop end marker id; original member name unknown.
  u16 unknown06; // Inferred role: release loop play mode; original member name unknown.
  u16 unknown08; // Inferred role: release loop begin marker id; original member name unknown.
  u16 unknown0a; // Inferred role: release loop end marker id; original member name unknown.
};

static_assert(sizeof(unknown001) == 0xc, "");

class AudioFileAiff : public AudioFileBase {
public:
  Result Open(IoStreamBase *stream) override;
  Result Close() override;
  Result PreLoad() override;
  void SetPositionBySample(u64 sample) override;
  void ReadAiffSound(AudioChunk *chunk);
  void CheckAiffLoopPosition();

  unknown001 unknown98; // Inferred role: instrument loop points; original member name unknown.
  u8 _a4[0xc0 - 0xa4];
};

static_assert(offsetof(AudioFileAiff, unknown98) == 0x98, "");
static_assert(sizeof(AudioFileAiff) == 0xc0, "");

class AudioFileWave : public AudioFileBase {
public:
  Result Open(IoStreamBase *stream) override;
  Result Close() override;
  Result PreLoad() override;
  void SetPositionBySample(u64 sample) override;
  Result PreSave() override;
  Result SaveAudioData(const s16 *data, int count) override;
  void ReadWaveSound(AudioChunk *chunk);
  void ReadWaveLoopPosition(AudioChunk *chunk);
};

static_assert(sizeof(AudioFileWave) == 0x98, "");

class AudioFileSadf : public AudioFileBase {
public:
  Result Open(IoStreamBase *stream) override;
  Result Close() override;
  Result PreLoad() override;
  void SetPositionBySample(u64 sample) override;
};

static_assert(sizeof(AudioFileSadf) == 0x98, "");

} // namespace ssd
