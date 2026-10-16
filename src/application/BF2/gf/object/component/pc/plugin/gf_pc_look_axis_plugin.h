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
  f32 changeTime;
};

static_assert(offsetof(LookAxisParam, changeTime) == 0x14, "");

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

  GfComBehaviorPc *behavior;
  f32 yaw;
  f32 startYaw;
  f32 targetYaw;
  f32 changeTimer;
  bool isChanging;
  const fw::ParamList::Entry *paramEntry;
};

static_assert(offsetof(LookAxisPlugin, behavior) == 0x10, "");
static_assert(offsetof(LookAxisPlugin, yaw) == 0x18, "");
static_assert(offsetof(LookAxisPlugin, startYaw) == 0x1c, "");
static_assert(offsetof(LookAxisPlugin, targetYaw) == 0x20, "");
static_assert(offsetof(LookAxisPlugin, changeTimer) == 0x24, "");
static_assert(offsetof(LookAxisPlugin, isChanging) == 0x28, "");
static_assert(offsetof(LookAxisPlugin, paramEntry) == 0x30, "");
static_assert(sizeof(LookAxisPlugin) == 0x38, "");

} // namespace pc
} // namespace gf
