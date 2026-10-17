#pragma once
#include <stddef.h>

#include "event/curve.h"
#include "event/i_bou_callback.h"
#include "event/i_mani_callback.h"
#include "event/object.h"
#include "event/pos_axis.h"
#include "event/rot_axis.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class EffectObj;
class IAttachActor;
enum ATTACH_TYPE : int;

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
  void play(const char *name, f32 life, f32 speed, f32 skip, int prio, int offscrId);
  void stop();
  void linerPosAxis(const PosAxis &axis, f32 frame, CV_TYPE cv);
  void linerRotAxis(const RotAxis &axis, f32 frame, CV_TYPE cv);
  void setScale(const mm::Vec3 &scale);
  mm::Vec3 getScale() const;
  void setColor(const mm::Col4 &color);
  void linerColor(const mm::Col4 &color, f32 frame, CV_TYPE cv);
  mm::Col4 getColor() const;
  void setCaster(IAttachActor *caster);
  void setMount(IAttachActor *mount, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type);
  size_t getEffCount() const;

  EffectObj *getEffectObj() const { return mEffectObj; }

private:
  void resetAttach() {
    caster = nullptr;
    mount = nullptr;
    mountBone = "";
    mountOffset = mm::Vec3::zero;
    isMountRotate = false;
    attachType = static_cast<ATTACH_TYPE>(0);
    attachMat = mm::Mat44::identity;
    attachName.clear();
  }

  EffectObj *mEffectObj;
  PosAxis posAxis;
  RotAxis rotAxis;
  IAttachActor *caster;
  u8 _b8[0xc0 - 0xb8];
  IAttachActor *mount;
  mm::mtl::FixStr<32> mountBone;
  mm::Vec3 mountOffset;
  bool isMountRotate;
  ATTACH_TYPE attachType;
  mm::Mat44 attachMat;
  mm::mtl::FixStr<64> attachName;
};

static_assert(sizeof(ObjectEffect) == 0x1a0, "");

} // namespace event
