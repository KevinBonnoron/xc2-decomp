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
  if (ScriptUtil::getObjType(object) != OBJTYPE_UNKNOWN_3) {
    return;
  }
  ObjectCamera *camera = static_cast<ObjectCamera *>(object);
  TarAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  CV_TYPE cv = static_cast<CV_TYPE>(param.val(4).getS32());
  m_tarAxis = camera->getTarAxis();
  camera->setTarAxis(axis, cv);
  if (m_tarAxis.getAxis() != axis.getAxis() || !(__builtin_fabsf(axis.getTar().x - m_tarAxis.getTar().x) <= 1e-6f) || !(__builtin_fabsf(axis.getTar().y - m_tarAxis.getTar().y) <= 1e-6f) ||
      !(__builtin_fabsf(axis.getTar().z - m_tarAxis.getTar().z) <= 1e-6f)) {
    mm::mtl::Singleton<TextManager>::getPtr()->setCutChangeFrame();
  }
}

void ScriptCamTar::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_UNKNOWN_3) {
    return;
  }
  TarAxis axis = m_tarAxis;
  static_cast<ObjectCamera *>(object)->setTarAxis(axis, CV_TYPE_UNKNOWN_1);
}

} // namespace event
