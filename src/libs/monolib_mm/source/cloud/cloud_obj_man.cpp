#include "cloud/cloud_obj_man.h"

#include "cloud/cloud_calc_params.h"
#include "cloud/cloud_obj.h"
#include "cloud/cloud_obj_reduction.h"

// setMainRenderTarget is inlined by the game in alphaRender; keep its definition visible in this unit.
#include "cloud_calc_params.cpp"

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
