#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_param_manager.h"
#include "gf/camera/gf_camera_pad_data.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
class Reflection;
struct Transform;
} // namespace fw

namespace mm {

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

enum ResetCameraWallTiming {
  RESET_CAMERA_WALL_TIMING_UNKNOWN_0, // Inferred role: reset camera wall timing under ground; original name unknown.
  RESET_CAMERA_WALL_TIMING_UNKNOWN_1, // Inferred role: reset camera wall timing ground; original name unknown.
  RESET_CAMERA_WALL_TIMING_UNKNOWN_2, // Inferred role: reset camera wall timing air; original name unknown.
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

  // Inferred role: parameters of the camera, read through the param adapter; original type name unknown.
  // The member names are the names of createReflection.
  struct unknown002 {
    f32 fov;
    f32 collision_size;
    f32 distance_minimum;
    f32 distance_maximum;
    f32 distance_default;
    f32 camera_height;
    f32 look_height;
    f32 height_min;
    f32 height_max;
    f32 pitch_limit_upper;
    f32 pitch_limit_lower;
    f32 damp_horizontal_revise;
    f32 damp_vertical_revise;
    f32 zoom_speed;
    f32 yaw_speed;
    f32 pitch_speed;
    f32 height_speed;
    f32 rotate_revise;
    f32 rotate_revise_at_manual;
    f32 rotate_revise_at_reset;
    f32 rotate_revise_at_slope;
    f32 distance_revise;
    f32 target_range_width;
    f32 target_range_height;
    f32 target_range_offset_y;
    u32 flags;
    s32 camera_type;
    f32 ship_roll_min;
    f32 ship_roll_max;
    f32 ship_roll_move;
    f32 ship_pitch_min;
    f32 ship_pitch_max;
    f32 ship_pitch_move;
    s32 look_bone;
    f32 side_distance_min;
    f32 side_distance_max;
    f32 side_distance[3]; // The names of createReflection are side_distance1, side_distance2 and side_distance3.
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
  f32 getPitch(const mm::Vec3 &position, const mm::Vec3 &target);
  bool getHitPosition(const fw::ColiCheckConfig &config, const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 &hitPosition);
  void updateCollisionUp(const mm::Vec3 &start, mm::Vec3 &position, mm::Vec3 &target);
  void updateTracking(bool param1, bool param2);
  void updateCollisionSide(mm::Vec3 &position, mm::Vec3 &target);
  void updateTarget(const fw::Transform &transform, bool param2);
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

  GF_OBJ_HANDLE *unknowna8;   // Inferred role: target object; original member name unknown.
  fw::ParamAdapter unknownb0; // Inferred role: parameters of the camera; original member name unknown.
  f32 unknownb8;              // Inferred role: yaw; original member name unknown.
  f32 m_saveYaw;
  f32 unknownc0; // Inferred role: pitch; original member name unknown.
  f32 m_savePitch;
  f32 unknownc8; // Inferred role: pitch target; original member name unknown.
  f32 unknowncc; // Inferred role: roll; original member name unknown.
  f32 unknownd0; // Inferred role: current distance, set from the saved distance each frame; original member name unknown.
  f32 m_saveDistance;
  f32 unknownd8; // Inferred role: current height; original member name unknown.
  f32 m_saveHeight;
  f32 unknowne0; // Inferred role: current side offset; original member name unknown.
  f32 unknowne4; // Inferred role: side offset of the saved side; original member name unknown.
  u8 m_saveSide;
  u8 _e9[0xec - 0xe9];
  f32 unknownec; // Inferred role: revise rate of the target tracking; original member name unknown.
  f32 unknownf0; // Inferred role: climb reset time; original member name unknown.
  f32 unknownf4; // Inferred role: time left of the pause after the camera type change; original member name unknown.
  f32 unknownf8; // Role and original member name unknown; the constructor sets it to zero.
  u8 _fc[0x100 - 0xfc];
  mm::Vec3 unknown100; // Inferred role: position of the player target; original member name unknown.
  mm::Vec3 unknown110; // Inferred role: previous position of the player target; original member name unknown.
  bool m_manual;
  bool unknown121;                // Inferred role: yaw reset in progress; original member name unknown.
  bool unknown122;                // Inferred role: target in the screen; original member name unknown.
  bool unknown123;                // Inferred role: slope revise; original member name unknown.
  bool unknown124;                // Inferred role: climb reset requested; original member name unknown.
  bool unknown125;                // Inferred role: height tracking; original member name unknown.
  bool unknown126;                // Inferred role: target tracking; original member name unknown.
  bool unknown127;                // Inferred role: pause after the camera type change; original member name unknown.
  u32 unknown128;                 // Role and original member name unknown; the constructor sets it to zero.
  fw::ColiCheckConfig unknown12c; // Inferred role: collision check config of the side collision; original member name unknown.
  fw::ColiCheckConfig unknown144; // Inferred role: collision check config of the upward collision; original member name unknown.
  u8 _15c[0x160 - 0x15c];
  fw::TColiCheckResult<256> unknown160; // Inferred role: collision check result of the camera; original member name unknown.
  mm::Vec3 unknown5180;                 // Inferred role: position of the camera when the target is the player; original member name unknown.
  bool unknown5190;                     // Inferred role: target changed; original member name unknown.
  u8 _5191[0x51a0 - 0x5191];
  mm::Vec3 unknown51a0; // Inferred role: tracked position of the player target; original member name unknown.
  f32 unknown51b0;      // Inferred role: tracked height; original member name unknown.
  u8 _51b4[0x51b8 - 0x51b4];
  CameraPadData unknown51b8; // Inferred role: pad of the camera; original member name unknown.
  u8 _5200[0x5280 - 0x5200];
  mm::Vec3 unknown5280;              // Inferred role: start of the side collision on the first side; original member name unknown.
  mm::Vec3 unknown5290;              // Inferred role: end of the side collision on the first side; original member name unknown.
  mm::Vec3 unknown52a0;              // Inferred role: start of the side collision on the second side; original member name unknown.
  mm::Vec3 unknown52b0;              // Inferred role: end of the side collision on the second side; original member name unknown.
  f32 unknown52c0;                   // Inferred role: aspect ratio of the screen; original member name unknown.
  ResetCameraWallTiming unknown52c4; // Inferred role: climb reset timing; original member name unknown.
  bool unknown52c8;                  // Inferred role: target is the player; original member name unknown.
  u8 _52c9[0x52cc - 0x52c9];
  f32 unknown52cc;                                  // Inferred role: horizontal collision margin of the camera; original member name unknown.
  f32 unknown52d0;                                  // Inferred role: collision margin of the camera, derived from the field of view in the constructor; original member name unknown.
  u8 unknown52d4;                                   // Inferred role: ZoomSpeed of CAM_MAX_LEVEL; original member name unknown.
  u8 unknown52d5;                                   // Inferred role: RotSpeed of CAM_MAX_LEVEL; original member name unknown.
  u8 unknown52d6;                                   // Inferred role: RevReset of CAM_MAX_LEVEL; original member name unknown.
  u8 unknown52d7;                                   // Inferred role: RevAuto of CAM_MAX_LEVEL; original member name unknown.
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
