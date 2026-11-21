#include <stdlib.h>
#include <vector>

#include "libs/movie/audio_out_renderer.h"
#include "libs/movie/cmovie_nx.h"
#include "libs/movie/media_clock.h"
#include "libs/movie/movie_decoder_player.h"
#include "libs/movie/movie_status.h"
#include "libs/movie/video_renderer.h"
#include "mm_mtl/allocator.h"
#include "nn/os.h"
#include "types.h"

namespace movie {
class Decoder;
} // namespace movie

namespace {

bool unknown001; // Inferred role: movie is paused; original name unknown.

} // namespace

namespace CMovieNX {

u8 *CMovie::randfill(u8 *buffer, size_t size) {
  unsigned int seed = rand();
  u8 *p = buffer;
  for (size_t i = 0; i < size; i++) {
    *p++ = seed >> 8;
    seed = seed * 1103515245 + 12345;
  }
  return p;
}

void CMovie::finalize() {
  if (unknown10 != nullptr) {
    unknown20->deallocate(unknown10);
    unknown10 = nullptr;
  }
}

float CMovie::get_length() { return 0.0f; }

float CMovie::pos() { return 0.0f; }

void CMovie::play() {
  if (unknown001 == true) {
    unknown001 = false;
  }
}

void CMovie::pause() {
  if (!unknown001) {
    unknown001 = true;
  }
}

bool CMovie::isstandby() {
  if (unknown08 == nullptr) {
    return false;
  }
  if (unknown08->unknown438 != nullptr) {
    return unknown08->unknown438->unknown268;
  }
  return false;
}

bool CMovie::ispause() { return unknown001; }

bool CMovie::isplaying() {
  MovieDecoderPlayer *player = unknown08;
  if (player == nullptr) {
    return false;
  }
  return !player->IsPlaybackComplete();
}

} // namespace CMovieNX

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

movie::Status MediaClock::GetMediaTime(s64 currentTimeUs, s64 *mediaTimeUs, bool ignoreClamp) const {
  if (unknown28 == -1) {
    return movie::Status_UNKNOWN_4096;
  }
  s64 mediaTime = unknown20 + (currentTimeUs - unknown28); // Inferred: media time elapsed since the anchor, from the anchor pair.
  if (mediaTime > unknown30 && !ignoreClamp) {
    mediaTime = unknown30;
  }
  if (mediaTime < unknown38) {
    mediaTime = unknown38;
  }
  if (mediaTime < 0) {
    mediaTime = 0;
  }
  *mediaTimeUs = mediaTime;
  return movie::Status_Success;
}

VideoRenderer::VideoRenderer() {
  unknown20 = 0x40000;
  unknown28 = nullptr;
  unknown250 = 0;
  unknown258 = nullptr;
  unknown268 = false;
  unknown269 = false;
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

void VideoRenderer::Close() {
  m_doneProcessing = true;
  if (unknown0a) {
    if (unknown08) {
      nn::os::WaitThread(&unknown30);
      unknown08 = false;
    }
    nn::os::DestroyThread(&unknown30);
    unknown0a = false;
  }
}

movie::Status VideoRenderer::Start(int unknown01, int unknown02) {
  unknown260 = unknown01;
  unknown264 = unknown02;
  nn::os::StartThread(&unknown30);
  unknown08 = true;
  return movie::Status_Success;
}

bool VideoRenderer::DoneProcessing() { return m_doneProcessing; }

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

movie::Status MovieDecoderPlayer::SignalAudioVideoWorkerThreadExit() {
  nn::os::SignalEvent(&unknown18);
  return movie::Status_Success;
}

void MovieDecoderPlayer::StopAndDestroyAudioVideoWorkerThread() {
  if (unknown821) {
    unknown820 = true;
    nn::os::SignalEvent(&unknown18);
    nn::os::WaitThread(&unknown828);
    nn::os::DestroyThread(&unknown828);
    unknown821 = false;
  }
}

movie::Status MovieDecoderPlayer::SignalVideoInputReadThreadExit() {
  nn::os::SendMessageQueue(&unknowna68, 2);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::SignalAudioInputReadThreadExit() {
  nn::os::SendMessageQueue(&unknownab8, 4);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::SignalVideoInputBufferAvailable() {
  nn::os::SendMessageQueue(&unknowna68, 1);
  return movie::Status_Success;
}

movie::Status MovieDecoderPlayer::SignalAudioInputBufferAvailable() {
  nn::os::SendMessageQueue(&unknownab8, 3);
  return movie::Status_Success;
}

void MovieDecoderPlayer::StopAndDestroyVideoInputReaderThread() {
  if (unknown481) {
    unknown480 = true;
    nn::os::SendMessageQueue(&unknowna68, 2);
    nn::os::WaitThread(&unknown488);
    nn::os::DestroyThread(&unknown488);
    unknown481 = false;
  }
}

void MovieDecoderPlayer::StopAndDestroyAudioInputReaderThread() {
  if (unknown651) {
    unknown650 = true;
    nn::os::SendMessageQueue(&unknownab8, 4);
    nn::os::WaitThread(&unknown658);
    nn::os::DestroyThread(&unknown658);
    unknown651 = false;
  }
}

void MovieDecoderPlayer::StartVideoInputReaderThread() { nn::os::StartThread(&unknown488); }

void MovieDecoderPlayer::StartAudioInputReaderThread() { nn::os::StartThread(&unknown658); }

void MovieDecoderPlayer::StartAudioVideoWorkerThread() { nn::os::StartThread(&unknown828); }

void MovieDecoderPlayer::ResetPlaybackComplete() {
  unknownb48 = false;
  unknownb49 = false;
}

movie::Status MovieDecoderPlayer::AudioFormatChangedEvent() { return movie::Status_Success; }

bool MovieDecoderPlayer::IsPlaybackComplete() {
  bool audioFinished = unknown430 == nullptr || unknown430->unknown4b0;
  if ((unknown438 == nullptr || unknown438->unknown269) && audioFinished) {
    unknownb30 = true;
  }
  return unknownb30;
}

bool MovieDecoderPlayer::StartPlayback() {
  bool audioFilled = unknownb08 && unknownb4c < unknownb54;
  bool videoFilled = unknownb09 && unknownb50 < unknownb58;
  return !(audioFilled || videoFilled);
}
