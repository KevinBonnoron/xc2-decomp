#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace mm {
struct Mat33;
struct Mat44;
struct Quat;

struct Aabb {
  Aabb(const Vec3 &a, const Vec3 &b);
  void set(const Vec3 &a, const Vec3 &b);
  void setExtend(const Vec3 &center, const Vec3 &corner);
  void setVertices(const Vec3 *vertices, u32 count);
  void apply(const Vec3 &point);
  void add(const Vec3 &offset);
  void sub(const Vec3 &offset);
  void transform(const Mat44 &matrix);
  void getVertices(mtl::FixedArray<Vec3, 8> &vertices) const;
  void transform(const Mat33 &matrix);
  void transform(const Quat &rotation);
  Aabb &operator+=(const Vec3 &offset);
  Aabb &operator-=(const Vec3 &offset);
  void getCenter(Vec3 &center) const;

  Vec3 min;
  Vec3 max;
};

static_assert(offsetof(Aabb, max) == 0x10, "");
static_assert(sizeof(Aabb) == 0x20, "");

} // namespace mm
