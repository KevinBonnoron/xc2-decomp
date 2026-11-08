#include "gf/menu/model_view/gf_menu_model_view_camera.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_MENU_MODEL_VIEW = static_cast<fw::CAMERA_PRIO>(55);

GfMenuModelViewCamera::GfMenuModelViewCamera(const GimmickCameraParams::Param &param) : fw::Camera(CAMERA_PRIO_MENU_MODEL_VIEW) {
  unknownb0 = mm::Vec3(param.unknown00, param.unknown04, param.unknown08);
  unknownc0 = mm::Vec3(param.unknown0c, param.unknown10, param.unknown14);
  updateLookAt();
}

GfMenuModelViewCamera::~GfMenuModelViewCamera() { ; }

void GfMenuModelViewCamera::setPos(const mm::Vec3 &position) {
  unknownb0 = position;
  updateLookAt();
}

void GfMenuModelViewCamera::setRotY(f32 rotation) {
  unknownc0.y = rotation;
  updateLookAt();
}

const mm::mtl::RTTI *GfMenuModelViewCamera::getRTTI() const { return &m_rtti; }

const char *GfMenuModelViewCamera::getName() const { return "GfMenuModelViewCamera"; }

} // namespace gf
