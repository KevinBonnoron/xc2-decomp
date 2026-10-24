#include <vector>

#include "libs/movie/audio_out_renderer.h"
#include "libs/movie/media_clock.h"
#include "libs/movie/movie_decoder_player.h"
#include "libs/movie/movie_status.h"
#include "libs/movie/video_renderer.h"
#include "nn/os.h"
#include "types.h"

movie::Status MediaClock::SetMediaStartTime(s64 mediaStartTimeUs) {
  nn::os::LockMutex(&unknown00);
  this->unknown38 = mediaStartTimeUs;
  nn::os::UnlockMutex(&unknown00);
  return movie::Status_Success;
}

void AudioOutRenderer::OnOutputAvailable(int index, s64 presentationTimeUs, u32 flags) {
  audioData data;
  data.unknown00 = index;
  data.unknown08 = presentationTimeUs;
  data.unknown10 = flags;
  nn::os::LockMutex(&unknown490);
  unknown430.push_back(data);
  nn::os::UnlockMutex(&unknown490);
  GenerateFixedSizeAudioFrame();
  if (unknown4c0 == -1) {
    unknown4b8->SetMediaStartTime(presentationTimeUs);
    unknown4c0 = presentationTimeUs;
  }
}

void VideoRenderer::OnOutputAvailable(int index, s64 presentationTimeUs, u32 flags) {
  VideoData data;
  data.unknown00 = index;
  data.unknown08 = presentationTimeUs;
  data.unknown10 = flags;
  nn::os::LockMutex(&unknown230);
  unknown210.push_back(data);
  nn::os::UnlockMutex(&unknown230);
}

movie::Status MovieDecoderPlayer::AddBufferToAudioIndexList(int index) {
  nn::os::LockMutex(&unknowna18);
  unknown9e8.push_back(index);
  nn::os::UnlockMutex(&unknowna18);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::RemoveBufferFromAudioIndexList(int *index) {
  int front = -1;
  nn::os::LockMutex(&unknowna18);
  if (static_cast<int>(unknown9e8.size()) > 0) {
    front = unknown9e8.front();
    unknown9e8.erase(unknown9e8.begin());
  }
  *index = front;
  nn::os::UnlockMutex(&unknowna18);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::GetAudioIndexListSize(int *size) {
  nn::os::LockMutex(&unknowna18);
  *size = unknown9e8.size();
  nn::os::UnlockMutex(&unknowna18);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::GetVideoIndexListSize(int *size) {
  nn::os::LockMutex(&unknowna38);
  *size = unknowna00.size();
  nn::os::UnlockMutex(&unknowna38);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::AddBufferToVideoIndexList(int index) {
  nn::os::LockMutex(&unknowna38);
  unknowna00.push_back(index);
  nn::os::UnlockMutex(&unknowna38);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::RemoveBufferFromVideoIndexList(int *index) {
  int front = -1;
  nn::os::LockMutex(&unknowna38);
  if (static_cast<int>(unknowna00.size()) > 0) {
    front = unknowna00.front();
    unknowna00.erase(unknowna00.begin());
  }
  *index = front;
  nn::os::UnlockMutex(&unknowna38);
  return movie::Status_Success;
}
