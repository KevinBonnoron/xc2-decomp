#pragma once
#include <stddef.h>

#include <vector>

#include "nn/os.h"
#include "types.h"

class MediaClock;

class AudioOutRenderer {
public:
  struct audioData {
    int index;
    s64 presentationTimeUs;
    u32 flags;
  };

  void GenerateFixedSizeAudioFrame();
  void OnOutputAvailable(int index, s64 presentationTimeUs, u32 flags);

  u8 _000[0x430 - 0x000];
  std::vector<audioData> audioDataList;
  u8 _448[0x490 - 0x448];
  nn::os::MutexType audioDataMutex;
  u8 _4b0[0x4b8 - 0x4b0];
  MediaClock *mediaClock;
  s64 startTimeUs;
};

static_assert(offsetof(AudioOutRenderer, audioDataList) == 0x430, "");
static_assert(offsetof(AudioOutRenderer, audioDataMutex) == 0x490, "");
static_assert(offsetof(AudioOutRenderer, mediaClock) == 0x4b8, "");
static_assert(offsetof(AudioOutRenderer, startTimeUs) == 0x4c0, "");
