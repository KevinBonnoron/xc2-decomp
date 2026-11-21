#include "event/chara_set_rot.h"

#include "event/cmd_variable.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace event {

ICmd::RESULT CharaSetRot::update(const Param &param) {
  if (unknown08 != gf::unknown020) {
    gf::GfObj *obj = gf::GfObjUtil::getObj(unknown08);
    if (obj == nullptr) {
      return RESULT_UNKNOWN_0;
    }
    gf::GfComTransform *transform = obj->getComponent<gf::GfComTransform>();
    mm::Quat rotation;
    mm::unknown009(rotation, mm::Vec3(param.val(0).getF32(), param.val(1).getF32(), param.val(2).getF32()));
    transform->setRotation(rotation);
  }
  return RESULT_UNKNOWN_1;
}

} // namespace event
