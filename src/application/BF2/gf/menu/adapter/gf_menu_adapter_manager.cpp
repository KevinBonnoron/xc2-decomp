#include "gf/menu/adapter/gf_menu_adapter_manager.h"

namespace gf {

bool GfMenuAdapterManager::isAdapterFull() { return false; }

bool GfMenuAdapterManager::isInitialized() { return true; }

void GfMenuAdapterManager::destroy() { delete get(); }

void GfMenuAdapterManager::beginCategory(u32 category) {
  GfMenuAdapterManager *manager = get();
  if (manager != nullptr) {
    manager->unknown9c = category;
  }
}

void GfMenuAdapterManager::endCategory() {
  GfMenuAdapterManager *manager = get();
  if (manager != nullptr) {
    manager->unknown9c = 0;
  }
}

void GfMenuAdapterManager::beginAddAfter() {
  GfMenuAdapterManager *manager = get();
  if (manager != nullptr) {
    manager->unknowna0 = true;
  }
}

void GfMenuAdapterManager::endAddAfter() {
  GfMenuAdapterManager *manager = get();
  if (manager != nullptr) {
    manager->unknowna0 = false;
  }
}

} // namespace gf
