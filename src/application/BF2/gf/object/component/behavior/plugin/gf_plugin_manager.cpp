#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"

#include "gf/object/component/behavior/plugin/gf_plugin.h"

namespace gf {

PluginManager::PluginManager(mm::mtl::IAllocator *allocator) : unknown00(allocator), unknown28(allocator), unknown50(allocator), unknown78(nullptr), unknown80(false) {}

void PluginManager::beginSetup(GfComBehavior &behavior, u32 count) {
  unknown00.resize(count, nullptr);
  unknown28.resize(count, nullptr);
  unknown50.resize(count, false);
  unknown78 = &behavior;
  unknown80 = true;
}

void PluginManager::endSetup() {
  for (u32 i = 0; i < unknown00.size(); i++) {
    if (unknown00[i] != nullptr) {
      if (unknown50[i]) {
        unknown28[i] = unknown00[i]();
      }
    }
  }

  for (u32 i = 0; i < unknown28.size(); i++) {
    if (unknown28[i] != nullptr) {
      if (!unknown28[i]->onSetup(*unknown78)) {
        if (unknown28[i] != nullptr) {
          delete unknown28[i];
        }
        unknown28[i] = nullptr;
      }
    }
  }

  unknown80 = false;
}

void PluginManager::cleanup() {
  if (unknown78 != nullptr) {
    for (u32 i = 0; i < unknown28.size(); i++) {
      if (unknown28[i] != nullptr) {
        unknown28[i]->onCleanup(*unknown78);
        if (unknown28[i] != nullptr) {
          delete unknown28[i];
        }
        unknown28[i] = nullptr;
      }
    }
  }
}

void PluginManager::update(const fw::UpdateInfo &info) {
  for (u32 i = 0; i < unknown28.size(); i++) {
    if (unknown28[i] != nullptr) {
      if (unknown28[i]->unknown08) {
        unknown28[i]->onUpdate(*unknown78, info);
      }
    }
  }
}

} // namespace gf
