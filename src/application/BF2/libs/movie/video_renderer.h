#pragma once
#include <stddef.h>

#include <vector>

#include "nn/os.h"
#include "types.h"

class VideoRenderer {
public:
  struct VideoData {
    int index;
    s64 presentationTimeUs;
    u32 flags;
  };

  void OnOutputAvailable(int index, s64 presentationTimeUs, u32 flags);

  u8 _000[0x210 - 0x000];
  std::vector<VideoData> videoDataList;
  u8 _228[0x230 - 0x228];
  nn::os::MutexType videoDataMutex;
};

static_assert(offsetof(VideoRenderer, videoDataList) == 0x210, "");
static_assert(offsetof(VideoRenderer, videoDataMutex) == 0x230, "");
