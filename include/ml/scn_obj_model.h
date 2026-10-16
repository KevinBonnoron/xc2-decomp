#pragma once
#include "types.h"

namespace mm {
struct Quat;
struct Vec3;
} // namespace mm

namespace ml {

class DebDraw;

class ScnObjModel {
public:
  virtual ~ScnObjModel();
  virtual void update();
  virtual void renderDebug(DebDraw *debDraw);
  virtual void apply();
  virtual void tail();
  virtual const char *getName() const;
  virtual void setDelete();
  virtual void setPos(const mm::Vec3 &position);
  virtual void setPosWarp(const mm::Vec3 &position);
  virtual void addPos(const mm::Vec3 &position);
  virtual void setRot(const mm::Vec3 &rotation);
  virtual void addRot(const mm::Vec3 &rotation);
  virtual void addRot(const mm::Quat &rotation);
  virtual void setScl(const mm::Vec3 &scale);

  void setFrameSpd(f32 speed);
  void setDisp(bool isDisp);
  void setClip(bool isClip);
};

class ScnObjAccResMdlInfo {
public:
  ScnObjAccResMdlInfo(ScnObjModel *model);
  void setGpuClip(bool isClip);
  void setSpAlphaMode(bool isEnable);
  void setCamCheckMode(bool isEnable);
  bool isCamCheckResl() const;

private:
  u8 _00[0x08 - 0x00];
};

class ScnObjAccEtcParams {
public:
  ScnObjAccEtcParams(ScnObjModel *model);
  int getIndex(const char *name) const;
  void setInitParams(u32 index, f32 value);

private:
  u8 _00[0x08 - 0x00];
};

class ScnObjAccResSubMesh {
public:
  ScnObjAccResSubMesh(ScnObjModel *model);
  int getExtMax() const;
  int getExtIdx(const char *name) const;
  const char *getExtName(int index) const;
  void setExtAlpha(int index, f32 alpha);
  f32 getExtAlpha(int index) const;

private:
  u8 _00[0x10 - 0x00];
};

} // namespace ml
