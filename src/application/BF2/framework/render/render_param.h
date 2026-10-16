#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {

enum CAMERA_TYPE : int {
  CAMERA_TYPE_MAIN = 0,
};

class RenderParam {
public:
  static void initialize();
  static void finalize();
  static void setPlayerPosition(const mm::Vec3 &position, CAMERA_TYPE type);
  static bool isRoom(const mm::Vec3 &position, CAMERA_TYPE type);
  static void setMotionBlur(bool isEnable, CAMERA_TYPE type);
  static void setTime(u32 hour, u32 minute, CAMERA_TYPE type);
  static void setWeather(u32 weather, CAMERA_TYPE type);
  static int getWindIndex(CAMERA_TYPE type);
  static void setGlobalWindPower(const mm::Vec3 &power, CAMERA_TYPE type);
  static void setColorFilter(int filter, int farFilter, f32 time, CAMERA_TYPE type);
  static void resetColorFilter(f32 time, CAMERA_TYPE type);
  static void setCloudSea(u32 num);
  static void resetScene();
};

} // namespace fw
