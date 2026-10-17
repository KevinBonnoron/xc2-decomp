#pragma once
#include <stddef.h>

#include <vector>

#include "libs/movie/movie_status.h"
#include "nn/os.h"
#include "types.h"

class MovieDecoderPlayer {
public:
  movie::Status AddBufferToAudioIndexList(int index);
  movie::Status RemoveBufferFromAudioIndexList(int *index);
  movie::Status GetAudioIndexListSize(int *size);
  movie::Status GetVideoIndexListSize(int *size);
  movie::Status AddBufferToVideoIndexList(int index);
  movie::Status RemoveBufferFromVideoIndexList(int *index);

  u8 _000[0x9e8 - 0x000];
  std::vector<int> audioIndexList;
  std::vector<int> videoIndexList;
  nn::os::MutexType audioIndexListMutex;
  nn::os::MutexType videoIndexListMutex;
};

static_assert(offsetof(MovieDecoderPlayer, audioIndexList) == 0x9e8, "");
static_assert(offsetof(MovieDecoderPlayer, videoIndexList) == 0xa00, "");
static_assert(offsetof(MovieDecoderPlayer, audioIndexListMutex) == 0xa18, "");
static_assert(offsetof(MovieDecoderPlayer, videoIndexListMutex) == 0xa38, "");
