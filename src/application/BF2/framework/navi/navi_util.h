#pragma once

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {

class NaviUtil {
public:
  static bool testNaviColi(mm::Vec3 &position, const mm::Vec3 &target, float radius, float height);
  static bool testNaviColiRange(mm::Vec3 &position, const mm::Vec3 &target, float radius, float height, float range);
  static int testNaviStraightLine(mm::Vec3 &position, const mm::Vec3 &start, const mm::Vec3 &end, float radius, float height);
  static int testNaviFindPos(const mm::Vec3 &position, float radius, float height, float range, const mm::Vec3 &target, float targetRadius,
                             float targetHeight, float targetRange, int count);
  static bool isNaviMeshReadCheck(const mm::Vec3 &position);
};

} // namespace fw
