#pragma once
#include "fw/fw_camera.h"
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

} // namespace gf
