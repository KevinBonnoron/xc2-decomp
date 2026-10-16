#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_ptr.h"
#include "ssd/ssd_sound.h"
#include "types.h"

namespace ssd {
class SoundEntry;
class SoundListener;
} // namespace ssd

namespace mm {
struct Vec3;

namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class SoundSsdBank;
enum SoundCategory : int;
enum SoundVolumeType : int;

class SoundSsdDriver {
public:
  class SoundAllocator : public ssd::Allocator {
  public:
    void *AllocInstance(size_t size) override;
    void FreeInstance(void *pointer) override;
    void *AllocBuffer(size_t size, size_t alignment) override;
    void FreeBuffer(void *pointer) override;
    void *AllocStream(size_t size, size_t alignment) override;
    void FreeStream(void *pointer) override;

    mm::mtl::IAllocator *allocator;
  };
};

static_assert(offsetof(SoundSsdDriver::SoundAllocator, allocator) == 0x08, "");

class SoundReferenceObject {
public:
  virtual ~SoundReferenceObject();

  void addRef() { refCount++; }
  int release();

  int refCount;
};

struct SoundSsdSourceData {
  u8 _00[0x50 - 0x00];
  bool isLoop;
};

class SoundSsdSource : public SoundReferenceObject {
public:
  static const u8 FLAG_3D = 1 << 1;

  u8 _0c[0x10 - 0x0c];
  SoundSsdSourceData *data;
  ssd::SoundEntry *entry;
  u8 _20[0x240 - 0x20];
  u8 flags;
};

static_assert(offsetof(SoundSsdSource, entry) == 0x18, "");
static_assert(offsetof(SoundSsdSource, flags) == 0x240, "");

class SoundSsdPlayer : public ssd::SoundActor3D {
public:
  static const u32 FLAG_RELEASED = 1 << 1;
  static const u32 FLAG_STREAM = 1 << 2;
  static const u32 FLAG_LISTENER = 1 << 3;

  ~SoundSsdPlayer();
  bool getTotalTime(f32 &time) const;
  bool isValid() const;
  bool setPlayTime(f32 time);
  bool getPlayTime(f32 &time) const;
  bool is3DSource() const;
  bool is3D() const;
  bool isLoop() const;
  bool setRemainLoopCount(int count);
  bool getRemainLoopCount(int &count) const;
  void pause(bool isPause, f32 time);
  bool isPause() const;
  void setCategory(SoundCategory category);
  void setListener(ssd::SoundListener *listener);
  bool play();
  bool prepare();
  bool start();
  void setVolume(f32 volume, f32 time);
  f32 getVolume(SoundVolumeType type) const;
  void setPitch(f32 pitch, f32 time);
  void setPan(f32 pan, f32 time);
  void setPos(const mm::Vec3 &position);
  void setPos(f32 x, f32 y, f32 z);
  void getPos(mm::Vec3 &position) const;
  int getState() const;
  bool isReady() const;
  bool isPreparing() const;
  bool isPlaying() const;
  void progress(f32 deltaTime);
  bool canDestroy() const;
  void setHandle(u32 handle);
  void stop(f32 time);

  SoundSsdBank *bank;
  mm::mtl::IntrusivePtr<SoundSsdSource> source;
  ssd::SoundHandle *handle;
  ssd::SoundListener *listener;
  SoundCategory category;
  f32 volume;
  f32 fadeTime;
  f32 pitch;
  f32 pan;
  u8 _ac[0xb8 - 0xac];
  u32 fwHandle;
  f32 _bc;
  u8 _c0[0xc4 - 0xc0];
  u32 flags;
  int pauseCount;
};

static_assert(offsetof(SoundSsdPlayer, bank) == 0x78, "");
static_assert(offsetof(SoundSsdPlayer, handle) == 0x88, "");
static_assert(offsetof(SoundSsdPlayer, category) == 0x98, "");
static_assert(offsetof(SoundSsdPlayer, pan) == 0xa8, "");
static_assert(offsetof(SoundSsdPlayer, fwHandle) == 0xb8, "");
static_assert(offsetof(SoundSsdPlayer, flags) == 0xc4, "");

} // namespace fw
