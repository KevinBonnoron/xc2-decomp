#include "gf/asset/gf_asset_manager.h"

#include "gf/asset/gf_slot_mapping.h"

namespace gf {

GfSlotMapping *GfAssetManager::getSlotMapping() {
  GfAssetManager *manager = get();
  if (manager != nullptr) {
    return manager->m_slotMapping;
  }
  return nullptr;
}

bool GfAssetManager::isInitialized() {
  if (get() != nullptr) {
    return get()->unknowne04c0;
  }
  return false;
}

void GfAssetManager::releaseSlotHandle(GF_SLOT_HANDLE *handle) { get()->m_slotMapping->releaseSlot(handle); }

bool GfAssetManager::isLoading() { return get()->unknownce0b8.size() > 0; }

void GfAssetManager::clear() { destroySlotCache(ASSET_TYPE_BASE); }

size_t GfAssetManager::getSlotBlockSize(GfAssetType type) { return get()->m_slotMapping->getSlotBlockSize(type); }

u32 GfAssetManager::getSlotNumByByteSize(GfAssetType type, size_t size) { return get()->m_slotMapping->getSlotNumByByteSize(type, size); }

mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> *GfAssetManager::getLoadingAsset() { return &get()->unknownce0b8; }

GF_SLOT_HANDLE *GfAssetManager::allocateFromAssetTypeSlot(GfAssetType type, size_t size) {
  GfAssetManager *manager = get();
  if (manager != nullptr && manager->m_slotMapping != nullptr) {
    return manager->m_slotMapping->allocateSlot(type, size);
  }
  return reinterpret_cast<GF_SLOT_HANDLE *>(-1);
}

bool GfAssetManager::getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle) {
  GfAssetManager *manager = get();
  if (manager != nullptr && manager->m_slotMapping != nullptr) {
    return manager->m_slotMapping->getSlotInfo(allocator, buffer, size, handle);
  }
  return true;
}

u32 GfAssetManager::getUsedAssetPackInfo() {
  if (get() != nullptr) {
    return get()->unknownce0b4;
  }
  return 0;
}

u32 GfAssetManager::getDestroyAssetPackInfo() {
  if (get() != nullptr) {
    return get()->unknownd28d8.size();
  }
  return 0;
}

} // namespace gf
