#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "mm_math/mm_vec3.h"

namespace gf {

class GfGameFallDeadCamera : public fw::Camera {
public:
  GfGameFallDeadCamera();
  ~GfGameFallDeadCamera() override;
  void onActivate() override;
  void update(const fw::UpdateInfo &info) override;

  mm::Vec3 unknownb0; // Inferred role: offset from the player to the target; original member name unknown.
  mm::Vec3 unknownc0; // Inferred role: position; original member name unknown.
  mm::Vec3 unknownd0; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(GfGameFallDeadCamera, unknownb0) == 0xb0, "");
static_assert(offsetof(GfGameFallDeadCamera, unknownc0) == 0xc0, "");
static_assert(offsetof(GfGameFallDeadCamera, unknownd0) == 0xd0, "");

} // namespace gf
