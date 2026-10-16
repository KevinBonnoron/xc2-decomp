#include "event/script_cam_motion.h"

#include "event/object.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCamMotion::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  camera->playMotion(param.val(0).getStr(), mm::Vec3(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
}

void ScriptCamMotion::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  static_cast<ObjectCamera *>(object)->stopMotion();
}

} // namespace event
