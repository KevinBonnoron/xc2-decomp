#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"

#include "fw/fw_update_info.h"

namespace gf {

namespace pc {

TimerPlugin::TimerPlugin() {
  for (u32 i = 0; i < TYPE_MAX; i++) {
    timers[i].isActive = false;
    timers[i].time = 0.0f;
  }
}

void TimerPlugin::setActivateTimer(TYPE type, bool isActive) {
  if (timers[type].isActive != isActive) {
    timers[type].isActive = isActive;
    timers[type].time = 0.0f;
  }
}

void TimerPlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &info) {
  for (u32 i = 0; i < TYPE_MAX; i++) {
    if (timers[i].isActive) {
      timers[i].time += info.deltaTime;
    }
  }
}

} // namespace pc
} // namespace gf
