#pragma once
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class PosAxis {
public:
  enum {
    AXIS_UNKNOWN_0 = 0, // Inferred role: none; original name unknown.
    AXIS_UNKNOWN_1 = 1, // Inferred role: pos; original name unknown.
    AXIS_UNKNOWN_2 = 2, // Inferred role: pos global; original name unknown.
    AXIS_UNKNOWN_3 = 3, // Inferred role: say; original name unknown.
    AXIS_UNKNOWN_4 = 4, // Inferred role: chara; original name unknown.
  };

  PosAxis();
  PosAxis(u32 axis, f32 x, f32 y, f32 z);
  PosAxis(u32 axis, const mm::Vec3 &pos);
  virtual ~PosAxis() {}
  void set(u32 axis, f32 x, f32 y, f32 z);
  void set(u32 axis, const mm::Vec3 &pos);
  mm::Vec3 calcPos() const;
  mm::Mat44 calcOrigMat() const;
  mm::Mat44 calcOrigMatInv() const;
  const char *getOrigName() const;
  u32 getAxis() const { return unknown08; }
  const mm::Vec3 &getPos() const { return unknown10; }

private:
  u32 unknown08;      // Inferred role: axis; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: pos; original member name unknown.
};

static_assert(sizeof(PosAxis) == 0x20, "");

} // namespace event
