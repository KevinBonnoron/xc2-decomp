#pragma once
#include <stddef.h>

#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {
class SoundBank;
class SoundCategory;
class SoundEffecter;
class SoundListener;

class SoundCore {
public:
  virtual int GetOutputMode() const = 0;
  virtual Result SetOutputMode(int mode) = 0;
  virtual f32 GetMasterVolume() const = 0;
  virtual Result SetMasterVolume(f32 volume, f32 fadeTime) = 0;
  virtual f32 GetMasterPitch() const = 0;
  virtual Result SetMasterPitch(f32 pitch, f32 fadeTime) = 0;
  virtual Result AddSoundListener(SoundListener *listener) = 0;
  virtual Result RemoveSoundListener(SoundListener *listener) = 0;
  virtual Result GetSoundEffectList(int bus, SoundEffecter **effecters, int *num) = 0;
  virtual Result AddSoundEffecter(u8 bus, SoundEffecter *effecter) = 0;
  virtual Result RemoveSoundEffecter(SoundEffecter *effecter) = 0;
  virtual bool IsActiveEffect(u8 bus) = 0;
  virtual int GetNumPlaySound() const = 0;
  virtual f32 GetSpeedOfSound() const = 0;
  virtual Result SetSpeedOfSound(f32 speed) = 0;
  virtual f32 GetAudioCpuLoad() const = 0;
  virtual void LockAudio() const = 0;
  virtual void UnlockAudio() const = 0;
  virtual void *GetPlatformDataImpl(const char *name) = 0;
  virtual ~SoundCore();
  virtual const void *GetDebugInfo() const = 0;

  static bool IsInstance();
  static SoundCore *GetInstance();
  void GetVersion(int *major, int *minor, int *revision, int *build, char16_t *configuration);
  bool IsInit();
  Result Quit(bool isForce);
  Result GetCategory(int id, SoundCategory *category) const;
  Result SetCategory(const SoundCategory &category);
  Result ResetCategory(int id);
  Result GetSoundBankList(SoundBank **banks, size_t num) const;
  Result GetSoundBank(int id, SoundBank **bank) const;
  Result NumSoundBank(int *num) const;
  Result NumSoundActor(int *num) const;
  void UpdateGameFrame(f32 deltaTime);
  Result StopSound(f32 fadeTime);
  Result PauseSound(bool isPause, f32 fadeTime);
  u64 GetGameFrameCounter() const;
  f64 GetAudioTimerCounter() const;
  u64 GetAudioFrameCounter() const;
  u64 GetAudioProcessCounter() const;
  int GetInstanceAllocCount() const;
  int GetBufferAllocCount() const;
  int GetStreamAllocCount() const;
  int GetVoiceHandleCount() const;
  int GetHWAllocVoiceCount() const;
  int GetAllocMemoryCount() const;

  static SoundCore *instance_;

  u8 _08[0x10 - 0x08];
  bool isInit;
};

static_assert(offsetof(SoundCore, isInit) == 0x10, "");

class SystemCore : public SoundCore {
public:
  Result Quit();
  Result StopSound(f32 fadeTime);
  Result PauseSound(bool isPause, f32 fadeTime);
  SoundBank *GetBank(int id) const;
  Result GetBankList(SoundBank **banks, size_t num) const;
  Result SetCategory(const SoundCategory &category);
  Result ResetCategory(int id);
  Result GetCategory(int id, SoundCategory *category) const;
  void UpdateGameFrame(f32 deltaTime);

  u8 _011[0x270 - 0x011];
  u64 gameFrameCounter;
  u64 audioFrameCounter;
  f64 audioTimerCounter;
  u8 _288[0x3c0 - 0x288];
  int voiceHandleCount;
  u8 _3c4[0x410 - 0x3c4];
  int hwAllocVoiceCount;
  u8 _414[0x438 - 0x414];
  int numSoundBank;
  u8 _43c[0x460 - 0x43c];
  int numSoundActor;
};

static_assert(offsetof(SystemCore, gameFrameCounter) == 0x270, "");
static_assert(offsetof(SystemCore, voiceHandleCount) == 0x3c0, "");
static_assert(offsetof(SystemCore, hwAllocVoiceCount) == 0x410, "");
static_assert(offsetof(SystemCore, numSoundBank) == 0x438, "");
static_assert(offsetof(SystemCore, numSoundActor) == 0x460, "");

} // namespace ssd
