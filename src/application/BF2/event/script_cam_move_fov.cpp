#include "event/script_cam_move_fov.h"

#include "event/curve.h"
#include "event/object.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCamMoveFov::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  static_cast<ObjectCamera *>(object)->moveFov(param.val(0).getF32(), param.val(1).getF32(), CV_TYPE_LINEAR);
}

void ScriptCamMoveFov::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  static_cast<ObjectCamera *>(object)->moveFov(param.val(0).getF32(), 0.0f, CV_TYPE_LINEAR);
}

} // namespace event
