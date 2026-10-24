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
  std::vector<int> unknown9e8;  // Inferred role: audio index list; original member name unknown.
  std::vector<int> unknowna00;  // Inferred role: video index list; original member name unknown.
  nn::os::MutexType unknowna18; // Inferred role: audio index list mutex; original member name unknown.
  nn::os::MutexType unknowna38; // Inferred role: video index list mutex; original member name unknown.
};

static_assert(offsetof(MovieDecoderPlayer, unknown9e8) == 0x9e8, "");
static_assert(offsetof(MovieDecoderPlayer, unknowna00) == 0xa00, "");
static_assert(offsetof(MovieDecoderPlayer, unknowna18) == 0xa18, "");
static_assert(offsetof(MovieDecoderPlayer, unknowna38) == 0xa38, "");
