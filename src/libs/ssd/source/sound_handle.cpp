#include "ssd/ssd_debug.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_stream_controller.h"
#include "ssd/ssd_text.h"
#include "ssd/ssd_voice_handle.h"
#include "types.h"

namespace ssd {

bool SoundHandle::IsValidHandle() const {
  if (!isValid) {
    return false;
  }
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return false;
  }
  return core->GetVoiceHandle(voiceHandleId) != nullptr;
}

long SoundHandle::Stop(f32 fadeTime) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->Stop(fadeTime));
}

int SoundHandle::GetState() const {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -1;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return 0;
  }
  return voice->state_;
}

bool SoundHandle::HasEnded() const {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return false;
  }
  return core->GetVoiceHandle(voiceHandleId) != nullptr;
}

bool SoundHandle::IsPlay() const {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return false;
  }
  return core->GetVoiceHandle(voiceHandleId) != nullptr;
}

void SoundHandle::SetPitch(f32 pitch, f32 fadeTime) { this->pitch.Set(pitch, fadeTime); }

void SoundHandle::SetVolume(f32 volume, f32 fadeTime) {
  f32 current = this->volume;
  volumeTime = fadeTime;
  f32 begin = fadeTime != 0.0f ? current : volume;
  volumeTarget = volume;
  volumeStart = begin;
  this->volume = begin;
  volumeDelta = volume - begin;
  volumeElapsed = 0.0f;
}

void SoundHandle::SetPan(f32 pan, f32 fadeTime) { this->pan.Set(pan, fadeTime); }

long SoundHandle::SetEnableEffect(int index, bool isEnable) {
  if (index > 1) {
    return -6;
  }
  effects[index].isEnable = isEnable;
  return 0;
}

long SoundHandle::SetEffectVolume(int index, f32 volume, f32 fadeTime) {
  if (index > 1) {
    return -6;
  }
  effects[index].volume.Reset(volume);
  return 0;
}

long SoundHandle::SetPregapTime(f32 time) {
  pregapTime = time;
  return set_result(static_cast<Result>(0));
}

long SoundHandle::GetPlayPosition(u64 *position) const {
  *position = 0;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->GetPlayPosition(position));
}

long SoundHandle::GetPlaySample(unsigned long long *sample) const {
  *sample = 0;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->GetPlaySample(sample));
}

long SoundHandle::GetFilePosition(u64 *position) const {
  *position = 0;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->GetFilePosition(position));
}

long SoundHandle::GetPlayTime(f32 *time) const {
  *time = 0.0f;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->GetPlayTime(time));
}

long SoundHandle::SetPlayPosition(u64 position) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->SetPlayPosition(position));
}

long SoundHandle::SetPlaySample(unsigned long long sample) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->SetPlaySample(sample));
}

long SoundHandle::SetPlayTime(f32 time) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->SetPlayTime(time));
}

long SoundHandle::GetLoopTime(bool *isLoop, f32 *begin, f32 *end) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->GetLoopTime(isLoop, begin, end));
}

f32 SoundHandle::GetDistanceVolume() const {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    log_error(static_cast<Result>(-12), Debug::LogFlag::All, TextRef::EmptyText, TextRef::EmptyText);
    return 0.0f;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    log_error(static_cast<Result>(-29), static_cast<Debug::LogFlag::Type>(2), TextRef::EmptyText, TextRef::EmptyText);
    return 0.0f;
  }
  return voice->distanceVolume;
}

long SoundHandle::GetRemainLoopCount(int *count) const {
  *count = 0;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->stream == nullptr) {
    return -44;
  }
  return set_result(voice->GetRemainLoopCount(count));
}

long SoundHandle::SetRemainLoopCount(int count) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->stream == nullptr) {
    return -44;
  }
  if (!voice->stream->isLoop) {
    return -1;
  }
  return set_result(voice->SetRemainLoopCount(count));
}

long SoundHandle::GetVoiceQueueCount(int *count) const {
  *count = 0;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->stream == nullptr) {
    return -44;
  }
  return set_result(voice->GetVoiceQueueCount(count));
}

long SoundHandle::IsEmptyVoiceQueue(bool *isEmpty) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  voice->IsEmptyVoiceQueue(isEmpty);
  return set_result(static_cast<Result>(0));
}

long SoundHandle::IsEmptyStreamBuffer(bool *isEmpty) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->stream == nullptr) {
    return -44;
  }
  voice->IsEmptyStreamBuffer(isEmpty);
  return set_result(static_cast<Result>(0));
}

long SoundHandle::KeepStreamOpen(bool isKeep) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->stream == nullptr) {
    return -44;
  }
  voice->stream->isKeepOpen = isKeep;
  return set_result(static_cast<Result>(0));
}

void SoundHandle::DisplayDebugVerbose() {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return;
  }
  VoiceHandle *voice = core->GetVoiceHandle(voiceHandleId);
  if (voice == nullptr) {
    log_message("このIDは無効です。");
    return;
  }
  voice->DisplayDebugVerbose();
}

} // namespace ssd
