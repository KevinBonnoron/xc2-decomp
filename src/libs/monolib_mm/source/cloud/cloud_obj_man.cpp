#include "cloud/cloud_obj_man.h"

#include "cloud/cloud_calc_params.h"
#include "cloud/cloud_obj.h"
#include "cloud/cloud_obj_reduction.h"

// setMainRenderTarget is inlined by the game in alphaRender; keep its definition visible in this unit.
#include "cloud_calc_params.cpp"
// The game builds the cloud object files in one unit (0x71007b68b4 to 0x71007c1694), in this order: CloudCalcParams, CloudObjFlow (0x71007b761c), CloudObjMan (0x71007b87e0), the other objects,
// CloudObjReduction (0x71007bfe10) and CloudUniform (0x71007c0c9c). Functions of the last two also sit after their first callers earlier in the unit (CloudUniform::createUniform at 0x71007b6ce8).
#include "cloud_obj_flow.cpp"

namespace cloud {

bool CloudObjMan::isRender() const {
  if (unknown38->unknown420 == nullptr) {
    return false;
  }
  return unknown58;
}

void CloudObjMan::alphaRender(const ml::IDrDrawWorkInfo *workInfo) {
  unknown40->alphaFastRender();
  for (CloudObj *object = unknown00; object != nullptr; object = object->unknown10) {
    object->alphaRender();
  }
  for (CloudObj *object = unknown00; object != nullptr; object = object->unknown10) {
    object->alphaRenderSec();
  }
  unknown38->setMainRenderTarget();
}

} // namespace cloud

#include "cloud_obj_reduction.cpp"
#include "cloud_uniform.cpp"
