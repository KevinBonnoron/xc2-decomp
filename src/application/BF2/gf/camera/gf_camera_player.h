#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "fw/fw_pad.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

enum ResetCameraWallTiming {
  RESET_CAMERA_WALL_TIMING_UNDER_GROUND,
  RESET_CAMERA_WALL_TIMING_GROUND,
  RESET_CAMERA_WALL_TIMING_AIR,
};

class PlayerCamera : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  static mm::mtl::IntrusivePtr<fw::Camera> create();
  static f32 getNearClip();
  static f32 getFarClip();
  static f32 getFov();
  void reset();
  void resetClimb(ResetCameraWallTiming timing);
  void resetLoad();
  void resetBattleWarp();
  void setTarget(GF_OBJ_HANDLE *target);
  bool isManual();
  f32 getSaveYaw() const;
  f32 getSavePitch() const;
  f32 getSaveDistance() const;
  f32 getSaveHeight() const;
  u32 getSaveSide() const;
  bool isSaveFreeMode() const;
};

class CameraPadData : public fw::PadRelay {
public:
  CameraPadData();
  void reset();
  void bind();
  ~CameraPadData();
  void unbind();
  void update();
  void resetAction();
  void zoomCamera();
  void heightCamera();
  void sideLeftCamera();
  void sideRightCamera();
  void sideResetCamera();
  void allResetAction();
  void setARX(f32 value);
  void setARY(f32 value);

  f32 m_ARX;
  f32 m_ARY;
  bool unknown40; // Inferred role: reset; original member name unknown.
  bool unknown41; // Inferred role: all reset; original member name unknown.
  bool unknown42; // Inferred role: zoom; original member name unknown.
  bool unknown43; // Inferred role: height; original member name unknown.
  bool unknown44; // Inferred role: side left; original member name unknown.
  bool unknown45; // Inferred role: side right; original member name unknown.
  bool unknown46; // Inferred role: side reset; original member name unknown.
};

static_assert(offsetof(CameraPadData, m_ARX) == 0x38, "");
static_assert(offsetof(CameraPadData, unknown40) == 0x40, "");
static_assert(offsetof(CameraPadData, unknown46) == 0x46, "");

} // namespace gf
