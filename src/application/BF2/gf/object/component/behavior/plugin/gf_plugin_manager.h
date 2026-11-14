#pragma once
#include <stddef.h>

#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComBehavior;
class Plugin;

class PluginManager {
public:
  explicit PluginManager(mm::mtl::IAllocator *allocator);
  void beginSetup(GfComBehavior &behavior, u32 count);
  void endSetup();
  void cleanup();
  void update(const fw::UpdateInfo &info);

  // Inferred helper: registers the creator of the plugin at index and its enable; original name unknown.
  template <typename T> void unknown001(u32 index, bool isEnable) {
    unknown00[index] = &T::create;
    unknown50[index] = isEnable;
  }

  // Inferred name; shared by every plugin class for GfPluginManager::createPlugin<T> and destroyPlugin<T>.
  template <typename T> void createPlugin() {
    // Inferred name; shared by every plugin class for the GfPluginManager templates.
    if (unknown00[T::PLUGIN_INDEX] != nullptr) {
      unknown28[T::PLUGIN_INDEX] = unknown00[T::PLUGIN_INDEX]();
      if (unknown28[T::PLUGIN_INDEX] != nullptr) {
        unknown28[T::PLUGIN_INDEX]->onSetup(*unknown78);
      }
    }
  }

  template <typename T> void destroyPlugin() {
    if (unknown28[T::PLUGIN_INDEX] != nullptr) {
      unknown28[T::PLUGIN_INDEX]->onCleanup(*unknown78);
      if (unknown28[T::PLUGIN_INDEX] != nullptr) {
        delete unknown28[T::PLUGIN_INDEX];
        unknown28[T::PLUGIN_INDEX] = nullptr;
      }
    }
  }

  mm::mtl::Vector<Plugin *(*)()> unknown00; // Inferred role: plugin creators; original member name unknown.
  mm::mtl::Vector<Plugin *> unknown28;      // Inferred role: plugins; original member name unknown.
  mm::mtl::Vector<bool> unknown50;          // Inferred role: plugin enables; original member name unknown.
  GfComBehavior *unknown78;                 // Inferred role: behavior; original member name unknown.
  bool unknown80;                           // Inferred role: in setup; original member name unknown.
};

static_assert(offsetof(PluginManager, unknown28) == 0x28, "");
static_assert(offsetof(PluginManager, unknown50) == 0x50, "");
static_assert(offsetof(PluginManager, unknown78) == 0x78, "");
static_assert(offsetof(PluginManager, unknown80) == 0x80, "");
static_assert(sizeof(PluginManager) == 0x88, "");

} // namespace gf
