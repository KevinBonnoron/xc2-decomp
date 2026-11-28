#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_param_manager.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace mm {
struct Quat;

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

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

  enum Mode {
    MODE_UNKNOWN_0, // Inferred role: zoom from the position of the object to the target; original name unknown.
    MODE_UNKNOWN_1, // Inferred role: turn around the object; original name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  FusionComboCamera(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, Mode mode);

  ~FusionComboCamera() override;
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void onActivate() override;
  void update(const fw::UpdateInfo &info) override;
  bool isPlayEnd() const;
  f32 getYaw(const mm::Quat &rotation);
  void getAxis(const mm::Vec3 &from, const mm::Vec3 &to, mm::Vec3 &axis);
  f32 getYaw(const mm::Vec3 &direction, const mm::Vec3 &reference);
  f32 getPitch(const mm::Vec3 &direction, const mm::Vec3 &reference);
  static f32 fastOut(f32 t);
  static f32 slowOut(f32 t);
  static f32 curve(f32 a, f32 b, f32 t);
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;

  static mm::mtl::IntrusivePtr<fw::Camera> create(GF_OBJ_HANDLE *handle, Mode mode);
  static mm::mtl::IntrusivePtr<fw::Camera> create(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, Mode mode);
  void calcSpeedTypeSlowInSlowOut(const f32 &start, const f32 &end, f32 t, f32 &result);
  static f32 slowInSlowOut(f32 t);

  mm::Vec3 unknownb0;  // Inferred role: position; original member name unknown.
  mm::Vec3 unknownc0;  // Inferred role: cleared by the constructor; original member name unknown.
  f32 unknownd0;       // Inferred role: set to 45 by the constructor; original member name unknown.
  mm::Vec3 unknowne0;  // Inferred role: start position; original member name unknown.
  mm::Vec3 unknownf0;  // Inferred role: end position; original member name unknown.
  mm::Vec3 unknown100; // Inferred role: rotation axis; original member name unknown.
  mm::Vec3 unknown110; // Inferred role: center; original member name unknown.
  f32 unknown120;      // Inferred role: play duration; original member name unknown.
  f32 unknown124;      // Inferred role: play time; original member name unknown.
  f32 unknown128;      // Inferred role: total rotation angle; original member name unknown.
  Mode unknown12c;     // Inferred role: mode; original member name unknown.
  bool unknown130;     // Inferred role: collision enabled; original member name unknown.
  bool unknown131;     // Inferred role: slow in and out; original member name unknown.
  fw::ParamAdapter m_paramAdapter;
  fw::ColiCheckConfig m_coliCheckConfig;
};

static_assert(offsetof(FusionComboCamera, unknown120) == 0x120, "");
static_assert(offsetof(FusionComboCamera, unknown124) == 0x124, "");
static_assert(sizeof(FusionComboCamera) == 0x160, "");
static_assert(sizeof(FusionComboCamera::unknown001) == 0x40, "");

} // namespace gf
