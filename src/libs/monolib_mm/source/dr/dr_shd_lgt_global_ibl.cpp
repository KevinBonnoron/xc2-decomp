#include "dr/dr_shd_lgt_global_ibl.h"

#include "dr/dr_light_obj_global_ibl.h"
#include "types.h"

namespace ml {

namespace _dr_shd_lgt_glb_ibl {

bool CompareByPriority(const DrLightObjGlobalIBL *a, const DrLightObjGlobalIBL *b) {
  u32 priorityA = a->getPriority();
  u32 priorityB = b->getPriority();
  return priorityA > priorityB;
}

} // namespace _dr_shd_lgt_glb_ibl

void DrShdLgtGlobalIBL::delViewInfo(int viewNum) {}

} // namespace ml
