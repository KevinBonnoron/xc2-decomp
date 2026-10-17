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
  bool isActive_;
  bool isStart_;
  bool isPlay_;
  bool isPause_;
  bool isPausing_;
  bool isResuming_;
  bool isStopping_;
  bool isStopped_;
  bool isCutoff_;
  bool isPregap_;
  bool isFinished_;
  bool isAllocHWVoice_;
  u8 _3c[0x3d - 0x3c];
  bool isAutoStop_;
  bool isSDKPlaying_;
  bool isEmptyStreamBuffer;
  bool isEmptyVoiceQueue;
  u8 _41[0x44 - 0x41];
  int state_;
  int numChannel_;
  int numSource_;
  int number_;
  u32 soundControlId_;
  SoundHandle *soundHandle_;
  const SoundEntry *soundEntry_;
  WaveSource *waveSource_;
  StreamController *stream;
  u8 _78[0x88 - 0x78];
  int voiceQueueCount;
  u8 _8c[0x6f0 - 0x8c];
  f32 distanceVolume;
};

static_assert(offsetof(VoiceHandle, isActive_) == 0x30, "");
static_assert(offsetof(VoiceHandle, state_) == 0x44, "");
static_assert(offsetof(VoiceHandle, voiceQueueCount) == 0x88, "");
static_assert(offsetof(VoiceHandle, stream) == 0x70, "");
static_assert(offsetof(VoiceHandle, distanceVolume) == 0x6f0, "");

} // namespace ssd
