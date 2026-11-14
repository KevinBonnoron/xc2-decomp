#include "gf/field/gf_field_exec_cmd_turn.h"

#include <math.h>

#include "fw/fw_transform.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"

namespace gf {

template <typename T> void TFieldExecCmdTurn<T>::create(const CreateInfo &info) {
  dispose();
  unknown00 = info;
  mm::mtl::FixStr<32> command;
  {
    GfObjAcc acc(unknown00.unknown00);
    mm::Vec3 front = acc.getWorldTransform().unknown10.rotate(mm::Vec3::unitZ);
    f32 angle = atan2f(front.x, front.z);
    unknown58 = mm::unknown003(unknown00.unknown08 - angle);
    if (fabsf(unknown58) < unknown00.unknown0c) {
      command.clear();
    } else if (fabsf(unknown58) < unknown00.unknown10) {
      command = unknown58 > 0.0f ? "C_turnLA" : "C_turnRA";
    } else {
      command = unknown58 > 0.0f ? "C_turnLB" : "C_turnRB";
    }
  }

  if (command.empty()) {
    unknown68 = 0.0f;
    if (unknown00.unknown18 > 0.0f) {
      unknown64 = unknown00.unknown18;
    } else {
      unknown6c = true;
    }
    return;
  }
  {
    GfObjAcc acc(unknown00.unknown00);
    GfObj *obj = acc.getObj();
    if (obj != nullptr) {
      T *comAsm = obj->getComponent<T>();
      if (comAsm != nullptr) {
        if (!comAsm->execCmd("C_walkend")) {
          comAsm->execCmd("C_idle");
        }
      } else {
        GfComTransform *transform = obj->getComponent<GfComTransform>();
        if (transform != nullptr) {
          mm::Quat rotation;
          f32 half = info.unknown08 * 0.5f;
          rotation.y = sinf(half);
          rotation.w = cosf(half);
          rotation.x = 0.0f;
          rotation.z = 0.0f;
          transform->setRotation(rotation);
        }
        unknown6c = true;
        return;
      }
    }
  }
  typename TFieldExecCmd<T>::CreateInfo createInfo(unknown00.unknown00, command.c_str());
  unknown20.create(createInfo);
}

template class TFieldExecCmdTurn<GfComAsm>;
template class TFieldExecCmdTurn<GfComEvtAnim>;

} // namespace gf
