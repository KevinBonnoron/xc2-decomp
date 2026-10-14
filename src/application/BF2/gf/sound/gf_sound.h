#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class SoundHandle {
public:
  void clear();
  SoundHandle();
  bool isValid() const;

private:
  u64 mHandle;
};

static_assert(sizeof(SoundHandle) == 0x08, "");

class GfSound : public mm::mtl::PtrSingleton<GfSound> {
public:
  void setupGame();
  void stopSe(SoundHandle handle, f32 fadeSec);
  void setVolume(SoundHandle handle, f32 volume, f32 fadeSec);
  bool isPlaying(SoundHandle handle) const;
};

} // namespace gf
