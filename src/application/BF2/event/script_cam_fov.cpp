#include "event/script_cam_fov.h"

#include "event/curve.h"
#include "event/object.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCamFov::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  f32 fov = param.val(0).getF32();
  CV_TYPE cv = static_cast<CV_TYPE>(param.val(1).getS32());
  prevFov = camera->getFov();
  camera->setFov(fov, cv);
}

void ScriptCamFov::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  static_cast<ObjectCamera *>(object)->setFov(prevFov, CV_TYPE_LINEAR);
}

} // namespace event
