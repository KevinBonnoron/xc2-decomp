#include "event/script_cam_move_pos.h"

#include "event/curve.h"
#include "event/object.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/pos_axis.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCamMovePos::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  camera->movePosAxis(axis, param.val(4).getF32(), static_cast<CV_TYPE>(param.val(5).getS32()));
}

void ScriptCamMovePos::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  camera->movePosAxis(axis, 0.0f, static_cast<CV_TYPE>(param.val(5).getS32()));
}

} // namespace event
