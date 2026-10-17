#include "ssd/ssd_behavior.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_sound_core.h"
#include "types.h"

namespace ssd {

void SystemCore::StreamThreadEntry(SystemCore *core, void *argument) { core->StreamThreadImpl(); }

void SystemCore::SetMasterVolume(f32 volume, f32 fadeTime) { masterVolume.Set(this, &SystemCore::MasterVolumeBehavior, volume, fadeTime); }

void SystemCore::MasterVolumeBehavior(f32 volume) {}

void SystemCore::SetMasterPitch(f32 pitch, f32 fadeTime) { masterPitch.Set(this, &SystemCore::MasterPitchBehavior, pitch, fadeTime); }

void SystemCore::MasterPitchBehavior(f32 pitch) {}

void SystemCore::AddBehavior(BehaviorControl *behavior) {
  audioMutex.Lock();
  behaviors.PushBack(behavior);
  audioMutex.Unlock();
}

OutputMode::Type SystemCore::GetOutputMode() const { return outputMode; }

void SystemCore::SetOutputMode(OutputMode::Type mode) { outputMode = mode; }

f32 SystemCore::GetMasterVolume() const { return masterVolume.value; }

f32 SystemCore::GetMasterPitch() const { return masterPitch.value; }

int SystemCore::GetNumPlaySound() const { return voiceHandleCount; }

f32 SystemCore::GetSpeedOfSound() const { return speedOfSound; }

void SystemCore::SetSpeedOfSound(f32 speed) { speedOfSound = speed; }

f64 SystemCore::GetAudioCpuLoad() const {
  const CpuLoad &cpuLoad = cpuLoads[1 - cpuLoadIndex];
  if (cpuLoad.frameTime != 0.0) {
    return cpuLoad.processTime / cpuLoad.frameTime;
  }
  return 0.0;
}

void SystemCore::LockAudio() const { audioMutex.Lock(); }

void SystemCore::UnlockAudio() const { audioMutex.Unlock(); }

const void *SystemCore::GetDebugInfo() const { return &debugInfo_; }

} // namespace ssd
