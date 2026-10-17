#pragma once
#include <stddef.h>

#include "event/anm_col.h"
#include "event/anm_vec.h"
#include "event/cmd_queue.h"
#include "event/curve.h"
#include "event/effect_ctrl.h"
#include "event/frame_manager.h"
#include "event/i_cmd.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

class RchaEff;
namespace mm {
struct Col4;
struct Vec3;
} // namespace mm

namespace event {

class EffectObj;
class IAttachActor;
enum ATTACH_TYPE : int;

class EffectEvaPlayer {
public:
  EffectEvaPlayer();
  virtual ~EffectEvaPlayer();
  void stop();
  void update(f32 delta);
  void play(EffectCtrl *ctrl, void *data);

private:
  EffectCtrl *ctrl;
  RchaEff *rcha;
  f32 frame;
};

static_assert(sizeof(EffectEvaPlayer) == 0x20, "");

class EffectPlayEff : public ICmd {
public:
  EffectPlayEff() : obj(nullptr), ctrl(nullptr) {}
  virtual RESULT update(const Param &param);
  virtual void term();
  void render(const mm::Vec3 &pos);

  void setup(EffectObj *obj, EffectCtrl *ctrl) {
    this->ctrl = ctrl;
    this->obj = obj;
  }

private:
  EffectObj *obj;
  EffectCtrl *ctrl;
  f32 life;
};

static_assert(sizeof(EffectPlayEff) == 0x20, "");

class EffectPlayEva : public ICmd {
public:
  EffectPlayEva() : ctrl(nullptr), data(nullptr) {}
  virtual RESULT update(const Param &param);
  void render(const mm::Vec3 &pos);
  virtual void term();

  void setCtrl(EffectCtrl *ctrl) { this->ctrl = ctrl; }

private:
  EffectCtrl *ctrl;
  void *data;
  f32 life;
  EffectEvaPlayer evaPlayer;
};

static_assert(sizeof(EffectPlayEva) == 0x40, "");

class EffectLinearPos : public ICmd {
public:
  EffectLinearPos() : ctrl(nullptr) {}
  virtual RESULT update(const Param &param);

  void setCtrl(EffectCtrl *ctrl) { this->ctrl = ctrl; }

private:
  EffectCtrl *ctrl;
  AnmVec anm;
};

static_assert(sizeof(EffectLinearPos) == 0x200, "");

class EffectLinearRot : public ICmd {
public:
  EffectLinearRot() : ctrl(nullptr) {}
  virtual RESULT update(const Param &param);

  void setCtrl(EffectCtrl *ctrl) { this->ctrl = ctrl; }

private:
  EffectCtrl *ctrl;
  AnmVec anm;
};

static_assert(sizeof(EffectLinearRot) == 0x200, "");

class EffectLinearCol : public ICmd {
public:
  EffectLinearCol() : ctrl(nullptr) {}
  virtual RESULT update(const Param &param);

  void setCtrl(EffectCtrl *ctrl) { this->ctrl = ctrl; }

private:
  EffectCtrl *ctrl;
  AnmCol anm;
};

static_assert(sizeof(EffectLinearCol) == 0x1e8, "");

class EffectObj {
public:
  static constexpr size_t QUEUE_COUNT = 6;

  const mm::Vec3 &getPos() const;
  const mm::Vec3 &getRot() const;
  const mm::Col4 &getColor() const;
  EffectObj(const char *name);
  virtual ~EffectObj();
  void start();
  void end();
  void update(const FrameInfo &info);
  void renderEffect(const mm::Vec3 &pos);
  void renderEva(const mm::Vec3 &pos);
  void tail();
  void play(const char *name, f32 life, f32 speed, f32 skip, int prio, int offscrId);
  void stop();
  void dead();
  void kill();
  void setPos(const mm::Vec3 &pos);
  void moveTo(const mm::Vec3 &pos, f32 frame, CV_TYPE cv);
  void setRot(const mm::Vec3 &rot);
  void turnTo(const mm::Vec3 &rot, f32 frame, CV_TYPE cv);
  void setScale(const mm::Vec3 &scale);
  const mm::Vec3 &getScale() const;
  void setColor(const mm::Col4 &color);
  void colorTo(const mm::Col4 &color, f32 frame, CV_TYPE cv);
  void playAnim(const char *name, f32 frame);
  void stopAnim();
  void setCaster(IAttachActor *caster);
  void setMount(IAttachActor *mount, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type);
  size_t getEffCount() const;

  const char *getName() const { return name.c_str(); }
  const FrameInfo &getFrameInfo() const { return frameInfo; }

private:
  mm::mtl::FixStr<64> name;
  EffectCtrl ctrl;
  CmdQueue<QUEUE_COUNT, 0> queue;
  EffectPlayEff cmdPlayEff;
  EffectPlayEva cmdPlayEva;
  EffectLinearPos cmdLinearPos;
  EffectLinearRot cmdLinearRot;
  EffectLinearCol cmdLinearCol;
  FrameInfo frameInfo;
};

static_assert(sizeof(EffectObj) == 0xfc0, "");

} // namespace event
