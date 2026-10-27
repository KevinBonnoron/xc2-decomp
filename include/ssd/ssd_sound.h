#pragma once
#include <stddef.h>

#include "ssd/ssd_array.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_delegate.h"
#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {

struct Vec3 {
  Vec3() {}
  Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

  Vec3 &operator=(const Vec3 &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
  }

  f32 x;
  f32 y;
  f32 z;
};

class SoundCore;
class SoundEntry;
class SoundHandle;
class SoundListener;
class StreamBufferBase;
class WaveSource;

namespace ObjectType {
enum Id {
  WAVE_SOURCE = 1,
  SOUND_ENTRY = 2,
  SOUND_BANK = 3,
  SOUND_LISTENER = 6,
  SOUND_HANDLE = 7,
  SOUND_ACTOR = 8,
  SOUND_ACTOR_3D = 9,
  VOICE_HANDLE = 10,
  FILE_STREAM = 12,
};
} // namespace ObjectType

class Object {
public:
  Object(ObjectType::Id type);
  virtual ~Object() {}

  u32 unknown08;        // Inferred role: type; original member name unknown.
  u32 unknown0c;        // Inferred role: cleared by the constructor; original member name unknown.
  SoundCore *unknown10; // Inferred role: sound core instance at construction; original member name unknown.
};

class SoundActor : public Object, public List<SoundActor>::Node {
public:
  SoundActor();
  SoundActor(ObjectType::Id type);
  virtual ~SoundActor();
  virtual Result Init();
  virtual Result Quit();
  virtual long Play(SoundHandle *handle, const SoundEntry *entry, f32 volume, f32 fadeTime);
  virtual Result Stop(f32 fadeTime);
  virtual Result Pause(bool isPause, f32 fadeTime);
  virtual void UpdateGameFrame(f32 deltaTime);

  bool IsPlay() const;
  void SetPitch(f32 pitch, f32 fadeTime);
  void SetVolume(f32 volume, f32 fadeTime);
  void SetPan(f32 pan, f32 fadeTime);
  void SetCategoryId(int category);
  int CountPlaySoundHandle() const;
  SoundHandle *GetPlaySoundHandle(int index) const;

  bool unknown30; // Inferred role: init; original member name unknown.
  bool unknown31; // Inferred role: connect; original member name unknown.
  bool unknown32; // Inferred role: is3 d; original member name unknown.
  u8 _33[0x38 - 0x33];
  f32 m_pitch;
  f32 m_volume;
  u8 _40[0x44 - 0x40];
};

static_assert(offsetof(SoundActor, unknown30) == 0x30, "");
static_assert(offsetof(SoundActor, m_pitch) == 0x38, "");
static_assert(sizeof(SoundActor) == 0x48, "");

class SoundActor3D : public SoundActor {
public:
  SoundActor3D();
  ~SoundActor3D() override;
  Result Init() override;
  long Play(SoundHandle *handle, const SoundEntry *entry, f32 volume, f32 fadeTime) override;
  void SetListener(const SoundListener *listener);
  void SetPosition(const Vec3 &position);
  void SetPosition(f32 x, f32 y, f32 z);
  void SetVelocity(const Vec3 &velocity);
  void SetVelocity(f32 x, f32 y, f32 z);
  void UpdateGameFrame(f32 deltaTime) override;
  Result Quit() override;

  Vec3 unknown44; // Inferred role: position; original member name unknown.
  Vec3 unknown50; // Inferred role: velocity; original member name unknown.
  Vec3 unknown5c; // Inferred role: prev position; original member name unknown.
  u8 _68[0x69 - 0x68];
  bool unknown69; // Inferred role: position update; original member name unknown.
  u8 _6a[0x6b - 0x6a];
  bool unknown6b; // Inferred role: velocity update; original member name unknown.
  const SoundListener *m_listener;
};

static_assert(offsetof(SoundActor3D, unknown44) == 0x44, "");
static_assert(offsetof(SoundActor3D, unknown5c) == 0x5c, "");
static_assert(offsetof(SoundActor3D, m_listener) == 0x70, "");
static_assert(sizeof(SoundActor3D) == 0x78, "");

class SoundGroup : public Object {
public:
  int unknown18; // Inferred role: id; original member name unknown.
  int unknown1c; // Inferred role: max sound; original member name unknown.
};

static_assert(sizeof(SoundGroup) == 0x20, "");

class SoundBank;

class SoundEntry : public Object, public List<SoundEntry>::Node {
public:
  SoundEntry();
  ~SoundEntry() override;
  SoundGroup *GetSoundGroup() const;

  u8 _30[0x70 - 0x30];
  u64 unknown70; // Inferred role: cleared by the constructor; original member name unknown.
  u16 unknown78; // Inferred role: sound number; original member name unknown.
  u8 _7a[0x7d - 0x7a];
  u8 unknown7d; // Inferred role: sound group id; original member name unknown.
  u8 _7e[0xc8 - 0x7e];
  WaveSource *unknownc8; // Inferred role: wave source; original member name unknown.
  SoundBank *unknownd0;  // Inferred role: sound bank; original member name unknown.
  bool unknownd8;        // Inferred role: allocated entry; original member name unknown.
  u8 _d9[0xe0 - 0xd9];
};

static_assert(offsetof(SoundEntry, unknown70) == 0x70, "");
static_assert(offsetof(SoundEntry, unknown78) == 0x78, "");
static_assert(offsetof(SoundEntry, unknown7d) == 0x7d, "");
static_assert(offsetof(SoundEntry, unknownc8) == 0xc8, "");
static_assert(offsetof(SoundEntry, unknownd0) == 0xd0, "");
static_assert(sizeof(SoundEntry) == 0xe0, "");

class SoundBank : public Object, public List<SoundBank>::Node {
public:
  virtual ~SoundBank();
  SoundEntry *begin() const;
  const SoundEntry *end() const;
  bool empty() const;
  SoundEntry *AddSoundEntry(SoundEntry *entry);
  Result RemoveSoundEntry(int number);
  Result RemoveSoundEntry(SoundEntry *entry);
  SoundEntry *GetSoundEntryFromNumber(int number) const;
  SoundEntry *GetSoundEntryFromIndex(int index) const;
  Result AddSoundGroup(SoundGroup *group);
  int GetReferenceCounter() const;
  int NumSoundEntry() const;
  int GetNumber() const;
  SoundGroup *GetSoundGroup(int id) const;
  Result Stop(f32 fadeTime);

  int m_number;
  u8 _34[0xe0 - 0x34];
  List<SoundEntry> unknowne0;     // Inferred role: sound entries; original member name unknown.
  Array<SoundGroup *> unknown108; // Inferred role: sound groups; original member name unknown.
};

static_assert(offsetof(SoundBank, m_number) == 0x30, "");
static_assert(offsetof(SoundBank, unknowne0) == 0xe0, "");
static_assert(offsetof(SoundBank, unknown108) == 0x108, "");

static_assert(sizeof(SoundBank) == 0x120, "");

class SoundCategory {
public:
  struct unknown001 {
    int unknown00; // Inferred role: category id; original member name unknown.
    f32 unknown04; // Inferred role: category volume; original member name unknown.
  };

  virtual ~SoundCategory() {}

  unknown001 unknown08; // Inferred role: category parameters; original member name unknown.
};

static_assert(offsetof(SoundCategory, unknown08) == 0x8, "");
static_assert(sizeof(SoundCategory) == 0x10, "");

class SoundHandle {
public:
  struct Fade {
    void Set(f32 target, f32 time) {
      f32 current = unknown00;
      this->unknown08 = time;
      f32 begin = time != 0.0f ? current : target;
      this->unknown14 = target;
      unknown10 = begin;
      unknown00 = begin;
      unknown0c = target - begin;
      unknown04 = 0.0f;
    }

    void Reset(f32 value) {
      unknown14 = value;
      unknown10 = value;
      this->unknown00 = value;
      unknown0c = 0.0f;
      unknown04 = 0.0f;
      unknown08 = 0.0f;
    }

    f32 unknown00; // Inferred role: value; original member name unknown.
    f32 unknown04; // Inferred role: elapsed; original member name unknown.
    f32 unknown08; // Inferred role: time; original member name unknown.
    f32 unknown0c; // Inferred role: delta; original member name unknown.
    f32 unknown10; // Inferred role: start; original member name unknown.
    f32 unknown14; // Inferred role: target; original member name unknown.
  };

  struct Effect {
    bool unknown00; // Inferred role: enable; original member name unknown.
    Fade unknown04; // Inferred role: volume; original member name unknown.
  };

  struct Notify {
    enum Type {};
  };

  struct DecodeInfo {
    u32 unknown00; // Inferred role: first stream decode value; original member name unknown.
    u32 unknown04; // Inferred role: second stream decode value; original member name unknown.
    f64 unknown08; // Inferred role: stream decode time in milliseconds; original member name unknown.
  };

  bool IsValidHandle() const;
  long Stop(f32 fadeTime);
  int GetState() const;
  bool HasEnded() const;
  bool IsPlay() const;
  long Play(const SoundEntry *entry, SoundActor *actor, f32 volume, f32 fadeTime);
  long Prepare(const SoundEntry *entry);
  long Start(SoundActor *actor, f32 volume, f32 fadeTime);
  long Pause(bool isPause, f32 fadeTime);
  void SetPitch(f32 pitch, f32 fadeTime);
  void SetVolume(f32 volume, f32 fadeTime);
  void SetPan(f32 pan, f32 fadeTime);
  void UpdateAudioFrame(f32 deltaTime);
  long SetEnableEffect(int index, bool isEnable);
  long SetEffectVolume(int index, f32 volume, f32 fadeTime);
  long SetPregapTime(f32 time);
  long GetPlayPosition(u64 *position) const;
  long GetPlaySample(unsigned long long *sample) const;
  long GetFilePosition(u64 *position) const;
  long GetPlayTime(f32 *time) const;
  long GetDataTime(f32 *time) const;
  long SetPlayPosition(u64 position);
  long SetPlaySample(unsigned long long sample);
  long SetPlayTime(f32 time);
  long GetLoopTime(bool *isLoop, f32 *begin, f32 *end);
  void SetCategoryId(int category);
  f32 GetDistanceVolume() const;
  long GetRemainLoopCount(int *count) const;
  long SetRemainLoopCount(int count);
  long GetVoiceQueueCount(int *count) const;
  long IsEmptyVoiceQueue(bool *isEmpty);
  long IsEmptyStreamBuffer(bool *isEmpty);
  long GetWaveSource(WaveSource **waveSource);
  long GetStreamBuffer(StreamBufferBase **buffer) const;
  long GetStreamDecodeInfo(DecodeInfo *info) const;
  long KeepStreamOpen(bool isKeep);
  void DisplayDebugVerbose();
  void AddDelegate(Delegate::Handle *handle);
  long RemoveDelegate(Delegate::Handle *handle);
  void AddDelegateInternal(Delegate::Handle *handle);
  void ClearDelegate();
  void ClearDelegateImpl();

  u8 _00[0x38 - 0x00];
  SoundActor *unknown38; // Inferred role: sound actor; original member name unknown.
  u8 _40[0x50 - 0x40];
  SoundCategory::unknown001 unknown50; // Inferred role: category parameters; original member name unknown.
  bool unknown58;                      // Inferred role: valid; original member name unknown.
  u8 _59[0x68 - 0x59];
  f32 unknown68;  // Inferred role: pregap time; original member name unknown.
  Fade unknown6c; // Inferred role: pitch; original member name unknown.
  f32 unknown84;  // Inferred role: volume; original member name unknown.
  f32 unknown88;  // Inferred role: volume elapsed; original member name unknown.
  f32 unknown8c;  // Inferred role: volume time; original member name unknown.
  f32 unknown90;  // Inferred role: volume delta; original member name unknown.
  f32 unknown94;  // Inferred role: volume start; original member name unknown.
  f32 unknown98;  // Inferred role: volume target; original member name unknown.
  Fade unknown9c; // Inferred role: pan; original member name unknown.
  u8 _b4[0xb8 - 0xb4];
  f32 unknownb8; // Inferred role: category volume; original member name unknown.
  u8 _bc[0xc0 - 0xbc];
  Effect unknownc0[2]; // Inferred role: effects; original member name unknown.
  u32 unknownf8;       // Inferred role: voice handle id; original member name unknown.
  u8 _fc[0x100 - 0xfc];
  Delegate::MultiCast unknown100;       // Inferred role: delegates; original member name unknown.
  Array<Delegate::Handle *> unknown128; // Inferred role: delegates added internally; original member name unknown.
};

static_assert(offsetof(SoundHandle, unknown38) == 0x38, "");
static_assert(offsetof(SoundHandle, unknown50) == 0x50, "");
static_assert(offsetof(SoundHandle, unknown68) == 0x68, "");
static_assert(offsetof(SoundHandle, unknown9c) == 0x9c, "");
static_assert(offsetof(SoundHandle, unknownc0) == 0xc0, "");
static_assert(offsetof(SoundHandle, unknownf8) == 0xf8, "");
static_assert(offsetof(SoundHandle, unknown100) == 0x100, "");
static_assert(offsetof(SoundHandle, unknown128) == 0x128, "");
static_assert(sizeof(SoundHandle) == 0x140, "");
static_assert(offsetof(SoundHandle, unknown84) == 0x84, "");
static_assert(offsetof(SoundHandle, unknownb8) == 0xb8, "");

} // namespace ssd
