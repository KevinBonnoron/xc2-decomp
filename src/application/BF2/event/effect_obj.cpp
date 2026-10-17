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

EffectEvaPlayer::EffectEvaPlayer() : ctrl(nullptr), rcha(nullptr), frame(0.0f) {}

EffectEvaPlayer::~EffectEvaPlayer() { stop(); }

void EffectEvaPlayer::stop() {
  if (rcha != nullptr) {
    delete rcha;
    rcha = nullptr;
  }
  ctrl = nullptr;
}

void EffectEvaPlayer::play(EffectCtrl *ctrl, void *data) {
  stop();
  this->ctrl = ctrl;
  rcha = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaEff;
  rcha->setup(mtl::ALLOC_HANDLE(), data);
  frame = 0.0f;
}

ICmd::RESULT EffectPlayEff::update(const Param &param) {
  if (ctrl == nullptr) {
    return RESULT_END;
  }
  f32 delta = static_cast<EffectObj *>(param.val(0).getUserdata())->getFrameInfo().delta;
  if (param.getFrame() <= 0) {
    f32 life = param.val(1).getF32();
    f32 speed = param.val(2).getF32();
    f32 skip = param.val(3).getF32();
    int prio = param.val(4).getS32();
    if (!mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
      ctrl->genelate();
      ctrl->setSpeed(speed);
      ctrl->setSkip(skip);
      ctrl->setPrio(prio);
    } else {
      ctrl->setPrio(prio);
    }
    this->life = life;
  }
  life -= delta;
  if (!(life < 0.0f)) {
    return RESULT_NEXT;
  }
  if (!mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
    ctrl->dead();
  } else {
    ctrl->kill();
  }
  return RESULT_END;
}

void EffectPlayEff::term() { life = -1.0f; }

void EffectPlayEff::render(const mm::Vec3 &pos) {
  if (obj == nullptr || ctrl == nullptr) {
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
  fw::debug::drawFont(x - 5, textY, "life(%.1f)", life);
  textX = x - 100;
  textY = y - 5;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, obj->getName());
  textY = y + 10;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "count %d", ctrl->getEffCount());
  textY = y + 25;
  fw::debug::drawFontColor(mm::Col4(0.8f, 0.8f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "pos %.2f %.2f %.2f", ctrl->getPos().x, ctrl->getPos().y, ctrl->getPos().z);
  fw::debug::drawFont(
      textX, y + 40, "rot %.2f %.2f %.2f", ctrl->getRot().x * mm::RAD_TO_DEG, ctrl->getRot().y * mm::RAD_TO_DEG, ctrl->getRot().z * mm::RAD_TO_DEG);
  fw::debug::drawFont(textX, y + 55, "sca %.2f", ctrl->getScale().x);
  fw::debug::drawFont(textX, y + 70, "col %.2f %.2f %.2f %.2f", ctrl->getColor().r, ctrl->getColor().g, ctrl->getColor().b, ctrl->getColor().a);
}

ICmd::RESULT EffectPlayEva::update(const Param &param) {
  if (ctrl != nullptr) {
    f32 delta = static_cast<EffectObj *>(param.val(0).getUserdata())->getFrameInfo().streamDelta;
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
        return RESULT_END;
      }
      evaPlayer.play(ctrl, data);
      life = param.val(2).getF32();
      this->data = data;
    }
    evaPlayer.update(delta);
    life -= delta;
    if (!(life < 0.0f)) {
      return RESULT_NEXT;
    }
  }
  evaPlayer.stop();
  if (mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode() && data != nullptr) {
    mm::mtl::Singleton<MotstmManager>::getPtr()->free(data);
  }
  data = nullptr;
  return RESULT_END;
}

void EffectPlayEva::render(const mm::Vec3 &pos) {
  if (ctrl == nullptr || data == nullptr) {
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
  fw::debug::drawFont(textX, textY, "life(%.1f)", life);
}

void EffectPlayEva::term() {
  if (mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode() && data != nullptr) {
    mm::mtl::Singleton<MotstmManager>::getPtr()->free(data);
  }
  data = nullptr;
}

ICmd::RESULT EffectLinearPos::update(const Param &param) {
  if (ctrl == nullptr) {
    return RESULT_END;
  }
  EffectObj *obj = static_cast<EffectObj *>(param.val(0).getUserdata());
  f32 delta = obj->getFrameInfo().streamDelta;
  if (param.getFrame() == 0) {
    mm::Vec3 pos(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
    anm.clear();
    anm.append(0.0f, obj->getPos(), CV_TYPE_STEP);
    anm.append(param.val(4).getF32(), pos, static_cast<CV_TYPE>(param.val(5).getS32()));
  }
  anm.update(delta);
  ctrl->setPos(anm.getValue());
  if (!anm.isEnd()) {
    return RESULT_NEXT;
  }
  anm.clear();
  return RESULT_END;
}

const mm::Vec3 &EffectObj::getPos() const { return ctrl.getPos(); }

ICmd::RESULT EffectLinearRot::update(const Param &param) {
  if (ctrl == nullptr) {
    return RESULT_END;
  }
  EffectObj *obj = static_cast<EffectObj *>(param.val(0).getUserdata());
  f32 delta = obj->getFrameInfo().streamDelta;
  if (param.getFrame() == 0) {
    mm::Vec3 rot(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
    anm.clear();
    anm.append(0.0f, obj->getRot(), CV_TYPE_STEP);
    anm.append(param.val(4).getF32(), rot, static_cast<CV_TYPE>(param.val(5).getS32()));
  }
  anm.update(delta);
  ctrl->setRot(anm.getValue());
  if (!anm.isEnd()) {
    return RESULT_NEXT;
  }
  anm.clear();
  return RESULT_END;
}

const mm::Vec3 &EffectObj::getRot() const { return ctrl.getRot(); }

ICmd::RESULT EffectLinearCol::update(const Param &param) {
  if (ctrl == nullptr) {
    return RESULT_END;
  }
  EffectObj *obj = static_cast<EffectObj *>(param.val(0).getUserdata());
  f32 delta = obj->getFrameInfo().streamDelta;
  if (param.getFrame() == 0) {
    mm::Col4 color(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32(), param.val(4).getF32());
    anm.clear();
    anm.append(0.0f, obj->getColor(), CV_TYPE_STEP);
    anm.append(param.val(5).getF32(), color, static_cast<CV_TYPE>(param.val(6).getS32()));
  }
  anm.update(delta);
  ctrl->setColor(anm.getValue());
  if (anm.isEnd()) {
    anm.clear();
    return RESULT_END;
  }
  return RESULT_NEXT;
}

const mm::Col4 &EffectObj::getColor() const { return ctrl.getColor(); }

EffectObj::EffectObj(const char *name) : name(name), frameInfo() {}

EffectObj::~EffectObj() {
  ctrl.kill();
  ctrl.destroy();
}

void EffectObj::start() {}

void EffectObj::end() {
  queue.eraseAll();
  ctrl.kill();
}

void EffectObj::update(const FrameInfo &info) {
  frameInfo = info;
  if (info.streamDelta > 0.0f) {
    queue.update();
  }
}

void EffectObj::renderEffect(const mm::Vec3 &pos) { cmdPlayEff.render(pos); }

void EffectObj::renderEva(const mm::Vec3 &pos) { cmdPlayEva.render(pos); }

void EffectObj::tail() { ctrl.update(); }

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
  ctrl.create(file.c_str(), offscrId);
  cmdPlayEff.setup(this, &ctrl);
  cmdLinearPos.setCtrl(&ctrl);
  cmdLinearRot.setCtrl(&ctrl);
  cmdLinearCol.setCtrl(&ctrl);
  cmdPlayEva.setCtrl(&ctrl);
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setF32(life);
  param.val(2).setF32(speed);
  param.val(3).setF32(skip);
  param.val(4).setS32(prio);
  queue.push_back(&cmdPlayEff, param);
}

void EffectObj::stop() {
  queue.erase(&cmdPlayEff);
  if (!mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
    ctrl.dead();
  } else {
    ctrl.kill();
  }
  ctrl.destroy();
}

void EffectObj::dead() { ctrl.dead(); }

void EffectObj::kill() { ctrl.kill(); }

void EffectObj::setPos(const mm::Vec3 &pos) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  ctrl.setPos(pos);
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
  queue.push_back(&cmdLinearPos, param);
}

void EffectObj::setRot(const mm::Vec3 &rot) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  ctrl.setRot(rot);
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
  queue.push_back(&cmdLinearRot, param);
}

void EffectObj::setScale(const mm::Vec3 &scale) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  ctrl.setScale(scale);
}

const mm::Vec3 &EffectObj::getScale() const { return ctrl.getScale(); }

void EffectObj::setColor(const mm::Col4 &color) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  ctrl.setColor(color);
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
  queue.push_back(&cmdLinearCol, param);
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
    queue.push_back(&cmdPlayEva, param);
  }
}

void EffectObj::stopAnim() {
  if (mm::mtl::Singleton<EffectManager>::getPtr()->isStreamMode()) {
    queue.erase(&cmdPlayEva);
  }
}

void EffectObj::setCaster(IAttachActor *caster) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  ctrl.setCaster(caster);
}

void EffectObj::setMount(IAttachActor *mount, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  ctrl.setMount(mount, bone, offset, isRotate, type);
}

size_t EffectObj::getEffCount() const { return ctrl.getEffCount(); }

} // namespace event
