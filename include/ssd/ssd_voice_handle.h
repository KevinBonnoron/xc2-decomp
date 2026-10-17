#pragma once
#include <stddef.h>

#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {

class StreamController;
class WaveSource;

class VoiceHandle {
public:
  void DisplayDebugVerbose();
  Result SetPlayPosition(u64 position);
  Result Stop(f32 fadeTime);
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
  void IsEmptyVoiceQueue(bool *isEmpty);
  void IsEmptyStreamBuffer(bool *isEmpty);

  u8 _00[0x44 - 0x00];
  int state;
  u8 _48[0x68 - 0x48];
  WaveSource *waveSource;
  StreamController *stream;
  u8 _78[0x6f0 - 0x78];
  f32 distanceVolume;
};

static_assert(offsetof(VoiceHandle, state) == 0x44, "");
static_assert(offsetof(VoiceHandle, stream) == 0x70, "");
static_assert(offsetof(VoiceHandle, distanceVolume) == 0x6f0, "");

} // namespace ssd
