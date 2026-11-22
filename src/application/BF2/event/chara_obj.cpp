#include "event/chara_obj.h"

#include <math.h>

#include "event/alpha_manager.h"
#include "event/alpha_obj.h"
#include "event/attach_actor_base.h"
#include "event/chara_facial_util.h"
#include "event/chara_manager.h"
#include "event/chara_util.h"
#include "event/cmd_param.h"
#include "event/cmd_variable.h"
#include "event/debug_manager.h"
#include "event/group_manager.h"
#include "event/i_attach_actor.h"
#include "event/light_manager.h"
#include "event/mdlstm_manager.h"
#include "event/model_manager.h"
#include "event/model_obj.h"
#include "event/offscr_manager.h"
#include "event/skip_manager.h"
#include "event/tar_axis.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_mtl/singleton.h"

namespace event {

const char *CharaObj::getName() const { return m_name.c_str(); }

// 0x71000bdf6c, 589 instructions (D2; the deleting D0 at 0x71000bec48 is the compiler's). The players are released in the order of the game (the
// dys updater after the ik updater), then the model by state. The game's jump table (0x7100f67dbc) has five entries for the states 2 to 6:
// 2, 3 and 6 share the ModelManager call (0x71000be0b4), but states 4 and 5 each have their own inlined MdlstmManager::dispose (0x71000be524 and
// 0x71000be6c0). A merged `case 4: case 5:` gives one copy (487 instructions instead of 589), so the two cases keep separate, identical bodies.
CharaObj::~CharaObj() {
  if (m_iAttachActor != nullptr) {
    delete m_iAttachActor;
    m_iAttachActor = nullptr;
  }
  m_charaPartUpdater.destroy();
  m_charaEffectPlayer.destroy();
  m_charaWinkPlayer.destroy();
  m_charaWeightPlayer.destroy();
  m_charaLensPlayer.destroy();
  m_charaTarPlayerMot.destroy();
  m_charaTarPlayer.destroy();
  m_charaIKUpdater.destroy();
  m_charaDysUpdater.destroy();
  switch (unknownca4) {
  case STATE_UNKNOWN_2:
  case STATE_UNKNOWN_3:
  case STATE_UNKNOWN_6:
    mm::mtl::Singleton<ModelManager>::getPtr()->destroyModel(m_modelObj, unknown3054);
    break;
  case STATE_UNKNOWN_4:
    mm::mtl::Singleton<MdlstmManager>::getPtr()->dispose(m_modelObj);
    break;
  case STATE_UNKNOWN_5:
    mm::mtl::Singleton<MdlstmManager>::getPtr()->dispose(m_modelObj);
    break;
  }
}

// 0x71000bec6c, 135 instructions: the Euler angles are written straight into the member, one angle per branch, which the out-parameter
// mm::quatToEuler does (the by-value form `m_rot = mm::quatToEuler(...)` costs six more instructions). The game reads the four
// components of the quaternion once from the getRotation() result (0x71000becfc); only a copy of the quaternion gives its register
// assignment (binding the returned reference directly gives s11 where the game has s14 at 0x71000bed00).
void CharaObj::createGfObj(gf::GF_OBJ_HANDLE *handle) {
  unknownd3c = 0;
  m_eyeOffset = 1.5f;
  unknownd40 = handle;
  gf::GfComTransform *transform = gf::GfObjUtil::getObj(handle)->getComponent<gf::GfComTransform>();
  m_pos = transform->getPosition();
  mm::Quat rotation = transform->getRotation();
  mm::quatToEuler(rotation, m_rot);
  unknownca4 = STATE_UNKNOWN_1;
  unknownd48 = nullptr;
}

void CharaObj::createGfObj(CHARA_TYPE type, u32 id, u32 param3, u32 param4) {
  // The game loads CharaManager::unknown10 before the first call (0x71000bef20, ldr w25) and tests
  // the bit later (0x71000bf12c, ubfx): this local places that load (ruling 2, P2).
  bool isUseHood = mm::mtl::Singleton<CharaManager>::getPtr()->isUseHood();
  if (param3 != 0) {
    mm::mtl::Singleton<OffscrManager>::getPtr()->createScreen(param3);
    mm::mtl::Singleton<LightManager>::getPtr()->loadOffScrLight(param3);
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isOffscrMode()) {
    param3 = mm::mtl::Singleton<CharaManager>::getPtr()->getOffscrID();
  }
  unknownd3c = param3;
  unknowncec = type;
  m_eyeOffset = 1.5f;
  unknowncf0 = id;
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
    unknownca4 = STATE_UNKNOWN_5;
    return;
  }
  ModelObj::OPTION option;
  option.unknown05 = isUseHood;
  option.unknown00 = param4;
  switch (type) {
  case CHARA_TYPE_UNKNOWN_1:
    // Second store of the same value, kept on purpose (ruling 5, P3): the game stores the OPTION
    // word before the switch (0x71000bf140, str w21,[sp,#8]) and again at the start of case 1
    // (0x71000bf15c); no other case stores it.
    option.unknown00 = param4;
    m_modelObj = mm::mtl::Singleton<ModelManager>::getPtr()->createModel(MODEL_TYPE_UNKNOWN_1, id, option, false, unknownd3c, unknown3054);
    break;
  case CHARA_TYPE_UNKNOWN_2:
    m_modelObj = mm::mtl::Singleton<ModelManager>::getPtr()->createModel(MODEL_TYPE_UNKNOWN_2, id, option, false, unknownd3c, unknown3054);
    break;
  case CHARA_TYPE_UNKNOWN_3:
    m_modelObj = mm::mtl::Singleton<ModelManager>::getPtr()->createModel(MODEL_TYPE_UNKNOWN_3, id, option, false, unknownd3c, unknown3054);
    break;
  case CHARA_TYPE_UNKNOWN_5:
    m_modelObj = mm::mtl::Singleton<ModelManager>::getPtr()->createModel(MODEL_TYPE_UNKNOWN_4, id, option, false, unknownd3c, unknown3054);
    break;
  }
  unknownca4 = STATE_UNKNOWN_2;
}

void CharaObj::createModel(const char *model, u32 param2, u32 param3) {
  if (param3 != 0) {
    mm::mtl::Singleton<OffscrManager>::getPtr()->createScreen(param3);
    mm::mtl::Singleton<LightManager>::getPtr()->loadOffScrLight(param3);
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isOffscrMode()) {
    param3 = mm::mtl::Singleton<CharaManager>::getPtr()->getOffscrID();
  }
  unknownd3c = param3;
  unknowncf4 = model;
  unknownd38 = param2;
  if (!mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
    m_modelObj = mm::mtl::Singleton<ModelManager>::getPtr()->createModel(model, false, unknownd3c, unknown3054);
    unknownca4 = STATE_UNKNOWN_3;
  } else {
    unknownca4 = STATE_UNKNOWN_4;
  }
}

void CharaObj::createGhost() {
  if (!mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
    m_modelObj = mm::mtl::Singleton<ModelManager>::getPtr()->createModel(unknown3054);
  }
  unknownca4 = STATE_UNKNOWN_6;
}

void CharaObj::clear() {
  unknown1738.eraseAll();
  unknown2088.eraseAll();
  unknown29d8.eraseAll();
}

void CharaObj::start() {
  if (unknownca4 == STATE_UNKNOWN_1) {
    return;
  }
  mm::mtl::Singleton<GroupManager>::getPtr()->push(this);
  if (unknownd40 != gf::unknown020) {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(unknownd40, ALPHA_ATTR_UNKNOWN_1, 1.0f, 1.0f);
  }
  m_charaDysUpdater.resetDynamics(0);
  if (unknownca4 == STATE_UNKNOWN_5 || unknownca4 == STATE_UNKNOWN_2) {
    playWink(0, -1.0f, false, 0.0f, 0.0f, -1, true, true);
  }
}

void CharaObj::end() {
  clear();
  if (unknownca4 != STATE_UNKNOWN_1) {
    if (unknownd40 != gf::unknown020) {
      mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(unknownd40, ALPHA_ATTR_UNKNOWN_1, 0.0f, 1.0f);
    }
    mm::mtl::Singleton<GroupManager>::getPtr()->pop(this);
  }
}

void CharaObj::playWink(int type, f32 frame, bool isLoop, f32 lensX, f32 lensY, int lensType, bool isDirect, bool isAuto) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown2088.erase(&m_charaPlayWink);
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
  unknown2088.push_back(&m_charaPlayWink, param);
}

const mm::Vec3 &CharaObj::getPos() const { return m_pos; }

// The routine at 0x71000c19cc reads GfObjSetup::unknown0c (the layer copied from
// GfInitParam::unknown40); values 10 through 12 skip pause.
bool CharaObj::isCharaObjPause(const FrameInfo &info) const {
  gf::GfObjSetup *setup = gf::GfObjUtil::getObjSetup(unknownd40);
  if (setup != nullptr) {
    u32 unknown0c = setup->unknown0c;
    if (unknown0c - 10 < 3)
      return false;
  }
  if (info.unknown0c <= 0.0f) {
    if (info.unknown04 <= 0.0f)
      return true;
  }
  return false;
}

void CharaObj::renderAction() {
  m_charaPlayAction.render(m_pos, m_eyeOffset);
  m_charaPlayActionAuto.render(m_pos, m_eyeOffset);
}

f32 CharaObj::getEyeOffset() const { return m_eyeOffset; }

void CharaObj::renderHead() { m_charaPlayHead.render(m_pos, m_eyeOffset); }

void CharaObj::renderMotion() {
  m_charaPlayMotion.render(m_pos, m_eyeOffset);
  m_charaPlayMotionABC.render(m_pos, m_eyeOffset);
}

void CharaObj::renderFacial() { m_charaPlayFacial.render(m_pos, m_eyeOffset); }

void CharaObj::renderTalk() { m_charaPlayTalk.render(m_pos, m_eyeOffset); }

void CharaObj::renderWink() { m_charaPlayWink.render(m_pos, m_eyeOffset); }

void CharaObj::renderLens() { m_charaLensPlayer.render(m_pos, m_eyeOffset); }

void CharaObj::renderWeight() { m_charaWeightPlayer.render(m_pos, m_eyeOffset); }

void CharaObj::renderIK() { m_charaIKUpdater.render(m_pos, m_eyeOffset); }

// The original flag names are unknown. The routine at 0x71000c1da8 tests
// bits 0 and 1 at +0xca0, then calls AttachActorBase::render for each set bit.
void CharaObj::renderBone() {
  if (m_iAttachActor != nullptr) {
    if ((unknownca0 & 1) != 0) {
      static_cast<AttachActorBase *>(m_iAttachActor)->render();
    }
    if ((unknownca0 & 2) != 0) {
      static_cast<AttachActorBase *>(m_iAttachActor)->render();
    }
  }
}

void CharaObj::setPos(const mm::Vec3 &pos) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  this->m_pos = pos;
  unknown29d8.erase(&m_charaSetPos);
  CmdParam param;
  param.val(0).setF32(pos.x);
  param.val(1).setF32(pos.y);
  param.val(2).setF32(pos.z);
  unknown29d8.push_back(&m_charaSetPos, param);
}

// The game (0x71000c41a8, 180 instructions) also calls atan2f in the cv == 0 arm (bl at 0x71000c42ec) and
// drops the result: the angle is assigned in both arms and tested after them, which clang threads (the
// call stays, atan2f may set errno). It loads pos.z before pos.x there (0x71000c42d4, ldr s1,[x23,#8]!);
// the local places that load (ruling 2, P2). Without it both arms start with the same loads and
// SimplifyCFG hoists them above the cv test (177 instructions). The distance test is `!(d > 0.1f)`
// (b.le at 0x71000c4294 also leaves for NaN) and the differences are written again after sqrtf as in
// the game, which reloads the members there.
void CharaObj::walkPos(const mm::Vec3 &pos, EVT_poscvtype cv, bool isRun) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  f32 angle;
  if (cv == 0) {
    f32 z = pos.z;
    angle = atan2f(pos.x - m_pos.x, z - m_pos.z);
    m_pos = pos;
  } else {
    if (!(sqrtf((pos.x - m_pos.x) * (pos.x - m_pos.x) + (pos.z - m_pos.z) * (pos.z - m_pos.z)) > 0.1f)) {
      return;
    }
    angle = atan2f(pos.x - m_pos.x, pos.z - m_pos.z);
  }
  if (cv >= 1 && cv <= 8) {
    m_rot.x = 0.0f;
    m_rot.y = angle;
    m_rot.z = 0.0f;
  }
  unknown2fc0 = pos;
  CmdParam param;
  param.val(0).setUserdata(this);
  param.unknown001(1, pos);
  param.val(4).setS32(cv);
  param.val(5).setBool(isRun);
  CmdQueue<QUEUE_UNKNOWN_8, 0> *target = &unknown1738;
  if (cv == 0) {
    if (unknown1738.isExist(&m_charaWalkPos)) {
      unknown1738.erase(&m_charaWalkPos);
    }
    target = &unknown2088;
  }
  target->push_back(&m_charaWalkPos, param);
  m_charaPlayEva.setPos(pos);
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
    this->m_pos = to;
    unknown2fc0 = to;
    unknown2088.erase(&m_charaLinerPos);
  } else {
    unknown2fc0 = to;
  }
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(to.x);
  param.val(2).setF32(to.y);
  param.val(3).setF32(to.z);
  param.val(4).setF32(frame);
  param.val(5).setS32(cv);
  unknown2088.push_back(&m_charaLinerPos, param);
  m_charaPlayEva.setPos(pos);
}

const mm::Vec3 &CharaObj::getPosTo() const {
  if (unknown1738.isExist(&m_charaWalkPos) || unknown2088.isExist(&m_charaWalkPos) || unknown2088.isExist(&m_charaLinerPos)) {
    return unknown2fc0;
  }
  return m_pos;
}

void CharaObj::setRot(const mm::Vec3 &rot) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  this->m_rot = rot;
  unknown29d8.erase(&m_charaSetRot);
  CmdParam param;
  param.val(0).setF32(rot.x);
  param.val(1).setF32(rot.y);
  param.val(2).setF32(rot.z);
  unknown29d8.push_back(&m_charaSetRot, param);
}

void CharaObj::turnRot(const mm::Vec3 &rot, EVT_rotcvtype cv, f32 frame) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  this->m_rot = rot;
  unknown2fe0 = rot;
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(rot.x);
  param.val(2).setF32(rot.y);
  param.val(3).setF32(rot.z);
  param.val(4).setS32(cv);
  param.val(5).setF32(frame);
  CmdQueue<QUEUE_UNKNOWN_8, 0> *target = &unknown1738;
  if (cv == 0) {
    if (unknown1738.isExist(&m_charaTurnRot)) {
      unknown1738.erase(&m_charaTurnRot);
    }
    target = &unknown2088;
  }
  target->push_back(&m_charaTurnRot, param);
}

void CharaObj::linerRot(const mm::Vec3 &rot, f32 frame, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (frame == 0.0f) {
    this->m_rot = rot;
    unknown2fe0 = rot;
    unknown2088.erase(&m_charaLinerRot);
  } else {
    unknown2fe0 = rot;
  }
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(rot.x);
  param.val(2).setF32(rot.y);
  param.val(3).setF32(rot.z);
  param.val(4).setF32(frame);
  param.val(5).setS32(cv);
  unknown2088.push_back(&m_charaLinerRot, param);
}

const mm::Vec3 &CharaObj::getRot() const { return m_rot; }

const mm::Vec3 &CharaObj::getRotTo() const {
  if (unknown1738.isExist(&m_charaTurnRot) || unknown2088.isExist(&m_charaTurnRot) || unknown2088.isExist(&m_charaLinerRot)) {
    return unknown2fe0;
  }
  return m_rot;
}

bool CharaObj::isTurnable() const { return !unknown29d8.isExist(&m_charaSetRot); }

void CharaObj::setTar(const TarAxis &axis, f32 frame, EVT_tarcvtype cv, EVT_aimtype aim, f32 weight, f32 speed) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isSystemTicket960() && CharaFacialUtil::checkBdatID(unknownd40, 2) && unknown1738.isExist(&m_charaPlayAction) &&
      (m_charaPlayAction.getType() == 6 || m_charaPlayAction.getType() == 11)) {
    return;
  }
  unknown29d8.erase(&m_charaSetTar);
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
  unknown29d8.push_back(&m_charaSetTar, param);
}

void CharaObj::resetTar() { unknown29d8.erase(&m_charaSetTar); }

const mm::Vec3 &CharaObj::getTar() const { return m_charaSetTar.getTar(); }

bool CharaObj::isTar() const { return unknown29d8.isExist(&m_charaSetTar); }

void CharaObj::setLensTarget(const mm::Vec2 &target) { m_charaLensPlayer.setManualTarget(true, target, true); }

const mm::Vec2 &CharaObj::getLensTarget() const { return m_charaLensPlayer.getTarget(); }

void CharaObj::setIdle(int type) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown1738.erase(&m_charaSetIdle);
  unknown1738.erase(&m_charaPlayActionAuto);
  unknown1738.erase(&m_charaPlayAction);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setS32(type);
  unknown1738.push_back(&m_charaSetIdle, param);
}

int CharaObj::getIdle() const {
  if (unknown1738.isExist(&m_charaSetIdle)) {
    return m_charaSetIdle.getType();
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
  unknown1738.erase(&m_charaSetIdle);
  unknown1738.erase(&m_charaPlayActionAuto);
  unknown1738.erase(&m_charaPlayAction);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(frame);
  unknown1738.push_back(&m_charaPlayActionAuto, param);
}

void CharaObj::playAction(int type, f32 frame, bool isLoop, bool isBlend) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isSeamlessAction() && unknown1738.isExist(&m_charaPlayAction) && m_charaPlayAction.getType() == type) {
    m_charaPlayAction.keep();
    mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("action seamless");
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isSystemTicket960() && CharaFacialUtil::checkBdatID(unknownd40, 2) && (type == 11 || type == 6)) {
    resetTar();
  }
  unknown1738.erase(&m_charaSetIdle);
  unknown1738.erase(&m_charaPlayActionAuto);
  unknown1738.erase(&m_charaPlayAction);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setS32(type);
  param.val(2).setF32(frame);
  param.val(3).setBool(isLoop);
  param.val(4).setBool(isBlend);
  unknown1738.push_back(&m_charaPlayAction, param);
}

void CharaObj::stopAction() {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (unknown1738.isExist(&m_charaPlayAction)) {
    unknown1738.erase(&m_charaPlayAction);
    unknown1738.push_back(&m_charaStopAction, CmdParam());
  }
}

int CharaObj::getAction() const {
  if (unknown1738.isExist(&m_charaPlayAction)) {
    return m_charaPlayAction.getType();
  }
  return 0;
}

f32 CharaObj::getActionLastFrame() const {
  if (unknown1738.isExist(&m_charaPlayAction)) {
    return m_charaPlayAction.getLastFrame();
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
  if ((unknownca4 & ~1) == 4) {
    initModelStream();
    unknownca0 |= FLAG_UNKNOWN_6;
    unknown3044 = frame;
  }
  unknown2088.erase(&m_charaPlayMotion);
  unknown2088.erase(&m_charaPlayMotionABC);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setStr(name);
  param.val(2).setF32(frame);
  param.val(3).setF32(blend);
  param.val(4).setF32(speed);
  unknown2088.push_back(&m_charaPlayMotion, param);
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
    unknown2088.erase(&m_charaPlayEva);
    unknown2088.erase(&m_charaPlayEvaEff);
    unknown2088.erase(&m_charaHideWpn);
    param.val(0).setUserdata(this);
    param.val(1).setStr(name);
    param.val(2).setF32(frame);
    param.val(3).setF32(blend);
    unknown2088.push_back(&m_charaPlayEva, param);
    param.val(0).setUserdata(this);
    param.val(1).setStr(name);
    param.val(2).setF32(frame);
    param.val(3).setF32(blend);
    unknown2088.push_back(&m_charaPlayEvaEff, param);
    param.val(0).setUserdata(this);
    param.val(1).setF32(frame);
    unknown2088.push_back(&m_charaHideWpn, param);
  }
}

void CharaObj::playMotionABC(const char *nameA, const char *nameB, const char *nameC, f32 frameA, f32 frameB, f32 frameC, f32 blendA, f32 blendB, f32 blendC) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown2088.erase(&m_charaPlayMotion);
  unknown2088.erase(&m_charaPlayMotionABC);
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
  unknown2088.push_back(&m_charaPlayMotionABC, param);
}

void CharaObj::playHead(int type, f32 life, bool isBlendIn, bool isBlendOut) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown2088.erase(&m_charaPlayHead);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setS32(type);
  param.val(2).setF32(life);
  param.val(3).setBool(isBlendIn);
  param.val(4).setBool(isBlendOut);
  unknown2088.push_back(&m_charaPlayHead, param);
}

void CharaObj::stopHead() {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (unknown2088.isExist(&m_charaPlayHead)) {
    unknown2088.erase(&m_charaPlayHead);
    unknown2088.push_back(&m_charaStopHead, CmdParam());
  }
}

int CharaObj::getHead() const {
  if (unknown2088.isExist(&m_charaPlayHead)) {
    return m_charaPlayHead.getType();
  }
  return 0;
}

void CharaObj::playFacial(int type, f32 life, int browType, f32 browWeight, int eyeType, f32 eyeWeight, int lipType, f32 lipWeight, f32 blendIn, f32 blendOut) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown2088.erase(&m_charaPlayFacial);
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
  unknown2088.push_back(&m_charaPlayFacial, param);
}

int CharaObj::getFacial() const {
  if (unknown2088.isExist(&m_charaPlayFacial)) {
    return m_charaPlayFacial.getType();
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
  unknown2088.erase(&m_charaPlayTalkAuto);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(frame);
  unknown2088.push_back(&m_charaPlayTalkAuto, param);
}

void CharaObj::playTalk(bool isManual, f32 frame, bool isBlend, bool isAuto, f32 openMin, f32 openMax, f32 closeMin, f32 closeMax) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (!isManual && unknown2088.isExist(&m_charaPlayTalk) && m_charaPlayTalk.isManual()) {
    return;
  }
  unknown2088.erase(&m_charaPlayTalk);
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
  unknown2088.push_back(&m_charaPlayTalk, param);
}

void CharaObj::mount(CharaObj *target, const char *bone, const mm::Vec3 &pos, const mm::Vec3 &rot) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown2088.erase(&m_charaMount);
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
    unknown2088.push_back(&m_charaMount, param);
    unknownca0 &= ~FLAG_UNKNOWN_4;
  } else {
    CmdParam param;
    param.val(0).setUserdata(target->unknownd48);
    param.val(1).setStr(bone);
    param.val(2).setF32(pos.x);
    param.val(3).setF32(pos.y);
    param.val(4).setF32(pos.z);
    param.val(5).setF32(rot.x);
    param.val(6).setF32(rot.y);
    param.val(7).setF32(rot.z);
    unknown2088.push_back(&m_charaMount, param);
    unknownca0 |= FLAG_UNKNOWN_4;
  }
}

void CharaObj::resetDynamics(int frame) { m_charaDysUpdater.resetDynamics(frame); }

void CharaObj::playFade(bool isOut, f32 frame) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown2088.erase(&m_charaFade);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setBool(isOut);
  param.val(2).setF32(frame);
  unknown2088.push_back(&m_charaFade, param);
  if (isOut) {
    unknownca0 |= FLAG_UNKNOWN_5;
  } else {
    unknownca0 &= ~FLAG_UNKNOWN_5;
  }
}

bool CharaObj::isFadeOut() const { return (unknownca0 & FLAG_UNKNOWN_5) != 0; }

void CharaObj::playVolumeFade(CharaEffectPlayer::VF_TYPE type, int id, const mm::Vec3 &position, const mm::Vec3 &scale, f32 frame, f32 rate, int mode, f32 speed) {
  m_charaEffectPlayer.playVolumeFade(type, id, position, scale, frame, rate, mode, speed);
}

void CharaObj::playVolumeFadeAnim(CharaEffectPlayer::VF_TYPE type, f32 rate, f32 frame) { m_charaEffectPlayer.playVolumeFadeAnim(type, rate, frame); }

void CharaObj::stopVolumeFade(CharaEffectPlayer::VF_TYPE type) { m_charaEffectPlayer.stopVolumeFade(type); }

void CharaObj::playRimBloom(int id) { m_charaEffectPlayer.playRimBloom(id); }

void CharaObj::stopRimBloom() { m_charaEffectPlayer.stopRimBloom(); }

void CharaObj::setExtDisp(const char *name, bool isDisp) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  m_charaPartUpdater.setExtDisp(name, isDisp);
}

void CharaObj::setExtDispWeapon(const char *name, bool isDisp) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  m_charaPartUpdater.setExtDispWeapon(name, isDisp);
}

void CharaObj::setExtParam(const char *name, f32 value) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  m_charaPartUpdater.setExtParam(name, value);
}

void CharaObj::setScaleWeapon(f32 scale) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown3048 = scale;
  updateScaleWeapon();
}

void CharaObj::updateScaleWeapon() {
  if (unknownd48 != nullptr && unknownd48->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_2) {
    static_cast<gf::GfEvtModelWeapon *>(unknownd48)->setScale(unknown3048);
  }
}

void CharaObj::setDispJiji(bool isDisp) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (isDisp) {
    unknownca0 |= FLAG_UNKNOWN_7;
  } else {
    unknownca0 &= ~FLAG_UNKNOWN_7;
  }
  updateDispJiji();
}

void CharaObj::updateDispJiji() {
  if (unknownd48 != nullptr && unknownd48->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_0) {
    bool isDisp = (unknownca0 & FLAG_UNKNOWN_7) != 0;
    if (gf::GfObjAcc(unknownd48->m_GF_OBJ_HANDLE).getBdatId() == 1 && unknownd48 != nullptr) {
      static_cast<gf::GfEvtModelDriver *>(unknownd48)->setDispJiji(isDisp);
    }
  }
}

template void CmdQueue<CharaObj::SUB_QUEUE_UNKNOWN_5, 0>::update();
template CmdQueue<CharaObj::SUB_QUEUE_UNKNOWN_5, 0>::~CmdQueue();

} // namespace event
