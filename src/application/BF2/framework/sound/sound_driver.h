#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace fw {

class SoundPack;
struct SoundCategoryDebugInfo;
struct SoundHandleDebugInfo;
struct SoundPlayInfo;
struct SoundResult;
struct UpdateInfo;
enum SoundCategory : int;
enum SoundOutputType : int;
enum SoundVolumeType : int;

class ISoundDriver {
public:
  virtual ~ISoundDriver() {}
  virtual void update(const UpdateInfo &info) = 0;
  virtual void finalize() = 0;
  virtual void updateDebugInfo(mm::mtl::FixedVector<SoundHandleDebugInfo, 128> &handles,
                               mm::mtl::FixedVector<SoundCategoryDebugInfo, 18> &categories) = 0;
  virtual void setListeningPoint(const mm::Mat44 &matrix) = 0;
  virtual const mm::Mat44 &getListeningPoint() const = 0;
  virtual void setMasterVolume(f32 volume) = 0;
  virtual void setCategoryVolume(SoundCategory category, f32 volume, f32 time) = 0;
  virtual f32 getCategoryVolume(SoundCategory category) const = 0;
  virtual void setCategoryMute(SoundCategory category, bool isMute, f32 time) = 0;
  virtual void setCategoryPitch(SoundCategory category, f32 pitch, f32 time) = 0;
  virtual void setOutputMode(SoundOutputType type) = 0;
  virtual void addCategory(SoundCategory category, f32 volume, const char *name) = 0;
  virtual void removeCategory(SoundCategory category) = 0;
  virtual void pauseCategory(SoundCategory category, bool isPause, f32 time) = 0;
  virtual bool isDeviceEnable() const { return false; }
  virtual u32 playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, SoundCategory category) = 0;
  virtual bool startBgm(u32 handle) = 0;
  virtual void stopBgm(u32 handle, f32 time) = 0;
  virtual void stopBgmAll() = 0;
  virtual u32 playVoice(const char *name, f32 volume, bool ignorePause, SoundCategory category) = 0;
  virtual bool startVoice(u32 handle) = 0;
  virtual void stopVoice(u32 handle, f32 time) = 0;
  virtual u32 playSe(const char *name, SoundPack *pack, f32 volume, SoundCategory category) = 0;
  virtual u32 playSe(u32 id, SoundPack *pack, f32 volume, SoundCategory category) = 0;
  virtual u32 playSeEx(const SoundPlayInfo &info, SoundResult &result) = 0;
  virtual void stopSe(u32 handle, f32 time) = 0;
  virtual bool isValid(u32 handle) const = 0;
  virtual bool isPlaying(u32 handle) const = 0;
  virtual bool isPreparing(u32 handle) const = 0;
  virtual bool isReady(u32 handle) const = 0;
  virtual bool isLoop(u32 handle) = 0;
  virtual bool isLoop(u32 id, SoundPack *pack) = 0;
  virtual bool isPause(u32 handle) const = 0;
  virtual void setCategory(u32 handle, SoundCategory category) = 0;
  virtual SoundCategory getCategory(u32 handle) = 0;
  virtual void setVolume(u32 handle, f32 volume, f32 time) = 0;
  virtual f32 getVolume(u32 handle, SoundVolumeType type) = 0;
  virtual void setPitch(u32 handle, f32 pitch, f32 time) = 0;
  virtual void setPan(u32 handle, f32 pan, f32 time) = 0;
  virtual void setPos(u32 handle, const mm::Vec3 &position) = 0;
  virtual bool setPlayTime(u32 handle, f32 time) = 0;
  virtual bool getPlayTime(u32 handle, f32 &time) = 0;
  virtual bool getTotalTime(u32 handle, f32 &time) = 0;
  virtual bool setRemainLoopCount(u32 handle, int count) = 0;
  virtual bool getRemainLoopCount(u32 handle, int &count) = 0;
  virtual void pause(u32 handle, bool isPause, f32 time) = 0;
  virtual void stopAll() = 0;
  virtual void stopVoiceAll() = 0;
  virtual void stopSeAll() = 0;
  virtual void pauseAll(bool isPause, f32 time) = 0;
  virtual u32 findSe(const char *name) const = 0;
  virtual void attachPoolMemory(void *memory, u32 size) {}
  virtual void detachPoolMemory(void *memory, u32 size) {}
};

} // namespace fw
