#pragma once
#include "event/curve.h"
#include "event/i_bou_callback.h"
#include "event/i_mani_callback.h"
#include "event/object.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class CamObj;
class PosAxis;
class TarAxis;

class ObjectCamera : public Object {
public:
  ObjectCamera(const char *name, u32 id);
  virtual ~ObjectCamera();
  virtual void start();
  virtual void end();
  virtual void update();
  void updateSyncFreeCam();
  virtual void render(const mm::Col4 &color);
  virtual void tail();
  void playMotion(const char *name, const mm::Vec3 &offset);
  void stopMotion();
  void setPosAxis(const PosAxis &axis, CV_TYPE cv);
  void movePosAxis(const PosAxis &axis, f32 frame, CV_TYPE cv);
  mm::Vec3 getPos() const;
  void setTarAxis(const TarAxis &axis, CV_TYPE cv);
  void moveTarAxis(const TarAxis &axis, f32 frame, CV_TYPE cv);
  mm::Vec3 getTar() const;
  void setFov(f32 fov, CV_TYPE cv);
  void moveFov(f32 fov, f32 frame, CV_TYPE cv);
  f32 getFov() const;
  void setRotZ(f32 rotZ, CV_TYPE cv);
  void moveRotZ(f32 rotZ, f32 frame, CV_TYPE cv);
  f32 getRotZ() const;
  void setCutName(const char *name);
  void followPos(bool isFollow);
  bool isFollowPos() const;
  void followTar(bool isFollow);
  bool isFollowTar() const;
  mm::Vec3 calcRot() const;
  virtual bool OnBouRectSelect(const IBouCallback::SelectParam &param);
  virtual void OnBouRender(const IBouCallback::RenderParam &param);
  virtual bool OnManiStartPos(IManiCallback::StartParam &param);
  virtual void OnManiSetPos(IManiCallback::SetParam &param);
  virtual bool OnManiStartTar(IManiCallback::StartParam &param);
  virtual void OnManiSetTar(IManiCallback::SetParam &param);
  virtual void OnManiRender(IManiCallback::RenderParam &param);
  const char *getCutName() const { return mCutName.c_str(); }

  CamObj *getCamObj() const { return mCamObj; }

private:
  CamObj *mCamObj;
  u32 mId;
  u8 _74[0x4e8 - 0x74];
  mm::mtl::FixStr<64> mCutName;
  u8 _52c[0x530 - 0x52c];
};

static_assert(sizeof(ObjectCamera) == 0x530, "");

} // namespace event
