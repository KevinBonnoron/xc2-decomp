#include "event/chara_tar_util.h"

#include <math.h>

#include "bdat.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"

namespace event {

mm::Vec3 CharaTarUtil::getCharaDefaultEyeVec(gf::GF_OBJ_HANDLE *handle) {
  if (handle != gf::unknown020) {
    switch (gf::GfObjUtil::getEyeRotControl(handle)) {
    case 1:
    case 4:
    case 6:
    case 7:
      return mm::Vec3(1.0f, 0.0f, 0.0f);
    }
  }
  return mm::Vec3(0.0f, 1.0f, 0.0f);
}

f32 CharaTarUtil::getCharaEyeRotY(gf::GF_OBJ_HANDLE *handle) { return mm::quatToEuler(gf::GfObjUtil::getObj(handle)->getComponent<gf::GfComTransform>()->getRotation()).y; }

mm::Vec3 CharaTarUtil::calcWeight(const mm::Vec3 &position, const mm::Vec3 &target, f32 rotation) {
  mm::Vec3 diff = target - position;
  f32 yaw = -atan2f(diff.x, -diff.z) - rotation;
  f32 pitch = atan2f(diff.y, sqrtf(diff.x * diff.x + diff.z * diff.z));
  while (pitch < -3.1415927f) {
    pitch += 6.2831855f;
  }
  while (pitch > 3.1415927f) {
    pitch -= 6.2831855f;
  }
  while (yaw < -3.1415927f) {
    yaw += 6.2831855f;
  }
  while (yaw > 3.1415927f) {
    yaw -= 6.2831855f;
  }
  mm::clampRef(pitch, -0.5235988f, 0.5235988f);
  mm::clampRef(yaw, -1.5707964f, 1.5707964f);
  mm::Vec3 weight(pitch / 0.5235988f, yaw / 1.5707964f, 0.0f);
  mm::clampRef(weight.x, -1.0f, 1.0f);
  mm::clampRef(weight.y, -1.0f, 1.0f);
  return weight;
}

const char *CharaTarUtil::aimmotType2stat(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_aimmottype"), "stat", type, 7)); }

const char *CharaTarUtil::aimmotType2name(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_aimmottype"), "name", type, 7)); }

} // namespace event
