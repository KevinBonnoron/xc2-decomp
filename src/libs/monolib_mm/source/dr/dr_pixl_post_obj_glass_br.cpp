#include "dr/dr_pixl_post_obj_glass_br.h"

#include "dr/dr_ap_gx_type.h"
#include "mtl/mem_manager.h"

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;

DrPixlPostObjGlassBr::DrPixlPostObjGlassBr(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
  unknown4f8 = nullptr;
  unknown4e0 = nullptr;
  unknown508 = 3;
  unknown4e8 = 0;
  unknown50c = 0;
}

void DrPixlPostObjGlassBr::render() {
  if ((unknown508 & FLAG_UNKNOWN_2) == 0) {
    DrAPGxType::setupScreenQuads(false);
    renderCaputre();
    renderGlass();
  }
}

void DrPixlPostObjGlassBr::release() {
  unknown98.release();
  unknown18.release();
  unknown40.release();
  unknown68.release();
  unknown460.release();
  if (unknown4f8 != nullptr) {
    mtl::MemManager::deallocate(unknown4f8, 0, false);
    unknown4f8 = nullptr;
  }
  unknown508 = 3;
}

DrPixlPostObjGlassBr::~DrPixlPostObjGlassBr() { release(); }

} // namespace ml
