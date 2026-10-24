#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep

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

class WaterInPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  WaterInPlugin();
  ~WaterInPlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  void onEvent(GfComBehaviorPc &behavior);
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);

  GfComBehaviorPc *unknown10; // Inferred role: behavior; original member name unknown.
  bool unknown18;             // Inferred role: event done; original member name unknown.
};

static_assert(offsetof(WaterInPlugin, unknown10) == 0x10, "");
static_assert(offsetof(WaterInPlugin, unknown18) == 0x18, "");
static_assert(sizeof(WaterInPlugin) == 0x20, "");

} // namespace pc
} // namespace gf
