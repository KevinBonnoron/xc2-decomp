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

class ColVelCalculatorPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  ColVelCalculatorPlugin();
  void onActivate() override;
  virtual bool setup(GfComBehaviorPc &) { return true; }
  virtual void cleanup(GfComBehaviorPc &) {}
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);

  bool isFirstFrame;
};

static_assert(offsetof(ColVelCalculatorPlugin, isFirstFrame) == 0x09, "");
static_assert(sizeof(ColVelCalculatorPlugin) == 0x10, "");

} // namespace pc
} // namespace gf
