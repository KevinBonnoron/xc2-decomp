#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/gf_com_behavior.h" // IWYU pragma: keep
#include "gf/object/component/behavior/plugin/gf_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class FootStepPlugin : public Plugin {
  GF_PLUGIN(GfComBehavior)

public:
  FootStepPlugin();
  static FootStepPlugin *create();
  virtual bool setup(GfComBehavior &behavior);
  void setAnkleHeight(GfComBehavior &behavior);
  virtual void cleanup(GfComBehavior &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehavior &behavior, const fw::UpdateInfo &info);

  bool unknown09; // Inferred role: running; original member name unknown.
};

static_assert(offsetof(FootStepPlugin, unknown09) == 0x09, "");
static_assert(sizeof(FootStepPlugin) == 0x10, "");

} // namespace gf
