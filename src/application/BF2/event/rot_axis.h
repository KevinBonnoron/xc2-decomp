#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class RotAxis {
public:
  enum {
    AXIS_NONE = 0,
    AXIS_ANGLE = 1,
    AXIS_ANGLE_GLOBAL = 2,
    AXIS_SAY = 3,
    AXIS_CHARA = 4,
  };

  RotAxis();
  RotAxis(u32 axis, f32 x, f32 y, f32 z);
  RotAxis(u32 axis, const mm::Vec3 &rot);
  virtual ~RotAxis() {}
  void set(u32 axis, f32 x, f32 y, f32 z);
  void set(u32 axis, const mm::Vec3 &rot);
  mm::Vec3 calcRot(const mm::Vec3 &pos) const;
  f32 calcOrigRot(const mm::Vec3 &pos) const;
  const char *getOrigName() const;
  u32 getAxis() const { return mAxis; }
  const mm::Vec3 &getRot() const { return mRot; }

private:
  u32 mAxis;
  mm::Vec3 mRot;
};

static_assert(sizeof(RotAxis) == 0x20, "");

} // namespace event
