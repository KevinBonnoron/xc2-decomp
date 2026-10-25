#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
struct Vec3;
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComPropertyPc;

namespace pc {

class FallDistancePlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  FallDistancePlugin();
  static FallDistancePlugin *create();
  ~FallDistancePlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  f32 calcDistance(const mm::Vec3 &position) const;
  void onActivate() override;
  void cacheMaxHeight(bool isReset);
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);

  GfComPropertyPc *unknown10; // Inferred role: property; original member name unknown.
  f32 unknown18;              // Inferred role: max height; original member name unknown.
};

static_assert(offsetof(FallDistancePlugin, unknown10) == 0x10, "");
static_assert(offsetof(FallDistancePlugin, unknown18) == 0x18, "");
static_assert(sizeof(FallDistancePlugin) == 0x20, "");

} // namespace pc
} // namespace gf
