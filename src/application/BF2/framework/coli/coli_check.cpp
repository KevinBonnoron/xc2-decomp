#include "framework/coli/coli_manager.h"
#include "fw/fw_coli_check.h"
#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace fw {
class ColiObject;

ColiObject *ColiCheck::getObjectFromUserData(u32 handle) {
  if (handle != 0) {
    return ColiManager::get()->getObject(handle);
  }

  return nullptr;
}

bool ColiCheck::moveColi(mm::Vec3 &result, const mm::Vec3 &position, const mm::Vec3 &move) {
  idcoli::IDColiMove coliMove;
  if (coliMove.moveColi(position, move)) {
    result = coliMove.unknown130;
    return true;
  }

  result = mm::Vec3::zero;
  return false;
}

} // namespace fw
