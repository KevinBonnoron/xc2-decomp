#include "ml/cam_util.h"

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

namespace ml {

void CamUtil::getViewLocalToDeviceCoord(mm::Vec3 &device, const mm::Mat44 &matrix, const mm::Vec3 &viewLocal) {
  device.x = matrix.rows[0][0] * (viewLocal.x / viewLocal.z) - matrix.rows[2][0];
  device.y = matrix.rows[1][1] * (viewLocal.y / viewLocal.z) - matrix.rows[2][1];
  device.z = -matrix.rows[3][2] / viewLocal.z - matrix.rows[2][2];
}

void CamUtil::getDeviceCoordToViewLocal(mm::Vec3 &viewLocal, const mm::Mat44 &matrix, const mm::Vec3 &device) {
  viewLocal.z = -matrix.rows[3][2] / (device.z + matrix.rows[2][2]);
  viewLocal.x = viewLocal.z * ((device.x + matrix.rows[2][0]) / matrix.rows[0][0]);
  viewLocal.y = ((device.y + matrix.rows[2][1]) / matrix.rows[1][1]) * viewLocal.z;
}

} // namespace ml
