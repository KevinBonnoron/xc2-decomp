#pragma once
#include <stddef.h>

#include "ssd/ssd_array.h" // IWYU pragma: keep
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {
class Allocator;
class SoundBank;
class SoundCategory;
class SoundActor;
class SoundHandle;
class StreamController;
class SoundListener;
class VoiceHandle;

class SoundEffecter {
public:
  enum unknown001 : u8 {
    unknown001_0 = 0,
    unknown001_1 = 1,
  };

  u8 _00[0x18 - 0x00];
  unknown001 unknown18; // Inferred role: effect type; original member name unknown.
  u8 _19[0x1c - 0x19];
  f32 unknown1c; // Inferred role: effect volume; original member name unknown.
};

static_assert(offsetof(SoundEffecter, unknown18) == 0x18, "");
static_assert(offsetof(SoundEffecter, unknown1c) == 0x1c, "");

class SoundDelayEffecter : public SoundEffecter {};

class SoundI3dl2ReverbEffecter : public SoundEffecter {};

struct OutputMode {
  enum Type {};
};

class SoundCore {
public:
  SoundCore();
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

  static SoundCore *NewInstance(Allocator *allocator);
  static void DeleteInstance();
  static bool IsInstance();
  static SoundCore *GetInstance();
  void GetVersion(int *major, int *minor, int *revision, int *build, char16_t *configuration);
  bool IsInit();
  Result Quit(bool isForce);
  Result GetCategory(int id, SoundCategory *category) const;
  Result SetCategory(const SoundCategory &category);
  Result ResetCategory(int id);
  Result GetSoundBankList(SoundBank **banks, size_t num) const;
  Result GetSoundActorListByCategoty(int category, Array<SoundActor *> *actors) const;
  Result GetSoundHandleListByCategoty(int category, Array<SoundHandle *> *handles) const;
  Result GetSoundBank(int id, SoundBank **bank) const;
  Result NumSoundBank(int *num) const;
  Result NumSoundActor(int *num) const;
  void UpdateGameFrame(f32 deltaTime);
  void StopSound(f32 fadeTime);
  void PauseSound(bool isPause, f32 fadeTime);
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
  u32 GetErrorLogFlag() const;
  u32 GetWarningLogFlag() const;
  LogTimeStamp::Type GetLogTimeStampType() const;

  static SoundCore *instance_;

  Result unknown08; // Inferred role: last result; original member name unknown.
  bool m_init;
};

static_assert(offsetof(SoundCore, m_init) == 0x10, "");

class SystemCorePlatform : public SoundCore {
public:
  struct EffectBusInfo {
    bool unknown00; // Inferred role: effect flag; original member name unknown.
    bool unknown01; // Inferred role: effect flag; original member name unknown.
    u8 _02[0x08 - 0x02];
    f32 unknown08; // Inferred role: effect volume; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    SoundEffecter *unknown10; // Inferred role: effecter; original member name unknown.
    u8 _18[0x38 - 0x18];
  };

  void *GetPlatformDataImpl(const char *name) override;
  Result InitEffect(u8 bus, SoundEffecter *effecter);
  Result InitI3dl2ReverbEffect(u8 bus, SoundI3dl2ReverbEffecter *effecter);
  Result InitDelayEffect(u8 bus, SoundDelayEffecter *effecter);
  Result QuitEffect(SoundEffecter *effecter);
  void FreeAudioDataBuffer(void *buffer);
  int GetBusNumberFormEffecter(SoundEffecter *effecter);
  void UpdateEffectVolume(SoundEffecter *effecter);
  void UpdateEffectParam(SoundEffecter *effecter);

  u8 _011[0x1f0 - 0x011];
  EffectBusInfo unknown1f0[2]; // Inferred role: effect buses; original member name unknown.
};

static_assert(offsetof(SystemCorePlatform, unknown1f0) == 0x1f0, "");
static_assert(sizeof(SystemCorePlatform::EffectBusInfo) == 0x38, "");
static_assert(sizeof(SystemCorePlatform) == 0x260, "");

class SystemCore : public SystemCorePlatform {
public:
  struct DebugInfo;

  // Inferred role: cpu load; original type name unknown.
  struct unknown002 {
    f64 unknown00; // Inferred role: process time; original member name unknown.
    f64 unknown08; // Inferred role: frame time; original member name unknown.
  };

  SystemCore();
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
  Result AddSoundListener(SoundListener *listener) override;
  Result RemoveSoundListener(SoundListener *listener) override;
  Result GetSoundEffectList(int bus, SoundEffecter **effecters, int *num) override;
  Result AddSoundEffecter(u8 bus, SoundEffecter *effecter) override;
  Result RemoveSoundEffecter(SoundEffecter *effecter) override;
  bool IsActiveEffect(u8 bus) override;
  Result Quit();
  void StopSound(f32 fadeTime);
  void PauseSound(bool isPause, f32 fadeTime);
  void AddStreamController(StreamController *controller);
  void RemoveStreamController(StreamController *controller);
  void AddBank(SoundBank *bank);
  void RemoveBank(SoundBank *bank);
  void StopBank(SoundBank *bank, f32 fadeTime);
  SoundBank *GetBank(int id) const;
  Result GetBankList(SoundBank **banks, size_t num) const;
  Result SetCategory(const SoundCategory &category);
  Result ResetCategory(int id);
  SoundCategory *GetCategory(int id) const;
  Result GetCategory(int id, SoundCategory *category) const;
  void ChangeCategoryEvent(const SoundCategory &category);
  bool IsPlayActor(const SoundActor *actor) const;
  void StopActor(SoundActor *actor, f32 fadeTime);
  void PauseActor(SoundActor *actor, bool isPause, f32 fadeTime);
  int CountPlaySoundHandleActor(const SoundActor *actor) const;
  SoundHandle *GetPlaySoundHandle(const SoundActor *actor, int index) const;
  int GetPlaySoundHandleFromActor(const SoundActor *actor, Array<SoundHandle *> *handles) const;
  Result GetSoundActorListByCategoty(int category, Array<SoundActor *> *actors) const;
  Result GetSoundHandleListByCategoty(int category, Array<SoundHandle *> *handles) const;
  Result AllocVoiceHandle(int, VoiceHandle **voice);
  void FreeVoiceHandle(VoiceHandle *voice);
  void ConnectActor(SoundActor *actor);
  void DisconnectActor(SoundActor *actor);
  void UpdateGameFrame(f32 deltaTime);

  u8 _260[0x270 - 0x260];
  u64 unknown270; // Inferred role: game frame counter; original member name unknown.
  u64 unknown278; // Inferred role: audio frame counter; original member name unknown.
  f64 unknown280; // Inferred role: audio timer counter; original member name unknown.
  u8 _288[0x300 - 0x288];
  OutputMode::Type m_outputMode;
  u8 _304[0x308 - 0x304];
  BehaviorInstance<SystemCore> unknown308; // Inferred role: master volume; original member name unknown.
  BehaviorInstance<SystemCore> unknown350; // Inferred role: master pitch; original member name unknown.
  u8 _398[0x39c - 0x398];
  int unknown39c;               // Inferred role: voice handle id counter; original member name unknown.
  List<VoiceHandle> unknown3a0; // Inferred role: playing voice handles; original member name unknown.
  List<VoiceHandle> unknown3c8; // Inferred role: free voice handles; original member name unknown.
  VoiceHandle *unknown3f0;      // Inferred role: voice handles; original member name unknown.
  u8 _3f8[0x410 - 0x3f8];
  int unknown410; // Inferred role: hw alloc voice count; original member name unknown.
  u8 _414[0x418 - 0x414];
  List<SoundBank> unknown418;      // Inferred role: sound banks; original member name unknown.
  List<SoundActor> unknown440;     // Inferred role: connected sound actors; original member name unknown.
  Array<SoundCategory> unknown468; // Inferred role: categories; original member name unknown.
  u8 _480[0x4e0 - 0x480];
  f32 m_speedOfSound;
  u8 _4e4[0x708 - 0x4e4];
  mutable Mutex unknown708; // Inferred role: audio mutex; original member name unknown.
  u8 _730[0x950 - 0x730];
  List<StreamController> unknown950; // Inferred role: stream controllers; original member name unknown.
  List<BehaviorControl> unknown978;  // Inferred role: behaviors; original member name unknown.
  u8 _9a0[0x9f8 - 0x9a0];
  unknown002 unknown9f8[2]; // Inferred role: cpu loads; original member name unknown.
  f64 unknowna18;           // Inferred role: last cpu load time; original member name unknown.
  s32 unknowna20;           // Inferred role: cpu load index; original member name unknown.

  static DebugInfo debugInfo_;
};

static_assert(offsetof(SystemCore, unknown270) == 0x270, "");
static_assert(offsetof(SystemCore, unknown3a0) == 0x3a0, "");
static_assert(offsetof(SystemCore, unknown3c8) == 0x3c8, "");
static_assert(offsetof(SystemCore, unknown3f0) == 0x3f0, "");
static_assert(offsetof(SystemCore, unknown410) == 0x410, "");
static_assert(offsetof(SystemCore, unknown418) == 0x418, "");
static_assert(offsetof(SystemCore, unknown440) == 0x440, "");
static_assert(offsetof(SystemCore, unknown950) == 0x950, "");
static_assert(offsetof(SystemCore, unknown308) == 0x308, "");
static_assert(offsetof(SystemCore, unknown350) == 0x350, "");
static_assert(offsetof(SystemCore, unknown468) == 0x468, "");
static_assert(offsetof(SystemCore, m_speedOfSound) == 0x4e0, "");
static_assert(offsetof(SystemCore, unknown708) == 0x708, "");
static_assert(offsetof(SystemCore, unknown978) == 0x978, "");
static_assert(offsetof(SystemCore, unknown9f8) == 0x9f8, "");
static_assert(offsetof(SystemCore, unknowna20) == 0xa20, "");
static_assert(sizeof(SystemCore) == 0xa28, "");

} // namespace ssd
