#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class WaveSource {
public:
  enum unknown001 : u8 {
    unknown001_3 = 3,
  };

  struct unknown002 {
    u8 unknown00[0x80]; // Inferred role: adpcm header bytes; original member name unknown.
  };

  struct unknown003 {
    u8 _00[0x34 - 0x00];
    u32 unknown34; // Inferred role: data size; original member name unknown.
    u8 _38[0x60 - 0x38];
    u32 unknown60[1]; // Inferred role: data offsets; original member name unknown.
  };

  virtual ~WaveSource();
  const unknown002 *GetAdpcmHeader(int index) const;
  u8 *GetDataAddress(int index) const;
  u32 GetDataSize() const;
  u64 TimeToSample(f32 time) const;

  u8 _08[0x18 - 0x08];
  bool unknown18; // Inferred role: has data; original member name unknown.
  u8 _19[0x24 - 0x19];
  u32 unknown24; // Inferred role: data size; original member name unknown.
  u8 _28[0x2c - 0x28];
  f32 unknown2c; // Inferred role: sample rate; original member name unknown.
  u8 _30[0x34 - 0x30];
  unknown001 unknown34; // Inferred role: format; original member name unknown.
  u8 _35[0x40 - 0x35];
  u32 unknown40; // Inferred role: sample size; original member name unknown.
  u32 unknown44; // Inferred role: loop start; original member name unknown.
  u32 unknown48; // Inferred role: loop end; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  bool unknown50; // Inferred role: loop; original member name unknown.
  u8 _51[0x6c - 0x51];
  int unknown6c;               // Inferred role: reference counter; original member name unknown.
  const unknown003 *unknown70; // Inferred role: file header; original member name unknown.
  u8 _78[0x80 - 0x78];
  u8 *unknown80; // Inferred role: data; original member name unknown.
  u8 _88[0x90 - 0x88];
  const unknown002 *unknown90; // Inferred role: adpcm headers; original member name unknown.
};

static_assert(offsetof(WaveSource, unknown18) == 0x18, "");
static_assert(offsetof(WaveSource, unknown24) == 0x24, "");
static_assert(offsetof(WaveSource, unknown2c) == 0x2c, "");
static_assert(offsetof(WaveSource, unknown34) == 0x34, "");
static_assert(offsetof(WaveSource, unknown40) == 0x40, "");
static_assert(offsetof(WaveSource, unknown50) == 0x50, "");
static_assert(offsetof(WaveSource, unknown6c) == 0x6c, "");
static_assert(offsetof(WaveSource, unknown70) == 0x70, "");
static_assert(offsetof(WaveSource, unknown80) == 0x80, "");
static_assert(offsetof(WaveSource, unknown90) == 0x90, "");

} // namespace ssd
