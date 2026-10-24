#pragma once
#include <stddef.h>

#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {

class SoundEntry;
class SoundHandle;
class StreamController;
class WaveSource;

class VoiceHandle {
public:
  void DisplayDebugVerbose();
  void DeleteHWVoice();
  Result AllocHWVoice();
  Result SetPlayPosition(u64 position);
  Result Stop(f32 fadeTime);
  Result ForceStop();
  Result GetPlayPosition(u64 *position) const;
  Result GetPlaySample(unsigned long long *sample) const;
  Result GetPlayTime(f32 *time) const;
  Result GetFilePosition(u64 *position) const;
  Result SetPlaySample(unsigned long long sample);
  Result SetPlayTime(f32 time);
  Result GetLoopTime(bool *isLoop, f32 *begin, f32 *end);
  Result GetRemainLoopCount(int *count) const;
  Result SetRemainLoopCount(int count);
  Result GetVoiceQueueCount(int *count) const;
  Result IsEmptyVoiceQueue(bool *isEmpty);
  Result IsEmptyStreamBuffer(bool *isEmpty);
  void UpdateAudioFrame(f32 deltaTime);
  void UpdateAudioInternal(f32 deltaTime);
  void UpdateAudioStream(f32 deltaTime);
  void NullBufferProcess();
  void LooppingBufferProcess();
  void AddLooppingBuffer();

  u8 _00[0x30 - 0x00];
  bool unknown30; // Inferred role: active; original member name unknown.
  bool unknown31; // Inferred role: start; original member name unknown.
  bool unknown32; // Inferred role: play; original member name unknown.
  bool unknown33; // Inferred role: pause; original member name unknown.
  bool unknown34; // Inferred role: pausing; original member name unknown.
  bool unknown35; // Inferred role: resuming; original member name unknown.
  bool unknown36; // Inferred role: stopping; original member name unknown.
  bool unknown37; // Inferred role: stopped; original member name unknown.
  bool unknown38; // Inferred role: cutoff; original member name unknown.
  bool unknown39; // Inferred role: pregap; original member name unknown.
  bool unknown3a; // Inferred role: finished; original member name unknown.
  bool unknown3b; // Inferred role: alloc hw voice; original member name unknown.
  u8 _3c[0x3d - 0x3c];
  bool unknown3d; // Inferred role: auto stop; original member name unknown.
  bool unknown3e; // Inferred role: sdk playing; original member name unknown.
  bool unknown3f; // Inferred role: empty stream buffer; original member name unknown.
  bool unknown40; // Inferred role: empty voice queue; original member name unknown.
  u8 _41[0x44 - 0x41];
  int unknown44;               // Inferred role: state; original member name unknown.
  int unknown48;               // Inferred role: num channel; original member name unknown.
  int unknown4c;               // Inferred role: num source; original member name unknown.
  int unknown50;               // Inferred role: number; original member name unknown.
  u32 unknown54;               // Inferred role: sound control id; original member name unknown.
  SoundHandle *unknown58;      // Inferred role: sound handle; original member name unknown.
  const SoundEntry *unknown60; // Inferred role: sound entry; original member name unknown.
  WaveSource *unknown68;       // Inferred role: wave source; original member name unknown.
  StreamController *unknown70; // Inferred role: stream; original member name unknown.
  u8 _78[0x88 - 0x78];
  int unknown88; // Inferred role: voice queue count; original member name unknown.
  u8 _8c[0x6f0 - 0x8c];
  f32 unknown6f0; // Inferred role: distance volume; original member name unknown.
};

static_assert(offsetof(VoiceHandle, unknown30) == 0x30, "");
static_assert(offsetof(VoiceHandle, unknown44) == 0x44, "");
static_assert(offsetof(VoiceHandle, unknown88) == 0x88, "");
static_assert(offsetof(VoiceHandle, unknown70) == 0x70, "");
static_assert(offsetof(VoiceHandle, unknown6f0) == 0x6f0, "");

} // namespace ssd
