#pragma once

namespace mm {
struct Vec3;
} // namespace mm

namespace navi {

class NvmshAccUtil {
public:
  NvmshAccUtil();
  bool testNaviColi(mm::Vec3 &position, const mm::Vec3 &target, float radius, float height, int layer = 0);
  bool testNaviColiRange(mm::Vec3 &position, const mm::Vec3 &target, float radius, float height, float range, int layer = 0);
  int testNaviStraightLine(mm::Vec3 &position, const mm::Vec3 &start, const mm::Vec3 &end, float radius, float height, int layer = 0);
  int checkNaviFindPos(const mm::Vec3 &position, float radius, float height, float range, float offset, const mm::Vec3 &target, float targetRadius, float targetHeight, float targetRange,
                       float targetOffset, int layer = 0);
  bool isNaviMeshReadCheck(const mm::Vec3 &position);

  unsigned char _00[0x10 - 0x00];
};

} // namespace navi
