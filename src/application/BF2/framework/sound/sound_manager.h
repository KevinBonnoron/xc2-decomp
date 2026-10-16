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

struct SoundVolumeFade {
  void start(f32 target, f32 fadeTime) {
    if (fadeTime > 0.0f) {
      startVolume = volume;
    } else {
      fadeTime = 0.0f;
      volume = target;
      startVolume = target;
    }

    targetVolume = target;
    duration = fadeTime;
    time = 0.0f;
  }

  void update(f32 deltaTime) {
    time += deltaTime;
    if (time >= duration) {
      time = duration;
      volume = targetVolume;
    } else {
      volume = startVolume + (targetVolume - startVolume) * (time / duration);
    }
  }

  f32 volume;
  f32 targetVolume;
  f32 startVolume;
  f32 duration;
  f32 time;
};

class SoundManager : public ManagerObject, public mm::mtl::PtrSingleton<SoundManager> {
public:
  struct UniqueID {
    u32 current;
    u32 min;
    u32 max;
  };

  static const u32 BATTLE_RESOURCE_MAX = 3;

  static UniqueID m_uniqueID;

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
  bool isCommonLoaded() const;
  SoundPack *getBattlePack();
  bool isBattleLoaded() const;
  void detachPoolMemory(void *memory, u32 size);
  void setMasterVolume(f32 volume, f32 time);
  f32 getMasterVolumeOrg() const;
  void setMasterMute(bool isMute, f32 time);

  ISoundDriver *driver;
  u8 _20[0x6c - 0x20];
  SoundVolumeFade masterFade;
  SoundVolumeFade muteFade;
  int pauseCount;
  bool soundEnable;
  u8 _99[0xa0 - 0x99];
  mm::mtl::List<SoundPack *> packs;
  ResourceObject *commonResource;
  ResourceObject *battleResources[BATTLE_RESOURCE_MAX];
};

static_assert(offsetof(SoundManager, driver) == 0x18, "");
static_assert(offsetof(SoundManager, masterFade) == 0x6c, "");
static_assert(offsetof(SoundManager, muteFade) == 0x80, "");
static_assert(offsetof(SoundManager, pauseCount) == 0x94, "");
static_assert(offsetof(SoundManager, soundEnable) == 0x98, "");
static_assert(offsetof(SoundManager, packs) == 0xa0, "");
static_assert(offsetof(SoundManager, commonResource) == 0xe0, "");

} // namespace fw
