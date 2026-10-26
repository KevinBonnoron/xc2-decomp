#pragma once

#include <stddef.h>

#include "fw/fw_camera.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GimmickCamera : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  struct Param {
    u8 _00[0x40];
  };

  static mm::mtl::IntrusivePtr<fw::Camera> create(const char *name);
  static mm::mtl::IntrusivePtr<fw::Camera> create(const char *name, const mm::Vec3 &position, f32 rotation);
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
  const s32 &getIndex() const;
  const s32 &getFrame() const;
  const f32 &getSpeed() const;
  const f32 &getControlSpeed() const;
  void clear();
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;
  void onActivate() override;

  u8 _a8[0xb0 - 0xa8];
  mm::Vec3 unknownb0; // Inferred role: position; original member name unknown.
  mm::Vec3 unknownc0; // Inferred role: rotation; original member name unknown.
  f32 unknownd0;      // Inferred role: fov; original member name unknown.
  u8 _d4[0xe0 - 0xd4];
  mm::mtl::FixedVector<Param, 1024> unknown00e0; // Inferred role: camera params; original member name unknown.
  u8 _100e8[0x100f8 - 0x100e8];
  bool unknown100f8; // Inferred role: playing; original member name unknown.
  bool unknown100f9; // Inferred role: played; original member name unknown.
  bool unknown100fa; // Inferred role: auto; original member name unknown.
  bool unknown100fb; // Inferred role: collision; original member name unknown.
  bool unknown100fc; // Inferred role: speed flag; original member name unknown.
  bool unknown100fd; // Inferred role: pause; original member name unknown.
  u8 _100fe[0x10100 - 0x100fe];
  s32 unknown10100; // Inferred role: index; original member name unknown.
  s32 unknown10104; // Inferred role: frame; original member name unknown.
  f32 unknown10108; // Inferred role: speed; original member name unknown.
  u8 _1010c[0x10138 - 0x1010c];
  f32 unknown10138; // Inferred role: control speed; original member name unknown.
  u8 _1013c[0x10154 - 0x1013c];
  bool unknown10154; // Inferred role: look lock; original member name unknown.
  u8 _10155[0x10170 - 0x10155];
};

static_assert(offsetof(GimmickCamera, unknownb0) == 0xb0, "");
static_assert(offsetof(GimmickCamera, unknownc0) == 0xc0, "");
static_assert(offsetof(GimmickCamera, unknownd0) == 0xd0, "");
static_assert(offsetof(GimmickCamera, unknown00e0) == 0xe0, "");
static_assert(sizeof(GimmickCamera::Param) == 0x40, "");
static_assert(offsetof(GimmickCamera, unknown100f8) == 0x100f8, "");
static_assert(offsetof(GimmickCamera, unknown10100) == 0x10100, "");
static_assert(offsetof(GimmickCamera, unknown10104) == 0x10104, "");
static_assert(offsetof(GimmickCamera, unknown10108) == 0x10108, "");
static_assert(offsetof(GimmickCamera, unknown10138) == 0x10138, "");
static_assert(offsetof(GimmickCamera, unknown10154) == 0x10154, "");
static_assert(sizeof(GimmickCamera) == 0x10170, "");

} // namespace gf
