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
  void Close();
  movie::Status Start(int unknown01, int unknown02);
  bool DoneProcessing();

  movie::Decoder *unknown00; // Inferred role: decoder passed to Open; original member name unknown.
  bool unknown08;            // Inferred role: thread must be joined; set by Start and cleared after WaitThread in Close; original member name unknown.
  bool m_doneProcessing;     // Named by the accessor DoneProcessing, which returns it; Close also sets it.
  bool unknown0a;            // Inferred role: thread was created; gates the thread shutdown in Close; original member name unknown.
  u8 _0b[0x18 - 0x0b];
  double unknown18; // Double argument of Open; role unknown, original member name unknown.
  u8 _20[0x30 - 0x20];
  nn::os::ThreadType unknown30; // Inferred role: thread passed to nn::os::CreateThread by Initialize, waited and destroyed by Close; original member name unknown.
  u8 _1f0[0x210 - 0x1f0];
  std::vector<VideoData> unknown210; // Inferred role: video data list; original member name unknown.
  u8 _228[0x230 - 0x228];
  nn::os::MutexType unknown230; // Inferred role: video data mutex; original member name unknown.
  u8 _250[0x260 - 0x250];
  int unknown260;  // First int argument of Open; role unknown, original member name unknown.
  int unknown264;  // Second int argument of Open; role unknown, original member name unknown.
  bool unknown268; // Inferred role: flag tested by CMovie::isstandby; original member name unknown.
  bool unknown269; // Inferred role: flag tested by CMovie::isplaying; original member name unknown.
  u8 _26a[0x278 - 0x26a];
  s64 m_videoPostDelayUs; // Read and clamped to 2000..300000 by GetVideoPostDelayUs, hence the accessor-derived name.
};

static_assert(offsetof(VideoRenderer, unknown00) == 0x00, "");
static_assert(offsetof(VideoRenderer, unknown08) == 0x08, "");
static_assert(offsetof(VideoRenderer, m_doneProcessing) == 0x09, "");
static_assert(offsetof(VideoRenderer, unknown0a) == 0x0a, "");
static_assert(offsetof(VideoRenderer, unknown18) == 0x18, "");
static_assert(offsetof(VideoRenderer, unknown30) == 0x30, "");
static_assert(offsetof(VideoRenderer, unknown210) == 0x210, "");
static_assert(offsetof(VideoRenderer, unknown230) == 0x230, "");
static_assert(offsetof(VideoRenderer, unknown260) == 0x260, "");
static_assert(offsetof(VideoRenderer, unknown264) == 0x264, "");
static_assert(offsetof(VideoRenderer, unknown268) == 0x268, "");
static_assert(offsetof(VideoRenderer, unknown269) == 0x269, "");
static_assert(offsetof(VideoRenderer, m_videoPostDelayUs) == 0x278, "");
