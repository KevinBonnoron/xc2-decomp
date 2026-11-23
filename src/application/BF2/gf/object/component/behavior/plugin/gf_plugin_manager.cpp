#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"

#include "gf/object/component/behavior/plugin/gf_plugin.h"

namespace gf {

PluginManager::PluginManager(mm::mtl::IAllocator *allocator) : unknown00(allocator), unknown28(allocator), unknown50(allocator), m_comBehavior(nullptr), unknown80(false) {}

void PluginManager::beginSetup(GfComBehavior &behavior, u32 count) {
  unknown00.resize(count, nullptr);
  unknown28.resize(count, nullptr);
  unknown50.resize(count, false);
  m_comBehavior = &behavior;
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
      if (!unknown28[i]->onSetup(*m_comBehavior)) {
        if (unknown28[i] != nullptr) {
          delete unknown28[i];
          unknown28[i] = nullptr;
        }
      }
    }
  }

  unknown80 = false;
}

void PluginManager::cleanup() {
  if (m_comBehavior != nullptr) {
    for (u32 i = 0; i < unknown28.size(); i++) {
      if (unknown28[i] != nullptr) {
        unknown28[i]->onCleanup(*m_comBehavior);
        if (unknown28[i] != nullptr) {
          delete unknown28[i];
          unknown28[i] = nullptr;
        }
      }
    }
  }
}

void PluginManager::update(const fw::UpdateInfo &info) {
  for (u32 i = 0; i < unknown28.size(); i++) {
    if (unknown28[i] != nullptr) {
      if (unknown28[i]->unknown08) {
        unknown28[i]->onUpdate(*m_comBehavior, info);
      }
    }
  }
}

} // namespace gf
