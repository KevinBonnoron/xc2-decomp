#include "event/script_cam_move_rot_z.h"

#include "event/curve.h"
#include "event/object.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCamMoveRotZ::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  static_cast<ObjectCamera *>(object)->moveRotZ(param.val(0).getF32() * mm::DEG_TO_RAD, param.val(1).getF32(), CV_TYPE_LINEAR);
}

void ScriptCamMoveRotZ::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  static_cast<ObjectCamera *>(object)->moveRotZ(param.val(0).getF32() * mm::DEG_TO_RAD, 0.0f, CV_TYPE_LINEAR);
}

} // namespace event
