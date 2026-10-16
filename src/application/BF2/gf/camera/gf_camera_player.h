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

enum ResetCameraWallTiming {};

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

  f32 arx;
  f32 ary;
  bool isReset;
  bool isAllReset;
  bool isZoom;
  bool isHeight;
  bool isSideLeft;
  bool isSideRight;
  bool isSideReset;
};

static_assert(offsetof(CameraPadData, arx) == 0x38, "");
static_assert(offsetof(CameraPadData, isReset) == 0x40, "");
static_assert(offsetof(CameraPadData, isSideReset) == 0x46, "");

} // namespace gf
