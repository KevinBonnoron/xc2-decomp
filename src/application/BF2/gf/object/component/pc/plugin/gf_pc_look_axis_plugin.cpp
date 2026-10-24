#include "gf/object/component/pc/plugin/gf_pc_look_axis_plugin.h"

#include "fw/fw_update_info.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

constexpr u32 PC_PARAM_LOOK_AXIS = 4;

LookAxisPlugin::LookAxisPlugin() : unknown10(nullptr), unknown18(0.0f), unknown1c(0.0f), unknown20(0.0f), unknown24(0.0f), unknown28(false), unknown30(nullptr) {}

bool LookAxisPlugin::setup(GfComBehaviorPc &behavior) {
  mm::mtl::IntrusivePtr<fw::ParamList> paramList = fw::ParamManager::get()->pcParamList;
  unknown30 = paramList->count > PC_PARAM_LOOK_AXIS ? &paramList->entries[PC_PARAM_LOOK_AXIS] : nullptr;
  this->unknown10 = &behavior;
  return true;
}

void LookAxisPlugin::cleanup(GfComBehaviorPc &) {}

void LookAxisPlugin::onActivate() {}

void LookAxisPlugin::onDeactivate() {
  setYaw(0.0f);
  unknown28 = false;
}

void LookAxisPlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &info) {
  if (!unknown28) {
    return;
  }

  const LookAxisParam *param = getParam();
  unknown24 += info.deltaTime;
  setYaw(calcYaw(param->unknown14));
  if (unknown24 >= param->unknown14) {
    unknown28 = false;
  }
}

const LookAxisParam *LookAxisPlugin::getParam() const { return unknown30 != nullptr ? static_cast<const LookAxisParam *>(unknown30->param) : nullptr; }

f32 LookAxisPlugin::calcYaw(f32 changeTime) const {
  f32 rate = mm::clamp(unknown24 / changeTime, 0.0f, 1.0f);
  f32 startRate = 1.0f - rate;
  return unknown20 * rate + unknown1c * startRate;
}

void LookAxisPlugin::changeAxisYaw(f32 yaw) {
  unknown1c = this->unknown18;
  unknown20 = yaw;
  unknown24 = 0.0f;
  unknown28 = true;
}

} // namespace pc
} // namespace gf
