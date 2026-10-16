#include "event/script_cam_follow_pos.h"

#include "event/object.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCamFollowPos::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  prevFollow = camera->isFollowPos();
  camera->followPos(param.val(0).getBool());
}

void ScriptCamFollowPos::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  static_cast<ObjectCamera *>(object)->followPos(prevFollow);
}

} // namespace event
