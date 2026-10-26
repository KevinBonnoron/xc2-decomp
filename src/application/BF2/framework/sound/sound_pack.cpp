#include "framework/sound/sound_pack.h"

#include <string.h>

#include "framework/sound/sound_ssd_drv.h"
#include "mm_mtl/hash.h"

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

mm::mtl::IntrusivePtr<SoundSsdSource> SoundPack::findSource(const char *name) const {
  u32 hash = mm::mtl::hashStrCrc(name);
  for (u32 i = 0; i < unknown988.size(); i++) {
    if (unknown988[i].unknown04 == hash) {
      if (strcmp(unknown180[i]->unknown134.c_str(), name) == 0) {
        return unknown180[i];
      }
    }
  }

  return nullptr;
}

bool SoundPack::isLoopSource(const char *name) const {
  mm::mtl::IntrusivePtr<SoundSsdSource> source = findSource(name);
  if (source.get() == nullptr) {
    return false;
  }

  return source->isLoop();
}

bool SoundPack::isLoopSource(u32 id) const {
  for (u32 i = 0; i < unknown988.size(); i++) {
    if (unknown988[i].unknown00 == id) {
      SoundSsdSource *source = unknown180[i].get();
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
