#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {

// Unsigned underlying type: fw::CameraManager::pop indexes the layers with it through a zero extension. Evidence: Xenoblade Chronicles: Definitive Edition has the function out of line,
// _ZN2fw13CameraManager3popENS_11CAMERA_TYPEERN2mm3mtl12IntrusivePtrINS_6CameraEEEf (umaddl x8, w1, w8, x0), and GfMenuModelView::popCamera has the same umaddl.
enum CAMERA_TYPE : unsigned int {
  CAMERA_TYPE_UNKNOWN_0 = 0, // Inferred role: main; original name unknown.
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
