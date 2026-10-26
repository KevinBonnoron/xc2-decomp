#pragma once
#include <stddef.h>

#include "framework/pointer_map.h"
#include "framework/sound/sound_driver.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/list.h"
#include "mm_mtl/singleton.h"
#include "ssd/ssd_sound.h"
#include "types.h"

namespace ssd {
class SoundCore;
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
class SoundSsdPlayer;
enum SoundCategory : int;
enum SoundType : int;

struct SoundCategoryData {
  u8 _00[8];
  u32 unknown08; // Inferred role: category id; original member name unknown.
  f32 unknown0c; // Inferred role: volume; original member name unknown.
  u8 _10[0x14 - 0x10];
  f32 unknown14; // Inferred role: current volume; original member name unknown.
  u8 _18[0x40 - 0x18];
  u32 unknown40; // Inferred role: mute count; original member name unknown.
  u8 _44[0x48 - 0x44];
  u32 unknown48;                 // Inferred role: registered; original member name unknown.
  mm::mtl::FixStr<16> unknown4c; // Inferred role: name; original member name unknown.
  u8 _60[0x68 - 0x60];
};

static_assert(offsetof(SoundCategoryData, unknown08) == 0x08, "");
static_assert(offsetof(SoundCategoryData, unknown40) == 0x40, "");
static_assert(offsetof(SoundCategoryData, unknown48) == 0x48, "");
static_assert(offsetof(SoundCategoryData, unknown4c) == 0x4c, "");
static_assert(sizeof(SoundCategoryData) == 0x68, "");

class SoundSsdDriver : public ISoundDriver, public mm::mtl::PtrSingleton<SoundSsdDriver> {
public:
  static const u32 CATEGORY_COUNT = 18;

  class SoundAllocator : public ssd::Allocator {
  public:
    void *AllocInstance(size_t size) override;
    void FreeInstance(void *pointer) override;
    void *AllocBuffer(size_t size, size_t alignment) override;
    void FreeBuffer(void *pointer) override;
    void *AllocStream(size_t size, size_t alignment) override;
    void FreeStream(void *pointer) override;

    mm::mtl::IAllocator *unknown08; // Inferred role: allocator; original member name unknown.
  };

  ~SoundSsdDriver() override;
  SoundSsdBank *findBank(u32 id);
  SoundSsdBank *findBank(u32 id) const;
  SoundSsdPlayer *getPlayer(u32 id);
  SoundSsdPlayer *getPlayer(u32 id) const;
  SoundSsdBank *findBank(const char *name);
  SoundSsdBank *findBank(const char *name) const;
  void applyCategoryVolume(SoundCategory category, f32 volume);
  bool isValid() const;
  const mm::Mat44 &getListeningPoint() const;
  SoundCategoryData *findCategory(SoundCategory category);
  const SoundCategoryData *findCategory(SoundCategory category) const;
  void removeCategory(SoundCategory category);
  u32 registPlayer(SoundSsdPlayer *player, SoundType type);
  f32 getCategoryVolume(SoundCategory category) const;

  ssd::SoundCore *unknown10; // Inferred role: sound device; original member name unknown.
  u8 _18[0x30 - 0x18];
  mm::Mat44 unknown30; // Inferred role: listening point; original member name unknown.
  u8 _70[0xe8 - 0x70];
  SoundCategoryData unknowne8[CATEGORY_COUNT]; // Inferred role: categories; original member name unknown.
  mm::mtl::List<SoundSsdBank *> unknown838;    // Inferred role: banks; original member name unknown.
  u8 _878[0x8b8 - 0x878];
  PointerMap unknown8b8; // Inferred role: players; original member name unknown.
};

static_assert(offsetof(SoundSsdDriver::SoundAllocator, unknown08) == 0x08, "");
static_assert(offsetof(SoundSsdDriver, unknown10) == 0x10, "");
static_assert(offsetof(SoundSsdDriver, unknown30) == 0x30, "");
static_assert(offsetof(SoundSsdDriver, unknowne8) == 0xe8, "");
static_assert(sizeof(SoundCategoryData[SoundSsdDriver::CATEGORY_COUNT]) == 0x750, "");
static_assert(offsetof(SoundSsdDriver, unknown838) == 0x838, "");
static_assert(offsetof(SoundSsdDriver, unknown8b8) == 0x8b8, "");

class SoundReferenceObject {
public:
  virtual ~SoundReferenceObject();

  void addRef() { m_RefCount++; }
  int release();

  int m_RefCount;
};

class SoundSsdSource;

class SoundSsdBank : public SoundReferenceObject {
public:
  void addEntry(ssd::SoundEntry *entry);
  void addSource(SoundSsdSource *source);
  void removeEntry(ssd::SoundEntry *entry);
  void removeSource(SoundSsdSource *source);
  void setMaxSound(int maxSound);
  bool canRelease() const;
  u32 getActivityRatio() const;
  void stopAll();

  ssd::SoundBank unknown10;                   // Inferred role: sound bank; original member name unknown.
  ssd::SoundGroup unknown130;                 // Inferred role: sound group; original member name unknown.
  SoundCategory unknown150;                   // Inferred role: category; original member name unknown.
  mm::mtl::FixStr<256> unknown154;            // Inferred role: name; original member name unknown.
  u32 unknown258;                             // Inferred role: name hash; original member name unknown.
  u32 unknown25c;                             // Inferred role: id; original member name unknown.
  int unknown260;                             // Inferred role: max sound; original member name unknown.
  mm::mtl::IAllocator *unknown268;            // Inferred role: allocator; original member name unknown.
  mm::mtl::List<SoundSsdSource *> unknown270; // Inferred role: sources; original member name unknown.
};

static_assert(offsetof(SoundSsdBank, unknown10) == 0x10, "");
static_assert(offsetof(SoundSsdBank, unknown130) == 0x130, "");
static_assert(offsetof(SoundSsdBank, unknown154) == 0x154, "");
static_assert(offsetof(SoundSsdBank, unknown25c) == 0x25c, "");
static_assert(offsetof(SoundSsdBank, unknown270) == 0x270, "");
static_assert(sizeof(SoundSsdBank) == 0x2b0, "");

struct SoundSsdSourceData {
  u8 _00[0x50 - 0x00];
  bool isLoop;
  u8 _51[0x6c - 0x51];
  int refCount;
};

class SoundSsdSource : public SoundReferenceObject {
public:
  static const u8 FLAG_3D = 1 << 1;

  bool isLoop() const;
  int getSourceRefCount() const;

  u8 _0c[0x10 - 0x0c];
  SoundSsdSourceData *unknown10; // Inferred role: data; original member name unknown.
  ssd::SoundEntry *unknown18;    // Inferred role: entry; original member name unknown.
  u8 _20[0x240 - 0x20];
  u8 unknown240; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(SoundSsdSource, unknown18) == 0x18, "");
static_assert(offsetof(SoundSsdSource, unknown240) == 0x240, "");

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

  SoundSsdBank *unknown78;                         // Inferred role: bank; original member name unknown.
  mm::mtl::IntrusivePtr<SoundSsdSource> unknown80; // Inferred role: source; original member name unknown.
  ssd::SoundHandle *unknown88;                     // Inferred role: handle; original member name unknown.
  ssd::SoundListener *unknown90;                   // Inferred role: listener; original member name unknown.
  SoundCategory unknown98;                         // Inferred role: category; original member name unknown.
  f32 unknown9c;                                   // Inferred role: volume; original member name unknown.
  f32 unknowna0;                                   // Inferred role: fade time; original member name unknown.
  f32 unknowna4;                                   // Inferred role: pitch; original member name unknown.
  f32 unknowna8;                                   // Inferred role: pan; original member name unknown.
  u8 _ac[0xb8 - 0xac];
  u32 m_handle;
  f32 _bc;
  u8 _c0[0xc4 - 0xc0];
  u32 unknownc4; // Inferred role: flags; original member name unknown.
  int unknownc8; // Inferred role: pause count; original member name unknown.
};

static_assert(offsetof(SoundSsdPlayer, unknown78) == 0x78, "");
static_assert(offsetof(SoundSsdPlayer, unknown88) == 0x88, "");
static_assert(offsetof(SoundSsdPlayer, unknown98) == 0x98, "");
static_assert(offsetof(SoundSsdPlayer, unknowna8) == 0xa8, "");
static_assert(offsetof(SoundSsdPlayer, m_handle) == 0xb8, "");
static_assert(offsetof(SoundSsdPlayer, unknownc4) == 0xc4, "");

} // namespace fw
