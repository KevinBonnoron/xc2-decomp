#include "framework/effect/effect_lod_manager.h"

namespace fw {

EffectLodManager::EffectLodManager() {
  unknown08 = nullptr;
  unknown10 = nullptr;
}

EffectLodManager::~EffectLodManager() { term(); }

} // namespace fw
