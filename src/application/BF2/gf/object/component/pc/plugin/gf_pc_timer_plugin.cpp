#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"

#include "fw/fw_update_info.h"

namespace gf {

namespace pc {

TimerPlugin::TimerPlugin() {
  for (u32 i = 0; i < TYPE_MAX; i++) {
    unknown0c[i].unknown00 = false;
    unknown0c[i].unknown04 = 0.0f;
  }
}

void TimerPlugin::setActivateTimer(TYPE type, bool isActive) {
  if (unknown0c[type].unknown00 != isActive) {
    unknown0c[type].unknown00 = isActive;
    unknown0c[type].unknown04 = 0.0f;
  }
}

void TimerPlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &info) {
  for (u32 i = 0; i < TYPE_MAX; i++) {
    if (unknown0c[i].unknown00) {
      unknown0c[i].unknown04 += info.unknown04;
    }
  }
}

} // namespace pc
} // namespace gf
