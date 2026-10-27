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

class FootIkControllerPlugin : public Plugin {
  GF_PLUGIN(GfComBehavior)

public:
  enum Mode {
    MODE_UNKNOWN_0,
    MODE_UNKNOWN_1,
    MODE_UNKNOWN_2,
    MODE_UNKNOWN_3,
  };

  FootIkControllerPlugin();
  static FootIkControllerPlugin *create();
  virtual bool setup(GfComBehavior &behavior);
  u64 getASMStateAttribute(GfComBehavior &behavior) const;
  void setGroundPlacement(bool enable);
  virtual void cleanup(GfComBehavior &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehavior &behavior, const fw::UpdateInfo &info);
  void switchMode(Mode mode);

  GfComBehavior *unknown10; // Inferred role: behavior; original member name unknown.
  Mode unknown18;           // Inferred role: ground solver mode; original member name unknown.
  bool unknown1c;           // Inferred role: slope solver with placement solver; original member name unknown.
  bool unknown1d;           // Inferred role: ground placement enabled; original member name unknown.
  u8 unknown1e;             // Inferred role: force foot ground fit; original member name unknown.
  bool unknown1f;           // Inferred role: ground placement allowed; original member name unknown.
  bool unknown20;           // Inferred role: force two chara ground fit; original member name unknown.
};

static_assert(offsetof(FootIkControllerPlugin, unknown10) == 0x10, "");
static_assert(offsetof(FootIkControllerPlugin, unknown18) == 0x18, "");
static_assert(offsetof(FootIkControllerPlugin, unknown1c) == 0x1c, "");
static_assert(offsetof(FootIkControllerPlugin, unknown1d) == 0x1d, "");
static_assert(offsetof(FootIkControllerPlugin, unknown1e) == 0x1e, "");
static_assert(offsetof(FootIkControllerPlugin, unknown1f) == 0x1f, "");
static_assert(offsetof(FootIkControllerPlugin, unknown20) == 0x20, "");
static_assert(sizeof(FootIkControllerPlugin) == 0x28, "");

} // namespace gf
