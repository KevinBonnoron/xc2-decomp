#include "event/cam_obj.h"

#include <stddef.h>

#include "event/cam_interface.h"
#include "event/cam_manager.h"
#include "event/cam_util.h"
#include "event/cmd_param.h"
#include "event/cmd_variable.h"
#include "event/frame_manager.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {

// Inferred role: stores a vector in three consecutive variables of a command parameter; original name unknown.
static void unknown001(CmdParam &param, size_t index, const mm::Vec3 &vec) {
  param.val(index).setF32(vec.x);
  param.val(index + 1).setF32(vec.y);
  param.val(index + 2).setF32(vec.z);
}

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

void CamObj::changeActive(CamBase *cam) {
  if (unknownc70 == cam) {
    return;
  }
  if (unknownc70 != nullptr && unknownc70 != &unknown70) {
    CmdParam param;
    param.val(0).setS32(unknown64);
    param.val(1).setBool(false);
    unknownc78.push_back(&unknown40, param);
  }
  unknownc70 = cam;
  if (cam != nullptr && cam != &unknown70) {
    CmdParam param;
    param.val(0).setS32(unknown64);
    param.val(1).setBool(true);
    unknownc78.push_back(&unknown40, param);
  }
}

void CamObj::start() {}

void CamObj::end() {
  unknownc78.eraseAll();
  unknownbb0.stop();
}

void CamObj::update(const FrameInfo &info) {
  if (unknownc70 == nullptr || !(info.unknown0c > 0.0f)) {
    return;
  }
  unknownc70->update(info);
  mm::Vec3 pos = unknownc70->getPos();
  mm::Vec3 target = unknownc70->getTarget();
  f32 fov = unknownc70->getFov();
  f32 roll = unknownc70->getRoll();
  f32 nearClip = unknownc70->getNear();
  f32 farClip = unknownc70->getFar();
  unknown10 = pos;
  unknown20 = target;
  unknown30 = fov;
  unknown34 = roll;
  unknown38 = nearClip;
  unknown3c = farClip;
  if (unknownc70 == &unknown70) {
    return;
  }
  if (mm::mtl::Singleton<CamManager>::getPtr()->isFreeCam()) {
    return;
  }
  CmdParam param;
  param.val(0).setS32(unknown64);
  unknown001(param, 1, pos);
  unknown001(param, 4, target);
  param.val(7).setF32(roll);
  unknownc78.push_back(&unknown48, param);
  param.val(0).setS32(unknown64);
  param.val(1).setF32(fov);
  param.val(2).setBool(unknown08);
  unknownc78.push_back(&unknown50, param);
  param.val(0).setS32(unknown64);
  param.val(1).setF32(nearClip);
  param.val(2).setF32(farClip);
  unknownc78.push_back(&unknown58, param);
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
