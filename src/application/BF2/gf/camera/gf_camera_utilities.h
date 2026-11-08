#pragma once

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

class CameraUtilities {
public:
  static void getCameraLookBonePosition(GF_OBJ_HANDLE *handle, mm::Vec3 &position);
  static bool getRotateAxis(const mm::Vec3 &from, const mm::Vec3 &to, mm::Vec3 &axis);
};

} // namespace gf
