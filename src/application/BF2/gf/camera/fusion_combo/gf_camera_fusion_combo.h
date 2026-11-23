#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace mm {
struct Quat;
struct Vec3;

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class FusionComboCamera : public fw::Camera {
public:
  // Inferred role: parameters of the camera, built by createReflection; original type name unknown.
  // The member names are the names of createReflection.
  struct unknown001 {
    f32 zoom_frame;
    f32 zoom_start_distance;
    f32 zoom_end_distance;
    f32 zoom_base_width;
    f32 zoom_add_width;
    f32 zoom_base_height;
    f32 zoom_add_height;
    s32 zoom_mode;
    f32 around_frame;
    f32 around_start_distance;
    f32 around_end_distance;
    f32 around_rotate;
    f32 around_add_yaw;
    f32 around_add_pitch;
    s32 around_mode;
    u32 flags;
  };

  static mm::mtl::RTTI m_rtti;

  ~FusionComboCamera() override;
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void onActivate() override;
  void update(const fw::UpdateInfo &info) override;
  bool isPlayEnd() const;
  f32 getYaw(const mm::Quat &rotation);
  f32 getYaw(const mm::Vec3 &direction, const mm::Vec3 &reference);
  f32 getPitch(const mm::Vec3 &direction, const mm::Vec3 &reference);
  static f32 fastOut(f32 t);
  static f32 slowOut(f32 t);
  static f32 curve(f32 a, f32 b, f32 t);
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;

  u8 _a8[0x120 - 0xa8];
  f32 unknown120; // Inferred role: play time; original member name unknown.
  f32 unknown124; // Inferred role: play duration; original member name unknown.
  u8 _128[0x160 - 0x128];
};

static_assert(offsetof(FusionComboCamera, unknown120) == 0x120, "");
static_assert(offsetof(FusionComboCamera, unknown124) == 0x124, "");
static_assert(sizeof(FusionComboCamera) == 0x160, "");
static_assert(sizeof(FusionComboCamera::unknown001) == 0x40, "");

} // namespace gf
