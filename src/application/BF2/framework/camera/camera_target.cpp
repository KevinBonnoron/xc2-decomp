#include "fw/fw_camera.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

const mm::mtl::RTTI *CameraTarget::getRTTI() const { return &m_rtti; }

void CameraTarget::requestResetCamera() {}

} // namespace fw
