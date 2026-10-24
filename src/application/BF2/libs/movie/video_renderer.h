#pragma once
#include <stddef.h>

#include <vector>

#include "nn/os.h"
#include "types.h"

class VideoRenderer {
public:
  struct VideoData {
    int unknown00; // Inferred role: index; original member name unknown.
    s64 unknown08; // Inferred role: presentation time us; original member name unknown.
    u32 unknown10; // Inferred role: flags; original member name unknown.
  };

  void OnOutputAvailable(int index, s64 presentationTimeUs, u32 flags);

  u8 _000[0x210 - 0x000];
  std::vector<VideoData> unknown210; // Inferred role: video data list; original member name unknown.
  u8 _228[0x230 - 0x228];
  nn::os::MutexType unknown230; // Inferred role: video data mutex; original member name unknown.
};

static_assert(offsetof(VideoRenderer, unknown210) == 0x210, "");
static_assert(offsetof(VideoRenderer, unknown230) == 0x230, "");
