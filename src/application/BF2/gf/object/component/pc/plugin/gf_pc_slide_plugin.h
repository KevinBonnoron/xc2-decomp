#pragma once
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

class SlidePlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  SlidePlugin();
  static SlidePlugin *create();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
};

static_assert(sizeof(SlidePlugin) == 0x10, "");

} // namespace pc
} // namespace gf
