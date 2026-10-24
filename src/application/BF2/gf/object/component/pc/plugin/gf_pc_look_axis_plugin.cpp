#include "gf/object/component/pc/plugin/gf_pc_look_axis_plugin.h"

#include "fw/fw_update_info.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

constexpr u32 PC_PARAM_LOOK_AXIS = 4;

LookAxisPlugin::LookAxisPlugin() : behavior(nullptr), yaw(0.0f), startYaw(0.0f), targetYaw(0.0f), changeTimer(0.0f), isChanging(false), paramEntry(nullptr) {}

bool LookAxisPlugin::setup(GfComBehaviorPc &behavior) {
  mm::mtl::IntrusivePtr<fw::ParamList> paramList = fw::ParamManager::get()->pcParamList;
  paramEntry = paramList->count > PC_PARAM_LOOK_AXIS ? &paramList->entries[PC_PARAM_LOOK_AXIS] : nullptr;
  this->behavior = &behavior;
  return true;
}

void LookAxisPlugin::cleanup(GfComBehaviorPc &) {}

void LookAxisPlugin::onActivate() {}

void LookAxisPlugin::onDeactivate() {
  setYaw(0.0f);
  isChanging = false;
}

void LookAxisPlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &info) {
  if (!isChanging) {
    return;
  }

  const LookAxisParam *param = getParam();
  changeTimer += info.deltaTime;
  setYaw(calcYaw(param->changeTime));
  if (changeTimer >= param->changeTime) {
    isChanging = false;
  }
}

const LookAxisParam *LookAxisPlugin::getParam() const { return paramEntry != nullptr ? static_cast<const LookAxisParam *>(paramEntry->param) : nullptr; }

f32 LookAxisPlugin::calcYaw(f32 changeTime) const {
  f32 rate = mm::clamp(changeTimer / changeTime, 0.0f, 1.0f);
  f32 startRate = 1.0f - rate;
  return targetYaw * rate + startYaw * startRate;
}

void LookAxisPlugin::changeAxisYaw(f32 yaw) {
  startYaw = this->yaw;
  targetYaw = yaw;
  changeTimer = 0.0f;
  isChanging = true;
}

} // namespace pc
} // namespace gf
