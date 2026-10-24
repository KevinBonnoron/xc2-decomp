#include "event/script_cam_rot_z.h"

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

void ScriptCamRotZ::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  f32 rotZ = param.val(0).getF32() * mm::DEG_TO_RAD;
  CV_TYPE cv = static_cast<CV_TYPE>(param.val(1).getS32());
  unknown08 = camera->getRotZ();
  camera->setRotZ(rotZ, cv);
}

void ScriptCamRotZ::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  static_cast<ObjectCamera *>(object)->setRotZ(unknown08, CV_TYPE_LINEAR);
}

} // namespace event
