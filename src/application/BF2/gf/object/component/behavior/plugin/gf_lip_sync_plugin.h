#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/gf_com_behavior.h" // IWYU pragma: keep
#include "gf/object/component/behavior/plugin/gf_plugin.h"
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

class LipSyncPlugin : public Plugin {
  GF_PLUGIN(GfComBehavior)

public:
  LipSyncPlugin();
  virtual bool setup(GfComBehavior &behavior);
  virtual void cleanup(GfComBehavior &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehavior &behavior, const fw::UpdateInfo &info);
  bool judgeTalk();
  void setSpeed(f32 speed);
  void setWeight(f32 weight);

  GfComBehavior *behavior;
  f32 speed;
  f32 weight;
  bool isTalking;
  bool isForceTalk;
};

static_assert(offsetof(LipSyncPlugin, behavior) == 0x10, "");
static_assert(offsetof(LipSyncPlugin, speed) == 0x18, "");
static_assert(offsetof(LipSyncPlugin, weight) == 0x1c, "");
static_assert(offsetof(LipSyncPlugin, isTalking) == 0x20, "");
static_assert(offsetof(LipSyncPlugin, isForceTalk) == 0x21, "");
static_assert(sizeof(LipSyncPlugin) == 0x28, "");

} // namespace gf
