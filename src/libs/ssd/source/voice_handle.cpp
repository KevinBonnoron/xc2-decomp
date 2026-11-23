#include <math.h>

#include "nn/audio.h"
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_delegate.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_sound_listener.h"
#include "ssd/ssd_sound_param.h"
#include "ssd/ssd_stream_controller.h"
#include "ssd/ssd_voice_handle.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {

VoiceHandle::VoiceHandle()
    : Object(ObjectType::VOICE_HANDLE), unknown31(false), unknown32(false), unknown33(false), unknown34(false), unknown35(false), unknown36(false), unknown37(false), unknown38(false),
      unknown3b(false), unknown3c(false), unknown3d(true), unknown44(0), unknown48(0), unknown4c(0), unknown50(-1), unknown54(0), m_soundHandle(nullptr), m_soundEntry(nullptr), m_waveSource(nullptr),
      m_streamController(nullptr), unknown78(&VoiceHandle::NullBufferProcess), unknown88(0), unknown6b0(false), unknown6b1(false), unknown6b4(1.0f), unknown6b8(1.0f), unknown6bc(0.0f),
      unknown6c0(1.0f), unknown6f0(1.0f) {
  unknown668 = false;
  unknown669 = 0;
  unknown688 = 0;
  unknown690 = 0;
  unknown6a0.unknown00 = 0;
  unknown6a8 = 0;
  for (int i = 0; i < 8; i++) {
    unknown90[i].unknown00 = nn::audio::VoiceType();
    for (int j = 0; j < 3; j++) {
      unknown90[i].unknown98[j] = nullptr;
    }
  }
}

VoiceHandle::~VoiceHandle() {}

void VoiceHandle::AllocAdpcmSplitBuffer() {
  Allocator::Block *block = SoundMemory::allocator_->NewBufferImpl(0x10000, 1, 16);
  if (block != nullptr) {
    adpcmSplitBuffer_ = block->unknown08;
  } else {
    adpcmSplitBuffer_ = nullptr;
  }
}

void VoiceHandle::FreeAdpcmSplitBuffer() {
  if (adpcmSplitBuffer_ != nullptr) {
    Allocator *allocator = SoundMemory::allocator_;
    Allocator::Block *block = allocator->GetMemoryBlock(adpcmSplitBuffer_);
    allocator->DeleteBufferImpl(block);
    adpcmSplitBuffer_ = nullptr;
  }
}

void VoiceHandle::Init(int number) {
  unknown44 = 0;
  unknown670 = 24000;
  unknown4c = 0;
  unknown50 = number;
  unknown658 = nullptr;
  unknown678 = 12000;
  for (int i = 0; i < 8; i++) {
    unknown90[i].unknown00 = nn::audio::VoiceType();
    unknown90[i].unknown98[0] = nullptr;
    unknown90[i].unknownb0 = 0;
  }
  unknown660 = 0;
  unknown48 = 0;
  unknown54 = 0;
  m_soundHandle = nullptr;
  m_soundEntry = nullptr;
  unknown78 = &VoiceHandle::NullBufferProcess;
  unknown669 = 0;
  unknown6a8 = 0;
  unknown6a0.unknown00 = 0;
  unknown698 = 0;
  unknown690 = 0;
  unknown688 = 0;
  unknown680 = 0;
  unknown6d0.Reset(0.0f);
  m_streamController = nullptr;
}

void VoiceHandle::Quit() {
  if (unknown658 != nullptr) {
    static_cast<SystemCore *>(SoundCore::instance_)->FreeAudioDataBuffer(unknown658);
    unknown658 = nullptr;
  }
}

void VoiceHandle::DeleteHWVoice() {}

void VoiceHandle::FreeVoice() {
  unknown78 = &VoiceHandle::NullBufferProcess;
  unknown3a = true;
  if (m_soundHandle != nullptr) {
    m_soundHandle->unknown59 = false;
    m_soundHandle->unknown5a = true;
    m_soundHandle->m_multiCast.ExecuteDelegateImpl(reinterpret_cast<unsigned long long>(m_soundHandle), 1);
    m_soundHandle->m_soundEntry = nullptr;
    m_soundHandle->unknownf8 = 0;
    m_soundHandle = nullptr;
  }
  if (m_streamController != nullptr) {
    DeleteStream();
  }
  static_cast<SystemCore *>(SoundCore::instance_)->FreeVoiceHandle(this);
  if (unknown3b) {
    DeleteHWVoice();
    unknown3b = false;
  }
  Quit();
  if (m_waveSource != nullptr) {
    m_waveSource->unknown6c--;
    m_soundEntry = nullptr;
    m_waveSource = nullptr;
  }
}

Result VoiceHandle::AllocHWVoice() { return static_cast<Result>(0); }

Result VoiceHandle::ForceStop() {
  unknown36 = true;
  unknown37 = false;
  unknown32 = false;
  unknown44 = 9;
  if (m_soundHandle != nullptr) {
    m_soundHandle->unknownf8 = 0;
    m_soundHandle = nullptr;
  }
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::Pause(bool isPause, f32 fadeTime) {
  if (isPause) {
    unknown6d0.Set(0.0f, fadeTime);
    if (unknown44 == 13) {
      unknown44 = 11;
    }
    unknown34 = true;
    unknown35 = false;
    return static_cast<Result>(1);
  }
  if (!unknown34 && !unknown33) {
    return static_cast<Result>(0);
  }
  if (unknown32) {
    unknown6d0.Set(1.0f, fadeTime);
    unknown44 = 13;
    unknown34 = false;
    unknown35 = true;
    return static_cast<Result>(1);
  }
  return static_cast<Result>(0);
}

Result VoiceHandle::GetPlayPosition(u64 *position) const {
  u64 limit = unknown690 + unknown680;
  u64 current = unknown688;
  if (limit <= current) {
    current = limit;
  }
  u64 result = current;
  if (!m_waveSource->unknown50) {
    result = unknown698;
    if (current <= unknown698) {
      result = current;
    }
  }
  *position = result;
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::GetPlaySample(unsigned long long *sample) const {
  u64 position;
  Result result = GetPlayPosition(&position);
  if (result < 0) {
    return result;
  }
  u64 value = 0;
  if (m_waveSource->unknown34 == WaveSource::unknown001_3) {
    if (m_waveSource->unknown18) {
      value = position * 14 / 8;
    }
  } else if (m_waveSource->unknown18 && m_waveSource->unknown40 != 0) {
    value = static_cast<u32>(position / m_waveSource->unknown40);
  }
  *sample = value;
  return result;
}

Result VoiceHandle::GetPlayTime(f32 *time) const {
  u64 position;
  Result result = GetPlayPosition(&position);
  if (result >= 0) {
    WaveSource *source = m_waveSource;
    f32 value = 0.0f;
    if (source->unknown34 == WaveSource::unknown001_3) {
      bool hasData = source->unknown18;
      f32 sample = static_cast<f32>(position * 14 / 8);
      if (hasData == false) {
        sample = 0.0f;
      }
      value = sample / source->unknown2c;
    } else if (source->unknown18) {
      f32 sample = 0.0f;
      if (source->unknown40 != 0) {
        u64 count = static_cast<u32>(position / source->unknown40);
        sample = count;
      }
      value = sample / source->unknown2c;
    }
    *time = value;
  }
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::Start(f32 fadeTime, bool pregap) {
  if (SoundCore::instance_->unknown11) {
    unknown44 = 4;
    return static_cast<Result>(0);
  }
  if (m_streamController != nullptr && unknown44 == 2) {
    SetPlayPosition(0);
    m_streamController->ResetStream();
    unknown44 = 6;
  }
  unknown6d0.Set(1.0f, fadeTime);
  unknown35 = false;
  unknown36 = false;
  unknown37 = false;
  unknown38 = false;
  unknown39 = pregap;
  unknown31 = true;
  return static_cast<Result>(0);
}

Result VoiceHandle::SetPlayPosition(u64 position) {
  SoundCore *core = SoundCore::instance_;
  core->LockAudio();
  unknown6a0.unknown00 = static_cast<s32>(position);
  unknown669 = 1;
  core->UnlockAudio();
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::Stop(f32 fadeTime) {
  unknown6d0.Set(0.0f, fadeTime);
  if (m_streamController != nullptr) {
    m_streamController->unknownf5 = false;
  }
  unknown44 = 9;
  unknown36 = true;
  unknown37 = false;
  unknown32 = false;
  unknown3d = true;
  unknown33 = false;
  unknown34 = false;
  unknown35 = false;
  return static_cast<Result>(0);
}

Result VoiceHandle::SetPlaySample(unsigned long long sample) {
  SoundCore *core = SoundCore::instance_;
  core->LockAudio();
  unknown6a0.unknown00 = static_cast<s32>(sample);
  unknown669 = 2;
  core->UnlockAudio();
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::SetPlayTime(f32 time) {
  SoundCore *core = SoundCore::instance_;
  core->LockAudio();
  unknown6a0.unknown01 = time;
  unknown669 = 3;
  core->UnlockAudio();
  return static_cast<Result>(0);
}

Result VoiceHandle::GetFilePosition(u64 *position) const {
  *position = m_streamController != nullptr ? m_streamController->unknown218 : 0;
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::GetLoopTime(bool *isLoop, f32 *begin, f32 *end) {
  f32 sampleRate = m_waveSource->unknown2c;
  *isLoop = m_waveSource->unknown50;
  *begin = m_waveSource->unknown44 / sampleRate;
  *end = m_waveSource->unknown48 / sampleRate;
  return static_cast<Result>(0);
}

Result VoiceHandle::GetRemainLoopCount(int *count) const {
  if (count == nullptr || m_streamController == nullptr) {
    return static_cast<Result>(-6);
  }
  *count = m_streamController->unknown250;
  return static_cast<Result>(0);
}

Result VoiceHandle::SetRemainLoopCount(int count) {
  if (m_streamController == nullptr) {
    return static_cast<Result>(-6);
  }
  m_streamController->unknown250 = count;
  return static_cast<Result>(0);
}

Result VoiceHandle::GetVoiceQueueCount(int *count) const {
  if (count == nullptr) {
    return static_cast<Result>(-6);
  }
  *count = unknown88;
  return static_cast<Result>(0);
}

Result VoiceHandle::IsEmptyVoiceQueue(bool *isEmpty) {
  if (isEmpty == nullptr) {
    return static_cast<Result>(-6);
  }
  *isEmpty = unknown40;
  unknown40 = false;
  return static_cast<Result>(0);
}

Result VoiceHandle::IsEmptyStreamBuffer(bool *isEmpty) {
  if (isEmpty == nullptr) {
    return static_cast<Result>(-6);
  }
  *isEmpty = unknown3f;
  unknown3f = false;
  return static_cast<Result>(0);
}

void VoiceHandle::UpdateGameFrame(f32 deltaTime) {
  if (m_soundHandle == nullptr) {
    return;
  }
  SoundActor *actor = m_soundHandle->m_soundActor;
  if (actor == nullptr) {
    return;
  }
  unknown6c4 = 1.0f;
  if (!actor->unknown32) {
    return;
  }
  SoundActor3D *actor3D = static_cast<SoundActor3D *>(actor);
  // SoundListener::Vec3Transform is not const in the game, so the listener stored as const is cast back.
  SoundListener *listener = const_cast<SoundListener *>(actor3D->m_listener);
  if (listener == nullptr) {
    return;
  }
  const SoundEntry *entry = m_soundEntry;
  if (entry->m_soundParam.m_state.unknown03) {
    SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
    if (listener->IsEnableDoppler() && core->unknown4e4) {
      f32 x = actor3D->unknown5c.x - listener->unknown48.unknown00.x;
      f32 y = actor3D->unknown5c.y - listener->unknown48.unknown00.y;
      f32 z = actor3D->unknown5c.z - listener->unknown48.unknown00.z;
      f32 distance = sqrtf(x * x + y * y + z * z);
      if (distance != 0.0f) {
        f32 listenerSpeed = (x * listener->unknown48.unknown24.x + y * listener->unknown48.unknown24.y + z * listener->unknown48.unknown24.z) / distance;
        f32 sourceSpeed = (x * actor3D->unknown50.x + y * actor3D->unknown50.y + z * actor3D->unknown50.z) / distance;
        f32 speedOfSound = core->GetSpeedOfSound() * deltaTime;
        f32 limit = speedOfSound / unknown6c0;
        listenerSpeed = listenerSpeed < limit ? listenerSpeed : limit;
        sourceSpeed = sourceSpeed < limit ? sourceSpeed : limit;
        f32 pitch = (speedOfSound - unknown6c0 * listenerSpeed) / (speedOfSound - unknown6c0 * sourceSpeed);
        unknown6c4 = pitch;
        // Original game bug: a pitch out of range returns before the distance volume and the pan are updated.
        if (!(pitch <= 10000.0f && pitch >= 0.0001)) {
          return;
        }
        f32 result;
        if (pitch <= 0.0001f) {
          result = 0.0001f;
        } else if (pitch >= 10000.0f) {
          result = 10000.0f;
        } else {
          result = pitch;
        }
        unknown6c4 = result;
      }
    }
  }
  if (entry->m_soundParam.m_state.unknown01) {
    Vec3 listenerPosition = actor3D->m_listener->unknown18.unknown00;
    f32 x = actor3D->unknown5c.x - listenerPosition.x;
    f32 y = actor3D->unknown5c.y - listenerPosition.y;
    f32 z = actor3D->unknown5c.z - listenerPosition.z;
    f32 distance = sqrtf(x * x + y * y + z * z);
    f32 volume = unknown006(distance, entry->m_soundParam.m_surround.unknown00, unknown6c8, entry->m_soundParam.m_surround.unknown08, unknown6cc);
    f32 result;
    if (volume <= unknown6cc) {
      result = unknown6cc;
    } else if (volume >= unknown6c8) {
      result = unknown6c8;
    } else {
      result = volume;
    }
    unknown6f0 = result;
  }
  if (entry->m_soundParam.m_state.unknown02) {
    listener->Vec3Transform(&actor3D->unknown5c, &m_vec3);
    f32 x = m_vec3.x;
    f32 z = m_vec3.z;
    f32 angle = acosf(x / sqrtf(x * x + z * z)) * 180.0f / 3.1415927f;
    if (z < 0.0f) {
      angle = 360.0f - angle;
    }
    unknown6f4 = angle;
  }
}

template List<VoiceHandle> *List<VoiceHandle>::Delete();
template List<VoiceHandle>::Node::~Node();

} // namespace ssd
