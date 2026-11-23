#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace fw {

class SoundPack;

// Layout from SoundManager::disp3DPoint (1.0.0: 0x71001a0e98): elements of 0x80 bytes, the name at 0x00, a flag at 0x2c, the position at 0x40.
struct SoundHandleDebugInfo {
  u8 _00[0x40];
  mm::Vec3 unknown40; // Inferred role: position; original member name unknown.
  u8 _50[0x80 - 0x50];
};

static_assert(offsetof(SoundHandleDebugInfo, unknown40) == 0x40, "");
static_assert(sizeof(SoundHandleDebugInfo) == 0x80, "");

// Size from the SoundManager layout (1.0.0: 0x710019fafc): 18 elements between 0x4110 and the size at 0x4470.
struct SoundCategoryDebugInfo {
  u8 _00[0x30];
};

static_assert(sizeof(SoundCategoryDebugInfo) == 0x30, "");

struct UpdateInfo;

enum SoundPriority : int {
  SOUND_PRIORITY_UNKNOWN_254 = 254, // Inferred role: priority of the streams of the voice bank; original name unknown.
  SOUND_PRIORITY_UNKNOWN_255 = 255, // Inferred role: priority of the streams of the bgm bank; original name unknown.
};

enum SoundCategory : int;
enum SoundOutputType : int;

// Inferred role: request of ISoundDriver::playSeEx; original member names unknown. Types from the accesses of
// SoundSsdDriver::playSeEx (0x71001a9580): the pack (x), the id (w), the volume (s) and the category (w) that it passes to
// playSeLocal, the flag (b) that selects the position (a Vec3 passed by address) at 0x20. The game (0x71001a1bbc,
// SoundManager::playSeEx) copies the request field by field (one load and store per member, the Vec3 through its own copy
// constructor, nothing from the padding), where the implicit copy constructor moves the members before the position as
// one block (81 instructions against 84): the original declares a copy constructor, which has no symbol, being inline
// (P1, decision of 2026-11-14).
struct SoundPlayInfo {
  SoundPlayInfo(const SoundPlayInfo &other)
      : m_soundPack(other.m_soundPack), unknown08(other.unknown08), unknown0c(other.unknown0c), unknown10(other.unknown10), unknown14(other.unknown14), unknown20(other.unknown20) {}

  SoundPack *m_soundPack;  // Inferred role: pack, the common pack when null; original member name unknown.
  u32 unknown08;           // Inferred role: sound id; original member name unknown.
  f32 unknown0c;           // Inferred role: volume; original member name unknown.
  SoundCategory unknown10; // Inferred role: category; original member name unknown.
  bool unknown14;          // Inferred role: set when the position is used; original member name unknown.
  mm::Vec3 unknown20;      // Inferred role: position; original member name unknown.
};

// Inferred role: result of ISoundDriver::playSeEx; original member names unknown.
struct SoundResult {
  u32 unknown00; // Inferred role: handle; original member name unknown.
  u32 unknown04; // Inferred role: status, 3 until a sound is started and 0 once it is; original member name unknown.
};

static_assert(offsetof(SoundPlayInfo, unknown08) == 0x08, "");
static_assert(offsetof(SoundPlayInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(SoundPlayInfo, unknown10) == 0x10, "");
static_assert(offsetof(SoundPlayInfo, unknown14) == 0x14, "");
static_assert(offsetof(SoundPlayInfo, unknown20) == 0x20, "");
static_assert(sizeof(SoundPlayInfo) == 0x30, "");
static_assert(sizeof(SoundResult) == 0x08, "");

enum SoundType : int {
  SOUND_TYPE_UNKNOWN_1 = 1, // Inferred role: bgm; original name unknown.
  SOUND_TYPE_UNKNOWN_2 = 2, // Inferred role: voice; original name unknown.
  SOUND_TYPE_UNKNOWN_3 = 3, // Inferred role: se; original name unknown.
};

enum SoundVolumeType : int {
  SOUND_VOLUME_TYPE_UNKNOWN_0 = 0, // Inferred role: handle; original name unknown.
  SOUND_VOLUME_TYPE_UNKNOWN_1 = 1, // Inferred role: distance; original name unknown.
  SOUND_VOLUME_TYPE_UNKNOWN_2 = 2, // Inferred role: category; original name unknown.
};

class ISoundDriver {
public:
  virtual ~ISoundDriver() {}
  virtual void update(const UpdateInfo &info) = 0;
  virtual bool finalize() = 0;
  virtual void updateDebugInfo(mm::mtl::FixedVector<SoundHandleDebugInfo, 128> &handles, mm::mtl::FixedVector<SoundCategoryDebugInfo, 18> &categories) = 0;
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
  virtual bool isDeviceEnable() const;
  virtual u32 playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, SoundCategory category) = 0;
  virtual bool startBgm(u32 handle) = 0;
  virtual bool stopBgm(u32 handle, f32 time) = 0;
  virtual void stopBgmAll() = 0;
  virtual u32 playVoice(const char *name, f32 volume, bool ignorePause, SoundCategory category) = 0;
  virtual bool startVoice(u32 handle) = 0;
  virtual bool stopVoice(u32 handle, f32 time) = 0;
  virtual u32 playSe(const char *name, SoundPack *pack, f32 volume, SoundCategory category) = 0;
  virtual u32 playSe(u32 id, SoundPack *pack, f32 volume, SoundCategory category) = 0;
  virtual u32 playSeEx(const SoundPlayInfo &info, SoundResult &result) = 0;
  virtual bool stopSe(u32 handle, f32 time) = 0;
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
  virtual void attachPoolMemory(void *memory, u32 size);
  virtual void detachPoolMemory(void *memory, u32 size);
};

} // namespace fw
