#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "gf/object/gf_init_param.h"
#include "mm_math/mm_vec3.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class SubViewCamera : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  ~SubViewCamera() override;
  void onActivate() override;
  void update(const fw::UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;

  VIEWCAM unknowna8;  // Inferred role: view camera; original member name unknown.
  mm::Vec3 unknownb0; // Inferred role: position; original member name unknown.
  mm::Vec3 unknownc0; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(SubViewCamera, unknowna8) == 0xa8, "");
static_assert(offsetof(SubViewCamera, unknownb0) == 0xb0, "");
static_assert(offsetof(SubViewCamera, unknownc0) == 0xc0, "");
static_assert(sizeof(SubViewCamera) == 0xd0, "");

} // namespace gf
