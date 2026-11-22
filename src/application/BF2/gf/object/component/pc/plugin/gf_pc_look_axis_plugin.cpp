#include "gf/object/component/pc/plugin/gf_pc_look_axis_plugin.h"

#include <float.h>
#include <math.h>

#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_look_solver.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/component/pc/plugin/gf_pc_target_ik_plugin.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

constexpr u32 PC_UNKNOWN_4 = 4; // Inferred role: pc param look axis; original name unknown.

LookAxisPlugin::LookAxisPlugin() : m_comBehaviorPc(nullptr), unknown18(0.0f), unknown1c(0.0f), unknown20(0.0f), unknown24(0.0f), unknown28(false), unknown30(nullptr) {}

bool LookAxisPlugin::setup(GfComBehaviorPc &behavior) {
  mm::mtl::IntrusivePtr<fw::ParamList> paramList = fw::ParamManager::get()->unknown408[5];
  unknown30 = paramList->unknown0c > PC_UNKNOWN_4 ? &paramList->unknown10[PC_UNKNOWN_4] : nullptr;
  this->m_comBehaviorPc = &behavior;
  return true;
}

void LookAxisPlugin::cleanup(GfComBehaviorPc &) {}

void LookAxisPlugin::onActivate() {}

void LookAxisPlugin::onDeactivate() {
  setYaw(0.0f);
  unknown28 = false;
}

// 1.0.0: 0x710057aaac, 198 instructions. The single-use local `radian` is the case of decisions 44 and 57 (a named variable whose only effect comes from its DBG_VALUE under -g).
// Measured with -mllvm -print-after-all on this function, with and without the local, ignoring debug intrinsics and DBG_VALUE: the IR is identical from SROA to the last IR pass, and
// every machine pass from Expand ISel Pseudo-instructions to Virtual Register Rewriter is identical, register allocation included. The first pass that differs is `A57 FP
// Anti-dependency breaker` (AArch64A57FPLoadBalancing): with the local the DBG_VALUE of `radian` sits between the `fmul` and its use, and the chain keeps s0 (`fmul s0, s0, s1`, then
// `fmul s8, s0, s1`, the game's); without it the pass renames the first product to s3 and the product with w to s18. The rotation is the plain Quat::rotate (mm::unknown010 gives the
// same code here).
void LookAxisPlugin::setYaw(f32 yaw) {
  unknown18 = yaw;
  mm::Vec3 front = mm::Vec3::unitZ;
  if (fabsf(yaw) > FLT_EPSILON) {
    f32 radian = yaw * mm::DEG_TO_RAD;
    mm::Quat rotation;
    rotation.unknown001(radian * 0.5f);
    front = rotation.rotate(front);
  }
  GfComIK *ik = m_comBehaviorPc->unknown08->getComponent<GfComIK>();
  if (ik != nullptr) {
    fw::LookIkSolver *look = ik->unknown003<fw::LookIkSolver>(unknown002_3);
    if (look != nullptr) {
      look->setFrontMS(front);
    } else {
      fw::LookAtIkSolver *lookAt = ik->unknown003<fw::LookAtIkSolver>(unknown002_5);
      if (lookAt != nullptr) {
        lookAt->unknown60 = front;
      }
    }
  }
  TargetIKPlugin *targetIK = m_comBehaviorPc->unknown001<TargetIKPlugin>(6);
  if (targetIK != nullptr) {
    targetIK->unknown30 = front;
  }
}

void LookAxisPlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &info) {
  if (!unknown28) {
    return;
  }

  const unknown088 *param = getParam();
  unknown24 += info.unknown04;
  setYaw(calcYaw(param->unknown14));
  if (unknown24 >= param->unknown14) {
    unknown28 = false;
  }
}

const unknown088 *LookAxisPlugin::getParam() const { return unknown30 != nullptr ? static_cast<const unknown088 *>(unknown30->param) : nullptr; }

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
