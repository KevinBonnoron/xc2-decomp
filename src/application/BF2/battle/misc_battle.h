#pragma once
#include "types.h"

namespace mm {
struct Vec3;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class Misc {
public:
  enum TRANS_TYPE {
    TRANS_TYPE_POSITION,
  };

  static void NormalizeXZ(mm::Vec3 &vector);
  static f32 CalcSquareLength(const mm::Vec3 &from, const mm::Vec3 &to);
  static bool CalcDirectionXZ(const mm::Vec3 &from, const mm::Vec3 &to, mm::Vec3 &direction);
  static bool GetObjectTransform(gf::GF_OBJ_HANDLE *handle, mm::Vec3 &transform, TRANS_TYPE type);
  static bool IsInWater(const mm::Vec3 &position, f32 depth);
};

} // namespace btl
