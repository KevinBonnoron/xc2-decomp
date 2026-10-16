#include "event/script_cam_tar.h"

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

void ScriptCamTar::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  TarAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  CV_TYPE cv = static_cast<CV_TYPE>(param.val(4).getS32());
  prevAxis = camera->getTarAxis();
  camera->setTarAxis(axis, cv);
  if (prevAxis.getAxis() != axis.getAxis() || !(__builtin_fabsf(axis.getTar().x - prevAxis.getTar().x) <= 1e-6f) ||
      !(__builtin_fabsf(axis.getTar().y - prevAxis.getTar().y) <= 1e-6f) || !(__builtin_fabsf(axis.getTar().z - prevAxis.getTar().z) <= 1e-6f)) {
    mm::mtl::Singleton<TextManager>::getPtr()->setCutChangeFrame();
  }
}

void ScriptCamTar::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CAMERA) {
    return;
  }
  TarAxis axis = prevAxis;
  static_cast<ObjectCamera *>(object)->setTarAxis(axis, CV_TYPE_LINEAR);
}

} // namespace event
