#pragma once
#include <stddef.h>

#include "libs/movie/movie_status.h"
#include "nn/os.h"
#include "types.h"

class MediaClock {
public:
  movie::Status SetMediaStartTime(s64 mediaStartTimeUs);

  nn::os::MutexType mutex;
  u8 _20[0x38 - 0x20];
  s64 mediaStartTimeUs;
};

static_assert(offsetof(MediaClock, mediaStartTimeUs) == 0x38, "");
