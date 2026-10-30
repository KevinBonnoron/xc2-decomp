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

  // Inferred role: timer; original type name unknown.
  struct unknown005 {
    bool unknown00; // Inferred role: active; original member name unknown.
    f32 unknown04;  // Inferred role: time; original member name unknown.
  };

  TimerPlugin();
  static TimerPlugin *create();
  void setActivateTimer(TYPE type, bool isActive);
  virtual bool setup(GfComBehaviorPc &) { return true; }
  virtual void cleanup(GfComBehaviorPc &) {}
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);

  unknown005 unknown0c[TYPE_MAX]; // Inferred role: timers; original member name unknown.
};

static_assert(offsetof(TimerPlugin, unknown0c) == 0x0c, "");
static_assert(sizeof(TimerPlugin) == 0x18, "");

} // namespace pc
} // namespace gf
