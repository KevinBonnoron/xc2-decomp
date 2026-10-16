#pragma once
#include "event/curve.h"
#include "event/i_bou_callback.h"
#include "event/i_mani_callback.h"
#include "event/object.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace mm {
struct Mat44;
} // namespace mm

namespace event {

class CharaObj;
class PosAxis;
class RotAxis;

enum CHARA_TYPE {
  CHARA_TYPE_DRIVER = 1,
  CHARA_TYPE_BLADE = 2,
  CHARA_TYPE_NPC = 3,
  CHARA_TYPE_ENEMY = 5,
};

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
  void linerPosAxis(const PosAxis &axis, bool isWalk, f32 frame, CV_TYPE cv);
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
  void resetTar();

  CharaObj *getCharaObj() const { return mCharaObj; }

private:
  u32 flags;
  CharaObj *mCharaObj;
  u8 _78[0xe0 - 0x78];
};

static_assert(sizeof(ObjectChara) == 0xe0, "");

} // namespace event
