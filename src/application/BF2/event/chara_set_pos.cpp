#include "event/chara_set_pos.h"

#include "event/cmd_variable.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"

namespace event {

ICmd::RESULT CharaSetPos::update(const Param &param) {
  if (unknown08 != gf::unknown020) {
    gf::GfObj *obj = gf::GfObjUtil::getObj(unknown08);
    if (obj == nullptr) {
      return RESULT_UNKNOWN_0;
    }
    obj->getComponent<gf::GfComTransform>()->setPosition(mm::Vec3(param.val(0).getF32(), param.val(1).getF32(), param.val(2).getF32()));
  }
  return RESULT_UNKNOWN_1;
}

} // namespace event
