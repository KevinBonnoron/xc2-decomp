#pragma once
#include <stddef.h>

#include "ssd/ssd_behavior.h"
#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {

struct Vec3 {
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

class SoundEntry;
class SoundHandle;
class SoundListener;
class WaveSource;

class Allocator {
public:
  virtual ~Allocator() {}
  virtual void *AllocInstance(size_t size) = 0;
  virtual void FreeInstance(void *pointer) = 0;
  virtual void *AllocBuffer(size_t size, size_t alignment) = 0;
  virtual void FreeBuffer(void *pointer) = 0;
  virtual void *AllocStream(size_t size, size_t alignment) = 0;
  virtual void FreeStream(void *pointer) = 0;
};

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

  u32 type;
  u8 _0c[0x18 - 0x0c];
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

  bool isInit;
  bool isConnect;
  bool is3D;
  u8 _33[0x38 - 0x33];
  f32 pitch;
  f32 volume;
  u8 _40[0x44 - 0x40];
};

static_assert(offsetof(SoundActor, isInit) == 0x30, "");
static_assert(offsetof(SoundActor, pitch) == 0x38, "");
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

  Vec3 position;
  Vec3 velocity;
  Vec3 prevPosition;
  u8 _68[0x69 - 0x68];
  bool isPositionUpdate;
  u8 _6a[0x6b - 0x6a];
  bool isVelocityUpdate;
  const SoundListener *listener;
};

static_assert(offsetof(SoundActor3D, position) == 0x44, "");
static_assert(offsetof(SoundActor3D, prevPosition) == 0x5c, "");
static_assert(offsetof(SoundActor3D, listener) == 0x70, "");
static_assert(sizeof(SoundActor3D) == 0x78, "");

class SoundGroup : public Object {
public:
  int id;
  int maxSound;
};

static_assert(sizeof(SoundGroup) == 0x20, "");

class SoundBank {
public:
  virtual ~SoundBank();
  void AddSoundEntry(SoundEntry *entry);
  void RemoveSoundEntry(SoundEntry *entry);
  int GetReferenceCounter() const;
  int NumSoundEntry() const;
  void Stop(f32 fadeTime);

  u8 _08[0x120 - 0x08];
};

static_assert(sizeof(SoundBank) == 0x120, "");

class SoundHandle {
public:
  struct Fade {
    void Set(f32 target, f32 time) {
      f32 current = value;
      this->time = time;
      f32 begin = time != 0.0f ? current : target;
      this->target = target;
      start = begin;
      value = begin;
      delta = target - begin;
      elapsed = 0.0f;
    }

    void Reset(f32 value) {
      target = value;
      start = value;
      this->value = value;
      delta = 0.0f;
      elapsed = 0.0f;
      time = 0.0f;
    }

    f32 value;
    f32 elapsed;
    f32 time;
    f32 delta;
    f32 start;
    f32 target;
  };

  struct Effect {
    bool isEnable;
    Fade volume;
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
  long KeepStreamOpen(bool isKeep);
  void DisplayDebugVerbose();

  u8 _00[0x58 - 0x00];
  bool isValid;
  u8 _59[0x68 - 0x59];
  f32 pregapTime;
  Fade pitch;
  f32 volume;
  f32 volumeElapsed;
  f32 volumeTime;
  f32 volumeDelta;
  f32 volumeStart;
  f32 volumeTarget;
  Fade pan;
  u8 _b4[0xb8 - 0xb4];
  f32 categoryVolume;
  u8 _bc[0xc0 - 0xbc];
  Effect effects[2];
  u32 voiceHandleId;
};

static_assert(offsetof(SoundHandle, pregapTime) == 0x68, "");
static_assert(offsetof(SoundHandle, pan) == 0x9c, "");
static_assert(offsetof(SoundHandle, effects) == 0xc0, "");
static_assert(offsetof(SoundHandle, voiceHandleId) == 0xf8, "");
static_assert(offsetof(SoundHandle, volume) == 0x84, "");
static_assert(offsetof(SoundHandle, categoryVolume) == 0xb8, "");

} // namespace ssd
