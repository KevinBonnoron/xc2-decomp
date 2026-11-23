#pragma once
#include <stddef.h>

#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {

class WaveSource : public Object {
public:
  enum unknown001 : u8 {
    unknown001_3 = 3,
    unknown001_4 = 4,
  };

  struct unknown002 {
    u8 unknown00[0x80]; // Inferred role: adpcm header bytes; original member name unknown.
  };

  struct unknown003 {
    u8 _00[0x34 - 0x00];
    u32 unknown34; // Inferred role: data size; original member name unknown.
    u8 _38[0x60 - 0x38];
    u32 unknown60[8]; // Inferred role: data offsets per channel; original member name unknown.
  };

  WaveSource();
  virtual ~WaveSource();
  Result Init(void *data, size_t size);
  Result Quit();
  const unknown002 *GetAdpcmHeader(int index) const;
  u8 *GetDataAddress(int index) const;
  u32 GetDataSize() const;
  Result InitWithFile(const TextRef &name);
  void SetName(const TextRef &text);
  u64 TimeToSample(f32 time) const;
  u64 SampleToPosition(u32 sample) const;

  bool unknown18;       // Inferred role: has data; original member name unknown.
  bool unknown19;       // Inferred role: initialized from a file; original member name unknown.
  u8 unknown1a;         // Inferred role: format read from the file; original member name unknown.
  u32 unknown1c;        // Inferred role: cleared by the constructor; original member name unknown.
  u32 unknown20;        // Inferred role: data offset; original member name unknown.
  u32 unknown24;        // Inferred role: data size; original member name unknown.
  u32 unknown28;        // Inferred role: cleared by the constructor; original member name unknown.
  f32 unknown2c;        // Inferred role: sample rate; original member name unknown.
  u32 unknown30;        // Inferred role: sample count; original member name unknown.
  unknown001 unknown34; // Inferred role: format; original member name unknown.
  u8 unknown35;         // Inferred role: channel count; original member name unknown.
  u8 _36[0x38 - 0x36];
  u32 unknown38;  // Inferred role: bits per sample; original member name unknown.
  u32 unknown3c;  // Inferred role: cleared by the constructor; original member name unknown.
  u32 unknown40;  // Inferred role: sample size; original member name unknown.
  u32 unknown44;  // Inferred role: loop start; original member name unknown.
  u32 unknown48;  // Inferred role: loop end; original member name unknown.
  u16 unknown4c;  // Inferred role: cleared by the constructor; original member name unknown.
  u16 unknown4e;  // Inferred role: cleared by the constructor; original member name unknown.
  bool unknown50; // Inferred role: loop; original member name unknown.
  u8 _51[0x5c - 0x51];
  int unknown5c; // Inferred role: frame size; original member name unknown.
  u8 _60[0x68 - 0x60];
  int unknown68;               // Inferred role: frame count; original member name unknown.
  int unknown6c;               // Inferred role: reference counter; original member name unknown.
  unknown003 *unknown70;       // Inferred role: file header; original member name unknown.
  u64 unknown78;               // Inferred role: cleared by Quit; original member name unknown.
  u8 *unknown80;               // Inferred role: data; original member name unknown.
  u64 unknown88;               // Inferred role: cleared by Quit; original member name unknown.
  const unknown002 *unknown90; // Inferred role: adpcm headers; original member name unknown.
  void *unknown98;             // Inferred role: audio data buffer; original member name unknown.
  String m_string;             // Inferred role: name; original member name unknown.
};

static_assert(sizeof(WaveSource::unknown003) == 0x80, "");

static_assert(offsetof(WaveSource, unknown18) == 0x18, "");
static_assert(offsetof(WaveSource, unknown1a) == 0x1a, "");
static_assert(offsetof(WaveSource, unknown1c) == 0x1c, "");
static_assert(offsetof(WaveSource, unknown24) == 0x24, "");
static_assert(offsetof(WaveSource, unknown2c) == 0x2c, "");
static_assert(offsetof(WaveSource, unknown30) == 0x30, "");
static_assert(offsetof(WaveSource, unknown34) == 0x34, "");
static_assert(offsetof(WaveSource, unknown35) == 0x35, "");
static_assert(offsetof(WaveSource, unknown38) == 0x38, "");
static_assert(offsetof(WaveSource, unknown40) == 0x40, "");
static_assert(offsetof(WaveSource, unknown4c) == 0x4c, "");
static_assert(offsetof(WaveSource, unknown50) == 0x50, "");
static_assert(offsetof(WaveSource, unknown5c) == 0x5c, "");
static_assert(offsetof(WaveSource, unknown68) == 0x68, "");
static_assert(offsetof(WaveSource, unknown6c) == 0x6c, "");
static_assert(offsetof(WaveSource, unknown70) == 0x70, "");
static_assert(offsetof(WaveSource, unknown78) == 0x78, "");
static_assert(offsetof(WaveSource, unknown80) == 0x80, "");
static_assert(offsetof(WaveSource, unknown88) == 0x88, "");
static_assert(offsetof(WaveSource, unknown90) == 0x90, "");
static_assert(offsetof(WaveSource, unknown98) == 0x98, "");
static_assert(offsetof(WaveSource, m_string) == 0xa0, "");
static_assert(sizeof(WaveSource) == 0xd0, "");

} // namespace ssd
