#pragma once
#include <stddef.h>
#include <string.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct Aabb;
struct Obb;

class PrimBase {
public:
  enum Type {
    PRIM_CUBE = 0,
    PRIM_CYLINDER = 1,
    PRIM_SPHERE = 2,
  };

  virtual ~PrimBase() {}
  virtual void getOBB(Obb &obb) const = 0;
  virtual void getAABB(Aabb &aabb) const = 0;
  virtual const Vec3 &getPos() const { return pos; }
  virtual const Quat &getRot() const { return rot; }
  virtual bool isCollide(const PrimBase &prim) const = 0;
  Type getType() const { return type; }
  void getMat(Mat44 &matrix) const;

  // Inferred helper: rotation and translation matrix shared by the getOBB overrides; original name unknown.
  void unknown001(Mat44 &matrix) const {
    quatToMatrix(matrix, getRot());
    matrix.rows[0][3] = 0.0f;
    matrix.rows[1][3] = 0.0f;
    matrix.rows[2][3] = 0.0f;
    matrix.rows[3][0] = 0.0f;
    matrix.rows[3][1] = 0.0f;
    matrix.rows[3][2] = 0.0f;
    matrix.rows[3][3] = 1.0f;
    Vec3 position;
    memcpy(&position, &getPos(), sizeof(f32) * 3);
    matrix.setTrans(position);
  }

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
