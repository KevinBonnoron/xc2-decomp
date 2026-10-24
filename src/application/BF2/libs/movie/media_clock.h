#pragma once
#include <stddef.h>

#include "libs/movie/movie_status.h"
#include "nn/os.h"
#include "types.h"

class MediaClock {
public:
  movie::Status SetMediaStartTime(s64 mediaStartTimeUs);

  nn::os::MutexType unknown00; // Inferred role: mutex; original member name unknown.
  u8 _20[0x38 - 0x20];
  s64 unknown38; // Inferred role: media start time us; original member name unknown.
};

static_assert(offsetof(MediaClock, unknown38) == 0x38, "");
