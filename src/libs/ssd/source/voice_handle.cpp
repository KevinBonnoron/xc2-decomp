#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_stream_controller.h"
#include "ssd/ssd_voice_handle.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {

void VoiceHandle::DeleteHWVoice() {}

Result VoiceHandle::AllocHWVoice() { return static_cast<Result>(0); }

Result VoiceHandle::ForceStop() {
  isStopping_ = true;
  isStopped_ = false;
  isPlay_ = false;
  state_ = 9;
  if (soundHandle_ != nullptr) {
    soundHandle_->voiceHandleId = 0;
    soundHandle_ = nullptr;
  }
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::GetFilePosition(u64 *position) const {
  *position = stream != nullptr ? stream->filePosition : 0;
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::GetLoopTime(bool *isLoop, f32 *begin, f32 *end) {
  f32 sampleRate = waveSource_->sampleRate;
  *isLoop = waveSource_->isLoop;
  *begin = waveSource_->loopStart / sampleRate;
  *end = waveSource_->loopEnd / sampleRate;
  return static_cast<Result>(0);
}

Result VoiceHandle::GetRemainLoopCount(int *count) const {
  if (count == nullptr || stream == nullptr) {
    return static_cast<Result>(-6);
  }
  *count = stream->remainLoopCount;
  return static_cast<Result>(0);
}

Result VoiceHandle::SetRemainLoopCount(int count) {
  if (stream == nullptr) {
    return static_cast<Result>(-6);
  }
  stream->remainLoopCount = count;
  return static_cast<Result>(0);
}

Result VoiceHandle::GetVoiceQueueCount(int *count) const {
  if (count == nullptr) {
    return static_cast<Result>(-6);
  }
  *count = voiceQueueCount;
  return static_cast<Result>(0);
}

Result VoiceHandle::IsEmptyVoiceQueue(bool *isEmpty) {
  if (isEmpty == nullptr) {
    return static_cast<Result>(-6);
  }
  *isEmpty = isEmptyVoiceQueue;
  isEmptyVoiceQueue = false;
  return static_cast<Result>(0);
}

Result VoiceHandle::IsEmptyStreamBuffer(bool *isEmpty) {
  if (isEmpty == nullptr) {
    return static_cast<Result>(-6);
  }
  *isEmpty = isEmptyStreamBuffer;
  isEmptyStreamBuffer = false;
  return static_cast<Result>(0);
}

void VoiceHandle::UpdateAudioFrame(f32 deltaTime) {
  if (stream != nullptr) {
    UpdateAudioStream(deltaTime);
  } else {
    UpdateAudioInternal(deltaTime);
  }
}

void VoiceHandle::NullBufferProcess() {}

void VoiceHandle::LooppingBufferProcess() {}

void VoiceHandle::AddLooppingBuffer() { voiceQueueCount++; }

} // namespace ssd
