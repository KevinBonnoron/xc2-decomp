#pragma once
#include "event/curve.h"
#include "event/i_bou_callback.h"
#include "event/i_mani_callback.h"
#include "event/object.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class EffectObj;
class IAttachActor;
class PosAxis;
class RotAxis;

class ObjectEffect : public Object {
public:
  ObjectEffect(const char *name);
  virtual ~ObjectEffect();
  virtual void start();
  virtual void end();
  virtual void update();
  virtual void render(const mm::Col4 &color);
  mm::Vec3 getPos() const;
  mm::Vec3 getRot() const;
  virtual void tail();
  virtual bool OnBouRectSelect(const IBouCallback::SelectParam &param);
  virtual void OnBouRender(const IBouCallback::RenderParam &param);
  virtual bool OnManiStartPos(IManiCallback::StartParam &param);
  virtual void OnManiSetPos(IManiCallback::SetParam &param);
  void setPosAxis(const PosAxis &axis);
  virtual bool OnManiStartRot(IManiCallback::StartParam &param);
  virtual void OnManiSetRot(IManiCallback::SetParam &param);
  void setRotAxis(const RotAxis &axis);
  virtual void OnManiRender(IManiCallback::RenderParam &param);
  void play(const char *name, f32 frame, f32 speed, f32 param3, int param4, int param5);
  void stop();
  void linerPosAxis(const PosAxis &axis, f32 frame, CV_TYPE cv);
  void linerRotAxis(const RotAxis &axis, f32 frame, CV_TYPE cv);
  void setScale(const mm::Vec3 &scale);
  mm::Vec3 getScale() const;
  void setColor(const mm::Col4 &color);
  void linerColor(const mm::Col4 &color, f32 frame, CV_TYPE cv);
  mm::Col4 getColor() const;
  void setCaster(IAttachActor *caster);
  u32 getEffCount() const;

  EffectObj *getEffectObj() const { return mEffectObj; }

private:
  EffectObj *mEffectObj;
  u8 _70[0x1a0 - 0x70];
};

static_assert(sizeof(ObjectEffect) == 0x1a0, "");

} // namespace event
