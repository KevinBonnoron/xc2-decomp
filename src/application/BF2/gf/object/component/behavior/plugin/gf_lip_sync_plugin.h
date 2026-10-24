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

  GfComBehavior *unknown10; // Inferred role: behavior; original member name unknown.
  f32 unknown18;            // Inferred role: speed; original member name unknown.
  f32 unknown1c;            // Inferred role: weight; original member name unknown.
  bool unknown20;           // Inferred role: talking; original member name unknown.
  bool unknown21;           // Inferred role: force talk; original member name unknown.
};

static_assert(offsetof(LipSyncPlugin, unknown10) == 0x10, "");
static_assert(offsetof(LipSyncPlugin, unknown18) == 0x18, "");
static_assert(offsetof(LipSyncPlugin, unknown1c) == 0x1c, "");
static_assert(offsetof(LipSyncPlugin, unknown20) == 0x20, "");
static_assert(offsetof(LipSyncPlugin, unknown21) == 0x21, "");
static_assert(sizeof(LipSyncPlugin) == 0x28, "");

} // namespace gf
