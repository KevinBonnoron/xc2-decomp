#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "gf/camera/gimmick/gf_camera_gimmick_params.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

// Evidence: size 0xd0 from the operator new in GfMenuModelView::addCamera; the constructor copies the position and the rotation of the parameter to 0xb0 and 0xc0.
class GfMenuModelViewCamera : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  GfMenuModelViewCamera(const GimmickCameraParams::Param &param);
  ~GfMenuModelViewCamera() override;
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;
  void updateLookAt();
  void setPos(const mm::Vec3 &position);
  void setRotY(f32 rotation);

  mm::Vec3 unknownb0; // Inferred role: position; original member name unknown.
  mm::Vec3 unknownc0; // Inferred role: rotation; original member name unknown.
};

static_assert(offsetof(GfMenuModelViewCamera, unknownb0) == 0xb0, "");
static_assert(offsetof(GfMenuModelViewCamera, unknownc0) == 0xc0, "");
static_assert(sizeof(GfMenuModelViewCamera) == 0xd0, "");

} // namespace gf
