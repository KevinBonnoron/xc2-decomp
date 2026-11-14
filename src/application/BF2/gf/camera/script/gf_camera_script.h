#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class ScriptCameraEntity : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  ScriptCameraEntity(const mm::Vec3 &position, const mm::Vec3 &rotation);
  static mm::mtl::IntrusivePtr<fw::Camera> create(const mm::Vec3 &position, const mm::Vec3 &rotation);
  ~ScriptCameraEntity() override;
  void onActivate() override;
  void update(const fw::UpdateInfo &info) override;
  void calcSpeedTypeLinearSpacing();
  void move(const mm::Vec3 &position, const mm::Vec3 &rotation, f32 time);
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;

  u8 _a8[0xb0 - 0xa8];
  mm::Vec3 unknownb0;  // Inferred role: position at the start of the move; original member name unknown.
  mm::Vec3 unknownc0;  // Inferred role: rotation at the start of the move; original member name unknown.
  mm::Vec3 unknownd0;  // Inferred role: position at the end of the move; original member name unknown.
  mm::Vec3 unknowne0;  // Inferred role: rotation at the end of the move; original member name unknown.
  mm::Vec3 unknownf0;  // Inferred role: position; original member name unknown.
  mm::Vec3 unknown100; // Inferred role: rotation; original member name unknown.
  f32 unknown110;      // Inferred role: move time; original member name unknown.
  f32 unknown114;      // Inferred role: elapsed move time; original member name unknown.
  u8 _118[0x120 - 0x118];
};

class ScriptCamera {
public:
  ScriptCamera();
  virtual ~ScriptCamera();
  void start(const mm::Vec3 &position, const mm::Vec3 &rotation, f32 time);
  void end(f32 time);
  void move(const mm::Vec3 &position, const mm::Vec3 &rotation, f32 time);

  mm::mtl::IntrusivePtr<fw::Camera> unknown08; // Inferred role: script camera; original member name unknown.
};

static_assert(offsetof(ScriptCamera, unknown08) == 0x08, "");
static_assert(sizeof(ScriptCamera) == 0x10, "");

static_assert(offsetof(ScriptCameraEntity, unknownb0) == 0xb0, "");
static_assert(offsetof(ScriptCameraEntity, unknownf0) == 0xf0, "");
static_assert(offsetof(ScriptCameraEntity, unknown100) == 0x100, "");
static_assert(offsetof(ScriptCameraEntity, unknown110) == 0x110, "");
static_assert(sizeof(ScriptCameraEntity) == 0x120, "");

} // namespace gf
