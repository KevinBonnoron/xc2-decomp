#pragma once
#include "types.h"

namespace mm {
struct Col4;
struct Vec3;
} // namespace mm
namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

class RchaEff {
public:
  RchaEff();
  virtual ~RchaEff();
  virtual void setup(mtl::ALLOC_HANDLE handle, const void *data);
  void getPos(mm::Vec3 &pos, f32 frame) const;
  void getRot(mm::Vec3 &rot, f32 frame) const;
  void getScl(mm::Vec3 &scale, f32 frame) const;
  void getProgress(int &current, int &total, f32 frame) const;
  void getCol(mm::Col4 &color, f32 frame) const;
  bool isGenelate(f32 frame) const;
  bool isEnd(f32 frame) const;
  bool isKill(f32 frame) const;
  void getSpeed(f32 &speed, f32 frame) const;

  int getFrameCount() const { return frameCount; }

private:
  u8 _8[0x199c - 0x8];
  int frameCount;
  u8 _19a0[0x19f8 - 0x19a0];
};

static_assert(sizeof(RchaEff) == 0x19f8, "");
