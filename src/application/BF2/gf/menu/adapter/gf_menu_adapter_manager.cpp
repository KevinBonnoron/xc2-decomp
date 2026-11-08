#include "gf/menu/adapter/gf_menu_adapter_manager.h"

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "ui/ui_object_plugin.h"

namespace gf {

GfMenuAdapterManager::GfMenuAdapterManager(const GfSetupParam &param) : unknown08(), unknown98(1), unknown9c(0), unknowna0(false), unknowna8(unknown68.begin()) {}

// The game repeats the loop that deletes the adapters of a list for each of the three kinds of lists (confirmed by the instructions).
GfMenuAdapterManager::~GfMenuAdapterManager() {
  for (u32 i = 0; i < 4; i++) {
    mm::mtl::IntrusiveList<GfMenuAdapter> &list = unknown08[i].unknown00;
    mm::mtl::IntrusiveList<GfMenuAdapter>::iterator it = list.begin();
    while (it != list.end()) {
      GfMenuAdapter *adapter = it.get();
      it = list.erase(it);
      delete adapter;
    }
    list.clear();
  }
  mm::mtl::IntrusiveList<GfMenuAdapter>::iterator it68 = unknown68.begin();
  while (it68 != unknown68.end()) {
    GfMenuAdapter *adapter = it68.get();
    it68 = unknown68.erase(it68);
    delete adapter;
  }
  unknown68.clear();
  mm::mtl::IntrusiveList<GfMenuAdapter>::iterator it80 = unknown80.begin();
  while (it80 != unknown80.end()) {
    GfMenuAdapter *adapter = it80.get();
    it80 = unknown80.erase(it80);
    delete adapter;
  }
  unknown80.clear();
}

void GfMenuAdapterManager::destroy() { delete get(); }

bool GfMenuAdapterManager::isInitialized() { return true; }

void GfMenuAdapterManager::postUpdate(const fw::UpdateInfo &info) {
  GfMenuAdapterManager *manager = get();
  if (manager != nullptr) {
    for (u32 i = 0; i < 4; i++) {
      if ((manager->unknown98 & (1 << i)) != 0) {
        mm::mtl::IntrusiveList<GfMenuAdapter> &list = manager->unknown08[i].unknown00;
        mm::mtl::IntrusiveList<GfMenuAdapter>::iterator it = list.begin();
        while (it != list.end()) {
          GfMenuAdapter *adapter = it.get();
          if (adapter->unknown18 == nullptr || adapter->unknown18->getRefCount() == 1) {
            it = list.erase(it);
            delete adapter;
          } else {
            adapter->update(info);
            ++it;
          }
        }
      }
    }

    mm::mtl::IntrusiveList<GfMenuAdapter>::iterator it = manager->unknowna8;
    for (u32 count = 0; count < 200; count++) {
      if (manager->unknown68.end() == it) {
        break;
      }
      GfMenuAdapter *adapter = it.get();
      if (adapter->unknown18 == nullptr || adapter->unknown18->getRefCount() == 1) {
        it = manager->unknown68.erase(it);
        delete adapter;
      } else {
        adapter->update(info);
        ++it;
      }
    }
    if (manager->unknown68.end() == it) {
      manager->unknowna8 = manager->unknown68.begin();
    } else {
      manager->unknowna8 = it;
    }
  }
}

void GfMenuAdapterManager::postUpdateAfter(const fw::UpdateInfo &info) {
  GfMenuAdapterManager *manager = get();
  if (manager != nullptr) {
    mm::mtl::IntrusiveList<GfMenuAdapter>::iterator it = manager->unknown80.begin();
    while (it != manager->unknown80.end()) {
      GfMenuAdapter *adapter = it.get();
      if (adapter->unknown18 == nullptr || adapter->unknown18->getRefCount() == 1) {
        it = manager->unknown80.erase(it);
        delete adapter;
      } else {
        adapter->update(info);
        ++it;
      }
    }
  }
}

bool GfMenuAdapterManager::isAdapterFull() { return false; }

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

void GfMenuAdapterManager::addActiveCategory(u32 category) {
  GfMenuAdapterManager *manager = get();
  if (manager != nullptr) {
    manager->unknown98 |= 1 << category;
  }
}

void GfMenuAdapterManager::delActiveCategory(u32 category) {
  GfMenuAdapterManager *manager = get();
  if (manager != nullptr) {
    manager->unknown98 &= ~(1 << category);
  }
}

void GfMenuAdapterManager::addAdapter(GfMenuAdapter *adapter, bool isUpdateAfter) {
  if (unknown9c == 0 && isUpdateAfter) {
    unknown68.push_back(adapter);
  } else if (!unknowna0) {
    unknown08[unknown9c].unknown00.push_back(adapter);
  } else {
    unknown80.push_back(adapter);
  }
}

void GfMenuAdapterManager::setAfterUpdate(GfMenuAdapter *adapter) {
  GfMenuAdapterManager *manager = get();
  if (manager != nullptr) {
    for (u32 i = 0; i < 4; i++) {
      mm::mtl::IntrusiveList<GfMenuAdapter> &list = manager->unknown08[i].unknown00;
      for (mm::mtl::IntrusiveList<GfMenuAdapter>::iterator it = list.begin(); it != list.end(); ++it) {
        if (it.get() == adapter) {
          list.erase(it);
          manager->unknown80.push_back(adapter);
          break;
        }
      }
    }
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuAdapterManager>::~PtrSingleton();
