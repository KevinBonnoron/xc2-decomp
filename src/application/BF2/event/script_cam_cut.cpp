#include "event/script_cam_cut.h"

#include "event/object.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCamCut::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  const char *name = param.val(0).getStr();
  unknown08 = camera->getCutName();
  camera->setCutName(name);
}

void ScriptCamCut::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) == OBJTYPE_CAMERA) {
    static_cast<ObjectCamera *>(object)->setCutName(unknown08.c_str());
  }
}

} // namespace event
