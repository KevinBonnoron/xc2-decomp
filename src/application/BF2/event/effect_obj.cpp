#include "event/effect_obj.h"

#include "event/cmd_param.h"
#include "event/cmd_variable.h"
#include "event/effect_manager.h"
#include "event/extend.h"
#include "event/manager.h"
#include "event/memory_manager.h"
#include "event/motstm_manager.h"
#include "event/offscr_manager.h"
#include "event/res_manager.h"
#include "event/skip_manager.h"
#include "fw/fw_debug.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_eff.h"

namespace event {

EffectEvaPlayer::EffectEvaPlayer() : m_effectCtrl(nullptr), m_rchaEff(nullptr), unknown18(0.0f) {}

EffectEvaPlayer::~EffectEvaPlayer() { stop(); }

void EffectEvaPlayer::stop() {
  if (m_rchaEff != nullptr) {
    delete m_rchaEff;
    m_rchaEff = nullptr;
  }
  m_effectCtrl = nullptr;
}

void EffectEvaPlayer::play(EffectCtrl *ctrl, void *data) {
  stop();
  this->m_effectCtrl = ctrl;
  m_rchaEff = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaEff;
  m_rchaEff->setup(mtl::ALLOC_HANDLE(), data);
  unknown18 = 0.0f;
}

ICmd::RESULT EffectPlayEff::update(const Param &param) {
  if (m_effectCtrl == nullptr) {
    return RESULT_UNKNOWN_1;
  }
  f32 delta = static_cast<EffectObj *>(param.val(0).getUserdata())->getFrameInfo().unknown04;
  if (param.getFrame() <= 0) {
    f32 life = param.val(1).getF32();
    f32 speed = param.val(2).getF32();
    f32 skip = param.val(3).getF32();
    int prio = param.val(4).getS32();
    if (!mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
      m_effectCtrl->genelate();
      m_effectCtrl->setSpeed(speed);
      m_effectCtrl->setSkip(skip);
      m_effectCtrl->setPrio(prio);
    } else {
      m_effectCtrl->setPrio(prio);
    }
    this->unknown18 = life;
  }
  unknown18 -= delta;
  if (!(unknown18 < 0.0f)) {
    return RESULT_UNKNOWN_2;
  }
  if (!mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
    m_effectCtrl->dead();
  } else {
    m_effectCtrl->kill();
  }
  return RESULT_UNKNOWN_1;
}

void EffectPlayEff::term() { unknown18 = -1.0f; }

void EffectPlayEff::render(const mm::Vec3 &pos) {
  if (m_effectObj == nullptr || m_effectCtrl == nullptr) {
    return;
  }
  ml::ScnObjCam *cam = Manager::get()->getScn()->getCam(-1);
  mm::Vec3 screen;
  if (!ml::ScnCamUtil::getScreenPos(screen, cam, pos)) {
    return;
  }
  s32 x = screen.x;
  s32 y = screen.y;
  fw::debug::drawSquare2D(mm::Rect<s32>(x - 110, y - 25, 220, 115), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 110, y - 25, 220, 115), mm::Col4(0.8f, 1.0f, 0.8f, 1.0f));
  s32 textX = x - 105;
  s32 textY = y - 20;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "EFF");
  fw::debug::drawFont(x - 5, textY, "life(%.1f)", unknown18);
  textX = x - 100;
  textY = y - 5;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, m_effectObj->getName());
  textY = y + 10;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "count %d", m_effectCtrl->getEffCount());
  textY = y + 25;
  fw::debug::drawFontColor(mm::Col4(0.8f, 0.8f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "pos %.2f %.2f %.2f", m_effectCtrl->getPos().x, m_effectCtrl->getPos().y, m_effectCtrl->getPos().z);
  fw::debug::drawFont(textX, y + 40, "rot %.2f %.2f %.2f", m_effectCtrl->getRot().x * mm::RAD_TO_DEG, m_effectCtrl->getRot().y * mm::RAD_TO_DEG, m_effectCtrl->getRot().z * mm::RAD_TO_DEG);
  fw::debug::drawFont(textX, y + 55, "sca %.2f", m_effectCtrl->getScale().x);
  fw::debug::drawFont(textX, y + 70, "col %.2f %.2f %.2f %.2f", m_effectCtrl->getColor().r, m_effectCtrl->getColor().g, m_effectCtrl->getColor().b, m_effectCtrl->getColor().a);
}

ICmd::RESULT EffectPlayEva::update(const Param &param) {
  if (m_effectCtrl != nullptr) {
    f32 delta = static_cast<EffectObj *>(param.val(0).getUserdata())->getFrameInfo().unknown0c;
    if (param.getFrame() <= 0) {
      const char *name = param.val(1).getStr();
      void *data;
      size_t size;
      if (!mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
        data = mm::mtl::Singleton<ResManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->eva(name), &size);
      } else {
        data = mm::mtl::Singleton<MotstmManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->eva(name), &size);
      }
      if (data == nullptr) {
        return RESULT_UNKNOWN_1;
      }
      m_effectEvaPlayer.play(m_effectCtrl, data);
      unknown18 = param.val(2).getF32();
      this->unknown10 = data;
    }
    m_effectEvaPlayer.update(delta);
    unknown18 -= delta;
    if (!(unknown18 < 0.0f)) {
      return RESULT_UNKNOWN_2;
    }
  }
  m_effectEvaPlayer.stop();
  if (mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode() && unknown10 != nullptr) {
    mm::mtl::Singleton<MotstmManager>::getPtr()->free(unknown10);
  }
  unknown10 = nullptr;
  return RESULT_UNKNOWN_1;
}

void EffectPlayEva::render(const mm::Vec3 &pos) {
  if (m_effectCtrl == nullptr || unknown10 == nullptr) {
    return;
  }
  ml::ScnObjCam *cam = Manager::get()->getScn()->getCam(-1);
  mm::Vec3 screen;
  if (!ml::ScnCamUtil::getScreenPos(screen, cam, pos)) {
    return;
  }
  s32 x = screen.x;
  s32 y = screen.y;
  fw::debug::drawSquare2D(mm::Rect<s32>(x + 115, y - 25, 110, 40), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x + 115, y - 25, 110, 40), mm::Col4(0.8f, 1.0f, 0.8f, 1.0f));
  s32 textX = x + 120;
  s32 textY = y - 20;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "EVA");
  textX = x + 125;
  textY = y - 5;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "life(%.1f)", unknown18);
}

void EffectPlayEva::term() {
  if (mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode() && unknown10 != nullptr) {
    mm::mtl::Singleton<MotstmManager>::getPtr()->free(unknown10);
  }
  unknown10 = nullptr;
}

ICmd::RESULT EffectLinearPos::update(const Param &param) {
  if (m_effectCtrl == nullptr) {
    return RESULT_UNKNOWN_1;
  }
  EffectObj *obj = static_cast<EffectObj *>(param.val(0).getUserdata());
  f32 delta = obj->getFrameInfo().unknown0c;
  if (param.getFrame() == 0) {
    mm::Vec3 pos(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
    m_anmVec.clear();
    m_anmVec.append(0.0f, obj->getPos(), CV_TYPE_UNKNOWN_0);
    m_anmVec.append(param.val(4).getF32(), pos, static_cast<CV_TYPE>(param.val(5).getS32()));
  }
  m_anmVec.update(delta);
  m_effectCtrl->setPos(m_anmVec.getValue());
  if (!m_anmVec.isEnd()) {
    return RESULT_UNKNOWN_2;
  }
  m_anmVec.clear();
  return RESULT_UNKNOWN_1;
}

const mm::Vec3 &EffectObj::getPos() const { return m_effectCtrl.getPos(); }

ICmd::RESULT EffectLinearRot::update(const Param &param) {
  if (m_effectCtrl == nullptr) {
    return RESULT_UNKNOWN_1;
  }
  EffectObj *obj = static_cast<EffectObj *>(param.val(0).getUserdata());
  f32 delta = obj->getFrameInfo().unknown0c;
  if (param.getFrame() == 0) {
    mm::Vec3 rot(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
    m_anmVec.clear();
    m_anmVec.append(0.0f, obj->getRot(), CV_TYPE_UNKNOWN_0);
    m_anmVec.append(param.val(4).getF32(), rot, static_cast<CV_TYPE>(param.val(5).getS32()));
  }
  m_anmVec.update(delta);
  m_effectCtrl->setRot(m_anmVec.getValue());
  if (!m_anmVec.isEnd()) {
    return RESULT_UNKNOWN_2;
  }
  m_anmVec.clear();
  return RESULT_UNKNOWN_1;
}

const mm::Vec3 &EffectObj::getRot() const { return m_effectCtrl.getRot(); }

ICmd::RESULT EffectLinearCol::update(const Param &param) {
  if (m_effectCtrl == nullptr) {
    return RESULT_UNKNOWN_1;
  }
  EffectObj *obj = static_cast<EffectObj *>(param.val(0).getUserdata());
  f32 delta = obj->getFrameInfo().unknown0c;
  if (param.getFrame() == 0) {
    mm::Col4 color(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32(), param.val(4).getF32());
    m_anmCol.clear();
    m_anmCol.append(0.0f, obj->getColor(), CV_TYPE_UNKNOWN_0);
    m_anmCol.append(param.val(5).getF32(), color, static_cast<CV_TYPE>(param.val(6).getS32()));
  }
  m_anmCol.update(delta);
  m_effectCtrl->setColor(m_anmCol.getValue());
  if (m_anmCol.isEnd()) {
    m_anmCol.clear();
    return RESULT_UNKNOWN_1;
  }
  return RESULT_UNKNOWN_2;
}

const mm::Col4 &EffectObj::getColor() const { return m_effectCtrl.getColor(); }

EffectObj::EffectObj(const char *name) : unknown08(name), m_frameInfo() {}

EffectObj::~EffectObj() {
  m_effectCtrl.kill();
  m_effectCtrl.destroy();
}

void EffectObj::start() {}

void EffectObj::end() {
  unknown260.eraseAll();
  m_effectCtrl.kill();
}

void EffectObj::update(const FrameInfo &info) {
  m_frameInfo = info;
  if (info.unknown0c > 0.0f) {
    unknown260.update();
  }
}

void EffectObj::renderEffect(const mm::Vec3 &pos) { m_effectPlayEff.render(pos); }

void EffectObj::renderEva(const mm::Vec3 &pos) { m_effectPlayEva.render(pos); }

void EffectObj::tail() { m_effectCtrl.update(); }

void EffectObj::play(const char *name, f32 life, f32 speed, f32 skip, int prio, int offscrId) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mm::mtl::FixStr<128> file(name);
  if (offscrId > 0) {
    mm::mtl::Singleton<OffscrManager>::getPtr()->createScreen(offscrId);
  }
  if (mm::mtl::Singleton<EffectManager>::getPtr()->isOffscrMode()) {
    offscrId = mm::mtl::Singleton<EffectManager>::getPtr()->getOffscrID();
  }
  if (mm::mtl::Singleton<EffectManager>::getPtr()->isReplaceMode()) {
    mm::mtl::Singleton<EffectManager>::getPtr()->replaceFile(file);
  }
  stop();
  m_effectCtrl.create(file.c_str(), offscrId);
  m_effectPlayEff.setup(this, &m_effectCtrl);
  m_effectLinearPos.setCtrl(&m_effectCtrl);
  m_effectLinearRot.setCtrl(&m_effectCtrl);
  m_effectLinearCol.setCtrl(&m_effectCtrl);
  m_effectPlayEva.setCtrl(&m_effectCtrl);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(life);
  param.val(2).setF32(speed);
  param.val(3).setF32(skip);
  param.val(4).setS32(prio);
  unknown260.push_back(&m_effectPlayEff, param);
}

void EffectObj::stop() {
  unknown260.erase(&m_effectPlayEff);
  if (!mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
    m_effectCtrl.dead();
  } else {
    m_effectCtrl.kill();
  }
  m_effectCtrl.destroy();
}

void EffectObj::dead() { m_effectCtrl.dead(); }

void EffectObj::kill() { m_effectCtrl.kill(); }

void EffectObj::setPos(const mm::Vec3 &pos) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  m_effectCtrl.setPos(pos);
}

void EffectObj::moveTo(const mm::Vec3 &pos, f32 frame, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(pos.x);
  param.val(2).setF32(pos.y);
  param.val(3).setF32(pos.z);
  param.val(4).setF32(frame);
  param.val(5).setS32(cv);
  unknown260.push_back(&m_effectLinearPos, param);
}

void EffectObj::setRot(const mm::Vec3 &rot) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  m_effectCtrl.setRot(rot);
}

void EffectObj::turnTo(const mm::Vec3 &rot, f32 frame, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(rot.x);
  param.val(2).setF32(rot.y);
  param.val(3).setF32(rot.z);
  param.val(4).setF32(frame);
  param.val(5).setS32(cv);
  unknown260.push_back(&m_effectLinearRot, param);
}

void EffectObj::setScale(const mm::Vec3 &scale) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  m_effectCtrl.setScale(scale);
}

const mm::Vec3 &EffectObj::getScale() const { return m_effectCtrl.getScale(); }

void EffectObj::setColor(const mm::Col4 &color) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  m_effectCtrl.setColor(color);
}

void EffectObj::colorTo(const mm::Col4 &color, f32 frame, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(color.r);
  param.val(2).setF32(color.g);
  param.val(3).setF32(color.b);
  param.val(4).setF32(color.a);
  param.val(5).setF32(frame);
  param.val(6).setS32(cv);
  unknown260.push_back(&m_effectLinearCol, param);
}

void EffectObj::playAnim(const char *name, f32 frame) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  stopAnim();
  if (mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setStr(name);
    param.val(2).setF32(frame);
    unknown260.push_back(&m_effectPlayEva, param);
  }
}

void EffectObj::stopAnim() {
  if (mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
    unknown260.erase(&m_effectPlayEva);
  }
}

void EffectObj::setCaster(IAttachActor *caster) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  m_effectCtrl.setCaster(caster);
}

void EffectObj::setMount(IAttachActor *mount, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  m_effectCtrl.setMount(mount, bone, offset, isRotate, type);
}

size_t EffectObj::getEffCount() const { return m_effectCtrl.getEffCount(); }

} // namespace event
