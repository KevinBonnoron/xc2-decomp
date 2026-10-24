#include "ssd/ssd_behavior.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_sound_core.h"
#include "types.h"

namespace ssd {

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

int SystemCore::GetNumPlaySound() const { return m_numPlaySound; }

f32 SystemCore::GetSpeedOfSound() const { return m_speedOfSound; }

void SystemCore::SetSpeedOfSound(f32 speed) { m_speedOfSound = speed; }

f64 SystemCore::GetAudioCpuLoad() const {
  const CpuLoad &cpuLoad = unknown9f8[1 - unknowna20];
  if (cpuLoad.unknown08 != 0.0) {
    return cpuLoad.unknown00 / cpuLoad.unknown08;
  }
  return 0.0;
}

void SystemCore::LockAudio() const { unknown708.Lock(); }

void SystemCore::UnlockAudio() const { unknown708.Unlock(); }

const void *SystemCore::GetDebugInfo() const { return &debugInfo_; }

} // namespace ssd
