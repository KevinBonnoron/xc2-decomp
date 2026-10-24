#pragma once
#include <stddef.h>

#include "event/curve.h"
#include "event/i_bou_callback.h"
#include "event/i_mani_callback.h"
#include "event/object.h"
#include "event/pos_axis.h"
#include "event/tar_axis.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class CamObj;

class ObjectCamera : public Object {
public:
  static constexpr size_t KEY_COUNT = 16;

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
  const char *getCutName() const;

  CamObj *getCamObj() const { return unknown68; }
  const PosAxis &getPosAxis() const { return unknown80; }
  const TarAxis &getTarAxis() const { return unknown2b0; }

private:
  CamObj *unknown68; // Inferred role: cam object; original member name unknown.
  u32 unknown70;     // Inferred role: id; original member name unknown.
  u8 _74[0x80 - 0x74];
  PosAxis unknown80;                                   // Inferred role: pos axis; original member name unknown.
  mm::mtl::FixedVector<PosAxis, KEY_COUNT> unknowna0;  // Inferred role: pos axes; original member name unknown.
  TarAxis unknown2b0;                                  // Inferred role: tar axis; original member name unknown.
  mm::mtl::FixedVector<TarAxis, KEY_COUNT> unknown2d0; // Inferred role: tar axes; original member name unknown.
  u8 unknown4e0[0x4e8 - 0x4e0];                        // Inferred role: 4 e0; original member name unknown.
  mm::mtl::FixStr<64> m_cutName;
  u8 _52c[0x530 - 0x52c];
};

static_assert(sizeof(ObjectCamera) == 0x530, "");

} // namespace event
