#include "event/chara_set_rot.h"

#include <math.h>

#include "event/cmd_variable.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat.h"
#include "types.h"

namespace event {

ICmd::RESULT CharaSetRot::update(const Param &param) {
  if (handle != gf::INVALID_HANDLE) {
    gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
    if (obj == nullptr) {
      return RESULT_WAIT;
    }
    gf::GfComTransform *transform = obj->getComponent<gf::GfComTransform>();
    f32 x = param.val(0).getF32();
    f32 y = param.val(1).getF32();
    f32 z = param.val(2).getF32();
    f32 sinX = sinf(x * 0.5f);
    f32 cosX = cosf(x * 0.5f);
    f32 sinY = sinf(y * 0.5f);
    f32 cosY = cosf(y * 0.5f);
    f32 sinZ = sinf(z * 0.5f);
    f32 cosZ = cosf(z * 0.5f);
    mm::Quat rotation;
    rotation.x = sinX * cosY * cosZ + cosX * sinY * sinZ;
    rotation.y = cosX * sinY * cosZ - sinX * cosY * sinZ;
    rotation.z = cosX * cosY * sinZ - sinX * sinY * cosZ;
    rotation.w = cosX * cosY * cosZ + sinX * sinY * sinZ;
    transform->setRotation(rotation);
  }
  return RESULT_END;
}

} // namespace event
