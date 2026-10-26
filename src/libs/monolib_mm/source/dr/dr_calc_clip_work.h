#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrCalcClipWork {
public:
  struct unknown001 {
    mm::Vec3 unknown00; // Inferred role: plane normal; original member name unknown.
    f32 unknown10;      // Inferred role: plane distance; original member name unknown.
  };

  virtual bool clipLineTest(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) const;
  virtual bool clipTest(const f32 *min, const f32 *max) const;
  virtual bool clipTest(const mm::Vec3 *points, int count) const;
  virtual void debugDraw();
  virtual bool clipTest(const mm::Vec3 &position, f32 radius) const;
  virtual int clipTypeTest(const mm::Vec3 &position, f32 radius) const;

  s32 unknown08; // Inferred role: clip type; original member name unknown.
};

static_assert(offsetof(DrCalcClipWork, unknown08) == 0x8, "");

} // namespace ml
