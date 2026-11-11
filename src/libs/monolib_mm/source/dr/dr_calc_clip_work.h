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

  // Declared in the order of the game's vtable (slots 0x10 to 0x38 of every DrCalcClipWork vtable).
  virtual bool clipTest(const mm::Vec3 &position, f32 radius) const;
  virtual bool clipLineTest(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) const;
  virtual bool clipTest(const f32 *min, const f32 *max) const;
  virtual bool clipTest(const mm::Vec3 *points, int count) const;
  virtual int clipTypeTest(const mm::Vec3 &position, f32 radius) const;
  virtual void debugDraw();

  s32 unknown08; // Inferred role: clip type; original member name unknown.
};

static_assert(offsetof(DrCalcClipWork, unknown08) == 0x8, "");

} // namespace ml
