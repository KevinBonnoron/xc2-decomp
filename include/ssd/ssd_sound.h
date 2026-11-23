#pragma once
#include <stddef.h>

#include "ssd/ssd_array.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_delegate.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound_param.h"
#include "ssd/ssd_text.h"
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
  SOUND_GROUP = 4,
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

  u32 unknown08;          // Inferred role: type; original member name unknown.
  u32 unknown0c;          // Inferred role: cleared by the constructor; original member name unknown.
  SoundCore *m_soundCore; // Inferred role: sound core instance at construction; original member name unknown.
};

class SoundActor : public Object, public List<SoundActor>::Node {
public:
  SoundActor();
  SoundActor(ObjectType::Id type) : Object(type), unknown30(false), unknown31(false), unknown32(false), unknown33(false), unknown34(false), m_pitch(1.0f), m_volume(1.0f), unknown40(0) {}
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
  bool unknown33; // Inferred role: cleared by the constructor; original member name unknown.
  bool unknown34; // Inferred role: cleared by the constructor; original member name unknown.
  u8 _35[0x38 - 0x35];
  f32 m_pitch;
  f32 m_volume;
  u32 unknown40; // Inferred role: cleared by the constructor; original member name unknown.
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
  bool unknown68; // Inferred role: set by the constructor; original member name unknown.
  bool unknown69; // Inferred role: position update; original member name unknown.
  bool unknown6a; // Inferred role: cleared by the constructor; original member name unknown.
  bool unknown6b; // Inferred role: velocity update; original member name unknown.
  const SoundListener *m_listener;
};

static_assert(offsetof(SoundActor3D, unknown44) == 0x44, "");
static_assert(offsetof(SoundActor3D, unknown5c) == 0x5c, "");
static_assert(offsetof(SoundActor3D, m_listener) == 0x70, "");
static_assert(sizeof(SoundActor3D) == 0x78, "");

class SoundGroup : public Object {
public:
  SoundGroup() : Object(ObjectType::SOUND_GROUP), unknown18(0), unknown1c(256) {}

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

  SoundParam m_soundParam; // Inferred role: sound parameters; original member name unknown.
  u8 _c4[0xc8 - 0xc4];
  WaveSource *m_waveSource; // Inferred role: wave source; original member name unknown.
  SoundBank *m_soundBank;   // Inferred role: sound bank; original member name unknown.
  bool unknownd8;           // Inferred role: allocated entry; original member name unknown.
  u8 _d9[0xe0 - 0xd9];
};

static_assert(offsetof(SoundEntry, m_soundParam) == 0x30, "");
static_assert(offsetof(SoundEntry, m_waveSource) == 0xc8, "");
static_assert(offsetof(SoundEntry, m_soundBank) == 0xd0, "");
static_assert(sizeof(SoundEntry) == 0xe0, "");

class SoundBank : public Object, public List<SoundBank>::Node {
public:
  SoundBank();
  virtual ~SoundBank();
  SoundEntry *begin() const;
  const SoundEntry *end() const;
  bool empty() const;
  SoundEntry *AddSoundEntry(SoundEntry *entry);
  SoundEntry *AddWave(WaveSource *wave, const SoundParam &param);
  Result RemoveSoundEntry(int number);
  Result RemoveSoundEntry(SoundEntry *entry);
  SoundEntry *GetSoundEntryFromNumber(int number) const;
  SoundEntry *GetSoundEntryFromIndex(int index) const;
  SoundEntry *GetSoundEntryFromName(const TextRef &name) const;
  Result AddSoundGroup(SoundGroup *group);
  int GetReferenceCounter() const;
  int NumSoundEntry() const;
  int GetNumber() const;
  const TextRef &GetName() const;
  Result Init(int number, const TextRef &name);
  Result Quit();
  SoundGroup *GetSoundGroup(int id) const;
  Result Stop(f32 fadeTime);

  int m_number;
  u8 _34[0x38 - 0x34];
  TextFixed<64> m_name;           // Inferred role: name; named after the game accessor ssd::SoundBank::GetName.
  List<SoundEntry> unknowne0;     // Inferred role: sound entries; original member name unknown.
  Array<SoundGroup *> unknown108; // Inferred role: sound groups; original member name unknown.
};

static_assert(offsetof(SoundBank, m_number) == 0x30, "");
static_assert(offsetof(SoundBank, m_name) == 0x38, "");
static_assert(offsetof(SoundBank, unknowne0) == 0xe0, "");
static_assert(offsetof(SoundBank, unknown108) == 0x108, "");

static_assert(sizeof(SoundBank) == 0x120, "");

class SoundCategory {
public:
  struct unknown001 {
    int unknown00; // Inferred role: category id; original member name unknown.
    f32 unknown04; // Inferred role: category volume; original member name unknown.
  };

  SoundCategory(int id = 0, f32 volume = 1.0f) {
    unknown08.unknown00 = id;
    unknown08.unknown04 = volume;
  }

  virtual ~SoundCategory() {}

  unknown001 unknown08; // Inferred role: category parameters; original member name unknown.
};

static_assert(offsetof(SoundCategory, unknown08) == 0x8, "");
static_assert(sizeof(SoundCategory) == 0x10, "");

class SoundHandle : public Object, public List<SoundHandle>::Node {
public:
  // Inferred role: fade; original type name unknown.
  struct unknown003 {
    unknown003() { Reset(1.0f); }

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

    // Inferred role: advance the fade by a frame; original name unknown.
    void unknown004(f32 deltaTime) {
      f32 time = unknown08;
      if (unknown04 < time) {
        f32 elapsed = unknown04 + deltaTime;
        if (elapsed >= time) {
          elapsed = time;
        }
        unknown00 = unknown10 + (elapsed * unknown0c) / time;
        unknown04 = elapsed;
      }
    }

    f32 unknown00; // Inferred role: value; original member name unknown.
    f32 unknown04; // Inferred role: elapsed; original member name unknown.
    f32 unknown08; // Inferred role: time; original member name unknown.
    f32 unknown0c; // Inferred role: delta; original member name unknown.
    f32 unknown10; // Inferred role: start; original member name unknown.
    f32 unknown14; // Inferred role: target; original member name unknown.
  };

  struct Effect {
    bool unknown00;       // Inferred role: enable; original member name unknown.
    unknown003 unknown04; // Inferred role: volume; original member name unknown.
  };

  struct Notify {
    enum Type {};
  };

  struct DecodeInfo {
    u32 unknown00; // Inferred role: first stream decode value; original member name unknown.
    u32 unknown04; // Inferred role: second stream decode value; original member name unknown.
    f64 unknown08; // Inferred role: stream decode time in milliseconds; original member name unknown.
  };

  SoundHandle();
  ~SoundHandle() override;
  bool IsValidHandle() const;
  long Stop(f32 fadeTime);
  int GetState() const;
  TextRef GetStateName() const;
  bool HasEnded() const;
  bool IsPlay() const;
  long Play(const SoundEntry *entry, SoundActor *actor, f32 volume, f32 fadeTime);
  long PlayCommand(const SoundEntry *entry, SoundActor *actor, f32 volume, f32 fadeTime);
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
  void Init();
  void Quit();
  void Delete();
  void ClearDelegate();
  void ClearDelegateImpl();

  const SoundEntry *m_soundEntry; // Inferred role: sound entry; original member name unknown.
  SoundActor *m_soundActor;       // Inferred role: sound actor; original member name unknown.
  u32 unknown40;                  // Inferred role: cleared by the constructor; original member name unknown.
  SoundCategory m_soundCategory;  // Inferred role: category; original member name unknown.
  bool unknown58;                 // Inferred role: valid; original member name unknown.
  bool unknown59;                 // Inferred role: cleared by the constructor; original member name unknown.
  bool unknown5a;                 // Inferred role: cleared by the constructor; original member name unknown.
  u8 _5b[0x60 - 0x5b];
  f64 unknown60;        // Inferred role: time at the start; original member name unknown.
  f32 unknown68;        // Inferred role: pregap time; original member name unknown.
  unknown003 unknown6c; // Inferred role: pitch; original member name unknown.
  unknown003 unknown84; // Inferred role: volume; original member name unknown.
  unknown003 unknown9c; // Inferred role: pan; original member name unknown.
  f32 unknownb4;        // Inferred role: value set to 1.0 by Init; original member name unknown.
  f32 unknownb8;        // Inferred role: category volume; original member name unknown.
  f32 unknownbc;        // Inferred role: value cleared by Init; original member name unknown.
  Effect m_effect[2];   // Inferred role: effects; original member name unknown.
  u32 unknownf8;        // Inferred role: voice handle id; original member name unknown.
  u8 _fc[0x100 - 0xfc];
  Delegate::MultiCast m_multiCast;      // Inferred role: delegates; original member name unknown.
  Array<Delegate::Handle *> unknown128; // Inferred role: delegates added internally; original member name unknown.
};

static_assert(offsetof(SoundHandle, m_soundActor) == 0x38, "");
static_assert(offsetof(SoundHandle, m_soundEntry) == 0x30, "");
static_assert(offsetof(SoundHandle, m_soundCategory) == 0x48, "");
static_assert(offsetof(SoundHandle, unknown58) == 0x58, "");
static_assert(offsetof(SoundHandle, unknown68) == 0x68, "");
static_assert(offsetof(SoundHandle, unknown9c) == 0x9c, "");
static_assert(offsetof(SoundHandle, m_effect) == 0xc0, "");
static_assert(offsetof(SoundHandle, unknownf8) == 0xf8, "");
static_assert(offsetof(SoundHandle, m_multiCast) == 0x100, "");
static_assert(offsetof(SoundHandle, unknown128) == 0x128, "");
static_assert(sizeof(SoundHandle) == 0x140, "");
static_assert(offsetof(SoundHandle, unknown84) == 0x84, "");
static_assert(offsetof(SoundHandle, unknownb8) == 0xb8, "");

} // namespace ssd
