#include "framework/sound/sound_res_source_manager.h"

#include "framework/sound/sound_manager.h"

namespace fw {

void SoundResSourceManager::stopSe(u32 handle, f32 time) {
  if (SoundManager::get() != nullptr) {
    SoundManager::get()->stopSe(handle, time);
  }
}

} // namespace fw
