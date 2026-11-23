#include "mm_mtl/internal/object_allocator.h"
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_array.h"
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_command_manager.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_delegate.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_sound_param.h"
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

SoundHandle::SoundHandle()
    : Object(ObjectType::SOUND_HANDLE), m_soundEntry(nullptr), m_soundActor(nullptr), unknown40(0), m_soundCategory(0, 0.0f), unknown58(false), unknown59(false), unknown5a(false), unknownf8(0) {
  m_effect[0].unknown00 = false;
  m_effect[0].unknown04.Reset(1.0f);
  m_effect[1].unknown00 = false;
  m_effect[1].unknown04.Reset(1.0f);
}

SoundHandle::~SoundHandle() {
  unknown58 = false;
  Delete();
}

void SoundHandle::Init() {
  unknown6c.Reset(1.0f);
  unknown68 = 0.0f;
  unknown84.Reset(1.0f);
  unknown9c.Reset(0.0f);
  unknownb4 = 1.0f;
  unknownb8 = 1.0f;
  unknownbc = 0.0f;
  unknown60 = 0;
  m_effect[0].unknown00 = false;
  m_effect[0].unknown04.Reset(1.0f);
  m_effect[1].unknown00 = false;
  m_effect[1].unknown04.Reset(1.0f);
  ClearDelegate();
  unknown58 = true;
}

void SoundHandle::Quit() {
  unknown58 = false;
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core != nullptr) {
    VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
    if (voice != nullptr) {
      Stop(0.0f);
      voice->m_soundHandle = nullptr;
    }
    m_soundEntry = nullptr;
    ClearDelegate();
    unknown128.unknown001();
  }
}

void SoundHandle::Delete() {
  Quit();
  ClearDelegateImpl();
  unknown128.unknown001();
}

void SoundHandle::ClearDelegateImpl() {
  m_multiCast.Clear();
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
  Result result = m_multiCast.AddDelegate(handle);
  core->unknown708.Unlock();
  set_result(result);
}

long SoundHandle::RemoveDelegate(Delegate::Handle *handle) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -1;
  }
  core->unknown708.Lock();
  Result result = m_multiCast.RemoveDelegate(handle);
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
  Result result = m_multiCast.AddDelegate(handle);
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

long SoundHandle::PlayCommand(const SoundEntry *entry, SoundActor *actor, f32 volume, f32 fadeTime) {
  HandlePlay *command = static_cast<SystemCore *>(SoundCore::instance_)->m_commandManager.unknown003<HandlePlay>();
  command->unknown08 = this;
  command->m_soundEntry = entry;
  command->m_soundActor = actor;
  command->unknown20 = volume;
  command->unknown24 = fadeTime;
  return 0;
}

long SoundHandle::Play(const SoundEntry *entry, SoundActor *actor, f32 volume, f32 fadeTime) {
  if (!unknown58) {
    Init();
  } else if (m_soundEntry != nullptr) {
    return -33;
  }
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice != nullptr) {
    voice->Stop(0.0f);
  }
  long result = Prepare(entry);
  if (result >= 0) {
    result = Start(actor, volume, fadeTime);
  }
  return set_result(static_cast<Result>(result));
}

long SoundHandle::Prepare(const SoundEntry *entry) {
  if (!unknown58) {
    Init();
  } else if (m_soundEntry != nullptr) {
    return -33;
  }
  if (SoundCore::instance_ == nullptr) {
    return -12;
  }
  VoiceHandle *voice;
  static_cast<SystemCore *>(SoundCore::instance_)->AllocVoiceHandle(0, &voice);
  if (voice == nullptr) {
    return -50;
  }
  m_soundEntry = entry;
  long result = voice->Prepare(entry, this, &unknownf8);
  if (result < 0) {
    static_cast<SystemCore *>(SoundCore::instance_)->FreeVoiceHandle(voice);
  }
  return set_result(static_cast<Result>(result));
}

long SoundHandle::Start(SoundActor *actor, f32 volume, f32 fadeTime) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  if (m_soundEntry == nullptr) {
    return -20;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  if (actor == nullptr) {
    actor = core->m_soundActor;
  }
  m_soundActor = actor;
  SoundGroup *group = m_soundEntry->GetSoundGroup();
  if (group == nullptr) {
    group = &core->m_soundGroup;
  }
  unknown40 = group->unknown18;
  m_soundCategory.unknown08 = core->GetCategory(m_soundEntry->m_soundParam.m_base.unknown02)->unknown08;
  unknown6c.Reset(1.0f);
  unknown9c.Reset(0.0f);
  unknown84.Reset(volume);
  unknown60 = SystemCorePlatform::GetSystemTime();
  return set_result(voice->Start(fadeTime, unknown68 != 0.0f));
}

long SoundHandle::Pause(bool isPause, f32 fadeTime) {
  if (!unknown58 || m_soundEntry == nullptr) {
    return -5;
  }
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return -12;
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  if (voice == nullptr) {
    return -29;
  }
  return set_result(voice->Pause(isPause, fadeTime));
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

TextRef SoundHandle::GetStateName() const {
  static const char16_t *const names[] = {
      u"FAILURE", u"NONE", u"RELEASED", u"WAITING", u"CLOSING", u"STOPPED", u"INIT", u"PREPARING", u"PREPARED", u"READY", u"STOPPING", u"PAUSED", u"PAUSING", u"RESUMING", u"PLAYING", u"MAX"};
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return TextRef(TextRef::EmptyText);
  }
  VoiceHandle *voice = core->GetVoiceHandle(unknownf8);
  int index = 0;
  if (voice != nullptr) {
    index = voice->unknown44 + 1;
  }
  return TextRef(names[index]);
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
    m_soundCategory.unknown08 = static_cast<SystemCore *>(SoundCore::instance_)->GetCategory(category)->unknown08;
  }
}

void SoundHandle::SetPitch(f32 pitch, f32 fadeTime) { this->unknown6c.Set(pitch, fadeTime); }

void SoundHandle::SetVolume(f32 volume, f32 fadeTime) { this->unknown84.Set(volume, fadeTime); }

void SoundHandle::UpdateAudioFrame(f32 deltaTime) {
  unknown6c.unknown004(deltaTime);
  unknown84.unknown004(deltaTime);
}

void SoundHandle::SetPan(f32 pan, f32 fadeTime) { this->unknown9c.Set(pan, fadeTime); }

long SoundHandle::SetEnableEffect(int index, bool isEnable) {
  if (index > 1) {
    return -6;
  }
  m_effect[index].unknown00 = isEnable;
  return 0;
}

long SoundHandle::SetEffectVolume(int index, f32 volume, f32 fadeTime) {
  if (index > 1) {
    return -6;
  }
  m_effect[index].unknown04.Reset(volume);
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
  if (voice->m_streamController == nullptr) {
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
  if (voice->m_streamController == nullptr) {
    return -44;
  }
  if (!voice->m_streamController->m_waveSource.unknown50) {
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
  if (voice->m_streamController == nullptr) {
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
  if (voice->m_streamController == nullptr) {
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
  if (voice->m_streamController == nullptr) {
    return -44;
  }
  *buffer = &voice->m_streamController->m_streamBuffer;
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
  StreamController *stream = voice->m_streamController;
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
  if (voice->m_streamController == nullptr) {
    return -44;
  }
  voice->m_streamController->unknownf5 = isKeep;
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

template void mm::mtl::ObjectAllocator<ssd::SoundHandle>::destroy();
template void mm::mtl::ObjectAllocator<ssd::SoundHandle>::reserve(mm::mtl::IAllocator *, u32);
