#include "gf/camera/gf_camera_utilities.h"

#include <math.h>

#include "fw/fw_transform.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {

// Height added to the position of the object when it has no camera bone.
constexpr f32 unknown016 = 1.5f; // Inferred role: camera look height; original name unknown.

void CameraUtilities::getCameraLookBonePosition(GF_OBJ_HANDLE *handle, mm::Vec3 &position) {
  GfObjAcc acc(handle);
  position = acc.getWorldTransform().unknown00;
  position.y += unknown016;
  DataParamAcc dataParam(handle);
  const char *bone = dataParam.getCamBone();
  fw::Transform transform;
  if (bone != nullptr && acc.getBoneTransform(transform, bone)) {
    position = transform.unknown00;
  }
}

bool CameraUtilities::getRotateAxis(const mm::Vec3 &from, const mm::Vec3 &to, mm::Vec3 &axis) {
  axis.unknown004(to, from);
  if (!(fabsf(axis.x) <= 0.000001f) || !(fabsf(axis.y) <= 0.000001f) || !(fabsf(axis.z) <= 0.000001f)) {
    axis.unknown001();
  }
  return true;
}

} // namespace gf
