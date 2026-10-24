#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {
namespace pc {

class TerrainDamagePlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  TerrainDamagePlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void reset();
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  void onEnterDamage(GfComBehaviorPc &behavior);
  void onLeaveDamage(GfComBehaviorPc &behavior);

  f32 unknown0c;  // Inferred role: damage timer; original member name unknown.
  bool unknown10; // Inferred role: in damage; original member name unknown.
};

static_assert(offsetof(TerrainDamagePlugin, unknown0c) == 0x0c, "");
static_assert(offsetof(TerrainDamagePlugin, unknown10) == 0x10, "");
static_assert(sizeof(TerrainDamagePlugin) == 0x18, "");

} // namespace pc
} // namespace gf
