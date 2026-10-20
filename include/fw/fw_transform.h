#pragma once
#include <string.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace anm {
struct QsTransform;
} // namespace anm

namespace fw {

struct Transform {
  static void mul(const Transform &transform, const Transform &other, Transform *result);
  static void invert(const Transform &transform, Transform *result);

  // Inferred affine matrix conversion in AttachActorBase::render and the
  // AttachActorCS/Gf bone getters; original helper name unknown.
  __attribute__((always_inline)) void unknown001(mm::Mat44 &matrix) const {
    mm::quatToMatrix(matrix, rotation);
    matrix.rows[0][3] = 0.0f;
    matrix.rows[1][3] = 0.0f;
    matrix.rows[2][3] = 0.0f;
    matrix.rows[3][0] = 0.0f;
    matrix.rows[3][1] = 0.0f;
    matrix.rows[3][2] = 0.0f;
    matrix.rows[3][3] = 1.0f;
    mm::Vec3 translation;
    memcpy(&translation, &position, sizeof(f32) * 3);
    matrix.setTrans(translation);
  }

  mm::Vec3 position;
  mm::Quat rotation;
};

static_assert(sizeof(Transform) == 0x20, "");

class TransformUtil {
public:
  static void mul(const Transform &transform, const anm::QsTransform &other, f32 scale, Transform *result);
};

} // namespace fw
