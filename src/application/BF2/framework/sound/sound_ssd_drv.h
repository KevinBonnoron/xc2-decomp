#pragma once
#include <stddef.h>

#include "framework/pointer_map.h"
#include "framework/sound/sound_driver.h"
#include "ml/critical_section.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/list.h"
#include "mm_mtl/singleton.h"
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_sound.h"
#include "types.h"

namespace ssd {
class SoundCore;
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
struct SoundCategoryDebugInfo;
struct SoundHandleDebugInfo;

// Inferred role: sound category data; original type name unknown.
struct unknown126 {
  u8 _00[8];
  u32 unknown08; // Inferred role: category id; original member name unknown.
  f32 unknown0c; // Inferred role: volume; original member name unknown.
  u8 _10[0x14 - 0x10];
  f32 unknown14; // Inferred role: current volume; original member name unknown.
  u8 _18[0x40 - 0x18];
  u32 unknown40;                 // Inferred role: mute count; original member name unknown.
  f32 unknown44;                 // Inferred role: pitch; original member name unknown.
  u32 unknown48;                 // Inferred role: registered; original member name unknown.
  mm::mtl::FixStr<16> unknown4c; // Inferred role: name; original member name unknown.
  u8 _60[0x68 - 0x60];
};

static_assert(offsetof(unknown126, unknown08) == 0x08, "");
static_assert(offsetof(unknown126, unknown40) == 0x40, "");
static_assert(offsetof(unknown126, unknown44) == 0x44, "");
static_assert(offsetof(unknown126, unknown48) == 0x48, "");
static_assert(offsetof(unknown126, unknown4c) == 0x4c, "");
static_assert(sizeof(unknown126) == 0x68, "");

struct SoundPoolMemory {
  void *unknown00; // Inferred role: pool memory address; original member name unknown.
  u8 _08[0x10 - 0x08];
  u32 unknown10; // Inferred role: pool memory size; original member name unknown.
  u32 unknown14; // Inferred role: state; original member name unknown.
};

static_assert(offsetof(SoundPoolMemory, unknown10) == 0x10, "");
static_assert(offsetof(SoundPoolMemory, unknown14) == 0x14, "");
static_assert(sizeof(SoundPoolMemory) == 0x18, "");

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

  // Inferred helper: holds the lock while a handle is resolved to its player; original name unknown.
  class unknown001 {
  public:
    unknown001(SoundSsdDriver &driver, u32 handle) : unknown00(driver.unknown70), unknown08(driver.unknown8b8.isValid(handle) ? driver.getPlayer(handle) : nullptr) {}

    ml::CS unknown00;          // Inferred role: driver lock held during the access; original member name unknown.
    SoundSsdPlayer *unknown08; // Inferred role: player of the handle; original member name unknown.
  };

  ~SoundSsdDriver() override;
  void updateBank();
  SoundSsdBank *findBank(u32 id);
  SoundSsdBank *findBank(u32 id) const;
  SoundSsdPlayer *getPlayer(u32 id);
  SoundSsdPlayer *getPlayer(u32 id) const;
  SoundSsdBank *findBank(const char *name);
  SoundSsdBank *findBank(const char *name) const;
  void applyCategoryVolume(SoundCategory category, f32 volume);
  bool isValid() const;
  const mm::Mat44 &getListeningPoint() const;
  SoundPoolMemory *findPoolMemory(void *pointer, u32 size) const;
  void setListeningPoint(const mm::Mat44 &matrix);
  unknown126 *findCategory(SoundCategory category);
  const unknown126 *findCategory(SoundCategory category) const;
  void removeCategory(SoundCategory category);
  u32 registPlayer(SoundSsdPlayer *player, SoundType type);
  f32 getCategoryVolume(SoundCategory category) const;
  bool isValid(u32 handle) const override;
  bool isPlaying(u32 handle) const override;
  bool isPreparing(u32 handle) const override;
  bool isReady(u32 handle) const override;
  bool isLoop(u32 handle) override;
  bool isPause(u32 handle) const override;
  void setCategory(u32 handle, SoundCategory category) override;
  SoundCategory getCategory(u32 handle) override;
  void setVolume(u32 handle, f32 volume, f32 time) override;
  f32 getVolume(u32 handle, SoundVolumeType type) override;
  void setPitch(u32 handle, f32 pitch, f32 time) override;
  void setPan(u32 handle, f32 pan, f32 time) override;
  void setPos(u32 handle, const mm::Vec3 &position) override;
  bool setPlayTime(u32 handle, f32 time) override;
  bool getPlayTime(u32 handle, f32 &time) override;
  bool getTotalTime(u32 handle, f32 &time) override;
  bool setRemainLoopCount(u32 handle, int count) override;
  bool getRemainLoopCount(u32 handle, int &count) override;
  void pause(u32 handle, bool isPause, f32 time) override;
  bool startBgm(u32 handle) override;
  bool startVoice(u32 handle) override;
  bool stopSound(u32 handle, f32 time);
  void stopSoundAll(SoundType type, f32 time);
  bool stopBgm(u32 handle, f32 time) override;
  bool stopVoice(u32 handle, f32 time) override;
  bool stopSe(u32 handle, f32 time) override;
  void stopBgmAll() override;
  void stopVoiceAll() override;
  void stopSeAll() override;
  void stopAll() override;
  void pauseAll(bool isPause, f32 time) override;
  u32 findSe(const char *name) const override;
  bool isLoop(u32 id, SoundPack *pack) override;
  void pauseCategory(SoundCategory category, bool isPause, f32 time) override;
  void setCategoryPitch(SoundCategory category, f32 pitch, f32 time) override;
  void updateDebugInfo(mm::mtl::FixedVector<SoundHandleDebugInfo, 128> &handles, mm::mtl::FixedVector<SoundCategoryDebugInfo, 18> &categories) override;
  void updateDebugInfoLocal(mm::mtl::FixedVector<SoundHandleDebugInfo, 128> &handles);
  void updateDebugInfoLocal(mm::mtl::FixedVector<SoundCategoryDebugInfo, 18> &categories);

  ssd::SoundCore *unknown10;                // Inferred role: sound device; original member name unknown.
  SoundAllocator unknown18;                 // Inferred role: allocator; original member name unknown.
  ssd::SoundListener *unknown28;            // Inferred role: listener; original member name unknown.
  mm::Mat44 unknown30;                      // Inferred role: listening point; original member name unknown.
  ml::CriticalSection unknown70;            // Inferred role: lock; original member name unknown.
  ml::CriticalSectionNC unknown98;          // Inferred role: lock; original member name unknown.
  ml::CriticalSection unknownc0;            // Inferred role: lock; original member name unknown.
  unknown126 unknowne8[CATEGORY_COUNT];     // Inferred role: categories; original member name unknown.
  mm::mtl::List<SoundSsdBank *> unknown838; // Inferred role: banks; original member name unknown.
  u8 _878[0x8b8 - 0x878];
  PointerMap unknown8b8;                                 // Inferred role: players; original member name unknown.
  mm::mtl::FixedList<SoundPoolMemory *, 256> unknown8f0; // Inferred role: pool memories; original member name unknown.
};

static_assert(offsetof(SoundSsdDriver::SoundAllocator, unknown08) == 0x08, "");
static_assert(offsetof(SoundSsdDriver, unknown10) == 0x10, "");
static_assert(offsetof(SoundSsdDriver, unknown18) == 0x18, "");
static_assert(offsetof(SoundSsdDriver, unknown28) == 0x28, "");
static_assert(offsetof(SoundSsdDriver, unknown30) == 0x30, "");
static_assert(offsetof(SoundSsdDriver, unknown70) == 0x70, "");
static_assert(offsetof(SoundSsdDriver, unknown98) == 0x98, "");
static_assert(offsetof(SoundSsdDriver, unknownc0) == 0xc0, "");
static_assert(offsetof(SoundSsdDriver, unknowne8) == 0xe8, "");
static_assert(sizeof(unknown126[SoundSsdDriver::CATEGORY_COUNT]) == 0x750, "");
static_assert(offsetof(SoundSsdDriver, unknown838) == 0x838, "");
static_assert(offsetof(SoundSsdDriver, unknown8b8) == 0x8b8, "");
static_assert(offsetof(SoundSsdDriver, unknown8f0) == 0x8f0, "");
static_assert(sizeof(mm::mtl::FixedList<SoundPoolMemory *, 256>) == 0x1220, "");

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
  void update();
  mm::mtl::List<SoundSsdSource *>::iterator findSource(const char *name);
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

// Inferred role: sound ssd source data; original type name unknown.
struct unknown127 {
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
  unknown127 *unknown10;      // Inferred role: data; original member name unknown.
  ssd::SoundEntry *unknown18; // Inferred role: entry; original member name unknown.
  u8 _20[0x134 - 0x20];
  mm::mtl::FixStr<256> unknown134; // Inferred role: name; original member name unknown.
  u8 _238[0x240 - 0x238];
  u8 unknown240; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(SoundSsdSource, unknown18) == 0x18, "");
static_assert(offsetof(SoundSsdSource, unknown134) == 0x134, "");
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
  u8 _ac[0xb0 - 0xac];
  SoundType unknownb0; // Inferred role: sound type; original member name unknown.
  u8 _b4[0xb8 - 0xb4];
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
static_assert(offsetof(SoundSsdPlayer, unknownb0) == 0xb0, "");
static_assert(offsetof(SoundSsdPlayer, m_handle) == 0xb8, "");
static_assert(offsetof(SoundSsdPlayer, unknownc4) == 0xc4, "");

} // namespace fw
