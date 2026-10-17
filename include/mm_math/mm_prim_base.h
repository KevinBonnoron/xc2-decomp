#pragma once
#include <stddef.h>

#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace mm {

struct Aabb;
struct Obb;

class PrimBase {
public:
  enum Type {
    TYPE_CUBE = 0,
    TYPE_CYLINDER = 1,
    TYPE_SPHERE = 2,
  };

  virtual ~PrimBase() {}
  virtual void getOBB(Obb &obb) const = 0;
  virtual void getAABB(Aabb &aabb) const = 0;
  virtual const Vec3 &getPos() const { return pos; }
  virtual const Quat &getRot() const { return rot; }
  virtual bool isCollide(const PrimBase &prim) const = 0;

  Vec3 pos;
  Quat rot;
  Vec3 scale;
  Type type;
};

static_assert(offsetof(PrimBase, pos) == 0x10, "");
static_assert(offsetof(PrimBase, rot) == 0x20, "");
static_assert(offsetof(PrimBase, scale) == 0x30, "");
static_assert(offsetof(PrimBase, type) == 0x40, "");

} // namespace mm
