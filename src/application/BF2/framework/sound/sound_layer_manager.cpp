#include "framework/sound/sound_layer_manager.h"

namespace fw {

SoundLayerManager::SoundLayerManager() {}

SoundLayerManager::~SoundLayerManager() {}

void SoundLayerManager::update(u32 layerMask) {
  for (u32 i = 0; i < LAYER_MAX; i++) {
    if ((layerMask & 1 << i) != 0) {
      mm::mtl::IntrusiveList<SoundUpdater> &updaters = unknown08[i];
      for (mm::mtl::IntrusiveList<SoundUpdater>::iterator it = updaters.begin(); it != updaters.end(); ++it) {
        SoundUpdater &updater = *it;
        bool isKeep = false;
        if (updater.unknown10.isValid()) {
          isKeep = updater.unknown10() != 0;
        }
        updater.unknown30 = isKeep;
      }

      for (mm::mtl::IntrusiveList<SoundUpdater>::iterator it = updaters.begin(); it != updaters.end();) {
        if (!it.get()->unknown30) {
          it.get()->unknown31 = false;
          it = updaters.erase(it);
        } else {
          ++it;
        }
      }
    }
  }
}

} // namespace fw
