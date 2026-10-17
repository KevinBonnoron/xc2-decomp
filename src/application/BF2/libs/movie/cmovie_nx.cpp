#include <vector>

#include "libs/movie/audio_out_renderer.h"
#include "libs/movie/media_clock.h"
#include "libs/movie/movie_decoder_player.h"
#include "libs/movie/movie_status.h"
#include "libs/movie/video_renderer.h"
#include "nn/os.h"
#include "types.h"

movie::Status MediaClock::SetMediaStartTime(s64 mediaStartTimeUs) {
  nn::os::LockMutex(&mutex);
  this->mediaStartTimeUs = mediaStartTimeUs;
  nn::os::UnlockMutex(&mutex);
  return movie::Status_Success;
}

void AudioOutRenderer::OnOutputAvailable(int index, s64 presentationTimeUs, u32 flags) {
  audioData data;
  data.index = index;
  data.presentationTimeUs = presentationTimeUs;
  data.flags = flags;
  nn::os::LockMutex(&audioDataMutex);
  audioDataList.push_back(data);
  nn::os::UnlockMutex(&audioDataMutex);
  GenerateFixedSizeAudioFrame();
  if (startTimeUs == -1) {
    mediaClock->SetMediaStartTime(presentationTimeUs);
    startTimeUs = presentationTimeUs;
  }
}

void VideoRenderer::OnOutputAvailable(int index, s64 presentationTimeUs, u32 flags) {
  VideoData data;
  data.index = index;
  data.presentationTimeUs = presentationTimeUs;
  data.flags = flags;
  nn::os::LockMutex(&videoDataMutex);
  videoDataList.push_back(data);
  nn::os::UnlockMutex(&videoDataMutex);
}

movie::Status MovieDecoderPlayer::AddBufferToAudioIndexList(int index) {
  nn::os::LockMutex(&audioIndexListMutex);
  audioIndexList.push_back(index);
  nn::os::UnlockMutex(&audioIndexListMutex);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::RemoveBufferFromAudioIndexList(int *index) {
  int front = -1;
  nn::os::LockMutex(&audioIndexListMutex);
  if (static_cast<int>(audioIndexList.size()) > 0) {
    front = audioIndexList.front();
    audioIndexList.erase(audioIndexList.begin());
  }
  *index = front;
  nn::os::UnlockMutex(&audioIndexListMutex);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::GetAudioIndexListSize(int *size) {
  nn::os::LockMutex(&audioIndexListMutex);
  *size = audioIndexList.size();
  nn::os::UnlockMutex(&audioIndexListMutex);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::GetVideoIndexListSize(int *size) {
  nn::os::LockMutex(&videoIndexListMutex);
  *size = videoIndexList.size();
  nn::os::UnlockMutex(&videoIndexListMutex);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::AddBufferToVideoIndexList(int index) {
  nn::os::LockMutex(&videoIndexListMutex);
  videoIndexList.push_back(index);
  nn::os::UnlockMutex(&videoIndexListMutex);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::RemoveBufferFromVideoIndexList(int *index) {
  int front = -1;
  nn::os::LockMutex(&videoIndexListMutex);
  if (static_cast<int>(videoIndexList.size()) > 0) {
    front = videoIndexList.front();
    videoIndexList.erase(videoIndexList.begin());
  }
  *index = front;
  nn::os::UnlockMutex(&videoIndexListMutex);
  return movie::Status_Success;
}
