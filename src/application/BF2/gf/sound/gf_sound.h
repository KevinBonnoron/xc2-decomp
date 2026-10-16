#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
enum SoundCategory : int;
}

namespace gf {

class SoundHandle {
public:
  void clear();
  SoundHandle();
  bool isValid() const;

private:
  u32 handle;
  u32 id;
};

static_assert(sizeof(SoundHandle) == 0x08, "");
static_assert(alignof(SoundHandle) == 0x04, "");

class GfSound : public mm::mtl::PtrSingleton<GfSound> {
public:
  void setupGame();
  SoundHandle playSe(const char *name, fw::SoundCategory category);
  void stopSe(SoundHandle handle, f32 fadeSec);
  void setPause(SoundHandle handle, bool isPause, f32 fadeSec);
  void setPan(SoundHandle handle, f32 pan, f32 fadeSec);
  bool getPlayTime(SoundHandle handle, f32 &time) const;
  bool getTotalTime(SoundHandle handle, f32 &time) const;
  void setVolume(SoundHandle handle, f32 volume, f32 fadeSec);
  f32 getVolume(SoundHandle handle);
  bool isPlaying(SoundHandle handle) const;
};

} // namespace gf
