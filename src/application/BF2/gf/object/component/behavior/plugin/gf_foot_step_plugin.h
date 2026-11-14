#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/gf_com_behavior.h" // IWYU pragma: keep
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/property/gf_env_property.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class ParamAdapter;
struct UpdateInfo;
} // namespace fw

namespace gf {

// Field names from the reflection of gf::FootStepParam::createReflection.
struct FootStepParam {
  f32 rapidSpeed;
  u32 ankleHeight;
};

static_assert(offsetof(FootStepParam, ankleHeight) == 0x04, "");

GfEnvProperty::GROUND_INDEX getFootGroundIndex(const char *name);
bool isLeftFoot(GfEnvProperty::GROUND_INDEX ground);
bool isBearFoot(GfEnvProperty::GROUND_INDEX ground);
const FootStepParam *getFootParam(fw::ParamAdapter &adapter);

class FootStepPlugin : public Plugin {
  GF_PLUGIN(GfComBehavior)

public:
  FootStepPlugin();
  static Plugin *create();
  virtual bool setup(GfComBehavior &behavior);
  void setAnkleHeight(GfComBehavior &behavior);
  virtual void cleanup(GfComBehavior &behavior);
  void notifyStep(GfComBehavior &behavior, const char *name);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehavior &behavior, const fw::UpdateInfo &info);
  static const FootStepParam *getParam();
  void emissionEffect(GfComBehavior &behavior, GfEnvProperty::GROUND_INDEX ground);

  bool unknown09; // Inferred role: running; original member name unknown.
};

static_assert(offsetof(FootStepPlugin, unknown09) == 0x09, "");
static_assert(sizeof(FootStepPlugin) == 0x10, "");

} // namespace gf
