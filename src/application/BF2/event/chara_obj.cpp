#include "event/chara_obj.h"

#include "event/chara_facial_util.h"
#include "event/chara_manager.h"
#include "event/chara_util.h"
#include "event/cmd_param.h"
#include "event/cmd_variable.h"
#include "event/debug_manager.h"
#include "event/skip_manager.h"
#include "event/tar_axis.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_mtl/singleton.h"

namespace event {

void CharaObj::playWink(int type, f32 frame, bool isLoop, f32 lensX, f32 lensY, int lensType, bool isDirect, bool isAuto) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  subQueue.erase(&cmdPlayWink);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setS32(type);
  param.val(2).setF32(frame);
  param.val(3).setBool(isLoop);
  param.val(4).setF32(lensX);
  param.val(5).setF32(lensY);
  param.val(6).setS32(lensType);
  param.val(7).setBool(isDirect);
  param.val(8).setBool(isAuto);
  subQueue.push_back(&cmdPlayWink, param);
}

const mm::Vec3 &CharaObj::getPos() const { return pos; }

void CharaObj::renderAction() {
  cmdPlayAction.render(pos, eyeOffset);
  cmdPlayActionAuto.render(pos, eyeOffset);
}

f32 CharaObj::getEyeOffset() const { return eyeOffset; }

void CharaObj::renderHead() { cmdPlayHead.render(pos, eyeOffset); }

void CharaObj::renderFacial() { cmdPlayFacial.render(pos, eyeOffset); }

void CharaObj::renderLens() { lensPlayer.render(pos, eyeOffset); }

void CharaObj::renderWeight() { weightPlayer.render(pos, eyeOffset); }

void CharaObj::renderIK() { ikUpdater.render(pos, eyeOffset); }

void CharaObj::setPos(const mm::Vec3 &pos) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  this->pos = pos;
  fadeQueue.erase(&cmdSetPos);
  CmdParam param;
  param.val(0).setF32(pos.x);
  param.val(1).setF32(pos.y);
  param.val(2).setF32(pos.z);
  fadeQueue.push_back(&cmdSetPos, param);
}

void CharaObj::linerPos(const mm::Vec3 &pos, bool isWalk, f32 frame, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mm::Vec3 to = pos;
  if (isWalk) {
    CharaUtil::adjestPosY(to, nullptr);
  }
  if (frame == 0.0f) {
    this->pos = to;
    posTo = to;
    subQueue.erase(&cmdLinerPos);
  } else {
    posTo = to;
  }
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(to.x);
  param.val(2).setF32(to.y);
  param.val(3).setF32(to.z);
  param.val(4).setF32(frame);
  param.val(5).setS32(cv);
  subQueue.push_back(&cmdLinerPos, param);
  evaPlayer.setPos(pos);
}

const mm::Vec3 &CharaObj::getPosTo() const {
  if (queue.isExist(&cmdWalkPos) || subQueue.isExist(&cmdWalkPos) || subQueue.isExist(&cmdLinerPos)) {
    return posTo;
  }
  return pos;
}

void CharaObj::setRot(const mm::Vec3 &rot) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  this->rot = rot;
  fadeQueue.erase(&cmdSetRot);
  CmdParam param;
  param.val(0).setF32(rot.x);
  param.val(1).setF32(rot.y);
  param.val(2).setF32(rot.z);
  fadeQueue.push_back(&cmdSetRot, param);
}

void CharaObj::turnRot(const mm::Vec3 &rot, EVT_rotcvtype cv, f32 frame) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  this->rot = rot;
  rotTo = rot;
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(rot.x);
  param.val(2).setF32(rot.y);
  param.val(3).setF32(rot.z);
  param.val(4).setS32(cv);
  param.val(5).setF32(frame);
  CmdQueue<QUEUE_COUNT, 0> *target = &queue;
  if (cv == 0) {
    if (queue.isExist(&cmdTurnRot)) {
      queue.erase(&cmdTurnRot);
    }
    target = &subQueue;
  }
  target->push_back(&cmdTurnRot, param);
}

void CharaObj::linerRot(const mm::Vec3 &rot, f32 frame, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (frame == 0.0f) {
    this->rot = rot;
    rotTo = rot;
    subQueue.erase(&cmdLinerRot);
  } else {
    rotTo = rot;
  }
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(rot.x);
  param.val(2).setF32(rot.y);
  param.val(3).setF32(rot.z);
  param.val(4).setF32(frame);
  param.val(5).setS32(cv);
  subQueue.push_back(&cmdLinerRot, param);
}

const mm::Vec3 &CharaObj::getRot() const { return rot; }

const mm::Vec3 &CharaObj::getRotTo() const {
  if (queue.isExist(&cmdTurnRot) || subQueue.isExist(&cmdTurnRot) || subQueue.isExist(&cmdLinerRot)) {
    return rotTo;
  }
  return rot;
}

bool CharaObj::isTurnable() const { return !fadeQueue.isExist(&cmdSetRot); }

void CharaObj::setTar(const TarAxis &axis, f32 frame, EVT_tarcvtype cv, EVT_aimtype aim, f32 weight, f32 speed) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isSystemTicket960() && CharaFacialUtil::checkBdatID(handle, 2) && queue.isExist(&cmdPlayAction) &&
      (cmdPlayAction.getType() == 6 || cmdPlayAction.getType() == 11)) {
    return;
  }
  fadeQueue.erase(&cmdSetTar);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setS32(axis.getAxis());
  param.val(2).setF32(axis.getTar().x);
  param.val(3).setF32(axis.getTar().y);
  param.val(4).setF32(axis.getTar().z);
  param.val(5).setF32(frame);
  param.val(6).setS32(cv);
  param.val(7).setS32(aim);
  param.val(8).setF32(weight);
  param.val(9).setF32(speed);
  fadeQueue.push_back(&cmdSetTar, param);
}

void CharaObj::resetTar() { fadeQueue.erase(&cmdSetTar); }

const mm::Vec3 &CharaObj::getTar() const { return cmdSetTar.getTar(); }

bool CharaObj::isTar() const { return fadeQueue.isExist(&cmdSetTar); }

void CharaObj::setLensTarget(const mm::Vec2 &target) { lensPlayer.setManualTarget(true, target, true); }

const mm::Vec2 &CharaObj::getLensTarget() const { return lensPlayer.getTarget(); }

void CharaObj::setIdle(int type) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  queue.erase(&cmdSetIdle);
  queue.erase(&cmdPlayActionAuto);
  queue.erase(&cmdPlayAction);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setS32(type);
  queue.push_back(&cmdSetIdle, param);
}

int CharaObj::getIdle() const {
  if (queue.isExist(&cmdSetIdle)) {
    return cmdSetIdle.getType();
  }
  return 0;
}

void CharaObj::playAutoAction(f32 frame) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (!mm::mtl::Singleton<CharaManager>::getPtr()->isAutoTalkMode()) {
    return;
  }
  queue.erase(&cmdSetIdle);
  queue.erase(&cmdPlayActionAuto);
  queue.erase(&cmdPlayAction);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(frame);
  queue.push_back(&cmdPlayActionAuto, param);
}

void CharaObj::playAction(int type, f32 frame, bool isLoop, bool isBlend) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isSeamlessAction() && queue.isExist(&cmdPlayAction) && cmdPlayAction.getType() == type) {
    cmdPlayAction.keep();
    mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("action seamless");
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isSystemTicket960() && CharaFacialUtil::checkBdatID(handle, 2) && (type == 11 || type == 6)) {
    resetTar();
  }
  queue.erase(&cmdSetIdle);
  queue.erase(&cmdPlayActionAuto);
  queue.erase(&cmdPlayAction);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setS32(type);
  param.val(2).setF32(frame);
  param.val(3).setBool(isLoop);
  param.val(4).setBool(isBlend);
  queue.push_back(&cmdPlayAction, param);
}

void CharaObj::stopAction() {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (queue.isExist(&cmdPlayAction)) {
    queue.erase(&cmdPlayAction);
    queue.push_back(&cmdStopAction, CmdParam());
  }
}

int CharaObj::getAction() const {
  if (queue.isExist(&cmdPlayAction)) {
    return cmdPlayAction.getType();
  }
  return 0;
}

f32 CharaObj::getActionLastFrame() const {
  if (queue.isExist(&cmdPlayAction)) {
    return cmdPlayAction.getLastFrame();
  }
  return 0.0f;
}

void CharaObj::playMotion(const char *name, f32 frame, f32 blend, f32 speed) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (mm::mtl::Singleton<DebugManager>::getPtr()->isFailureSkip()) {
    return;
  }
  if ((state & ~1) == 4) {
    initModelStream();
    flags |= FLAG_MODEL_STREAM;
    streamFrame = frame;
  }
  subQueue.erase(&cmdPlayMotion);
  subQueue.erase(&cmdPlayMotionABC);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setStr(name);
  param.val(2).setF32(frame);
  param.val(3).setF32(blend);
  param.val(4).setF32(speed);
  subQueue.push_back(&cmdPlayMotion, param);
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
    subQueue.erase(&cmdPlayEva);
    subQueue.erase(&cmdPlayEvaEff);
    subQueue.erase(&cmdHideWpn);
    param.val(0).setUserdata(this);
    param.val(1).setStr(name);
    param.val(2).setF32(frame);
    param.val(3).setF32(blend);
    subQueue.push_back(&cmdPlayEva, param);
    param.val(0).setUserdata(this);
    param.val(1).setStr(name);
    param.val(2).setF32(frame);
    param.val(3).setF32(blend);
    subQueue.push_back(&cmdPlayEvaEff, param);
    param.val(0).setUserdata(this);
    param.val(1).setF32(frame);
    subQueue.push_back(&cmdHideWpn, param);
  }
}

void CharaObj::playMotionABC(const char *nameA, const char *nameB, const char *nameC, f32 frameA, f32 frameB, f32 frameC, f32 blendA, f32 blendB,
                             f32 blendC) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  subQueue.erase(&cmdPlayMotion);
  subQueue.erase(&cmdPlayMotionABC);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setStr(nameA);
  param.val(2).setStr(nameB);
  param.val(3).setStr(nameC);
  param.val(4).setF32(frameA);
  param.val(5).setF32(frameB);
  param.val(6).setF32(frameC);
  param.val(7).setF32(blendA);
  param.val(8).setF32(blendB);
  param.val(9).setF32(blendC);
  subQueue.push_back(&cmdPlayMotionABC, param);
}

void CharaObj::playHead(int type, f32 life, bool isBlendIn, bool isBlendOut) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  subQueue.erase(&cmdPlayHead);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setS32(type);
  param.val(2).setF32(life);
  param.val(3).setBool(isBlendIn);
  param.val(4).setBool(isBlendOut);
  subQueue.push_back(&cmdPlayHead, param);
}

void CharaObj::stopHead() {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (subQueue.isExist(&cmdPlayHead)) {
    subQueue.erase(&cmdPlayHead);
    subQueue.push_back(&cmdStopHead, CmdParam());
  }
}

int CharaObj::getHead() const {
  if (subQueue.isExist(&cmdPlayHead)) {
    return cmdPlayHead.getType();
  }
  return 0;
}

void CharaObj::playFacial(int type, f32 life, int browType, f32 browWeight, int eyeType, f32 eyeWeight, int lipType, f32 lipWeight, f32 blendIn,
                          f32 blendOut) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  subQueue.erase(&cmdPlayFacial);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setS32(type);
  param.val(2).setF32(life);
  param.val(3).setS32(browType);
  param.val(4).setF32(browWeight);
  param.val(5).setS32(eyeType);
  param.val(6).setF32(eyeWeight);
  param.val(7).setS32(lipType);
  param.val(8).setF32(lipWeight);
  param.val(9).setF32(blendIn);
  param.val(10).setF32(blendOut);
  subQueue.push_back(&cmdPlayFacial, param);
}

int CharaObj::getFacial() const {
  if (subQueue.isExist(&cmdPlayFacial)) {
    return cmdPlayFacial.getType();
  }
  return 0;
}

void CharaObj::playAutoTalk(f32 frame) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (!mm::mtl::Singleton<CharaManager>::getPtr()->isAutoTalkMode()) {
    return;
  }
  subQueue.erase(&cmdPlayTalkAuto);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(frame);
  subQueue.push_back(&cmdPlayTalkAuto, param);
}

void CharaObj::playTalk(bool isManual, f32 frame, bool isBlend, bool isAuto, f32 openMin, f32 openMax, f32 closeMin, f32 closeMax) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (!isManual && subQueue.isExist(&cmdPlayTalk) && cmdPlayTalk.isManual()) {
    return;
  }
  subQueue.erase(&cmdPlayTalk);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setBool(isManual);
  param.val(2).setF32(frame);
  param.val(3).setBool(isBlend);
  param.val(4).setBool(isAuto);
  param.val(5).setF32(openMin);
  param.val(6).setF32(openMax);
  param.val(7).setF32(closeMin);
  param.val(8).setF32(closeMax);
  subQueue.push_back(&cmdPlayTalk, param);
}

void CharaObj::mount(CharaObj *target, const char *bone, const mm::Vec3 &pos, const mm::Vec3 &rot) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  subQueue.erase(&cmdMount);
  if (target == nullptr) {
    CmdParam param;
    param.val(0).setUserdata(nullptr);
    param.val(1).setStr("");
    param.val(2).setF32(0.0f);
    param.val(3).setF32(0.0f);
    param.val(4).setF32(0.0f);
    param.val(5).setF32(0.0f);
    param.val(6).setF32(0.0f);
    param.val(7).setF32(0.0f);
    subQueue.push_back(&cmdMount, param);
    flags &= ~FLAG_MOUNT;
  } else {
    CmdParam param;
    param.val(0).setUserdata(target->model);
    param.val(1).setStr(bone);
    param.val(2).setF32(pos.x);
    param.val(3).setF32(pos.y);
    param.val(4).setF32(pos.z);
    param.val(5).setF32(rot.x);
    param.val(6).setF32(rot.y);
    param.val(7).setF32(rot.z);
    subQueue.push_back(&cmdMount, param);
    flags |= FLAG_MOUNT;
  }
}

void CharaObj::resetDynamics(int frame) { dysUpdater.resetDynamics(frame); }

void CharaObj::playFade(bool isOut, f32 frame) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  subQueue.erase(&cmdFade);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setBool(isOut);
  param.val(2).setF32(frame);
  subQueue.push_back(&cmdFade, param);
  if (isOut) {
    flags |= FLAG_FADE_OUT;
  } else {
    flags &= ~FLAG_FADE_OUT;
  }
}

bool CharaObj::isFadeOut() const { return (flags & FLAG_FADE_OUT) != 0; }

void CharaObj::playVolumeFade(CharaEffectPlayer::VF_TYPE type, int id, const mm::Vec3 &position, const mm::Vec3 &scale, f32 frame, f32 rate, int mode,
                              f32 speed) {
  effectPlayer.playVolumeFade(type, id, position, scale, frame, rate, mode, speed);
}

void CharaObj::playVolumeFadeAnim(CharaEffectPlayer::VF_TYPE type, f32 rate, f32 frame) { effectPlayer.playVolumeFadeAnim(type, rate, frame); }

void CharaObj::stopVolumeFade(CharaEffectPlayer::VF_TYPE type) { effectPlayer.stopVolumeFade(type); }

void CharaObj::playRimBloom(int id) { effectPlayer.playRimBloom(id); }

void CharaObj::stopRimBloom() { effectPlayer.stopRimBloom(); }

void CharaObj::setExtDisp(const char *name, bool isDisp) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  partUpdater.setExtDisp(name, isDisp);
}

void CharaObj::setExtDispWeapon(const char *name, bool isDisp) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  partUpdater.setExtDispWeapon(name, isDisp);
}

void CharaObj::setExtParam(const char *name, f32 value) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  partUpdater.setExtParam(name, value);
}

void CharaObj::setScaleWeapon(f32 scale) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  weaponScale = scale;
  updateScaleWeapon();
}

void CharaObj::updateScaleWeapon() {
  if (model != nullptr && model->type == gf::GF_EVT_MODEL_WEAPON) {
    static_cast<gf::GfEvtModelWeapon *>(model)->setScale(weaponScale);
  }
}

void CharaObj::setDispJiji(bool isDisp) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (isDisp) {
    flags |= FLAG_DISP_JIJI;
  } else {
    flags &= ~FLAG_DISP_JIJI;
  }
  updateDispJiji();
}

void CharaObj::updateDispJiji() {
  if (model != nullptr && model->type == gf::GF_EVT_MODEL_DRIVER) {
    bool isDisp = (flags & FLAG_DISP_JIJI) != 0;
    if (gf::GfObjAcc(model->handle).getBdatId() == 1 && model != nullptr) {
      static_cast<gf::GfEvtModelDriver *>(model)->setDispJiji(isDisp);
    }
  }
}

} // namespace event
