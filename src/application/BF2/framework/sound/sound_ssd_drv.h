#pragma once
#include <stddef.h>

#include "framework/pointer_map.h"
#include "framework/sound/sound_driver.h"
#include "framework/sound/sound_manager.h"
#include "ml/critical_section.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/internal/object_allocator.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/list.h"
#include "mm_mtl/map.h"
#include "mm_mtl/singleton.h"
#include "nn/audio.h"
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_param.h"
#include "types.h"

namespace csvb {
class CCsvbData;
} // namespace csvb

namespace ssd {
class SoundCore;
class SoundListener;
class WaveSource;
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
class SoundSsdSource;
enum SoundCategory : int;

// Layout from SoundSsdBank::create and the SoundSsdBank constructor (1.0.0: 0x71001a48e0, 0x71001a4bc8).
struct SoundBankSetup {
  SoundBankSetup() : unknown08(0), unknown10(""), unknown18(static_cast<SoundCategory>(0)), unknown1c(256) {}

  mm::mtl::IAllocator *unknown00; // Inferred role: allocator; original member name unknown.
  u32 unknown08;                  // Inferred role: id; original member name unknown.
  const char *unknown10;          // Inferred role: name; original member name unknown.
  SoundCategory unknown18;        // Inferred role: category; original member name unknown.
  u32 unknown1c;                  // Inferred role: max sound; original member name unknown.
};

static_assert(offsetof(SoundBankSetup, unknown08) == 0x08, "");
static_assert(offsetof(SoundBankSetup, unknown10) == 0x10, "");
static_assert(offsetof(SoundBankSetup, unknown18) == 0x18, "");
static_assert(offsetof(SoundBankSetup, unknown1c) == 0x1c, "");
static_assert(sizeof(SoundBankSetup) == 0x20, "");

// Inferred role: sound category data; original type name unknown.
// Layout from the SoundSsdDriver constructor and addCategory (1.0.0: 0x71001a587c, 0x71001a78c0): the constructor stores the vtable of
// ssd::SoundCategory at 0x00, so the category is a member, not a base.
struct unknown126 {
  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Sets the volume of the ssd category. SoundSsdDriver::setCategoryMute (1.0.0: 0x71001a79e8, 58 instructions) multiplies the four volume factors with both first fmul before the load of the
  // mute fade value (fmul, fmul, ldr s1, [x1, #0x28], fmul at 0x71001a7ab4-0x71001a7ac0), which clang gives only when the product is a named value: the argument of an inline function, or a local.
  // Forms tried without the helper, written in setCategoryMute, all 58 instructions with that load before the second fmul: the store of the product to unknown00.unknown08.unknown04, the product
  // accumulated in a local with *=, a reference to the ssd parameters or to the ssd category, a helper without argument that computes and stores the product, a helper that returns the product.
  // A local holding the product (f32 volume = ...;) matches too, but it is a single-use local of arithmetic; a setter on ssd::SoundCategory matches as well. setCategoryVolume (0x71001a7ad0)
  // and update (0x71001a6c8c) multiply the same factors in another operand order, so no helper computing the product can serve the three.
  void setVolume(f32 volume) { unknown00.unknown08.unknown04 = volume; }

  ssd::SoundCategory unknown00;  // Inferred role: ssd category; original member name unknown.
  f32 unknown10;                 // Inferred role: volume factor; original member name unknown.
  unknown129 unknown14;          // Inferred role: volume fade; original member name unknown.
  unknown129 unknown28;          // Inferred role: mute fade; original member name unknown.
  f32 unknown3c;                 // Inferred role: volume factor; original member name unknown.
  u32 unknown40;                 // Inferred role: mute count; original member name unknown.
  f32 unknown44;                 // Inferred role: pitch; original member name unknown.
  u32 unknown48;                 // Inferred role: registered; original member name unknown.
  mm::mtl::FixStr<16> unknown4c; // Inferred role: name; original member name unknown.
  bool unknown60;                // Inferred role: flag copied with the category, never set by the constructor; original member name unknown.
};

static_assert(offsetof(unknown126, unknown10) == 0x10, "");
static_assert(offsetof(unknown126, unknown14) == 0x14, "");
static_assert(offsetof(unknown126, unknown28) == 0x28, "");
static_assert(offsetof(unknown126, unknown3c) == 0x3c, "");
static_assert(offsetof(unknown126, unknown40) == 0x40, "");
static_assert(offsetof(unknown126, unknown44) == 0x44, "");
static_assert(offsetof(unknown126, unknown48) == 0x48, "");
static_assert(offsetof(unknown126, unknown4c) == 0x4c, "");
static_assert(offsetof(unknown126, unknown60) == 0x60, "");
static_assert(sizeof(unknown126) == 0x68, "");

struct SoundPoolMemory {
  static const u32 STATE_UNKNOWN_1 = 1; // Inferred role: attached; original name unknown.
  static const u32 STATE_UNKNOWN_2 = 2; // Inferred role: detach requested; original name unknown.
  static const u32 STATE_UNKNOWN_3 = 3; // Inferred role: detached; original name unknown.

  SoundPoolMemory(void *memory, u32 size) : unknown00(memory), unknown10(size), unknown14(STATE_UNKNOWN_1) {}

  // Inferred role: reset after the release of the memory pool; original name unknown.
  void unknown006() {
    unknown00 = nullptr;
    unknown10 = 0;
    unknown14 = STATE_UNKNOWN_3;
  }

  void *unknown00;                     // Inferred role: pool memory address; original member name unknown.
  nn::audio::MemoryPoolType unknown08; // Inferred role: audio renderer memory pool; original member name unknown.
  u32 unknown10;                       // Inferred role: pool memory size; original member name unknown.
  u32 unknown14;                       // Inferred role: state; original member name unknown.
};

static_assert(offsetof(SoundPoolMemory, unknown08) == 0x08, "");
static_assert(offsetof(SoundPoolMemory, unknown10) == 0x10, "");
static_assert(offsetof(SoundPoolMemory, unknown14) == 0x14, "");
static_assert(sizeof(SoundPoolMemory) == 0x18, "");

class SsdObjectAllocator {
public:
  template <typename T> static void deleteObject(T *object);
};

class SoundSsdDriver : public ISoundDriver, public mm::mtl::PtrSingleton<SoundSsdDriver> {
public:
  static const u32 CATEGORY_UNKNOWN_18 = 18; // Inferred role: number of categories; original name unknown.

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

  // Inferred helper: audio renderer config of the sound core of the driver singleton; original name unknown.
  static nn::audio::AudioRendererConfig *unknown004();

  // Inferred helper: requests the detach of an attached pool memory, or marks a pool without memory as detached; original name unknown.
  void unknown005(SoundPoolMemory *pool);

  SoundSsdDriver(mm::mtl::IAllocator *allocator, u32 capacity);
  ~SoundSsdDriver() override;
  void update(const UpdateInfo &info) override;
  bool finalize() override;
  void setMasterVolume(f32 volume) override;
  void setCategoryVolume(SoundCategory category, f32 volume, f32 time) override;
  void setCategoryMute(SoundCategory category, bool isMute, f32 time) override;
  void setOutputMode(SoundOutputType type) override;
  void addCategory(SoundCategory category, f32 volume, const char *name) override;
  u32 playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, SoundCategory category) override;
  u32 playVoice(const char *name, f32 volume, bool ignorePause, SoundCategory category) override;
  u32 playSe(const char *name, SoundPack *pack, f32 volume, SoundCategory category) override;
  u32 playSe(u32 id, SoundPack *pack, f32 volume, SoundCategory category) override;
  u32 playSeEx(const SoundPlayInfo &info, SoundResult &result) override;
  bool isDeviceEnable() const override;
  f32 getBgmVolume(const char *name);
  u32 getSoundHandleForFw(ssd::SoundHandle *handle);
  void updateBank();
  void updatePoolMemory();
  SoundSsdBank *findBank(u32 id);
  SoundSsdBank *findBank(u32 id) const;
  SoundSsdPlayer *getPlayer(u32 id);
  SoundSsdPlayer *getPlayer(u32 id) const;
  SoundSsdBank *findBank(const char *name);
  SoundSsdBank *findBank(const char *name) const;
  void registBank(const char *name, SoundSsdBank *bank);
  void removeBank(const char *name);
  u32 playStream(const char *name, f32 volume, bool ignorePause, SoundCategory category, SoundPriority priority, SoundSsdBank *bank, SoundType type);
  void applyCategoryVolume(SoundCategory category, f32 volume);
  bool isValid() const;
  void destroyResourceAll();
  const mm::Mat44 &getListeningPoint() const;
  void attachPoolMemory(void *memory, u32 size) override;
  void detachPoolMemory(void *memory, u32 size) override;
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

  ssd::SoundCore *unknown10;     // Inferred role: sound device; original member name unknown.
  SoundAllocator unknown18;      // Inferred role: allocator; original member name unknown.
  ssd::SoundListener *unknown28; // Inferred role: listener; original member name unknown.
  mm::Mat44 m_listeningPoint;
  ml::CriticalSection unknown70;                                  // Inferred role: lock; original member name unknown.
  ml::CriticalSectionNC unknown98;                                // Inferred role: lock; original member name unknown.
  ml::CriticalSection unknownc0;                                  // Inferred role: lock; original member name unknown.
  unknown126 unknowne8[CATEGORY_UNKNOWN_18];                      // Inferred role: categories; original member name unknown.
  mm::mtl::List<SoundSsdBank *> unknown838;                       // Inferred role: banks; original member name unknown.
  mm::mtl::List<ssd::SoundHandle *> unknown878;                   // Inferred role: handles waiting for release; original member name unknown.
  PointerMap unknown8b8;                                          // Inferred role: players; original member name unknown.
  mm::mtl::FixedList<SoundPoolMemory *, 256> unknown8f0;          // Inferred role: pool memories; original member name unknown.
  mm::mtl::Map<ssd::SoundHandle *, SoundSsdPlayer *> unknown1b10; // Inferred role: player of each handle; original member name unknown.
  mm::mtl::ObjectAllocator<ssd::SoundHandle> unknown1b28;         // Inferred role: handle allocator; original member name unknown.
  bool unknown1b60;                                               // Inferred role: initialized; original member name unknown.
  u32 unknown1b64;                                                // Inferred role: finalize state; original member name unknown.
  int unknown1b68;                                                // Inferred role: finalize wait counter; original member name unknown.
  csvb::CCsvbData *unknown1b70;                                   // Inferred role: bgm volume table; original member name unknown.
  u8 _1b78[0x1b80 - 0x1b78];
};

static_assert(offsetof(SoundSsdDriver::SoundAllocator, unknown08) == 0x08, "");
static_assert(offsetof(SoundSsdDriver, unknown10) == 0x10, "");
static_assert(offsetof(SoundSsdDriver, unknown18) == 0x18, "");
static_assert(offsetof(SoundSsdDriver, unknown28) == 0x28, "");
static_assert(offsetof(SoundSsdDriver, m_listeningPoint) == 0x30, "");
static_assert(offsetof(SoundSsdDriver, unknown70) == 0x70, "");
static_assert(offsetof(SoundSsdDriver, unknown98) == 0x98, "");
static_assert(offsetof(SoundSsdDriver, unknownc0) == 0xc0, "");
static_assert(offsetof(SoundSsdDriver, unknowne8) == 0xe8, "");
static_assert(sizeof(unknown126[SoundSsdDriver::CATEGORY_UNKNOWN_18]) == 0x750, "");
static_assert(offsetof(SoundSsdDriver, unknown838) == 0x838, "");
static_assert(offsetof(SoundSsdDriver, unknown878) == 0x878, "");
static_assert(offsetof(SoundSsdDriver, unknown8b8) == 0x8b8, "");
static_assert(offsetof(SoundSsdDriver, unknown8f0) == 0x8f0, "");
static_assert(sizeof(mm::mtl::FixedList<SoundPoolMemory *, 256>) == 0x1220, "");
static_assert(offsetof(SoundSsdDriver, unknown1b10) == 0x1b10, "");
static_assert(offsetof(SoundSsdDriver, unknown1b28) == 0x1b28, "");
static_assert(offsetof(SoundSsdDriver, unknown1b60) == 0x1b60, "");
static_assert(offsetof(SoundSsdDriver, unknown1b64) == 0x1b64, "");
static_assert(offsetof(SoundSsdDriver, unknown1b68) == 0x1b68, "");
static_assert(offsetof(SoundSsdDriver, unknown1b70) == 0x1b70, "");
// Size from the allocation in SoundManager::initialize (1.0.0: 0x710019ff18).
static_assert(sizeof(SoundSsdDriver) == 0x1b80, "");

class SoundReferenceObject {
public:
  SoundReferenceObject() : m_RefCount(0) {}
  virtual ~SoundReferenceObject() {}

  void addRef() { m_RefCount++; }
  int release();

  int m_RefCount;
};

class SoundSsdBank : public SoundReferenceObject {
public:
  // Layout from SoundSsdBank::addWave (1.0.0: 0x71001a5408).
  struct WaveInfo {
    const char *unknown00;   // Inferred role: path; original member name unknown.
    const char *unknown08;   // Inferred role: name; original member name unknown.
    void *unknown10;         // Inferred role: wave data; original member name unknown.
    u32 unknown18;           // Inferred role: wave data size; original member name unknown.
    SoundCategory unknown1c; // Inferred role: category; original member name unknown.
    SoundPriority unknown20; // Inferred role: priority; original member name unknown.
    bool unknown24;          // Inferred role: 3d sound; original member name unknown.
    f32 unknown28;           // Inferred role: minimum distance; original member name unknown.
    f32 unknown2c;           // Inferred role: volume; original member name unknown.
    f32 unknown30;           // Inferred role: maximum distance; original member name unknown.
    int unknown34;           // Inferred role: surround parameter; original member name unknown.
    int unknown38;           // Inferred role: percentage; original member name unknown.
    int unknown3c;           // Inferred role: percentage; original member name unknown.
    f32 unknown40;           // Inferred role: base parameter; original member name unknown.
    u16 unknown44;           // Inferred role: loop flag; original member name unknown.
  };

  static SoundManager::unknown130 m_bankUniqueID;

  static SoundSsdBank *create(const char *name, SoundCategory category, u32 maxSound);
  SoundSsdBank(const SoundBankSetup &setup);
  ~SoundSsdBank() override;
  void addEntry(ssd::SoundEntry *entry);
  void addSource(SoundSsdSource *source);
  void removeEntry(ssd::SoundEntry *entry);
  void removeSource(SoundSsdSource *source);
  void update();
  mm::mtl::List<SoundSsdSource *>::iterator findSource(const char *name);
  void setMaxSound(int maxSound);
  bool canRelease() const;
  void destroy();
  u32 getActivityRatio() const;
  void stopAll();
  mm::mtl::IntrusivePtr<SoundSsdSource> addWave(const WaveInfo &info);
  mm::mtl::IntrusivePtr<SoundSsdSource> addStream(const char *name, SoundCategory category, SoundPriority priority);

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

class SoundSsdSource : public SoundReferenceObject {
public:
  static const u32 FLAG_UNKNOWN_1 = 1 << 1; // Inferred role: 3d; original name unknown.

  // Layout from SoundSsdBank::addStream and the SoundSsdSource constructor (1.0.0: 0x71001a55fc, 0x71001a382c).
  struct SetupInfo {
    ssd::SoundParam unknown00; // Inferred role: sound parameters; original member name unknown.
    u8 _94[0x98 - 0x94];
    SoundCategory unknown98; // Inferred role: category; original member name unknown.
    u32 unknown9c;           // Inferred role: bank id; original member name unknown.
    const char *unknowna0;   // Inferred role: path; original member name unknown.
  };

  // Layout from SoundSsdBank::addWave and the SoundSsdSource constructor (1.0.0: 0x71001a5408, 0x71001a39e8).
  struct SetupWaveInfo : public SetupInfo {
    const char *unknowna8; // Inferred role: name; original member name unknown.
    void *unknownb0;       // Inferred role: wave data; original member name unknown.
    u32 unknownb8;         // Inferred role: wave data size; original member name unknown.
  };

  static SoundSsdSource *createStream(const SetupInfo &info);
  static SoundSsdSource *createWave(const SetupWaveInfo &info);
  SoundSsdSource(const SetupInfo &info);
  SoundSsdSource(const SetupWaveInfo &info);
  ~SoundSsdSource() override;
  bool isLoop() const;
  int getSourceRefCount() const;

  ssd::WaveSource *unknown10;      // Inferred role: wave source; original member name unknown.
  ssd::SoundEntry *unknown18;      // Inferred role: entry; original member name unknown.
  SoundSsdBank *unknown20;         // Inferred role: bank; original member name unknown.
  u32 unknown28;                   // Inferred role: bank id; original member name unknown.
  mm::mtl::FixStr<256> unknown2c;  // Inferred role: path; original member name unknown.
  u32 unknown130;                  // Inferred role: path hash; original member name unknown.
  mm::mtl::FixStr<256> unknown134; // Inferred role: name; original member name unknown.
  u32 unknown238;                  // Inferred role: name hash; original member name unknown.
  u32 unknown23c;                  // Inferred role: sound number; original member name unknown.
  u32 unknown240;                  // Inferred role: flags; original member name unknown.
  u32 unknown244;                  // Inferred role: set to 6 by the constructors; original member name unknown.
};

static_assert(sizeof(SoundSsdSource::SetupInfo) == 0xa8, "");
static_assert(offsetof(SoundSsdSource::SetupWaveInfo, unknownb8) == 0xb8, "");
static_assert(offsetof(SoundSsdSource, unknown10) == 0x10, "");
static_assert(offsetof(SoundSsdSource, unknown18) == 0x18, "");
static_assert(offsetof(SoundSsdSource, unknown28) == 0x28, "");
static_assert(offsetof(SoundSsdSource, unknown2c) == 0x2c, "");
static_assert(offsetof(SoundSsdSource, unknown130) == 0x130, "");
static_assert(offsetof(SoundSsdSource, unknown134) == 0x134, "");
static_assert(offsetof(SoundSsdSource, unknown238) == 0x238, "");
static_assert(offsetof(SoundSsdSource, unknown240) == 0x240, "");
static_assert(sizeof(SoundSsdSource) == 0x248, "");

class SoundSsdPlayer : public ssd::SoundActor3D {
public:
  static const u32 FLAG_UNKNOWN_1 = 1 << 1; // Inferred role: released; original name unknown.
  static const u32 FLAG_UNKNOWN_2 = 1 << 2; // Inferred role: stream; original name unknown.
  static const u32 FLAG_UNKNOWN_3 = 1 << 3; // Inferred role: listener; original name unknown.

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
