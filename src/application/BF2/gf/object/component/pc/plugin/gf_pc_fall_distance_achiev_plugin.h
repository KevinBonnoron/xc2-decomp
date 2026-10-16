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

class GfComPropertyPc;

namespace pc {

class FallDistanceAchievPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  FallDistanceAchievPlugin();
  ~FallDistanceAchievPlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void cacheMaxHeight(bool isReset);
  void onDeactivate() override;
  void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);

  GfComPropertyPc *property;
  f32 maxHeight;
};

static_assert(offsetof(FallDistanceAchievPlugin, property) == 0x10, "");
static_assert(offsetof(FallDistanceAchievPlugin, maxHeight) == 0x18, "");
static_assert(sizeof(FallDistanceAchievPlugin) == 0x20, "");

} // namespace pc
} // namespace gf
