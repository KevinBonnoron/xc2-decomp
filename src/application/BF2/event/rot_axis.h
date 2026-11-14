#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class RotAxis {
public:
  enum {
    AXIS_UNKNOWN_0 = 0, // Inferred role: none; original name unknown.
    AXIS_UNKNOWN_1 = 1, // Inferred role: angle; original name unknown.
    AXIS_UNKNOWN_2 = 2, // Inferred role: angle global; original name unknown.
    AXIS_UNKNOWN_3 = 3, // Inferred role: say; original name unknown.
    AXIS_UNKNOWN_4 = 4, // Inferred role: chara; original name unknown.
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
  u32 getAxis() const { return unknown08; }
  const mm::Vec3 &getRot() const { return unknown10; }

private:
  u32 unknown08;      // Inferred role: axis; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: rot; original member name unknown.
};

static_assert(sizeof(RotAxis) == 0x20, "");

} // namespace event
