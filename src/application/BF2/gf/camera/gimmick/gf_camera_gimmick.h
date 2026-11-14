#pragma once

#include <stddef.h>

#include "fw/fw_camera.h"
#include "fw/fw_coli_check.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
enum CAMERA_PRIO : int;
struct UpdateInfo;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

class GimmickCamera : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  struct Param {
    mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
    mm::Vec3 unknown10; // Inferred role: rotation; original member name unknown.
    f32 unknown20;      // Inferred role: fov; original member name unknown.
    s32 unknown24;      // Inferred role: coordinate type; original member name unknown.
    s32 unknown28;      // Inferred role: axis rotate flag; original member name unknown.
    s32 unknown2c;      // Inferred role: speed type; original member name unknown.
    f32 unknown30;      // Inferred role: duration; original member name unknown.
  };

  GimmickCamera();
  GimmickCamera(fw::CAMERA_PRIO prio);
  static mm::mtl::IntrusivePtr<fw::Camera> create();
  static mm::mtl::IntrusivePtr<fw::Camera> create(fw::CAMERA_PRIO prio);
  static mm::mtl::IntrusivePtr<fw::Camera> create(const char *name);
  static mm::mtl::IntrusivePtr<fw::Camera> create(const char *name, GF_OBJ_HANDLE *handle);
  static mm::mtl::IntrusivePtr<fw::Camera> create(const char *name, const mm::Vec3 &position, f32 rotation);
  void setReadFile(const char *name);
  void setHandle(GF_OBJ_HANDLE *handle);
  void setLookLock(const mm::Vec3 &position);
  void updatePlayCamera(const fw::UpdateInfo &info);
  void updateParams();
  void add(const Param &param);
  void calcSpeedTypeLinearSpacing(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov);
  void calcSpeedTypeSlowOut(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov);
  void calcSpeedTypeFastOut(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov);
  void calcSpeedTypeFastInFastOut(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov);
  mm::Vec3 calcAxisRotatePosition(const mm::Vec3 &from, const mm::Vec3 &to, f32 rate, f32 scale, f32 offset);
  f32 getPitch(const mm::Vec3 &direction, const mm::Vec3 &reference);
  f32 getYaw(const mm::Vec3 &direction, const mm::Vec3 &reference);
  void calcSpeedTypeLinearSpacingAxisRotate(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov);
  void calcSpeedTypeSlowOutAxisRotate(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov);
  void calcSpeedTypeFastOutAxisRotate(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov);
  void calcSpeedTypeFastInFastOutAxisRotate(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov);
  void calcSpeedTypeSlowInSlowOutAxisRotate(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov);
  void updateParamsByCoordinateType();
  void play();
  bool isPlayEnd() const;
  bool isLoaded() const;
  void setAuto(bool isAuto);
  void setCollision(bool isCollision);
  void setSpeedFlag(bool isEnable);
  void setPause(bool isPause);
  bool isPause() const;
  void setNearClip(f32 nearClip);
  void setFarClip(f32 farClip);
  void setLookUnlock();
  const mm::Vec3 &getPos() const;
  void setPos(const mm::Vec3 &position);
  const mm::Vec3 &getRot() const;
  void setRot(const mm::Vec3 &rotation);
  const f32 &getFov() const;
  void setFov(const f32 &fov);
  static f32 curve(f32 a, f32 b, f32 t);
  static f32 slowOut(f32 t);
  static f32 fastOut(f32 t);
  static f32 fastInFastOut(f32 t);
  const s32 &getIndex() const;
  const f32 &getFrame() const;
  const f32 &getSpeed() const;
  const f32 &getControlSpeed() const;
  void clear();
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;
  void onActivate() override;
  void update(const fw::UpdateInfo &info) override;

  u8 _a8[0xb0 - 0xa8];
  mm::Vec3 unknownb0; // Inferred role: position; original member name unknown.
  mm::Vec3 unknownc0; // Inferred role: rotation; original member name unknown.
  f32 unknownd0;      // Inferred role: fov; original member name unknown.
  u8 _d4[0xe0 - 0xd4];
  mm::mtl::FixedVector<Param, 1024> unknown00e0; // Inferred role: camera params; original member name unknown.
  s32 unknown100f0;                              // Inferred role: load mode; original member name unknown.
  s32 unknown100f4;                              // Inferred role: coordinate type; original member name unknown.
  bool unknown100f8;                             // Inferred role: playing; original member name unknown.
  bool unknown100f9;                             // Inferred role: played; original member name unknown.
  bool unknown100fa;                             // Inferred role: auto; original member name unknown.
  bool unknown100fb;                             // Inferred role: collision; original member name unknown.
  bool unknown100fc;                             // Inferred role: speed flag; original member name unknown.
  bool unknown100fd;                             // Inferred role: pause; original member name unknown.
  u8 _100fe[0x10100 - 0x100fe];
  s32 unknown10100; // Inferred role: index; original member name unknown.
  f32 unknown10104; // Inferred role: frame; original member name unknown.
  f32 unknown10108; // Inferred role: speed; original member name unknown.
  u8 _1010c[0x10110 - 0x1010c];
  mm::Vec3 unknown10110; // Inferred role: base position; original member name unknown.
  f32 unknown10120;      // Inferred role: base rotation; original member name unknown.
  u8 _10124[0x10128 - 0x10124];
  GF_OBJ_HANDLE *m_handle;
  const void *unknown10130;         // Inferred role: loaded params data; original member name unknown.
  f32 unknown10138;                 // Inferred role: control speed; original member name unknown.
  fw::ColiCheckConfig unknown1013c; // Inferred role: camera collision config; original member name unknown.
  bool unknown10154;                // Inferred role: look lock; original member name unknown.
  u8 _10155[0x10160 - 0x10155];
  mm::Vec3 unknown10160; // Inferred role: look lock position; original member name unknown.
};

static_assert(offsetof(GimmickCamera, unknownb0) == 0xb0, "");
static_assert(offsetof(GimmickCamera, unknownc0) == 0xc0, "");
static_assert(offsetof(GimmickCamera, unknownd0) == 0xd0, "");
static_assert(offsetof(GimmickCamera, unknown00e0) == 0xe0, "");
static_assert(sizeof(GimmickCamera::Param) == 0x40, "");
static_assert(offsetof(GimmickCamera::Param, unknown10) == 0x10, "");
static_assert(offsetof(GimmickCamera::Param, unknown20) == 0x20, "");
static_assert(offsetof(GimmickCamera::Param, unknown30) == 0x30, "");
static_assert(offsetof(GimmickCamera, unknown100f0) == 0x100f0, "");
static_assert(offsetof(GimmickCamera, unknown100f8) == 0x100f8, "");
static_assert(offsetof(GimmickCamera, unknown10100) == 0x10100, "");
static_assert(offsetof(GimmickCamera, unknown10104) == 0x10104, "");
static_assert(offsetof(GimmickCamera, unknown10108) == 0x10108, "");
static_assert(offsetof(GimmickCamera, unknown10110) == 0x10110, "");
static_assert(offsetof(GimmickCamera, unknown10120) == 0x10120, "");
static_assert(offsetof(GimmickCamera, m_handle) == 0x10128, "");
static_assert(offsetof(GimmickCamera, unknown10130) == 0x10130, "");
static_assert(offsetof(GimmickCamera, unknown10138) == 0x10138, "");
static_assert(offsetof(GimmickCamera, unknown1013c) == 0x1013c, "");
static_assert(offsetof(GimmickCamera, unknown10154) == 0x10154, "");
static_assert(offsetof(GimmickCamera, unknown10160) == 0x10160, "");
static_assert(sizeof(GimmickCamera) == 0x10170, "");

} // namespace gf
