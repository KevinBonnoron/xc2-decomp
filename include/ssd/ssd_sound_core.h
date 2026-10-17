#pragma once
#include <stddef.h>

#include "ssd/ssd_behavior.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {
class SoundBank;
class SoundCategory;
class SoundEffecter;
class SoundActor;
class SoundHandle;
class SoundListener;
class VoiceHandle;

struct OutputMode {
  enum Type {};
};

class SoundCore {
public:
  virtual OutputMode::Type GetOutputMode() const = 0;
  virtual void SetOutputMode(OutputMode::Type mode) = 0;
  virtual f32 GetMasterVolume() const = 0;
  virtual void SetMasterVolume(f32 volume, f32 fadeTime) = 0;
  virtual f32 GetMasterPitch() const = 0;
  virtual void SetMasterPitch(f32 pitch, f32 fadeTime) = 0;
  virtual Result AddSoundListener(SoundListener *listener) = 0;
  virtual Result RemoveSoundListener(SoundListener *listener) = 0;
  virtual Result GetSoundEffectList(int bus, SoundEffecter **effecters, int *num) = 0;
  virtual Result AddSoundEffecter(u8 bus, SoundEffecter *effecter) = 0;
  virtual Result RemoveSoundEffecter(SoundEffecter *effecter) = 0;
  virtual bool IsActiveEffect(u8 bus) = 0;
  virtual int GetNumPlaySound() const = 0;
  virtual f32 GetSpeedOfSound() const = 0;
  virtual void SetSpeedOfSound(f32 speed) = 0;
  virtual f64 GetAudioCpuLoad() const = 0;
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
  struct DebugInfo;

  struct CpuLoad {
    f64 processTime;
    f64 frameTime;
  };

  ~SystemCore() override;
  static void StreamThreadEntry(SystemCore *core, void *argument);
  void SetMasterVolume(f32 volume, f32 fadeTime) override;
  void MasterVolumeBehavior(f32 volume);
  void SetMasterPitch(f32 pitch, f32 fadeTime) override;
  void MasterPitchBehavior(f32 pitch);
  void AddBehavior(BehaviorControl *behavior);
  OutputMode::Type GetOutputMode() const override;
  void SetOutputMode(OutputMode::Type mode) override;
  VoiceHandle *GetVoiceHandle(u32 id) const;
  void StreamThreadImpl();
  f32 GetMasterVolume() const override;
  f32 GetMasterPitch() const override;
  int GetNumPlaySound() const override;
  f32 GetSpeedOfSound() const override;
  void SetSpeedOfSound(f32 speed) override;
  f64 GetAudioCpuLoad() const override;
  void LockAudio() const override;
  void UnlockAudio() const override;
  const void *GetDebugInfo() const override;
  Result Quit();
  Result StopSound(f32 fadeTime);
  Result PauseSound(bool isPause, f32 fadeTime);
  SoundBank *GetBank(int id) const;
  Result GetBankList(SoundBank **banks, size_t num) const;
  Result SetCategory(const SoundCategory &category);
  Result ResetCategory(int id);
  Result GetCategory(int id, SoundCategory *category) const;
  bool IsPlayActor(const SoundActor *actor) const;
  void StopActor(SoundActor *actor, f32 fadeTime);
  void PauseActor(SoundActor *actor, bool isPause, f32 fadeTime);
  int CountPlaySoundHandleActor(const SoundActor *actor) const;
  SoundHandle *GetPlaySoundHandle(const SoundActor *actor, int index) const;
  void ConnectActor(SoundActor *actor);
  void DisconnectActor(SoundActor *actor);
  void UpdateGameFrame(f32 deltaTime);

  u8 _011[0x270 - 0x011];
  u64 gameFrameCounter;
  u64 audioFrameCounter;
  f64 audioTimerCounter;
  u8 _288[0x300 - 0x288];
  OutputMode::Type outputMode;
  u8 _304[0x308 - 0x304];
  BehaviorInstance<SystemCore> masterVolume;
  BehaviorInstance<SystemCore> masterPitch;
  u8 _398[0x3c0 - 0x398];
  int voiceHandleCount;
  u8 _3c4[0x410 - 0x3c4];
  int hwAllocVoiceCount;
  u8 _414[0x438 - 0x414];
  int numSoundBank;
  u8 _43c[0x460 - 0x43c];
  int numSoundActor;
  u8 _464[0x4e0 - 0x464];
  f32 speedOfSound;
  u8 _4e4[0x708 - 0x4e4];
  mutable Mutex audioMutex;
  u8 _730[0x978 - 0x730];
  List<BehaviorControl> behaviors;
  u8 _9a0[0x9f8 - 0x9a0];
  CpuLoad cpuLoads[2];
  f64 lastCpuLoadTime;
  s32 cpuLoadIndex;

  static DebugInfo debugInfo_;
};

static_assert(offsetof(SystemCore, gameFrameCounter) == 0x270, "");
static_assert(offsetof(SystemCore, voiceHandleCount) == 0x3c0, "");
static_assert(offsetof(SystemCore, hwAllocVoiceCount) == 0x410, "");
static_assert(offsetof(SystemCore, numSoundBank) == 0x438, "");
static_assert(offsetof(SystemCore, numSoundActor) == 0x460, "");
static_assert(offsetof(SystemCore, masterVolume) == 0x308, "");
static_assert(offsetof(SystemCore, masterPitch) == 0x350, "");
static_assert(offsetof(SystemCore, speedOfSound) == 0x4e0, "");
static_assert(offsetof(SystemCore, audioMutex) == 0x708, "");
static_assert(offsetof(SystemCore, behaviors) == 0x978, "");
static_assert(offsetof(SystemCore, cpuLoads) == 0x9f8, "");
static_assert(offsetof(SystemCore, cpuLoadIndex) == 0xa20, "");

} // namespace ssd
