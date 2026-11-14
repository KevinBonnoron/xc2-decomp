#include "framework/effect/effect_lod_manager.h"

#include "framework/effect/effect_manager.h"

namespace fw {

EffectLodManager::EffectLodManager() {
  unknown08 = nullptr;
  unknown10 = nullptr;
}

EffectLodManager::~EffectLodManager() { term(); }

void EffectLodManager::term() {
  for (mm::mtl::IntrusiveList<unknown001>::iterator it = unknown18.begin(); it != unknown18.end();) {
    unknown001 *node = &*it;
    EffectManager::get()->remove(node->unknown10);
    it = unknown18.erase(it);
    delete node;
  }
  unknown18.clear();
  unknown08 = nullptr;
  unknown10 = nullptr;
}

} // namespace fw
