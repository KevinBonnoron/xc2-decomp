#pragma once
#include "math.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

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

  f32 rows[4][4];
};

static_assert(sizeof(Mat44) == 0x40, "");

} // namespace mm
