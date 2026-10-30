#pragma once
#include <stddef.h>

#include "nn/audio.h"
#include "nn/mem.h"
#include "nn/os.h"
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_array.h" // IWYU pragma: keep
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {
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
    unknown001_255 = 0xff,
  };

  u8 _00[0x18 - 0x00];
  unknown001 unknown18; // Inferred role: effect type; original member name unknown.
  bool unknown19;       // Inferred role: attached to a bus; original member name unknown.
  u8 unknown1a;         // Inferred role: bus number; original member name unknown.
  u8 _1b[0x1c - 0x1b];
  f32 unknown1c; // Inferred role: effect volume; original member name unknown.
};

static_assert(offsetof(SoundEffecter, unknown18) == 0x18, "");
static_assert(offsetof(SoundEffecter, unknown1a) == 0x1a, "");
static_assert(offsetof(SoundEffecter, unknown1c) == 0x1c, "");

class SoundDelayEffecter : public SoundEffecter {
public:
  f32 unknown20; // Inferred role: delay time in seconds; original member name unknown.
  f32 unknown24; // Inferred role: maximum delay time in seconds; original member name unknown.
  f32 unknown28; // Inferred role: in gain; original member name unknown.
  f32 unknown2c; // Inferred role: feedback gain; original member name unknown.
  f32 unknown30; // Inferred role: dry gain; original member name unknown.
  f32 unknown34; // Inferred role: channel spread; original member name unknown.
  f32 unknown38; // Inferred role: low pass amount; original member name unknown.
};

static_assert(offsetof(SoundDelayEffecter, unknown20) == 0x20, "");
static_assert(offsetof(SoundDelayEffecter, unknown38) == 0x38, "");

class SoundI3dl2ReverbEffecter : public SoundEffecter {
public:
  bool unknown20; // Inferred role: parameter change flag; original member name unknown.
  f32 unknown24;  // Inferred role: room gain; original member name unknown.
  f32 unknown28;  // Inferred role: room high frequency gain; original member name unknown.
  f32 unknown2c;  // Inferred role: late reverb decay time in seconds; original member name unknown.
  f32 unknown30;  // Inferred role: late reverb high frequency decay ratio; original member name unknown.
  f32 unknown34;  // Inferred role: reflections gain; original member name unknown.
  f32 unknown38;  // Inferred role: reflection delay time in seconds; original member name unknown.
  f32 unknown3c;  // Inferred role: reverb gain; original member name unknown.
  f32 unknown40;  // Inferred role: late reverb delay time in seconds; original member name unknown.
  f32 unknown44;  // Inferred role: late reverb diffusion; original member name unknown.
  f32 unknown48;  // Inferred role: late reverb density; original member name unknown.
  f32 unknown4c;  // Inferred role: high frequency reference; original member name unknown.
  f32 unknown50;  // Inferred role: dry gain; original member name unknown.
};

static_assert(offsetof(SoundI3dl2ReverbEffecter, unknown20) == 0x20, "");
static_assert(offsetof(SoundI3dl2ReverbEffecter, unknown24) == 0x24, "");
static_assert(offsetof(SoundI3dl2ReverbEffecter, unknown50) == 0x50, "");

struct OutputMode {
  enum Type {};
};

class SoundCore {
public:
  struct ThreadParam {
    ThreadParam();

    u64 unknown00;    // Inferred role: core mask; original member name unknown.
    int unknown08;    // Inferred role: priority; original member name unknown.
    int unknown0c;    // Inferred role: ideal core; original member name unknown.
    size_t unknown10; // Inferred role: stack size; original member name unknown.
  };

  struct InitParam {
    InitParam();

    ThreadParam unknown00;        // Inferred role: audio thread parameter; original member name unknown.
    ThreadParam unknown18;        // Inferred role: stream thread parameter; original member name unknown.
    int unknown30;                // Inferred role: voice count; original member name unknown.
    Debug::unknown001 unknown38;  // Inferred role: message method; original member name unknown.
    LogTimeStamp::Type unknown40; // Inferred role: log time stamp type; original member name unknown.
    u32 unknown44;                // Inferred role: audio data memory size; original member name unknown.
  };

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
static_assert(sizeof(SoundCore::ThreadParam) == 0x18, "");
static_assert(offsetof(SoundCore::InitParam, unknown18) == 0x18, "");
static_assert(offsetof(SoundCore::InitParam, unknown30) == 0x30, "");
static_assert(offsetof(SoundCore::InitParam, unknown38) == 0x38, "");
static_assert(offsetof(SoundCore::InitParam, unknown44) == 0x44, "");
static_assert(sizeof(SoundCore::InitParam) == 0x48, "");

class SystemCorePlatform : public SoundCore {
public:
  struct EffectBusInfo {
    bool unknown00;                      // Inferred role: effect enabled; original member name unknown.
    bool unknown01;                      // Inferred role: effect removal pending; original member name unknown.
    SoundEffecter::unknown001 unknown02; // Inferred role: effect type; original member name unknown.
    s8 unknown03[2];                     // Inferred role: effect mix buffer indices; original member name unknown.
    u8 _05[0x08 - 0x05];
    f32 unknown08; // Inferred role: effect volume; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    SoundEffecter *unknown10;             // Inferred role: effecter; original member name unknown.
    void *unknown18;                      // Inferred role: effect work buffer; original member name unknown.
    nn::audio::BufferMixerType unknown20; // Inferred role: effect output mixer; original member name unknown.
    nn::audio::DelayType unknown28;       // Inferred role: delay effect; original member name unknown.
    nn::audio::I3dl2ReverbType unknown30; // Inferred role: reverb effect; original member name unknown.
  };

  // Inferred role: allocate a device buffer from the sound allocator; original name unknown.
  static void *unknown001(size_t size) {
    Allocator::Block *block = SoundMemory::allocator_->NewBufferImpl(size, 1, 0x1000);
    if (block != nullptr) {
      return block->unknown08;
    }
    return nullptr;
  }

  void InitPlatform(const InitParam &param);
  Result InitAudioDevice(const InitParam &param);
  Result QuitAudioDevice();
  void UpdateDevice();
  static f64 GetSystemTime();
  void *GetPlatformDataImpl(const char *name) override;
  void *AllocAudioDataBuffer(size_t size);
  void FreeAudioDataBuffer(void *buffer);
  Result InitEffect(u8 bus, SoundEffecter *effecter);
  Result InitDelayEffect(u8 bus, SoundDelayEffecter *effecter);
  Result InitI3dl2ReverbEffect(u8 bus, SoundI3dl2ReverbEffecter *effecter);
  Result QuitEffect(SoundEffecter *effecter);
  int GetBusNumberFormEffecter(SoundEffecter *effecter);
  Result QuitDelayEffect(u8 bus);
  Result QuitI3dl2ReverbEffect(u8 bus);
  void DeleteEffect(EffectBusInfo &info);
  void UpdateEffectVolume(SoundEffecter *effecter);
  void UpdateEffectParam(SoundEffecter *effecter);

  f64 unknown18;                             // Inferred role: system tick frequency; original member name unknown.
  MemoryBlock unknown20;                     // Inferred role: audio renderer work memory; original member name unknown.
  nn::mem::StandardAllocator unknown30;      // Inferred role: audio renderer work allocator; original member name unknown.
  MemoryBlock unknown78;                     // Inferred role: effect memory; original member name unknown.
  nn::mem::StandardAllocator unknown88;      // Inferred role: effect allocator; original member name unknown.
  nn::audio::MemoryPoolType unknownd0;       // Inferred role: effect memory pool; original member name unknown.
  MemoryBlock unknownd8;                     // Inferred role: audio data memory; original member name unknown.
  nn::mem::StandardAllocator unknowne8;      // Inferred role: audio data allocator; original member name unknown.
  nn::audio::MemoryPoolType unknown130;      // Inferred role: audio data memory pool; original member name unknown.
  nn::os::SystemEvent unknown138;            // Inferred role: audio renderer event; original member name unknown.
  nn::audio::AudioRendererConfig unknown168; // Inferred role: audio renderer config; original member name unknown.
  u8 _1c0[0x1d8 - 0x1c0];
  nn::audio::AudioRendererHandle unknown1d8; // Inferred role: audio renderer; original member name unknown.
  s8 unknown1e8[6];                          // Inferred role: final mix buffer indices; original member name unknown.
  EffectBusInfo unknown1f0[2];               // Inferred role: effect buses; original member name unknown.
  nn::audio::FinalMixType unknown260;        // Inferred role: final mix; original member name unknown.
  u32 unknown268;                            // Inferred role: sample rate; original member name unknown.
  u32 unknown26c;                            // Inferred role: sample count; original member name unknown.
};

static_assert(offsetof(SystemCorePlatform, unknown18) == 0x18, "");
static_assert(offsetof(SystemCorePlatform, unknown30) == 0x30, "");
static_assert(offsetof(SystemCorePlatform, unknown88) == 0x88, "");
static_assert(offsetof(SystemCorePlatform, unknownd0) == 0xd0, "");
static_assert(offsetof(SystemCorePlatform, unknowne8) == 0xe8, "");
static_assert(offsetof(SystemCorePlatform, unknown138) == 0x138, "");
static_assert(offsetof(SystemCorePlatform, unknown168) == 0x168, "");
static_assert(offsetof(SystemCorePlatform, unknown1d8) == 0x1d8, "");
static_assert(offsetof(SystemCorePlatform, unknown1e8) == 0x1e8, "");
static_assert(offsetof(SystemCorePlatform, unknown1f0) == 0x1f0, "");
static_assert(offsetof(SystemCorePlatform, unknown260) == 0x260, "");
static_assert(offsetof(SystemCorePlatform, unknown26c) == 0x26c, "");
static_assert(offsetof(SystemCorePlatform::EffectBusInfo, unknown03) == 0x03, "");
static_assert(offsetof(SystemCorePlatform::EffectBusInfo, unknown18) == 0x18, "");
static_assert(offsetof(SystemCorePlatform::EffectBusInfo, unknown30) == 0x30, "");
static_assert(sizeof(SystemCorePlatform::EffectBusInfo) == 0x38, "");
static_assert(sizeof(SystemCorePlatform) == 0x270, "");

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
  static void AudioThreadEntry(SystemCore *core, void *argument);
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
  void AudioThreadImpl();
  void AudioFrameProcess();

  u64 unknown270; // Inferred role: game frame counter; original member name unknown.
  u64 unknown278; // Inferred role: audio frame counter; original member name unknown.
  f64 unknown280; // Inferred role: audio timer counter; original member name unknown.
  u8 _288[0x290 - 0x288];
  f64 unknown290; // Inferred role: audio frames per second; original member name unknown.
  u8 _298[0x2a0 - 0x298];
  f64 unknown2a0; // Inferred role: audio frame delta time; original member name unknown.
  f64 unknown2a8; // Inferred role: last audio frame time; original member name unknown.
  u8 _2b0[0x300 - 0x2b0];
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
  u8 _4e4[0x4ea - 0x4e4];
  bool unknown4ea; // Inferred role: audio thread exit request; original member name unknown.
  u8 _4eb[0x708 - 0x4eb];
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
