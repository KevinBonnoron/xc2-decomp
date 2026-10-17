#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct Obb {
  Obb();
  Obb(const Mat44 &matrix, const Vec3 &size);
  Obb(const Vec3 &position, const Vec3 &axisX, const Vec3 &axisY, const Vec3 &axisZ, const Vec3 &size);
  Obb(const Vec3 *vertices, u32 count);
  void setVertices(const Vec3 *vertices, u32 count);
  Obb(const Obb &obb);
  Obb &operator=(const Obb &obb);
  void setMat(const Mat44 &matrix, const Vec3 &size);

  Mat44 matrix;
  Vec3 size;
};

static_assert(offsetof(Obb, size) == 0x40, "");
static_assert(sizeof(Obb) == 0x50, "");

} // namespace mm
