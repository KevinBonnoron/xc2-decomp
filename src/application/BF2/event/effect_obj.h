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
  EffectCtrl *unknown08; // Inferred role: ctrl; original member name unknown.
  RchaEff *unknown10;    // Inferred role: rcha; original member name unknown.
  f32 unknown18;         // Inferred role: frame; original member name unknown.
};

static_assert(sizeof(EffectEvaPlayer) == 0x20, "");

class EffectPlayEff : public ICmd {
public:
  EffectPlayEff() : unknown08(nullptr), unknown10(nullptr) {}
  virtual RESULT update(const Param &param);
  virtual void term();
  void render(const mm::Vec3 &pos);

  void setup(EffectObj *obj, EffectCtrl *ctrl) {
    this->unknown10 = ctrl;
    this->unknown08 = obj;
  }

private:
  EffectObj *unknown08;  // Inferred role: object; original member name unknown.
  EffectCtrl *unknown10; // Inferred role: ctrl; original member name unknown.
  f32 unknown18;         // Inferred role: life; original member name unknown.
};

static_assert(sizeof(EffectPlayEff) == 0x20, "");

class EffectPlayEva : public ICmd {
public:
  EffectPlayEva() : unknown08(nullptr), unknown10(nullptr) {}
  virtual RESULT update(const Param &param);
  void render(const mm::Vec3 &pos);
  virtual void term();

  void setCtrl(EffectCtrl *ctrl) { this->unknown08 = ctrl; }

private:
  EffectCtrl *unknown08;     // Inferred role: ctrl; original member name unknown.
  void *unknown10;           // Inferred role: data; original member name unknown.
  f32 unknown18;             // Inferred role: life; original member name unknown.
  EffectEvaPlayer unknown20; // Inferred role: eva player; original member name unknown.
};

static_assert(sizeof(EffectPlayEva) == 0x40, "");

class EffectLinearPos : public ICmd {
public:
  EffectLinearPos() : unknown08(nullptr) {}
  virtual RESULT update(const Param &param);

  void setCtrl(EffectCtrl *ctrl) { this->unknown08 = ctrl; }

private:
  EffectCtrl *unknown08; // Inferred role: ctrl; original member name unknown.
  AnmVec unknown10;      // Inferred role: anm; original member name unknown.
};

static_assert(sizeof(EffectLinearPos) == 0x200, "");

class EffectLinearRot : public ICmd {
public:
  EffectLinearRot() : unknown08(nullptr) {}
  virtual RESULT update(const Param &param);

  void setCtrl(EffectCtrl *ctrl) { this->unknown08 = ctrl; }

private:
  EffectCtrl *unknown08; // Inferred role: ctrl; original member name unknown.
  AnmVec unknown10;      // Inferred role: anm; original member name unknown.
};

static_assert(sizeof(EffectLinearRot) == 0x200, "");

class EffectLinearCol : public ICmd {
public:
  EffectLinearCol() : unknown08(nullptr) {}
  virtual RESULT update(const Param &param);

  void setCtrl(EffectCtrl *ctrl) { this->unknown08 = ctrl; }

private:
  EffectCtrl *unknown08; // Inferred role: ctrl; original member name unknown.
  AnmCol unknown10;      // Inferred role: anm; original member name unknown.
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

  const char *getName() const { return unknown08.c_str(); }
  const FrameInfo &getFrameInfo() const { return unknownfa8; }

private:
  mm::mtl::FixStr<64> unknown08;       // Inferred role: name; original member name unknown.
  EffectCtrl unknown50;                // Inferred role: ctrl; original member name unknown.
  CmdQueue<QUEUE_COUNT, 0> unknown260; // Inferred role: queue; original member name unknown.
  EffectPlayEff unknown960;            // Inferred role: cmd play eff; original member name unknown.
  EffectPlayEva unknown980;            // Inferred role: cmd play eva; original member name unknown.
  EffectLinearPos unknown9c0;          // Inferred role: cmd linear pos; original member name unknown.
  EffectLinearRot unknownbc0;          // Inferred role: cmd linear rot; original member name unknown.
  EffectLinearCol unknowndc0;          // Inferred role: cmd linear col; original member name unknown.
  FrameInfo unknownfa8;                // Inferred role: frame info; original member name unknown.
};

static_assert(sizeof(EffectObj) == 0xfc0, "");

} // namespace event
