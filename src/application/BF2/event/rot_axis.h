#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class RotAxis {
public:
  RotAxis();
  RotAxis(u32 axis, f32 x, f32 y, f32 z);
  RotAxis(u32 axis, const mm::Vec3 &rot);
  virtual ~RotAxis() {}
  void set(u32 axis, f32 x, f32 y, f32 z);
  void set(u32 axis, const mm::Vec3 &rot);
  mm::Vec3 calcRot(const mm::Vec3 &pos) const;
  f32 calcOrigRot(const mm::Vec3 &pos) const;
  const char *getOrigName() const;

private:
  u32 mAxis;
  mm::Vec3 mRot;
};

static_assert(sizeof(RotAxis) == 0x20, "");

} // namespace event
