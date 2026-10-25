#pragma once

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {

class CamUtil {
public:
  static void getViewLocalToDeviceCoord(mm::Vec3 &device, const mm::Mat44 &matrix, const mm::Vec3 &viewLocal);
  static void getDeviceCoordToViewLocal(mm::Vec3 &viewLocal, const mm::Mat44 &matrix, const mm::Vec3 &device);
  static void getXYZ2ZXY(mm::Vec3 &zxy, const mm::Vec3 &xyz);
};

} // namespace ml
