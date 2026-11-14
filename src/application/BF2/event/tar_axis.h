#pragma once
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class TarAxis {
public:
  enum {
    AXIS_UNKNOWN_0 = 0, // Inferred role: none; original name unknown.
    AXIS_UNKNOWN_1 = 1, // Inferred role: pos; original name unknown.
    AXIS_UNKNOWN_2 = 2, // Inferred role: pos global; original name unknown.
    AXIS_UNKNOWN_3 = 3, // Inferred role: say; original name unknown.
    AXIS_UNKNOWN_4 = 4, // Inferred role: angle; original name unknown.
    AXIS_UNKNOWN_5 = 5, // Inferred role: angle global; original name unknown.
    AXIS_UNKNOWN_6 = 6, // Inferred role: chara; original name unknown.
  };

  TarAxis();
  TarAxis(u32 axis, f32 x, f32 y, f32 z);
  TarAxis(u32 axis, const mm::Vec3 &tar);
  virtual ~TarAxis() {}
  void set(u32 axis, f32 x, f32 y, f32 z);
  void set(u32 axis, const mm::Vec3 &tar);
  mm::Vec3 calcTar(const mm::Vec3 &pos) const;
  mm::Mat44 calcOrigMat() const;
  mm::Mat44 calcOrigMatInv() const;
  const char *getOrigName() const;
  u32 getAxis() const { return unknown08; }
  const mm::Vec3 &getTar() const { return unknown10; }

private:
  u32 unknown08;      // Inferred role: axis; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: tar; original member name unknown.
};

static_assert(sizeof(TarAxis) == 0x20, "");

} // namespace event
