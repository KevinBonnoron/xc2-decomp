#include "framework/navi/navi_util.h"

#include "navi/nvmsh_acc_util.h"

namespace fw {

bool NaviUtil::testNaviColi(mm::Vec3 &position, const mm::Vec3 &target, float radius, float height) {
  navi::NvmshAccUtil util;
  return util.testNaviColi(position, target, radius, height);
}

bool NaviUtil::testNaviColiRange(mm::Vec3 &position, const mm::Vec3 &target, float radius, float height, float range) {
  navi::NvmshAccUtil util;
  return util.testNaviColiRange(position, target, radius, height, range);
}

int NaviUtil::testNaviStraightLine(mm::Vec3 &position, const mm::Vec3 &start, const mm::Vec3 &end, float radius, float height) {
  navi::NvmshAccUtil util;
  return util.testNaviStraightLine(position, start, end, radius, height);
}

int NaviUtil::testNaviFindPos(const mm::Vec3 &position, float radius, float height, float range, const mm::Vec3 &target, float targetRadius,
                              float targetHeight, float targetRange, int count) {
  navi::NvmshAccUtil util;
  return util.checkNaviFindPos(position, radius, height, range, 0.0f, target, targetRadius, targetHeight, targetRange, 0.0f);
}

bool NaviUtil::isNaviMeshReadCheck(const mm::Vec3 &position) {
  navi::NvmshAccUtil util;
  return util.isNaviMeshReadCheck(position);
}

} // namespace fw
