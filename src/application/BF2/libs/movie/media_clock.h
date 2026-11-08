#pragma once
#include <stddef.h>

#include "libs/movie/movie_status.h"
#include "nn/os.h"
#include "types.h"

class MediaClock {
public:
  MediaClock();
  movie::Status SetMediaStartTime(s64 mediaStartTimeUs);
  movie::Status ClearAnchorTime();

  nn::os::MutexType unknown00; // Inferred role: mutex; original member name unknown.
  s64 unknown20;               // Inferred role: anchor media time us, -1 when unset; original member name unknown.
  s64 unknown28;               // Inferred role: anchor clock time, -1 when unset; original member name unknown.
  s64 unknown30;               // Inferred role: clamp bound read by GetMediaTime, INT64_MAX when constructed; original member name unknown.
  s64 unknown38;               // Inferred role: media start time us; original member name unknown.
};

static_assert(offsetof(MediaClock, unknown20) == 0x20, "");
static_assert(offsetof(MediaClock, unknown28) == 0x28, "");
static_assert(offsetof(MediaClock, unknown30) == 0x30, "");
static_assert(offsetof(MediaClock, unknown38) == 0x38, "");
