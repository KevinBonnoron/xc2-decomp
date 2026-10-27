#pragma once
#include <stddef.h>

#include "ssd/ssd_behavior.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_stream_controller.h"
#include "types.h"

namespace ssd {

class WaveSource;

class VoiceHandle : public Object, public List<VoiceHandle>::Node {
public:
  union unknown001 {
    s32 unknown00; // Inferred role: sample position; original member name unknown.
    f32 unknown01; // Inferred role: time position; original member name unknown.
  };

  ~VoiceHandle() override;

  // Inferred role: the wave source of the stream when streaming, otherwise of the voice; original name unknown.
  WaveSource *unknown002() const {
    if (unknown70 == nullptr) {
      return unknown68;
    }
    return unknown70;
  }

  static void AllocAdpcmSplitBuffer();
  static void FreeAdpcmSplitBuffer();
  void DisplayDebugVerbose();
  void DeleteHWVoice();
  Result AllocHWVoice();
  Result SetPlayPosition(u64 position);
  Result Stop(f32 fadeTime);
  Result Pause(bool isPause, f32 fadeTime);
  Result SetPlayPositionImpl();
  void Quit();
  void DeleteStream();
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

  static void *adpcmSplitBuffer_;

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
  u8 _8c[0x658 - 0x8c];
  void *unknown658; // Inferred role: audio data buffer; original member name unknown.
  u8 _660[0x668 - 0x660];
  bool unknown668; // Inferred role: play position request; original member name unknown.
  u8 unknown669;   // Inferred role: play position request type; original member name unknown.
  u8 _66a[0x680 - 0x66a];
  u64 unknown680;        // Inferred role: play position base; original member name unknown.
  u64 unknown688;        // Inferred role: play position; original member name unknown.
  u64 unknown690;        // Inferred role: play position offset; original member name unknown.
  u64 unknown698;        // Inferred role: play position limit; original member name unknown.
  unknown001 unknown6a0; // Inferred role: play position request value; original member name unknown.
  u8 _6a4[0x6d0 - 0x6a4];
  SoundHandle::Fade unknown6d0; // Inferred role: stop fade; original member name unknown.
  u8 _6e8[0x6f0 - 0x6e8];
  f32 unknown6f0; // Inferred role: distance volume; original member name unknown.
  u8 _6f4[0x710 - 0x6f4];
};

static_assert(offsetof(VoiceHandle, unknown30) == 0x30, "");
static_assert(offsetof(VoiceHandle, unknown44) == 0x44, "");
static_assert(offsetof(VoiceHandle, unknown88) == 0x88, "");
static_assert(offsetof(VoiceHandle, unknown658) == 0x658, "");
static_assert(offsetof(VoiceHandle, unknown668) == 0x668, "");
static_assert(offsetof(VoiceHandle, unknown70) == 0x70, "");
static_assert(offsetof(VoiceHandle, unknown6f0) == 0x6f0, "");
static_assert(offsetof(VoiceHandle, unknown669) == 0x669, "");
static_assert(offsetof(VoiceHandle, unknown680) == 0x680, "");
static_assert(offsetof(VoiceHandle, unknown6a0) == 0x6a0, "");
static_assert(offsetof(VoiceHandle, unknown6d0) == 0x6d0, "");
static_assert(sizeof(VoiceHandle) == 0x710, "");

} // namespace ssd
