#pragma once
#include "mm/mm_std_base.h"
#include <math.h>
#include <string.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

#define MM_MAT_ALIGN 16

namespace mm {

struct alignas(16) Mat44 {
  static const Mat44 identity;

  Mat44() {}

  void setRotXYZ(const Vec3 &rot) {
    f32 sinX = sinf(rot.x);
    f32 cosX = cosf(rot.x);
    f32 sinY = sinf(rot.y);
    f32 cosY = cosf(rot.y);
    f32 sinZ = sinf(rot.z);
    f32 cosZ = cosf(rot.z);
    rows[0][0] = cosY * cosZ;
    rows[0][1] = cosY * sinZ;
    rows[0][2] = -sinY;
    rows[0][3] = 0.0f;
    rows[1][0] = sinX * sinY * cosZ - cosX * sinZ;
    rows[1][1] = sinX * sinY * sinZ + cosX * cosZ;
    rows[1][2] = sinX * cosY;
    rows[1][3] = 0.0f;
    rows[2][0] = cosX * sinY * cosZ + sinX * sinZ;
    rows[2][1] = cosX * sinY * sinZ - sinX * cosZ;
    rows[2][2] = cosX * cosY;
    rows[2][3] = 0.0f;
    rows[3][0] = 0.0f;
    rows[3][1] = 0.0f;
    rows[3][2] = 0.0f;
    rows[3][3] = 1.0f;
  }

  void setRotY(f32 rotY) {
    f32 sinY = sinf(rotY);
    f32 cosY = cosf(rotY);
    rows[0][0] = cosY;
    rows[0][1] = 0.0f;
    rows[0][2] = -sinY;
    rows[0][3] = 0.0f;
    rows[1][0] = 0.0f;
    rows[1][1] = 1.0f;
    rows[1][2] = 0.0f;
    rows[1][3] = 0.0f;
    rows[2][0] = sinY;
    rows[2][1] = 0.0f;
    rows[2][2] = cosY;
    rows[2][3] = 0.0f;
    rows[3][0] = 0.0f;
    rows[3][1] = 0.0f;
    rows[3][2] = 0.0f;
    rows[3][3] = 1.0f;
  }

  void setTrans(const Vec3 &pos) {
    rows[3][0] = pos.x;
    rows[3][1] = pos.y;
    rows[3][2] = pos.z;
  }

  // Inferred from AttachActorBase::get{Mtp,Efp,Bone}MatGlobal
  // (1.0.0: 0x710009e7b8, 0x710009ed2c, 0x710009f2a0).
  // Product order: local * attachment transform; original helper names unknown.
  // Inferred helper: matrix product with a destination distinct from both inputs.
  // Keep the scalar operand order: it affects Clang's generated instructions.
  __attribute__((always_inline)) void unknown001(const Mat44 &__restrict a, const Mat44 &b) {
    rows[0][0] = a.rows[0][0] * b.rows[0][0] + a.rows[0][1] * b.rows[1][0] + a.rows[0][2] * b.rows[2][0] + a.rows[0][3] * b.rows[3][0];
    rows[0][1] = a.rows[0][0] * b.rows[0][1] + a.rows[0][1] * b.rows[1][1] + a.rows[0][2] * b.rows[2][1] + a.rows[0][3] * b.rows[3][1];
    rows[0][2] = a.rows[0][0] * b.rows[0][2] + a.rows[0][1] * b.rows[1][2] + a.rows[0][2] * b.rows[2][2] + a.rows[0][3] * b.rows[3][2];
    rows[0][3] = a.rows[0][0] * b.rows[0][3] + a.rows[0][1] * b.rows[1][3] + a.rows[0][2] * b.rows[2][3] + a.rows[0][3] * b.rows[3][3];
    rows[1][0] = b.rows[0][0] * a.rows[1][0] + b.rows[1][0] * a.rows[1][1] + b.rows[2][0] * a.rows[1][2] + b.rows[3][0] * a.rows[1][3];
    rows[1][1] = b.rows[0][1] * a.rows[1][0] + b.rows[1][1] * a.rows[1][1] + b.rows[2][1] * a.rows[1][2] + b.rows[3][1] * a.rows[1][3];
    rows[1][2] = b.rows[0][2] * a.rows[1][0] + b.rows[1][2] * a.rows[1][1] + b.rows[2][2] * a.rows[1][2] + b.rows[3][2] * a.rows[1][3];
    rows[1][3] = b.rows[0][3] * a.rows[1][0] + b.rows[1][3] * a.rows[1][1] + b.rows[2][3] * a.rows[1][2] + b.rows[3][3] * a.rows[1][3];
    rows[2][0] = b.rows[0][0] * a.rows[2][0] + a.rows[2][1] * b.rows[1][0] + a.rows[2][2] * b.rows[2][0] + a.rows[2][3] * b.rows[3][0];
    rows[2][1] = b.rows[0][1] * a.rows[2][0] + b.rows[1][1] * a.rows[2][1] + b.rows[2][1] * a.rows[2][2] + b.rows[3][1] * a.rows[2][3];
    rows[2][2] = b.rows[0][2] * a.rows[2][0] + b.rows[1][2] * a.rows[2][1] + b.rows[2][2] * a.rows[2][2] + b.rows[3][2] * a.rows[2][3];
    rows[2][3] = b.rows[0][3] * a.rows[2][0] + b.rows[1][3] * a.rows[2][1] + b.rows[2][3] * a.rows[2][2] + b.rows[3][3] * a.rows[2][3];
    rows[3][0] = a.rows[3][0] * b.rows[0][0] + b.rows[1][0] * a.rows[3][1] + b.rows[2][0] * a.rows[3][2] + b.rows[3][0] * a.rows[3][3];
    rows[3][1] = b.rows[0][1] * a.rows[3][0] + b.rows[1][1] * a.rows[3][1] + b.rows[2][1] * a.rows[3][2] + b.rows[3][1] * a.rows[3][3];
    rows[3][2] = b.rows[0][2] * a.rows[3][0] + b.rows[1][2] * a.rows[3][1] + b.rows[2][2] * a.rows[3][2] + b.rows[3][2] * a.rows[3][3];
    rows[3][3] = b.rows[0][3] * a.rows[3][0] + b.rows[1][3] * a.rows[3][1] + b.rows[2][3] * a.rows[3][2] + b.rows[3][3] * a.rows[3][3];
  }

  // Inferred helper: matrix product allowing an aliased destination; original name unknown.
  __attribute__((always_inline)) Mat44 &unknown002(const Mat44 &a, const Mat44 &b) {
    if (this == &a || this == &b) {
      Mat44 result;
      result.unknown001(a, b);
      *this = result;
    } else {
      unknown001(a, b);
    }
    return *this;
  }

  __attribute__((always_inline)) Mat44 operator*(const Mat44 &matrix) const {
    Mat44 result;
    return result.unknown002(*this, matrix);
  }

  // Inferred adjugate/determinant inverse; original helper name unknown.
  // Matches AttachActorCS/Gf::getEfpMat (646 instructions) and getBoneMat
  // (688 instructions) in 1.0.0. Build the signed first column before the
  // determinant check, then normalize only after computing all cofactors.
  __attribute__((always_inline)) Mat44 unknown003() const {
    const auto &m = rows;
    Mat44 result;
    result.rows[0][0] = unknown005(m[1][1], m[2][1], m[3][1], m[1][2], m[2][2], m[3][2], m[1][3], m[2][3], m[3][3]);
    result.rows[1][0] = -unknown005(m[1][0], m[2][0], m[3][0], m[1][2], m[2][2], m[3][2], m[1][3], m[2][3], m[3][3]);
    result.rows[2][0] = unknown005(m[1][0], m[2][0], m[3][0], m[1][1], m[2][1], m[3][1], m[1][3], m[2][3], m[3][3]);
    result.rows[3][0] = -unknown005(m[1][0], m[2][0], m[3][0], m[1][1], m[2][1], m[3][1], m[1][2], m[2][2], m[3][2]);
    f32 det = m[0][0] * result.rows[0][0] + m[0][1] * result.rows[1][0] + m[0][2] * result.rows[2][0] + m[0][3] * result.rows[3][0];
    if (!(fabsf(det) > 1.0e-6f)) {
      MMStdBase::mmAssert("mm::abs(det) > MM_FLOAT_EPSILON", __FILE__, 2993);
    }
    result.rows[0][1] = -unknown005(m[0][1], m[2][1], m[3][1], m[0][2], m[2][2], m[3][2], m[0][3], m[2][3], m[3][3]);
    result.rows[0][2] = unknown005(m[0][1], m[1][1], m[3][1], m[0][2], m[1][2], m[3][2], m[0][3], m[1][3], m[3][3]);
    result.rows[0][3] = -unknown005(m[0][1], m[1][1], m[2][1], m[0][2], m[1][2], m[2][2], m[0][3], m[1][3], m[2][3]);
    result.rows[1][1] = unknown005(m[0][0], m[2][0], m[3][0], m[0][2], m[2][2], m[3][2], m[0][3], m[2][3], m[3][3]);
    result.rows[1][2] = -unknown005(m[0][0], m[1][0], m[3][0], m[0][2], m[1][2], m[3][2], m[0][3], m[1][3], m[3][3]);
    result.rows[1][3] = unknown005(m[0][0], m[1][0], m[2][0], m[0][2], m[1][2], m[2][2], m[0][3], m[1][3], m[2][3]);
    result.rows[2][1] = -unknown005(m[0][0], m[2][0], m[3][0], m[0][1], m[2][1], m[3][1], m[0][3], m[2][3], m[3][3]);
    result.rows[2][2] = unknown005(m[0][0], m[1][0], m[3][0], m[0][1], m[1][1], m[3][1], m[0][3], m[1][3], m[3][3]);
    result.rows[2][3] = -unknown005(m[0][0], m[1][0], m[2][0], m[0][1], m[1][1], m[2][1], m[0][3], m[1][3], m[2][3]);
    result.rows[3][1] = unknown005(m[0][0], m[2][0], m[3][0], m[0][1], m[2][1], m[3][1], m[0][2], m[2][2], m[3][2]);
    result.rows[3][2] = -unknown005(m[0][0], m[1][0], m[3][0], m[0][1], m[1][1], m[3][1], m[0][2], m[1][2], m[3][2]);
    result.rows[3][3] = unknown005(m[0][0], m[1][0], m[2][0], m[0][1], m[1][1], m[2][1], m[0][2], m[1][2], m[2][2]);
    f32 invDet = 1.0f / det;
    for (u32 r = 0; r < 4; ++r) {
      for (u32 c = 0; c < 4; ++c) {
        result.rows[r][c] *= invDet;
      }
    }
    return result;
  }

  // Inferred 3x3 determinant expansion; original helper name unknown.
  // Arguments are passed by column. Preserve this order: it affects Clang
  // 3.9.1's operand order in the four matching attachment getters above.
  static f32 unknown005(f32 a00, f32 a10, f32 a20, f32 a01, f32 a11, f32 a21, f32 a02, f32 a12, f32 a22) {
    return a00 * (a11 * a22 - a12 * a21) - a01 * (a10 * a22 - a12 * a20) + a02 * (a10 * a21 - a20 * a11);
  }

  // Inferred translation extraction in AttachActorBase::render (1.0.0:
  // 0x710009e4bc, 179 matching instructions); original helper name unknown.
  // Copy only the three components, then use Vec3's component-wise copy.
  __attribute__((always_inline)) Vec3 unknown004() const {
    Vec3 position;
    memcpy(&position, rows[3], sizeof(f32) * 3);
    return Vec3(position);
  }

  // Inferred copy with an alignment check of the source (1.0.0: assert at line 195 of the original header); original helper name unknown.
  // The implicit copy constructor must stay trivial: other matching functions copy matrices without the check.
#line 194
  void unknown006(const Mat44 &ma) {
    MM_ASSERT((reinterpret_cast<size_t>(&ma) & size_t(MM_MAT_ALIGN - 1)) == 0);
    memcpy(this, &ma, sizeof(Mat44));
  }

  f32 rows[4][4];
};

static_assert(sizeof(Mat44) == 0x40, "");

} // namespace mm
