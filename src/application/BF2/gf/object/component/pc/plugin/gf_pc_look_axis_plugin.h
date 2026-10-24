#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
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
namespace pc {

struct LookAxisParam {
  u8 _00[0x14 - 0x00];
  f32 unknown14; // Inferred role: change time; original member name unknown.
};

static_assert(offsetof(LookAxisParam, unknown14) == 0x14, "");

class LookAxisPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  LookAxisPlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  void setYaw(f32 yaw);
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  const LookAxisParam *getParam() const;
  f32 calcYaw(f32 changeTime) const;
  void changeAxisYaw(f32 yaw);

  GfComBehaviorPc *unknown10;            // Inferred role: behavior; original member name unknown.
  f32 unknown18;                         // Inferred role: yaw; original member name unknown.
  f32 unknown1c;                         // Inferred role: start yaw; original member name unknown.
  f32 unknown20;                         // Inferred role: target yaw; original member name unknown.
  f32 unknown24;                         // Inferred role: change timer; original member name unknown.
  bool unknown28;                        // Inferred role: changing; original member name unknown.
  const fw::ParamList::Entry *unknown30; // Inferred role: param entry; original member name unknown.
};

static_assert(offsetof(LookAxisPlugin, unknown10) == 0x10, "");
static_assert(offsetof(LookAxisPlugin, unknown18) == 0x18, "");
static_assert(offsetof(LookAxisPlugin, unknown1c) == 0x1c, "");
static_assert(offsetof(LookAxisPlugin, unknown20) == 0x20, "");
static_assert(offsetof(LookAxisPlugin, unknown24) == 0x24, "");
static_assert(offsetof(LookAxisPlugin, unknown28) == 0x28, "");
static_assert(offsetof(LookAxisPlugin, unknown30) == 0x30, "");
static_assert(sizeof(LookAxisPlugin) == 0x38, "");

} // namespace pc
} // namespace gf
