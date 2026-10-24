#include "event/script_cam_pos.h"

#include "event/curve.h"
#include "event/object.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "event/text_manager.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCamPos::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  CV_TYPE cv = static_cast<CV_TYPE>(param.val(4).getS32());
  unknown10 = camera->getPosAxis();
  camera->setPosAxis(axis, cv);
  if (unknown10.getAxis() != axis.getAxis() || !(__builtin_fabsf(axis.getPos().x - unknown10.getPos().x) <= 1e-6f) || !(__builtin_fabsf(axis.getPos().y - unknown10.getPos().y) <= 1e-6f) ||
      !(__builtin_fabsf(axis.getPos().z - unknown10.getPos().z) <= 1e-6f)) {
    mm::mtl::Singleton<TextManager>::getPtr()->setCutChangeFrame();
  }
}

void ScriptCamPos::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  PosAxis axis = unknown10;
  static_cast<ObjectCamera *>(object)->setPosAxis(axis, CV_TYPE_LINEAR);
}

} // namespace event
