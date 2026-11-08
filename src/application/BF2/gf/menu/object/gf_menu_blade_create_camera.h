#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfMenuBladeCreateCamera : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  GfMenuBladeCreateCamera();
  ~GfMenuBladeCreateCamera() override;
  void update(const fw::UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;
  void setRotY(f32 rot, u32 direction, f32 duration);
  void setRotOffsetY(f32 offset);
  void setDefault(const mm::Vec3 &position, const mm::Vec3 &target);
  void getDefault(mm::Vec3 &position, mm::Vec3 &target);
  void getCurrent(mm::Vec3 &position, mm::Vec3 &target);

  u8 _a8[0xb0 - 0xa8];
  mm::Vec3 unknownb0; // Inferred role: default position; original member name unknown.
  mm::Vec3 unknownc0; // Inferred role: default target; original member name unknown.
  mm::Vec3 unknownd0; // Inferred role: current position; original member name unknown.
  mm::Vec3 unknowne0; // Inferred role: current target; original member name unknown.
  f32 unknownf0;      // Inferred role: rotation duration; original member name unknown.
  f32 unknownf4;      // Inferred role: rotation elapsed time; original member name unknown.
  f32 m_rotOffsetY;
  f32 unknownfc;  // Inferred role: current rotation; original member name unknown.
  f32 unknown100; // Inferred role: target rotation; original member name unknown.
  f32 unknown104; // Inferred role: start rotation; original member name unknown.
  u32 unknown108; // Inferred role: rotation direction; original member name unknown.
  u8 _10c[0x110 - 0x10c];
};

static_assert(offsetof(GfMenuBladeCreateCamera, unknownb0) == 0xb0, "");
static_assert(offsetof(GfMenuBladeCreateCamera, unknownc0) == 0xc0, "");
static_assert(offsetof(GfMenuBladeCreateCamera, unknownd0) == 0xd0, "");
static_assert(offsetof(GfMenuBladeCreateCamera, unknowne0) == 0xe0, "");
static_assert(offsetof(GfMenuBladeCreateCamera, unknownf0) == 0xf0, "");
static_assert(offsetof(GfMenuBladeCreateCamera, unknownf4) == 0xf4, "");
static_assert(offsetof(GfMenuBladeCreateCamera, m_rotOffsetY) == 0xf8, "");
static_assert(offsetof(GfMenuBladeCreateCamera, unknownfc) == 0xfc, "");
static_assert(offsetof(GfMenuBladeCreateCamera, unknown100) == 0x100, "");
static_assert(offsetof(GfMenuBladeCreateCamera, unknown104) == 0x104, "");
static_assert(offsetof(GfMenuBladeCreateCamera, unknown108) == 0x108, "");
static_assert(sizeof(GfMenuBladeCreateCamera) == 0x110, "");

} // namespace gf
