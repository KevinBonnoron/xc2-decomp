#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "fw/fw_coli_check.h"
#include "gf/camera/gf_camera_pad_data.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
class ParamAdapter;
class Reflection;
} // namespace fw

namespace mm {
struct Vec3;

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
  // Inferred role: speed parameters of one camera mode, read from the bdat in the constructor; original type name unknown.
  struct unknown001 {
    f32 unknown00; // Inferred role: zoom speed; original member name unknown.
    f32 unknown04; // Inferred role: yaw rotation speed; original member name unknown.
    f32 unknown08; // Inferred role: pitch rotation speed; original member name unknown.
    f32 unknown0c; // Inferred role: reset reverse; original member name unknown.
    f32 unknown10; // Inferred role: auto reverse; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  PlayerCamera(fw::ParamAdapter &param);
  ~PlayerCamera() override;
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;
  void onActivate() override;
  void update(const fw::UpdateInfo &info) override;
  void updateViewMatrix() override;
  void updateCollision2(mm::Vec3 &position, mm::Vec3 &target);
  f32 getYaw(const mm::Vec3 &position, const mm::Vec3 &target);
  static mm::mtl::IntrusivePtr<fw::Camera> create();
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  static f32 getNearClip();
  static f32 getFarClip();
  static f32 getFov();
  static void setOnceOff();
  void reset();
  void resetClimb(ResetCameraWallTiming timing);
  bool isResetClimb();
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

  GF_OBJ_HANDLE *unknowna8; // Inferred role: target object; original member name unknown.
  u8 _b0[0xb8 - 0xb0];
  f32 unknownb8; // Inferred role: yaw; original member name unknown.
  f32 m_saveYaw;
  u8 _c0[0xc4 - 0xc0];
  f32 m_savePitch;
  u8 _c8[0xd0 - 0xc8];
  f32 unknownd0; // Inferred role: current distance, set from the saved distance each frame; original member name unknown.
  f32 m_saveDistance;
  u8 _d8[0xdc - 0xd8];
  f32 m_saveHeight;
  u8 _e0[0xe8 - 0xe0];
  u8 m_saveSide;
  u8 _e9[0xf0 - 0xe9];
  f32 unknownf0; // Inferred role: climb reset time; original member name unknown.
  u8 _f4[0x120 - 0xf4];
  bool m_manual;
  u8 _121[0x124 - 0x121];
  bool unknown124; // Inferred role: climb reset requested; original member name unknown.
  u8 _125[0x160 - 0x125];
  fw::TColiCheckResult<256> unknown160; // Inferred role: collision check result of the camera; original member name unknown.
  u8 _5180[0x5190 - 0x5180];
  bool unknown5190; // Inferred role: target changed; original member name unknown.
  u8 _5191[0x51b8 - 0x5191];
  CameraPadData unknown51b8; // Inferred role: pad of the camera; original member name unknown.
  u8 _5200[0x52c4 - 0x5200];
  ResetCameraWallTiming unknown52c4; // Inferred role: climb reset timing; original member name unknown.
  u8 _52c8[0x52d8 - 0x52c8];
  mm::mtl::FixedVector<unknown001, 10> unknown52d8; // Inferred role: speed parameters of each camera mode; original member name unknown.
};

static_assert(offsetof(PlayerCamera, m_saveYaw) == 0xbc, "");
static_assert(offsetof(PlayerCamera, m_savePitch) == 0xc4, "");
static_assert(offsetof(PlayerCamera, m_saveDistance) == 0xd4, "");
static_assert(offsetof(PlayerCamera, m_saveHeight) == 0xdc, "");
static_assert(offsetof(PlayerCamera, m_saveSide) == 0xe8, "");
static_assert(offsetof(PlayerCamera, unknownf0) == 0xf0, "");
static_assert(offsetof(PlayerCamera, m_manual) == 0x120, "");
static_assert(offsetof(PlayerCamera, unknown124) == 0x124, "");
static_assert(offsetof(PlayerCamera, unknown52c4) == 0x52c4, "");
static_assert(offsetof(PlayerCamera, unknown160) == 0x160, "");
static_assert(offsetof(PlayerCamera, unknown51b8) == 0x51b8, "");
static_assert(offsetof(PlayerCamera, unknown52d8) == 0x52d8, "");
static_assert(sizeof(PlayerCamera) == 0x53b0, "");

} // namespace gf
