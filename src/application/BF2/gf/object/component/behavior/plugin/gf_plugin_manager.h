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
