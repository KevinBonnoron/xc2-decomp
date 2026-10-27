#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrGpuCheckBase {
public:
  virtual ~DrGpuCheckBase() {}
  virtual void release();
  virtual bool isRender() const;
  virtual void setPause(bool isPause);
  virtual void setPos(const mm::Vec3 &position, f32 radius);
  virtual void setWorldPos(const mm::Vec3 &position, f32 radius);
  virtual u32 isDeleteCall() const;
  virtual void update();
  virtual void render();

  static bool isClip(const mm::Vec3 &position, f32 radius);
  static DrGpuCheckBase *createGpuCheckObj(int type);
  static DrGpuCheckBase *createEffGpuCheckObj(int type);
};

} // namespace ml
