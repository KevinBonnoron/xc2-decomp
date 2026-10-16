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

namespace pc {

class TimerPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  enum TYPE {
    TYPE_FALL,
    TYPE_MAX,
  };

  struct Timer {
    bool isActive;
    f32 time;
  };

  TimerPlugin();
  void setActivateTimer(TYPE type, bool isActive);
  virtual bool setup(GfComBehaviorPc &) { return true; }
  virtual void cleanup(GfComBehaviorPc &) {}
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);

  Timer timers[TYPE_MAX];
};

static_assert(offsetof(TimerPlugin, timers) == 0x0c, "");
static_assert(sizeof(TimerPlugin) == 0x18, "");

} // namespace pc
} // namespace gf
