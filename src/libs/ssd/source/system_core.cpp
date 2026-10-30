#include "nn/os.h"
#include "ssd/ssd_array.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_stream_controller.h"
#include "ssd/ssd_voice_handle.h"
#include "types.h"

namespace ssd {

void SystemCore::AudioThreadEntry(SystemCore *core, void *argument) { core->AudioThreadImpl(); }

void SystemCore::StreamThreadEntry(SystemCore *core, void *argument) { core->StreamThreadImpl(); }

void SystemCore::SetMasterVolume(f32 volume, f32 fadeTime) { unknown308.Set(this, &SystemCore::MasterVolumeBehavior, volume, fadeTime); }

void SystemCore::MasterVolumeBehavior(f32 volume) {}

void SystemCore::SetMasterPitch(f32 pitch, f32 fadeTime) { unknown350.Set(this, &SystemCore::MasterPitchBehavior, pitch, fadeTime); }

void SystemCore::MasterPitchBehavior(f32 pitch) {}

void SystemCore::AddBehavior(BehaviorControl *behavior) {
  unknown708.Lock();
  unknown978.PushBack(behavior);
  unknown708.Unlock();
}

OutputMode::Type SystemCore::GetOutputMode() const { return m_outputMode; }

void SystemCore::SetOutputMode(OutputMode::Type mode) { m_outputMode = mode; }

f32 SystemCore::GetMasterVolume() const { return unknown308.unknown18; }

f32 SystemCore::GetMasterPitch() const { return unknown350.unknown18; }

int SystemCore::GetNumPlaySound() const { return unknown3a0.count; }

f32 SystemCore::GetSpeedOfSound() const { return m_speedOfSound; }

void SystemCore::SetSpeedOfSound(f32 speed) { m_speedOfSound = speed; }

f64 SystemCore::GetAudioCpuLoad() const {
  const unknown002 &cpuLoad = unknown9f8[1 - unknowna20];
  if (cpuLoad.unknown08 != 0.0) {
    return cpuLoad.unknown00 / cpuLoad.unknown08;
  }
  return 0.0;
}

void SystemCore::LockAudio() const { unknown708.Lock(); }

void SystemCore::UnlockAudio() const { unknown708.Unlock(); }

void SystemCore::AddStreamController(StreamController *controller) {
  unknown708.Lock();
  unknown950.PushBack(controller);
  unknown708.Unlock();
}

void SystemCore::RemoveStreamController(StreamController *controller) {
  unknown708.Lock();
  unknown950.unknown001(controller);
  unknown708.Unlock();
}

void SystemCore::AddBank(SoundBank *bank) {
  unknown708.Lock();
  unknown418.PushBack(bank);
  set_result(static_cast<Result>(0));
  unknown708.Unlock();
}

void SystemCore::StopSound(f32 fadeTime) {
  set_result(static_cast<Result>(0));
  unknown708.Lock();
  const VoiceHandle *end = unknown3a0.unknown003();
  for (VoiceHandle *it = unknown3a0.unknown002(); it != end; it = List<VoiceHandle>::unknown004(it)) {
    if (it->unknown58 != nullptr) {
      it->unknown58->Stop(fadeTime);
    }
  }
  unknown708.Unlock();
}

void SystemCore::RemoveBank(SoundBank *bank) {
  unknown708.Lock();
  unknown418.unknown001(bank);
  set_result(static_cast<Result>(0));
  unknown708.Unlock();
}

void SystemCore::PauseSound(bool isPause, f32 fadeTime) {
  set_result(static_cast<Result>(0));
  unknown708.Lock();
  const VoiceHandle *end = unknown3a0.unknown003();
  for (VoiceHandle *it = unknown3a0.unknown002(); it != end; it = List<VoiceHandle>::unknown004(it)) {
    if (it->unknown58 != nullptr) {
      it->unknown58->Pause(isPause, fadeTime);
    }
  }
  unknown708.Unlock();
}

void SystemCore::StopBank(SoundBank *bank, f32 fadeTime) {
  unknown708.Lock();
  VoiceHandle *it = unknown3a0.unknown002();
  while (it != unknown3a0.unknown003()) {
    if (it->unknown60->unknownd0 == bank) {
      it->unknown58->Stop(fadeTime);
    }
    it = List<VoiceHandle>::unknown004(it);
  }
  set_result(static_cast<Result>(0));
  unknown708.Unlock();
}

bool SystemCore::IsPlayActor(const SoundActor *actor) const {
  set_result(static_cast<Result>(0));
  unknown708.Lock();
  bool isPlay = false;
  VoiceHandle *it = unknown3a0.unknown002();
  while (it != unknown3a0.unknown003()) {
    if (it->unknown58 != nullptr && it->unknown58->unknown38 == actor) {
      isPlay = true;
      break;
    }
    it = List<VoiceHandle>::unknown004(it);
  }
  unknown708.Unlock();
  return isPlay;
}

void SystemCore::StopActor(SoundActor *actor, f32 fadeTime) {
  set_result(static_cast<Result>(0));
  unknown708.Lock();
  const VoiceHandle *end = unknown3a0.unknown003();
  for (VoiceHandle *it = unknown3a0.unknown002(); it != end; it = List<VoiceHandle>::unknown004(it)) {
    SoundHandle *handle = it->unknown58;
    if (handle != nullptr && handle->unknown38 == actor) {
      handle->Stop(fadeTime);
    }
  }
  unknown708.Unlock();
}

void SystemCore::PauseActor(SoundActor *actor, bool isPause, f32 fadeTime) {
  set_result(static_cast<Result>(0));
  unknown708.Lock();
  const VoiceHandle *end = unknown3a0.unknown003();
  for (VoiceHandle *it = unknown3a0.unknown002(); it != end; it = List<VoiceHandle>::unknown004(it)) {
    SoundHandle *handle = it->unknown58;
    if (handle != nullptr && handle->unknown38 == actor) {
      handle->Pause(isPause, fadeTime);
    }
  }
  unknown708.Unlock();
}

int SystemCore::CountPlaySoundHandleActor(const SoundActor *actor) const {
  set_result(static_cast<Result>(0));
  unknown708.Lock();
  int count = 0;
  VoiceHandle *it = unknown3a0.unknown002();
  while (it != unknown3a0.unknown003()) {
    if (it->unknown58 != nullptr && it->unknown58->unknown38 == actor) {
      count++;
    }
    it = List<VoiceHandle>::unknown004(it);
  }
  unknown708.Unlock();
  return count;
}

SoundHandle *SystemCore::GetPlaySoundHandle(const SoundActor *actor, int index) const {
  set_result(static_cast<Result>(0));
  unknown708.Lock();
  SoundHandle *handle = nullptr;
  VoiceHandle *it = unknown3a0.unknown002();
  while (it != unknown3a0.unknown003()) {
    if (index == 0) {
      handle = it->unknown58;
      if (handle != nullptr && handle->unknown38 == actor) {
        break;
      }
    }
    handle = nullptr;
    it = List<VoiceHandle>::unknown004(it);
  }
  unknown708.Unlock();
  return handle;
}

int SystemCore::GetPlaySoundHandleFromActor(const SoundActor *actor, Array<SoundHandle *> *handles) const {
  set_result(static_cast<Result>(0));
  unknown708.Lock();
  VoiceHandle *it = unknown3a0.unknown002();
  while (it != unknown3a0.unknown003()) {
    SoundHandle *handle = it->unknown58;
    if (handle != nullptr && handle->unknown38 == actor) {
      int count = handles->unknown08;
      if (handles->unknown0c <= count) {
        handles->SetArraySize(handles->unknown0c + 16);
        count = handles->unknown08;
      }
      handles->unknown10[count] = handle;
      handles->unknown08++;
    }
    it = List<VoiceHandle>::unknown004(it);
  }
  int count = handles->unknown08;
  unknown708.Unlock();
  return count;
}

Result SystemCore::GetSoundActorListByCategoty(int category, Array<SoundActor *> *actors) const {
  unknown708.Lock();
  VoiceHandle *it = unknown3a0.unknown002();
  while (it != unknown3a0.unknown003()) {
    SoundHandle *handle = it->unknown58;
    if (handle != nullptr && handle->unknown38 != nullptr) {
      int count = actors->unknown08;
      if (actors->unknown0c <= count) {
        actors->SetArraySize(actors->unknown0c + 16);
        count = actors->unknown08;
      }
      actors->unknown10[count] = handle->unknown38;
      actors->unknown08++;
    }
    it = List<VoiceHandle>::unknown004(it);
  }
  Result result = set_result(static_cast<Result>(0));
  unknown708.Unlock();
  return result;
}

Result SystemCore::GetSoundHandleListByCategoty(int category, Array<SoundHandle *> *handles) const {
  unknown708.Lock();
  VoiceHandle *it = unknown3a0.unknown002();
  if (category < 0) {
    while (it != unknown3a0.unknown003()) {
      SoundHandle *handle = it->unknown58;
      if (handle != nullptr) {
        int count = handles->unknown08;
        if (handles->unknown0c <= count) {
          handles->SetArraySize(handles->unknown0c + 16);
          count = handles->unknown08;
        }
        handles->unknown10[count] = handle;
        handles->unknown08++;
      }
      it = List<VoiceHandle>::unknown004(it);
    }
  } else {
    while (it != unknown3a0.unknown003()) {
      SoundHandle *handle = it->unknown58;
      if (handle != nullptr && handle->unknown50.unknown00 == category) {
        int count = handles->unknown08;
        if (handles->unknown0c <= count) {
          handles->SetArraySize(handles->unknown0c + 16);
          count = handles->unknown08;
        }
        handles->unknown10[count] = handle;
        handles->unknown08++;
      }
      it = List<VoiceHandle>::unknown004(it);
    }
  }
  Result result = set_result(static_cast<Result>(0));
  unknown708.Unlock();
  return result;
}

Result SystemCore::AllocVoiceHandle(int, VoiceHandle **voice) {
  VoiceHandle *allocated = unknown3c8.unknown002();
  VoiceHandle *result = nullptr;
  if (unknown3c8.unknown003() != allocated) {
    unknown3c8.unknown001(allocated);
    unknown3a0.PushBack(allocated);
    int id = unknown39c;
    allocated->unknown44 = 5;
    allocated->unknown30 = true;
    allocated->unknown54 = allocated->unknown50 + id * 0x100;
    if (unknown39c > 0xffffe) {
      unknown39c = 1;
    } else {
      unknown39c++;
    }
    allocated->unknown68 = nullptr;
    result = allocated;
  }
  *voice = result;
  return set_result(static_cast<Result>(0));
}

void SystemCore::FreeVoiceHandle(VoiceHandle *voice) {
  unknown3a0.unknown001(voice);
  unknown3c8.PushBack(voice);
  voice->unknown44 = 0;
  voice->unknown58 = nullptr;
  voice->unknown54 = 0;
  set_result(static_cast<Result>(0));
}

void SystemCore::ConnectActor(SoundActor *actor) {
  unknown708.Lock();
  unknown440.PushBack(actor);
  actor->unknown31 = true;
  unknown708.Unlock();
}

void SystemCore::DisconnectActor(SoundActor *actor) {
  unknown708.Lock();
  VoiceHandle *it = unknown3a0.unknown002();
  while (it != unknown3a0.unknown003()) {
    SoundHandle *handle = it->unknown58;
    if (handle != nullptr && handle->unknown38 == actor) {
      handle->unknown38 = nullptr;
    }
    it = List<VoiceHandle>::unknown004(it);
  }
  if (actor->unknown31) {
    actor->unknown31 = false;
    unknown440.unknown001(actor);
  }
  unknown708.Unlock();
}

SoundBank *SystemCore::GetBank(int id) const {
  unknown708.Lock();
  SoundBank *bank = unknown418.unknown002();
  while (bank != unknown418.unknown003()) {
    if (bank->GetNumber() == id) {
      break;
    }
    bank = List<SoundBank>::unknown004(bank);
  }
  if (bank == unknown418.unknown003()) {
    set_result(static_cast<Result>(0));
    bank = nullptr;
  }
  unknown708.Unlock();
  return bank;
}

VoiceHandle *SystemCore::GetVoiceHandle(u32 id) const {
  set_result(static_cast<Result>(0));
  VoiceHandle *voice = nullptr;
  if (id != 0) {
    VoiceHandle *candidate = &unknown3f0[id & 0xff];
    if (candidate->unknown54 == id) {
      voice = candidate;
    }
  }
  return voice;
}

Result SystemCore::GetSoundEffectList(int bus, SoundEffecter **effecters, int *num) {
  unknown708.Lock();
  int count = 0;
  for (int i = 0; i < 2; i++) {
    if (unknown1f0[i].unknown10 != nullptr && count < bus) {
      effecters[i] = unknown1f0[i].unknown10;
      count++;
    }
  }
  unknown708.Unlock();
  return static_cast<Result>(0);
}

bool SystemCore::IsActiveEffect(u8 bus) {
  if (bus > 1) {
    return false;
  }
  if (unknown1f0[bus].unknown10 != nullptr) {
    return true;
  }
  if (unknown1f0[bus].unknown00) {
    return true;
  }
  return unknown1f0[bus].unknown01;
}

Result SystemCore::SetCategory(const SoundCategory &category) {
  if (category.unknown08.unknown00 == 0) {
    return static_cast<Result>(-1);
  }
  for (int i = 1; i < unknown468.unknown08; i++) {
    if (unknown468.unknown10[i].unknown08.unknown00 == category.unknown08.unknown00) {
      unknown468.unknown10[i].unknown08 = category.unknown08;
      ChangeCategoryEvent(category);
      return set_result(static_cast<Result>(0));
    }
  }
  unknown708.Lock();
  int count = unknown468.unknown08;
  if (unknown468.unknown0c <= count) {
    unknown468.SetSize(unknown468.unknown0c + 16);
  }
  unknown468.unknown10[unknown468.unknown08] = category;
  unknown468.unknown08++;
  Result result = set_result(static_cast<Result>(0));
  unknown708.Unlock();
  return result;
}

SoundCategory *SystemCore::GetCategory(int id) const {
  if (id != 0) {
    SoundCategory *end = unknown468.unknown10 + unknown468.unknown08;
    for (SoundCategory *it = unknown468.unknown10; it != end; it++) {
      if (it->unknown08.unknown00 == id) {
        return it;
      }
    }
  }
  return unknown468.unknown10;
}

void SystemCore::ChangeCategoryEvent(const SoundCategory &category) {
  unknown708.Lock();
  VoiceHandle *it = unknown3a0.unknown002();
  while (it != unknown3a0.unknown003()) {
    SoundHandle *handle = it->unknown58;
    if (handle != nullptr && handle->unknown50.unknown00 == category.unknown08.unknown00) {
      handle->unknown50 = category.unknown08;
    }
    it = List<VoiceHandle>::unknown004(it);
  }
  unknown708.Unlock();
}

Result SystemCore::AddSoundEffecter(u8 bus, SoundEffecter *effecter) {
  unknown708.Lock();
  Result result = InitEffect(bus, effecter);
  unknown708.Unlock();
  return result;
}

Result SystemCore::RemoveSoundEffecter(SoundEffecter *effecter) {
  unknown708.Lock();
  Result result = QuitEffect(effecter);
  unknown708.Unlock();
  return result;
}

const void *SystemCore::GetDebugInfo() const { return &debugInfo_; }

void SystemCore::AudioThreadImpl() {
  f64 time = GetSystemTime();
  unknown2a8 = time;
  unknowna18 = time;
  while (!unknown4ea) {
    nn::os::WaitSystemEvent(&unknown138.m_SystemEventType);
    unknown280 = unknown278 / unknown290;
    unknown2a0 = unknown290;
    AudioFrameProcess();
    unknown278++;
  }
}

template class BehaviorInstance<SystemCore>;

template List<BehaviorControl>::Node::~Node();

} // namespace ssd
