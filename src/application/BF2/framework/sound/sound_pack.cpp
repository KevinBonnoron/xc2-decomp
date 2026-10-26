#include "framework/sound/sound_pack.h"

#include "framework/sound/sound_ssd_drv.h"

namespace fw {

void SoundPack::stopAll() {
  if (unknown178 != nullptr) {
    unknown178->stopAll();
  }
}

bool SoundPack::canRelease() const {
  if (unknown178 != nullptr) {
    return unknown178->canRelease();
  }

  return true;
}

mm::mtl::IntrusivePtr<SoundSsdSource> SoundPack::getSource(u32 index) const { return unknown180[index]; }

mm::mtl::IntrusivePtr<SoundSsdSource> SoundPack::findSourceFromID(u32 id) const {
  for (u32 i = 0; i < unknown988.size(); i++) {
    if (unknown988[i].unknown00 == id) {
      return unknown180[i];
    }
  }

  return nullptr;
}

bool SoundPack::isLoopSource(u32 id) const {
  for (u32 i = 0; i < unknown988.size(); i++) {
    if (unknown988[i].unknown00 == id) {
      SoundSsdSource *source = unknown180[i];
      if (source == nullptr) {
        return false;
      }

      mm::mtl::IntrusivePtr<SoundSsdSource> hold(source);
      return source->isLoop();
    }
  }

  return false;
}

} // namespace fw
