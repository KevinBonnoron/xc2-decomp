#pragma once

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class ScnObjCam;

class ScnCamUtil {
public:
  static bool getScreenPos(mm::Vec3 &screen, const ScnObjCam *cam, bool isBack, const mm::Vec3 &position);
  static bool getScreenPos(mm::Vec3 &screen, const ScnObjCam *cam, const mm::Vec3 &position);
  static bool isDispScreen(const ScnObjCam *cam, const mm::Vec3 &position);
};

} // namespace ml
