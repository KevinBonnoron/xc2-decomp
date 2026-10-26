#include "event/cam_obj.h"

#include "event/cam_interface.h"
#include "event/cam_manager.h"
#include "event/cam_util.h"
#include "event/cmd_variable.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {

ICmd::RESULT CamObj::SetEnable::update(const Param &param) {
  u32 screenID = param.val(0).getS32();
  bool isEnable = param.val(1).getBool();
  mm::mtl::Singleton<CamManager>::getPtr()->unknown001(screenID)->setEnable(isEnable);
  return RESULT_END;
}

ICmd::RESULT CamObj::SetTargetPos::update(const Param &param) {
  u32 screenID = param.val(0).getS32();
  mm::Vec3 position(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  mm::Vec3 target(param.val(4).getF32(), param.val(5).getF32(), param.val(6).getF32());
  f32 roll = param.val(7).getF32();
  mm::mtl::Singleton<CamManager>::getPtr()->unknown001(screenID)->setTargetPos(position, target, roll);
  return RESULT_END;
}

ICmd::RESULT CamObj::SetFov::update(const Param &param) {
  u32 screenID = param.val(0).getS32();
  f32 fov = param.val(1).getF32();
  if (param.val(2).getBool()) {
    fov = CamUtil::toFov(fov);
  }
  mm::mtl::Singleton<CamManager>::getPtr()->unknown001(screenID)->setFov(__builtin_fmaxf(fov, 5.0f));
  return RESULT_END;
}

ICmd::RESULT CamObj::SetNearfar::update(const Param &param) {
  u32 screenID = param.val(0).getS32();
  f32 nearClip = param.val(1).getF32();
  f32 farClip = param.val(2).getF32();
  mm::mtl::Singleton<CamManager>::getPtr()->unknown001(screenID)->setNearFar(nearClip, farClip);
  return RESULT_END;
}

void CamObj::start() {}

void CamObj::end() {
  unknownc78.eraseAll();
  unknownbb0.stop();
}

void CamObj::render(const mm::Col4 &color) {
  if (unknownc70 != nullptr) {
    unknownc70->render(color);
  }
}

void CamObj::tail() {
  if (unknownc70 != nullptr) {
    unknownc78.update();
  }
}

} // namespace event
