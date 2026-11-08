#include <vector>

#include "libs/movie/audio_out_renderer.h"
#include "libs/movie/media_clock.h"
#include "libs/movie/movie_decoder_player.h"
#include "libs/movie/movie_status.h"
#include "libs/movie/video_renderer.h"
#include "nn/os.h"
#include "types.h"

namespace movie {
class Decoder;
} // namespace movie

MediaClock::MediaClock() {
  nn::os::InitializeMutex(&unknown00, false, 0);
  unknown20 = -1;
  unknown28 = -1;
  unknown30 = 0x7fffffffffffffff;
  unknown38 = -1;
}

movie::Status MediaClock::SetMediaStartTime(s64 mediaStartTimeUs) {
  nn::os::LockMutex(&unknown00);
  this->unknown38 = mediaStartTimeUs;
  nn::os::UnlockMutex(&unknown00);
  return movie::Status_Success;
}

movie::Status MediaClock::ClearAnchorTime() {
  nn::os::LockMutex(&unknown00);
  unknown20 = -1;
  unknown28 = -1;
  nn::os::UnlockMutex(&unknown00);
  return movie::Status_Success;
}

movie::Status VideoRenderer::Open(movie::Decoder *decoder, int unknown01, int unknown02, double unknown03) {
  unknown260 = unknown01;
  unknown264 = unknown02;
  unknown00 = decoder;
  unknown18 = unknown03;
  return movie::Status_Success;
}

s64 VideoRenderer::GetVideoPostDelayUs() {
  if (m_videoPostDelayUs < 2000) {
    m_videoPostDelayUs = 2000;
  } else if (m_videoPostDelayUs > 300000) {
    m_videoPostDelayUs = 300000;
  }
  return m_videoPostDelayUs;
}

u64 AudioOutRenderer::GetRendererSleepTimeMs() { return m_rendererSleepTimeMs; }

s64 AudioOutRenderer::GetPlayedOutAudioDurationUs(s64 currentTimeUs) {
  s64 startTimeUs = unknown4c8;
  if (unknown4c8 == -1) {
    unknown4c8 = currentTimeUs;
    startTimeUs = currentTimeUs;
  }
  s64 duration = unknown4d0 * 1000000 / unknown10;
  if (currentTimeUs - startTimeUs <= duration) {
    duration = currentTimeUs - startTimeUs;
  }
  return duration;
}

bool AudioOutRenderer::ExitThread() { return m_exitThread; }

bool AudioOutRenderer::IsAudioOutStarted() { return m_audioOutStarted; }

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
