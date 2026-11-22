#pragma once
#include <stddef.h>

#include "nn/audio.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_stream_controller.h"
#include "types.h"

namespace ssd {

class SystemCore;
class WaveSource;

class VoiceHandle : public Object, public List<VoiceHandle>::Node {
public:
  union unknown001 {
    s32 unknown00; // Inferred role: sample position; original member name unknown.
    f32 unknown01; // Inferred role: time position; original member name unknown.
  };

  // Inferred role: hardware voice of one channel; original type name unknown.
  struct unknown003 {
    nn::audio::VoiceType unknown00; // Inferred role: voice; original member name unknown.
    u8 _08[0x98 - 0x08];
    void *unknown98[3]; // Inferred role: channel buffers; original member name unknown.
    int unknownb0;      // Inferred role: current buffer; original member name unknown.
    int unknownb4;      // Inferred role: hardware voice count; original member name unknown.
  };

  VoiceHandle();
  ~VoiceHandle() override;

  // Inferred role: the wave source of the stream when streaming, otherwise of the voice; original name unknown.
  WaveSource *unknown002() const {
    if (m_streamController == nullptr) {
      return m_waveSource;
    }
    return &m_streamController->m_waveSource;
  }

  static void AllocAdpcmSplitBuffer();
  static void FreeAdpcmSplitBuffer();
  void DisplayDebugVerbose();
  void DeleteHWVoice();
  void FreeVoice();
  Result AllocHWVoice();
  Result Start(f32 fadeTime, bool pregap);
  Result Prepare(const SoundEntry *entry, SoundHandle *handle, u32 *id);
  Result SetPlayPosition(u64 position);
  Result Stop(f32 fadeTime);
  Result Pause(bool isPause, f32 fadeTime);
  Result SetPlayPositionImpl();
  void Init(int number);
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
  void UpdateGameFrame(f32 deltaTime);
  void UpdateAudioFrame(f32 deltaTime);
  void UpdateAudioInternal(f32 deltaTime);
  void UpdateAudioVoice(f32 deltaTime);
  void UpdateAudioStream(f32 deltaTime);
  void NullBufferProcess();
  void LooppingBufferProcess();
  void AddLooppingBuffer();
  Result AcquireBuffer();
  Result EnableBuffer();
  void UpdateOutputParam(f32 deltaTime);
  Result ReleaseBuffer();
  Result DisableBuffer();
  void StreamingBufferProcess();
  u64 AddStreamingBuffer();
  void SetHWVoiceState(nn::audio::VoiceType::PlayState state);
  void OneShotBufferProcess();

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
  bool unknown3c; // Inferred role: cleared by the constructor; original member name unknown.
  bool unknown3d; // Inferred role: auto stop; original member name unknown.
  bool unknown3e; // Inferred role: sdk playing; original member name unknown.
  bool unknown3f; // Inferred role: empty stream buffer; original member name unknown.
  bool unknown40; // Inferred role: empty voice queue; original member name unknown.
  u8 _41[0x44 - 0x41];
  int unknown44;                        // Inferred role: state; original member name unknown.
  int unknown48;                        // Inferred role: num channel; original member name unknown.
  int unknown4c;                        // Inferred role: num source; original member name unknown.
  int unknown50;                        // Inferred role: number; original member name unknown.
  u32 unknown54;                        // Inferred role: sound control id; original member name unknown.
  SoundHandle *m_soundHandle;           // Inferred role: sound handle; original member name unknown.
  const SoundEntry *m_soundEntry;       // Inferred role: sound entry; original member name unknown.
  WaveSource *m_waveSource;             // Inferred role: wave source; original member name unknown.
  StreamController *m_streamController; // Inferred role: stream; original member name unknown.
  void (VoiceHandle::*unknown78)();     // Inferred role: buffer process; original member name unknown.
  int unknown88;                        // Inferred role: voice queue count; original member name unknown.
  int unknown8c;                        // Inferred role: free streaming buffer count; original member name unknown.
  unknown003 unknown90[8];              // Inferred role: channel voices; original member name unknown.
  SystemCore *m_systemCore;             // Inferred role: sound core; original member name unknown.
  void *unknown658;                     // Inferred role: audio data buffer; original member name unknown.
  int unknown660;                       // Inferred role: buffer index; original member name unknown.
  u8 _664[0x668 - 0x664];
  bool unknown668; // Inferred role: play position request; original member name unknown.
  u8 unknown669;   // Inferred role: play position request type; original member name unknown.
  u8 _66a[0x670 - 0x66a];
  size_t unknown670;     // Inferred role: streaming buffer size; original member name unknown.
  size_t unknown678;     // Inferred role: set to 12000 by Init; original member name unknown.
  u64 unknown680;        // Inferred role: play position base; original member name unknown.
  u64 unknown688;        // Inferred role: play position; original member name unknown.
  u64 unknown690;        // Inferred role: play position offset; original member name unknown.
  u64 unknown698;        // Inferred role: play position limit; original member name unknown.
  unknown001 unknown6a0; // Inferred role: play position request value; original member name unknown.
  u8 _6a4[0x6a8 - 0x6a4];
  u64 unknown6a8;  // Inferred role: cleared by the constructor; original member name unknown.
  bool unknown6b0; // Inferred role: cleared by the constructor; original member name unknown.
  bool unknown6b1; // Inferred role: cleared by the constructor; original member name unknown.
  u8 _6b2[0x6b4 - 0x6b2];
  f32 unknown6b4;                     // Inferred role: output volume; original member name unknown.
  f32 unknown6b8;                     // Inferred role: output pitch; original member name unknown.
  f32 unknown6bc;                     // Inferred role: output pan; original member name unknown.
  f32 unknown6c0;                     // Inferred role: set to 1.0 by the constructor; original member name unknown.
  f32 unknown6c4;                     // Inferred role: doppler pitch; original member name unknown.
  f32 unknown6c8;                     // Inferred role: volume at the minimum distance; original member name unknown.
  f32 unknown6cc;                     // Inferred role: volume at the maximum distance; original member name unknown.
  SoundHandle::unknown003 unknown6d0; // Inferred role: stop fade; original member name unknown.
  u8 _6e8[0x6f0 - 0x6e8];
  f32 unknown6f0; // Inferred role: distance volume; original member name unknown.
  f32 unknown6f4; // Inferred role: pan angle in degrees; original member name unknown.
  u8 _6f8[0x704 - 0x6f8];
  Vec3 m_vec3; // Inferred role: position in listener space; original member name unknown.
};

static_assert(offsetof(VoiceHandle, unknown30) == 0x30, "");
static_assert(offsetof(VoiceHandle, unknown44) == 0x44, "");
static_assert(offsetof(VoiceHandle, unknown88) == 0x88, "");
static_assert(offsetof(VoiceHandle, unknown658) == 0x658, "");
static_assert(offsetof(VoiceHandle, unknown668) == 0x668, "");
static_assert(offsetof(VoiceHandle, m_streamController) == 0x70, "");
static_assert(offsetof(VoiceHandle, unknown6f0) == 0x6f0, "");
static_assert(offsetof(VoiceHandle, unknown669) == 0x669, "");
static_assert(offsetof(VoiceHandle, unknown680) == 0x680, "");
static_assert(offsetof(VoiceHandle, unknown6a0) == 0x6a0, "");
static_assert(offsetof(VoiceHandle, unknown6d0) == 0x6d0, "");
static_assert(offsetof(VoiceHandle, unknown90) == 0x90, "");
static_assert(offsetof(VoiceHandle, m_systemCore) == 0x650, "");
static_assert(offsetof(VoiceHandle, unknown3c) == 0x3c, "");
static_assert(offsetof(VoiceHandle, unknown78) == 0x78, "");
static_assert(offsetof(VoiceHandle, unknown6a8) == 0x6a8, "");
static_assert(offsetof(VoiceHandle, unknown6b0) == 0x6b0, "");
static_assert(offsetof(VoiceHandle, unknown6b4) == 0x6b4, "");
static_assert(offsetof(VoiceHandle, unknown6c0) == 0x6c0, "");
static_assert(offsetof(VoiceHandle, unknown6c4) == 0x6c4, "");
static_assert(offsetof(VoiceHandle, unknown6cc) == 0x6cc, "");
static_assert(offsetof(VoiceHandle, unknown6f4) == 0x6f4, "");
static_assert(offsetof(VoiceHandle, m_vec3) == 0x704, "");
static_assert(offsetof(VoiceHandle::unknown003, unknown98) == 0x98, "");
static_assert(offsetof(VoiceHandle::unknown003, unknownb4) == 0xb4, "");
static_assert(sizeof(VoiceHandle::unknown003) == 0xb8, "");
static_assert(sizeof(VoiceHandle) == 0x710, "");

} // namespace ssd
