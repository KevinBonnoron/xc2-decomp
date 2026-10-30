#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;

namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class ResourceObject;
class SoundPack;
struct UpdateInfo;
class ISoundDriver;
enum SoundCategory : int;
enum SoundOutputType : int;
enum SoundVolumeType : int;

// Inferred role: sound volume fade; original type name unknown.
struct unknown129 {
  void start(f32 target, f32 fadeTime) {
    if (fadeTime > 0.0f) {
      unknown08 = unknown00;
    } else {
      fadeTime = 0.0f;
      unknown00 = target;
      unknown08 = target;
    }

    unknown04 = target;
    unknown0c = fadeTime;
    unknown10 = 0.0f;
  }

  void update(f32 deltaTime) {
    unknown10 += deltaTime;
    if (unknown10 >= unknown0c) {
      unknown10 = unknown0c;
      unknown00 = unknown04;
    } else {
      unknown00 = unknown08 + (unknown04 - unknown08) * (unknown10 / unknown0c);
    }
  }

  f32 unknown00; // Inferred role: volume; original member name unknown.
  f32 unknown04; // Inferred role: target volume; original member name unknown.
  f32 unknown08; // Inferred role: start volume; original member name unknown.
  f32 unknown0c; // Inferred role: duration; original member name unknown.
  f32 unknown10; // Inferred role: time; original member name unknown.
};

class SoundManager : public ManagerObject, public mm::mtl::PtrSingleton<SoundManager> {
public:
  // Inferred role: unique id; original type name unknown.
  struct unknown130 {
    u32 unknown00; // Inferred role: current; original member name unknown.
    u32 unknown04; // Inferred role: min; original member name unknown.
    u32 unknown08; // Inferred role: max; original member name unknown.
  };

  static const u32 BATTLE_RESOURCE_MAX = 3;

  static unknown130 m_uniqueID;

  ~SoundManager();
  bool initialize() override;
  bool finalize() override;
  const char *getName() const override;
  virtual void update(const UpdateInfo &info);
  virtual void tail(const UpdateInfo &info);
  void attachPoolMemory(void *memory, u32 size);
  void addCategory(SoundCategory category, f32 volume, const char *name);
  void pauseAll(bool isPause, f32 time);
  f32 getMasterVolume() const;
  static mm::mtl::IAllocator *getProcAllocator();
  static u32 getUniqueID(SoundCategory category);
  void setListeningPoint(const mm::Mat44 &matrix);
  const mm::Mat44 &getListeningPoint() const;
  void setOutputMode(SoundOutputType type);
  void removeCategory(SoundCategory category);
  void setCategoryVolume(SoundCategory category, f32 volume, f32 time);
  f32 getCategoryVolume(SoundCategory category) const;
  void setCategoryMute(SoundCategory category, bool isMute, f32 time);
  void setCategoryPitch(SoundCategory category, f32 pitch, f32 time);
  bool isSoundEbable() const;
  u32 playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, SoundCategory category);
  bool isPauseAll() const;
  bool startBgm(u32 handle);
  void stopBgm(u32 handle, f32 time);
  u32 playVoice(const char *name, f32 volume, bool ignorePause, SoundCategory category);
  bool startVoice(u32 handle);
  void stopVoice(u32 handle, f32 time);
  SoundPack *getCommonPack();
  SoundPack *findPack(const char *name, mm::mtl::IAllocator *allocator);
  u32 playSe(const char *name, SoundPack *pack, f32 volume, SoundCategory category);
  u32 playSe(u32 id, SoundPack *pack, f32 volume, SoundCategory category);
  void stopSe(u32 handle, f32 time);
  u32 findSe(const char *name) const;
  u32 getSoundType(u32 handle) const;
  bool isValid(u32 handle) const;
  bool isPlaying(u32 handle) const;
  bool isPause(u32 handle) const;
  bool isPreparing(u32 handle) const;
  bool isPrepared(u32 handle) const;
  void setCategory(u32 handle, SoundCategory category);
  void setVolume(u32 handle, f32 volume, f32 time);
  f32 getVolume(u32 handle, SoundVolumeType type);
  void setPitch(u32 handle, f32 pitch, f32 time);
  void setPan(u32 handle, f32 pan, f32 time);
  void setPos(u32 handle, const mm::Vec3 &position);
  bool setPlayTime(u32 handle, f32 time);
  bool getPlayTime(u32 handle, f32 &time);
  bool getTotalTime(u32 handle, f32 &time);
  bool isLoop(u32 handle);
  bool isLoop(u32 id, SoundPack *pack);
  bool setRemainLoopCount(u32 handle, int count);
  bool getRemainLoopCount(u32 handle, int &count);
  void pause(u32 handle, bool isPause, f32 time);
  void pauseCategory(SoundCategory category, bool isPause, f32 time);
  void stopAll();
  void stopVoiceAll();
  void stopBgmAll();
  void stopSeAll();
  void registPack(SoundPack *pack);
  void loadCommonSe();
  void loadBattleSe();
  bool isRegistPack(SoundPack *pack) const;
  bool isCommonLoaded() const;
  SoundPack *getBattlePack();
  bool isBattleLoaded() const;
  void detachPoolMemory(void *memory, u32 size);
  void setMasterVolume(f32 volume, f32 time);
  f32 getMasterVolumeOrg() const;
  void setMasterMute(bool isMute, f32 time);

  ISoundDriver *unknown18; // Inferred role: driver; original member name unknown.
  u8 _20[0x6c - 0x20];
  unknown129 m_masterVolumeOrg;
  unknown129 unknown80; // Inferred role: mute fade; original member name unknown.
  int unknown94;        // Inferred role: pause count; original member name unknown.
  bool unknown98;       // Inferred role: sound enable; original member name unknown.
  u8 _99[0xa0 - 0x99];
  mm::mtl::List<SoundPack *> unknowna0;           // Inferred role: packs; original member name unknown.
  ResourceObject *unknowne0;                      // Inferred role: common resource; original member name unknown.
  ResourceObject *unknowne8[BATTLE_RESOURCE_MAX]; // Inferred role: battle resources; original member name unknown.
};

static_assert(offsetof(SoundManager, unknown18) == 0x18, "");
static_assert(offsetof(SoundManager, m_masterVolumeOrg) == 0x6c, "");
static_assert(offsetof(SoundManager, unknown80) == 0x80, "");
static_assert(offsetof(SoundManager, unknown94) == 0x94, "");
static_assert(offsetof(SoundManager, unknown98) == 0x98, "");
static_assert(offsetof(SoundManager, unknowna0) == 0xa0, "");
static_assert(offsetof(SoundManager, unknowne0) == 0xe0, "");

} // namespace fw
