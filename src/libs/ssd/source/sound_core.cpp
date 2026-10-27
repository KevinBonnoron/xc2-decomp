#include <stddef.h>

#include "ssd/ssd_behavior.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_memory_manager.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound_core.h"
#include "types.h"

namespace ssd {
class SoundBank;
class SoundCategory;

bool SoundCore::IsInstance() { return instance_ != nullptr; }

SoundCore *SoundCore::GetInstance() { return instance_; }

SoundCore::~SoundCore() {}

void SoundCore::GetVersion(int *major, int *minor, int *revision, int *build, char16_t *configuration) {
  if (major != nullptr) {
    *major = 5;
  }
  if (minor != nullptr) {
    *minor = 1;
  }
  if (revision != nullptr) {
    *revision = 0;
  }
  if (build != nullptr) {
    *build = 1457;
  }
  if (configuration != nullptr) {
    configuration[0] = u'R';
    configuration[1] = u'e';
    configuration[2] = u'l';
    configuration[3] = u'e';
    configuration[4] = u'a';
    configuration[5] = u's';
    configuration[6] = u'e';
    configuration[7] = u'\0';
  }
}

bool SoundCore::IsInit() { return m_init; }

Result SoundCore::Quit(bool isForce) {
  if (!m_init) {
    return static_cast<Result>(-1);
  }
  m_init = false;
  return static_cast<SystemCore *>(this)->Quit();
}

Result SoundCore::GetCategory(int id, SoundCategory *category) const { return static_cast<const SystemCore *>(this)->GetCategory(id, category); }

Result SoundCore::SetCategory(const SoundCategory &category) { return static_cast<SystemCore *>(this)->SetCategory(category); }

Result SoundCore::ResetCategory(int id) { return static_cast<SystemCore *>(this)->ResetCategory(id); }

Result SoundCore::GetSoundBankList(SoundBank **banks, size_t num) const {
  if (banks == nullptr) {
    return static_cast<Result>(-6);
  }
  return static_cast<const SystemCore *>(this)->GetBankList(banks, num);
}

Result SoundCore::GetSoundBank(int id, SoundBank **bank) const {
  if (bank == nullptr) {
    return static_cast<Result>(-6);
  }
  SoundBank *found = static_cast<const SystemCore *>(this)->GetBank(id);
  *bank = found;
  return set_result(static_cast<Result>(found != nullptr ? 0 : -4));
}

Result SoundCore::NumSoundBank(int *num) const {
  if (num == nullptr) {
    return static_cast<Result>(-6);
  }
  *num = static_cast<const SystemCore *>(this)->unknown418.count;
  return set_result(static_cast<Result>(0));
}

Result SoundCore::NumSoundActor(int *num) const {
  if (num == nullptr) {
    return static_cast<Result>(-6);
  }
  *num = static_cast<const SystemCore *>(this)->unknown440.count;
  return set_result(static_cast<Result>(0));
}

void SoundCore::UpdateGameFrame(f32 deltaTime) {
  if (m_init) {
    static_cast<SystemCore *>(this)->UpdateGameFrame(deltaTime);
  }
}

Result SoundCore::StopSound(f32 fadeTime) { return static_cast<SystemCore *>(this)->StopSound(fadeTime); }

Result SoundCore::PauseSound(bool isPause, f32 fadeTime) { return static_cast<SystemCore *>(this)->PauseSound(isPause, fadeTime); }

u64 SoundCore::GetGameFrameCounter() const { return static_cast<const SystemCore *>(this)->unknown270; }

f64 SoundCore::GetAudioTimerCounter() const { return static_cast<const SystemCore *>(this)->unknown280; }

u64 SoundCore::GetAudioFrameCounter() const { return static_cast<const SystemCore *>(this)->unknown278; }

u64 SoundCore::GetAudioProcessCounter() const { return static_cast<const SystemCore *>(this)->unknown278; }

int SoundCore::GetInstanceAllocCount() const { return MemoryManager::memoryManager_.unknown94; }

int SoundCore::GetBufferAllocCount() const { return MemoryManager::memoryManager_.unknown98; }

int SoundCore::GetStreamAllocCount() const { return MemoryManager::memoryManager_.unknown9c; }

int SoundCore::GetVoiceHandleCount() const { return static_cast<const SystemCore *>(this)->unknown3a0.count; }

int SoundCore::GetHWAllocVoiceCount() const { return static_cast<const SystemCore *>(this)->unknown410; }

int SoundCore::GetAllocMemoryCount() const { return MemoryManager::memoryManager_.unknown38.count; }

u32 SoundCore::GetErrorLogFlag() const { return Debug::log_.m_errorLogFlag; }

u32 SoundCore::GetWarningLogFlag() const { return Debug::log_.m_warningLogFlag; }

LogTimeStamp::Type SoundCore::GetLogTimeStampType() const { return Debug::log_.m_logTimeStampType; }

} // namespace ssd
