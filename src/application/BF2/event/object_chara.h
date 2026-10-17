#pragma once
#include "event/chara_obj.h"
#include "event/curve.h"
#include "event/data_manager.h"
#include "event/i_bou_callback.h"
#include "event/i_mani_callback.h"
#include "event/object.h"
#include "event/pos_axis.h"
#include "event/rot_axis.h"
#include "event/tar_axis.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"

enum EVT_aimtype : int;
enum EVT_poscvtype : int;
enum EVT_rotcvtype : int;
enum EVT_tarcvtype : int;

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace mm {
struct Mat44;
} // namespace mm

namespace event {

class ObjectChara : public Object {
public:
  enum {
    FLAG_CREATED = 1 << 0,
  };

  ObjectChara(const char *name);
  virtual ~ObjectChara();
  void createGfObj(gf::GF_OBJ_HANDLE *handle);
  void createGfObj(CHARA_TYPE type, u32 id, u32 param3, u32 param4);
  void createModel(const char *model, u32 param2, u32 param3);
  void createGhost();
  virtual void clear();
  virtual void start();
  virtual void end();
  virtual void update();
  virtual void render(const mm::Col4 &color);
  bool isTar() const;
  virtual void tail();
  virtual bool isLoading() const;
  void walkPosAxis(const PosAxis &axis, EVT_poscvtype cv, bool isRun);
  void linerPosAxis(const PosAxis &axis, bool isWalk, f32 frame, CV_TYPE cv);
  void turnRotAxis(const RotAxis &axis, EVT_rotcvtype cv, f32 frame);
  void linerRotAxis(const RotAxis &axis, f32 frame, CV_TYPE cv);
  mm::Vec3 getTar() const;
  mm::Vec3 getEyeOffset() const;
  mm::Mat44 getMat();
  mm::Mat44 getEyeMat();
  virtual bool OnBouRectSelect(const IBouCallback::SelectParam &param);
  virtual void OnBouRender(const IBouCallback::RenderParam &param);
  virtual bool OnManiStartPos(IManiCallback::StartParam &param);
  virtual void OnManiSetPos(IManiCallback::SetParam &param);
  virtual bool OnManiStartRot(IManiCallback::StartParam &param);
  virtual void OnManiSetRot(IManiCallback::SetParam &param);
  virtual bool OnManiStartTar(IManiCallback::StartParam &param);
  virtual void OnManiSetTar(IManiCallback::SetParam &param);
  virtual void OnManiRender(IManiCallback::RenderParam &param);
  mm::Vec3 getEyePos() const;
  void setPosAxis(const PosAxis &axis);
  void setRotAxis(const RotAxis &axis);
  mm::Vec3 getPos() const;
  mm::Vec3 getRot() const;
  void setTar(const TarAxis &axis, f32 frame, EVT_tarcvtype cv, EVT_aimtype aim, f32 weight, f32 speed);
  void resetTar();

  CharaObj *getCharaObj() const { return mCharaObj; }

private:
  u32 flags;
  CharaObj *mCharaObj;
  PosAxis posAxis;
  RotAxis rotAxis;
  TarAxis tarAxis;
};

static_assert(sizeof(ObjectChara) == 0xe0, "");

inline mm::Vec3 ObjectChara::getEyePos() const {
  const mm::Vec3 &pos = mCharaObj->getPos();
  return mm::Vec3(pos.x, pos.y + mCharaObj->getEyeOffset(), pos.z);
}

inline void ObjectChara::setPosAxis(const PosAxis &axis) {
  posAxis = axis;
  mCharaObj->setPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z));
  mCharaObj->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

inline void ObjectChara::setRotAxis(const RotAxis &axis) {
  rotAxis = axis;
  const mm::Vec3 &pos = mCharaObj->getPosTo();
  mCharaObj->setRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos));
  mCharaObj->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

inline mm::Vec3 ObjectChara::getPos() const { return mCharaObj->getPos(); }

inline mm::Vec3 ObjectChara::getRot() const { return mCharaObj->getRotTo(); }

inline void ObjectChara::setTar(const TarAxis &axis, f32 frame, EVT_tarcvtype cv, EVT_aimtype aim, f32 weight, f32 speed) {
  tarAxis = axis;
  mCharaObj->setTar(axis, frame, cv, aim, weight, speed);
}

inline void ObjectChara::resetTar() { mCharaObj->resetTar(); }

} // namespace event
