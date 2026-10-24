#include "event/script_cam_nearfar.h"

#include "event/cam_hands.h"
#include "event/cam_obj.h"
#include "event/cam_util.h"
#include "event/object.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCamNearfar::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  EVT_nearfar nearfar = static_cast<EVT_nearfar>(param.val(0).getS32());
  unknown08 = camera->getCamObj()->getHands()->getNear();
  unknown0c = camera->getCamObj()->getHands()->getFar();
  camera->getCamObj()->getHands()->setNearfar(nearfar);
}

void ScriptCamNearfar::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  static_cast<ObjectCamera *>(object)->getCamObj()->getHands()->setNearfar(unknown08, unknown0c);
}

} // namespace event
