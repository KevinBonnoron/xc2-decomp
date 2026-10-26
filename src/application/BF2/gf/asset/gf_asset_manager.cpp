#include "gf/asset/gf_asset_manager.h"

namespace gf {

GfSlotMapping *GfAssetManager::getSlotMapping() {
  GfAssetManager *manager = get();
  if (manager != nullptr) {
    return manager->m_slotMapping;
  }
  return nullptr;
}

} // namespace gf
