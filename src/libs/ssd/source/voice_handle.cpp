#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_stream_controller.h"
#include "ssd/ssd_voice_handle.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {

void VoiceHandle::DeleteHWVoice() {}

Result VoiceHandle::AllocHWVoice() { return static_cast<Result>(0); }

Result VoiceHandle::ForceStop() {
  unknown36 = true;
  unknown37 = false;
  unknown32 = false;
  unknown44 = 9;
  if (unknown58 != nullptr) {
    unknown58->unknownf8 = 0;
    unknown58 = nullptr;
  }
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::GetPlayPosition(u64 *position) const {
  u64 limit = unknown690 + unknown680;
  u64 current = unknown688;
  if (limit <= current) {
    current = limit;
  }
  u64 result = current;
  if (!unknown68->unknown50) {
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
  if (unknown68->unknown34 == WaveSource::unknown001_3) {
    if (unknown68->unknown18) {
      value = position * 14 / 8;
    }
  } else if (unknown68->unknown18 && unknown68->unknown40 != 0) {
    value = static_cast<u32>(position / unknown68->unknown40);
  }
  *sample = value;
  return result;
}

Result VoiceHandle::SetPlayPosition(u64 position) {
  SoundCore *core = SoundCore::instance_;
  core->LockAudio();
  unknown6a0.unknown00 = static_cast<s32>(position);
  unknown669 = 1;
  core->UnlockAudio();
  return set_result(static_cast<Result>(0));
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
  *position = unknown70 != nullptr ? unknown70->unknown218 : 0;
  return set_result(static_cast<Result>(0));
}

Result VoiceHandle::GetLoopTime(bool *isLoop, f32 *begin, f32 *end) {
  f32 sampleRate = unknown68->unknown2c;
  *isLoop = unknown68->unknown50;
  *begin = unknown68->unknown44 / sampleRate;
  *end = unknown68->unknown48 / sampleRate;
  return static_cast<Result>(0);
}

Result VoiceHandle::GetRemainLoopCount(int *count) const {
  if (count == nullptr || unknown70 == nullptr) {
    return static_cast<Result>(-6);
  }
  *count = unknown70->unknown250;
  return static_cast<Result>(0);
}

Result VoiceHandle::SetRemainLoopCount(int count) {
  if (unknown70 == nullptr) {
    return static_cast<Result>(-6);
  }
  unknown70->unknown250 = count;
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

void VoiceHandle::UpdateAudioFrame(f32 deltaTime) {
  if (unknown70 != nullptr) {
    UpdateAudioStream(deltaTime);
  } else {
    UpdateAudioInternal(deltaTime);
  }
}

void VoiceHandle::NullBufferProcess() {}

void VoiceHandle::LooppingBufferProcess() {}

void VoiceHandle::AddLooppingBuffer() { unknown88++; }

template List<VoiceHandle> *List<VoiceHandle>::Delete();
template List<VoiceHandle>::Node::~Node();

} // namespace ssd
