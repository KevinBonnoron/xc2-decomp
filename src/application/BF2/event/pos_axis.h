#pragma once
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class PosAxis {
public:
  PosAxis();
  PosAxis(u32 axis, f32 x, f32 y, f32 z);
  PosAxis(u32 axis, const mm::Vec3 &pos);
  virtual ~PosAxis() {}
  void set(u32 axis, f32 x, f32 y, f32 z);
  void set(u32 axis, const mm::Vec3 &pos);
  mm::Vec3 calcPos() const;
  mm::Mat44 calcOrigMat() const;
  const char *getOrigName() const;
  u32 getAxis() const { return mAxis; }
  const mm::Vec3 &getPos() const { return mPos; }

private:
  u32 mAxis;
  mm::Vec3 mPos;
};

static_assert(sizeof(PosAxis) == 0x20, "");

} // namespace event
