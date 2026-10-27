#include "ssd/ssd_allocator.h"
#include "ssd/ssd_array.h"
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_debug.h"
#include "ssd/ssd_delegate.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_stream_buffer.h"
#include "ssd/ssd_stream_controller.h"
#include "ssd/ssd_text.h"
#include "ssd/ssd_voice_handle.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace fw {
class SoundSsdDriver;
} // namespace fw

namespace ssd {

void SoundHandle::ClearDelegateImpl() {
  unknown100.Clear();
  for (int i = 0; i < unknown128.unknown08; i++) {
    Delegate::Handle *handle = unknown128.unknown10[i];
    SoundMemory::allocator_->unknown001(handle);
  }
  unknown128.unknown08 = 0;
}

void SoundHandle::ClearDelegate() {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core != nullptr) {
    core->unknown708.Lock();
    ClearDelegateImpl();
    core->unknown708.Unlock();
  }
}

void SoundHandle::AddDelegate(Delegate::Handle *handle) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  core->unknown708.Lock();
  Result result = unknown100.AddDelegate(handle);
  core->unknown708.Unlock();
  set_result(result);
}

long SoundHandle::RemoveDelegate(Delegate::Handle *handle) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -1;
  }
  core->unknown708.Lock();
  Result result = unknown100.RemoveDelegate(handle);
  core->unknown708.Unlock();
  return result;
}

void SoundHandle::AddDelegateInternal(Delegate::Handle *handle) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  core->unknown708.Lock();
  int count = unknown128.unknown08;
  if (unknown128.unknown0c <= count) {
    unknown128.SetArraySize(unknown128.unknown0c + 16);
    count = unknown128.unknown08;
  }
  unknown128.unknown10[count] = handle;
  unknown128.unknown08++;
  Result result = unknown100.AddDelegate(handle);
  core->unknown708.Unlock();
  set_result(result);
}

bool SoundHandle::IsValidHandle() const {
  if (!unknown58) {
    return false;
  }
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return false;
  }
  return core->GetVoiceHandle(unknownf8) != nullptr;
}

long SoundHandle::Stop(f32 fadeTime) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return 0;
  }
  return voice->unknown44;
}

bool SoundHandle::HasEnded() const {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return false;
  }
  return core->GetVoiceHandle(unknownf8) != nullptr;
}

bool SoundHandle::IsPlay() const {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return false;
  }
  return core->GetVoiceHandle(unknownf8) != nullptr;
}

void SoundHandle::SetCategoryId(int category) {
  if (SoundCore::instance_ != nullptr) {
    unknown50 = static_cast<SystemCore *>(SoundCore::instance_)->GetCategory(category)->unknown08;
  }
}

void SoundHandle::SetPitch(f32 pitch, f32 fadeTime) { this->unknown6c.Set(pitch, fadeTime); }

void SoundHandle::SetVolume(f32 volume, f32 fadeTime) {
  f32 current = this->unknown84;
  unknown8c = fadeTime;
  f32 begin = fadeTime != 0.0f ? current : volume;
  unknown98 = volume;
  unknown94 = begin;
  this->unknown84 = begin;
  unknown90 = volume - begin;
  unknown88 = 0.0f;
}

void SoundHandle::UpdateAudioFrame(f32 deltaTime) {
  f32 time = unknown6c.unknown08;
  if (unknown6c.unknown04 < time) {
    f32 elapsed = unknown6c.unknown04 + deltaTime;
    if (elapsed >= time) {
      elapsed = time;
    }
    unknown6c.unknown00 = unknown6c.unknown10 + (elapsed * unknown6c.unknown0c) / time;
    unknown6c.unknown04 = elapsed;
  }
  time = unknown8c;
  if (unknown88 < time) {
    f32 elapsed = unknown88 + deltaTime;
    if (elapsed >= time) {
      elapsed = time;
    }
    unknown84 = unknown94 + (elapsed * unknown90) / time;
    unknown88 = elapsed;
  }
}

void SoundHandle::SetPan(f32 pan, f32 fadeTime) { this->unknown9c.Set(pan, fadeTime); }

long SoundHandle::SetEnableEffect(int index, bool isEnable) {
  if (index > 1) {
    return -6;
  }
  unknownc0[index].unknown00 = isEnable;
  return 0;
}

long SoundHandle::SetEffectVolume(int index, f32 volume, f32 fadeTime) {
  if (index > 1) {
    return -6;
  }
  unknownc0[index].unknown04.Reset(volume);
  return 0;
}

long SoundHandle::SetPregapTime(f32 time) {
  unknown68 = time;
  return set_result(static_cast<Result>(0));
}

long SoundHandle::GetPlayPosition(u64 *position) const {
  *position = 0;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->GetPlayTime(time));
}

long SoundHandle::GetDataTime(f32 *time) const {
  *time = 0.0f;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  WaveSource *waveSource = voice->unknown002();
  f32 dataTime;
  if (waveSource->unknown18) {
    dataTime = waveSource->unknown30 / waveSource->unknown2c;
  } else {
    dataTime = 0.0f;
  }
  *time = dataTime;
  return set_result(static_cast<Result>(0));
}

long SoundHandle::SetPlayPosition(u64 position) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    log_error(static_cast<Result>(-29), static_cast<Debug::LogFlag::Type>(2), TextRef::EmptyText, TextRef::EmptyText);
    return 0.0f;
  }
  return voice->unknown6f0;
}

long SoundHandle::GetRemainLoopCount(int *count) const {
  *count = 0;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->unknown70 == nullptr) {
    return -44;
  }
  return set_result(voice->GetRemainLoopCount(count));
}

long SoundHandle::SetRemainLoopCount(int count) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->unknown70 == nullptr) {
    return -44;
  }
  if (!voice->unknown70->unknown50) {
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->unknown70 == nullptr) {
    return -44;
  }
  return set_result(voice->GetVoiceQueueCount(count));
}

long SoundHandle::IsEmptyVoiceQueue(bool *isEmpty) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
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
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->unknown70 == nullptr) {
    return -44;
  }
  voice->IsEmptyStreamBuffer(isEmpty);
  return set_result(static_cast<Result>(0));
}

long SoundHandle::GetWaveSource(WaveSource **waveSource) {
  *waveSource = nullptr;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  *waveSource = voice->unknown002();
  return set_result(static_cast<Result>(0));
}

long SoundHandle::GetStreamBuffer(StreamBufferBase **buffer) const {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->unknown70 == nullptr) {
    return -44;
  }
  *buffer = &voice->unknown70->unknown158;
  return 0;
}

long SoundHandle::GetStreamDecodeInfo(DecodeInfo *info) const {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  StreamController *stream = voice->unknown70;
  if (stream == nullptr) {
    return -44;
  }
  info->unknown00 = stream->unknown1ec;
  info->unknown04 = stream->unknown1e8;
  info->unknown08 = stream->unknown1e0 * 1000.0;
  return 0;
}

long SoundHandle::KeepStreamOpen(bool isKeep) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  if (voice->unknown70 == nullptr) {
    return -44;
  }
  voice->unknown70->unknownf5 = isKeep;
  return set_result(static_cast<Result>(0));
}

void SoundHandle::DisplayDebugVerbose() {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    log_message("このIDは無効です。");
    return;
  }
  voice->DisplayDebugVerbose();
}

template class Delegate::Object<fw::SoundSsdDriver, SoundHandle *, SoundHandle::Notify::Type>;

} // namespace ssd
