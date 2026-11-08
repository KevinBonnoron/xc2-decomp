#pragma once
#include <stddef.h>

#include <vector>

#include "libs/movie/movie_status.h"
#include "nn/os.h"
#include "types.h"

namespace movie {
class Decoder;
} // namespace movie

class VideoRenderer {
public:
  struct VideoData {
    int unknown00; // Inferred role: index; original member name unknown.
    s64 unknown08; // Inferred role: presentation time us; original member name unknown.
    u32 unknown10; // Inferred role: flags; original member name unknown.
  };

  movie::Status Open(movie::Decoder *decoder, int unknown01, int unknown02, double unknown03);
  s64 GetVideoPostDelayUs();
  void OnOutputAvailable(int index, s64 presentationTimeUs, u32 flags);

  movie::Decoder *unknown00; // Inferred role: decoder passed to Open; original member name unknown.
  u8 _08[0x18 - 0x08];
  double unknown18; // Double argument of Open; role unknown, original member name unknown.
  u8 _20[0x210 - 0x20];
  std::vector<VideoData> unknown210; // Inferred role: video data list; original member name unknown.
  u8 _228[0x230 - 0x228];
  nn::os::MutexType unknown230; // Inferred role: video data mutex; original member name unknown.
  u8 _250[0x260 - 0x250];
  int unknown260; // First int argument of Open; role unknown, original member name unknown.
  int unknown264; // Second int argument of Open; role unknown, original member name unknown.
  u8 _268[0x278 - 0x268];
  s64 m_videoPostDelayUs; // Read and clamped to 2000..300000 by GetVideoPostDelayUs, hence the accessor-derived name.
};

static_assert(offsetof(VideoRenderer, unknown00) == 0x00, "");
static_assert(offsetof(VideoRenderer, unknown18) == 0x18, "");
static_assert(offsetof(VideoRenderer, unknown210) == 0x210, "");
static_assert(offsetof(VideoRenderer, unknown230) == 0x230, "");
static_assert(offsetof(VideoRenderer, unknown260) == 0x260, "");
static_assert(offsetof(VideoRenderer, unknown264) == 0x264, "");
static_assert(offsetof(VideoRenderer, m_videoPostDelayUs) == 0x278, "");
