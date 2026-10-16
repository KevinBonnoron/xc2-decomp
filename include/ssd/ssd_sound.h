#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

struct Vec3 {
  Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

  f32 x;
  f32 y;
  f32 z;
};

class SoundEntry;
class SoundHandle;
class SoundListener;

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

class SoundActor {
public:
  virtual ~SoundActor();
  virtual void Init();
  virtual void Quit();
  virtual long Play(SoundHandle *handle, const SoundEntry *entry, f32 volume, f32 fadeTime);
  virtual void Stop(f32 fadeTime);
  virtual void Pause(bool isPause, f32 fadeTime);
  virtual void UpdateGameFrame(f32 deltaTime);

  void SetVolume(f32 volume, f32 fadeTime);
  void SetCategoryId(int category);

  u8 _08[0x44 - 0x08];
  Vec3 position;
  u8 _50[0x78 - 0x50];
};

class SoundActor3D : public SoundActor {
public:
  void Init() override;
  void Quit() override;
  long Play(SoundHandle *handle, const SoundEntry *entry, f32 volume, f32 fadeTime) override;
  void UpdateGameFrame(f32 deltaTime) override;
  void SetListener(const SoundListener *listener);
  void SetPosition(const Vec3 &position);
  void SetVelocity(const Vec3 &velocity);
};

static_assert(offsetof(SoundActor3D, position) == 0x44, "");
static_assert(sizeof(SoundActor3D) == 0x78, "");

class SoundHandle {
public:
  bool IsValidHandle() const;
  int GetState() const;
  bool IsPlay() const;
  long Prepare(const SoundEntry *entry);
  long Start(SoundActor *actor, f32 volume, f32 fadeTime);
  long Stop(f32 fadeTime);
  long Pause(bool isPause, f32 fadeTime);
  long SetPitch(f32 pitch, f32 fadeTime);
  long SetVolume(f32 volume, f32 fadeTime);
  long SetPan(f32 pan, f32 fadeTime);
  long GetPlayTime(f32 *time) const;
  long GetDataTime(f32 *time) const;
  long SetPlayTime(f32 time);
  long SetCategoryId(int category);
  f32 GetDistanceVolume() const;
  long GetRemainLoopCount(int *count) const;
  long SetRemainLoopCount(int count);

  u8 _00[0x84 - 0x00];
  f32 volume;
  u8 _88[0xb8 - 0x88];
  f32 categoryVolume;
};

static_assert(offsetof(SoundHandle, volume) == 0x84, "");
static_assert(offsetof(SoundHandle, categoryVolume) == 0xb8, "");

} // namespace ssd
