#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Quat;
struct Vec3;
} // namespace mm

namespace ml {

class DebDraw;
class DrMdlObj;

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

  u8 _008[0x3d8 - 0x008];
  DrMdlObj *m_drMdl;
};

static_assert(offsetof(ScnObjModel, m_drMdl) == 0x3d8, "");

} // namespace ml
