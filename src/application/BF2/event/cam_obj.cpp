#include "event/cam_obj.h"

#include "event/cam_interface.h"
#include "event/cam_manager.h"
#include "event/cam_util.h"
#include "event/cmd_param.h"
#include "event/cmd_variable.h"
#include "event/curve.h"
#include "event/frame_manager.h"
#include "event/manager.h"
#include "event/offscr_manager.h"
#include "event/pos_axis.h"
#include "event/tar_axis.h"
#include "ml/attr_transform.h"
#include "ml/scn.h"
#include "ml/threadval.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {

ICmd::RESULT CamObj::SetEnable::update(const Param &param) {
  u32 screenID = param.val(0).getS32();
  bool isEnable = param.val(1).getBool();
  mm::mtl::Singleton<CamManager>::getPtr()->unknown001(screenID)->setEnable(isEnable);
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT CamObj::SetTargetPos::update(const Param &param) {
  u32 screenID = param.val(0).getS32();
  mm::Vec3 position(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  mm::Vec3 target(param.val(4).getF32(), param.val(5).getF32(), param.val(6).getF32());
  f32 roll = param.val(7).getF32();
  mm::mtl::Singleton<CamManager>::getPtr()->unknown001(screenID)->setTargetPos(position, target, roll);
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT CamObj::SetFov::update(const Param &param) {
  u32 screenID = param.val(0).getS32();
  f32 fov = param.val(1).getF32();
  if (param.val(2).getBool()) {
    fov = CamUtil::toFov(fov);
  }
  mm::mtl::Singleton<CamManager>::getPtr()->unknown001(screenID)->setFov(__builtin_fmaxf(fov, 5.0f));
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT CamObj::SetNearfar::update(const Param &param) {
  u32 screenID = param.val(0).getS32();
  f32 nearClip = param.val(1).getF32();
  f32 farClip = param.val(2).getF32();
  mm::mtl::Singleton<CamManager>::getPtr()->unknown001(screenID)->setNearFar(nearClip, farClip);
  return RESULT_UNKNOWN_1;
}

// The game inlines the CamBase, CamField, CamHands, CamMotion and CmdQueue constructors here (0x71000b45b8, 429 instructions). The scene camera
// is read through its front render info once per vector, as the game does. `active` carries the active camera out of the two branches: storing
// unknownc70 in each branch instead gives other stores and registers.
CamObj::CamObj(u32 screenID, bool isFocal, bool isStreamMode)
    : CamBase(isFocal), unknown60(0), unknown64(0), unknown70(isFocal), unknownb0(isFocal), unknownbb0(isFocal, isStreamMode), unknownc70(&unknownb0) {
  if (screenID != 0) {
    mm::mtl::Singleton<OffscrManager>::getPtr()->createScreen(screenID);
  }
  if (mm::mtl::Singleton<CamManager>::getPtr()->isOffscrMode()) {
    screenID = mm::mtl::Singleton<CamManager>::getPtr()->getOffscrID();
  }
  unknown64 = screenID;
  ml::ScnObjCam *cam = Manager::get()->getScn()->getCam(-1);
  CamBase *active = nullptr;
  if (screenID == 0) {
    unknown70.unknown003(cam);
    unknown70.unknown004();
    unknown70.setNearFar(0.1f, 40000.0f);
    unknownb0.setPos(PosAxis(PosAxis::AXIS_UNKNOWN_1, cam->unknown70.m_front->unknown00.unknown10), CV_TYPE_UNKNOWN_1);
    unknownb0.setTar(TarAxis(TarAxis::AXIS_UNKNOWN_1, cam->unknown70.m_front->m_targetPos), CV_TYPE_UNKNOWN_1);
    unknownb0.setFov(40.0f, CV_TYPE_UNKNOWN_1);
    unknownb0.setRotZ(0.0f, CV_TYPE_UNKNOWN_1);
    unknownb0.setNearFar(0.1f, 40000.0f);
    unknownbb0.unknown003(cam);
    unknownbb0.unknown004();
    unknownbb0.setNearFar(0.1f, 40000.0f);
    unknown003(cam);
    active = &unknown70;
  } else {
    unknown70.unknown004();
    unknown70.setNearFar(0.1f, 40000.0f);
    unknownb0.setFov(40.0f, CV_TYPE_UNKNOWN_1);
    unknownb0.setRotZ(0.0f, CV_TYPE_UNKNOWN_1);
    unknownb0.setNearFar(0.1f, 40000.0f);
    unknownbb0.unknown004();
    unknownbb0.setNearFar(0.1f, 40000.0f);
  }
  setNearFar(0.1f, 40000.0f);
  unknown004();
  unknownc70 = active;
  // The game empties the command queue again after the constructors (the loop that destroys its items, 0x71000b4c20).
  unknownc78.clear();
}

CamObj::~CamObj() {
  changeActive(nullptr);
  unknownc78.update();
  unknownc78.update();
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
  param.unknown001(1, pos);
  param.unknown001(4, target);
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
