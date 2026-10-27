#include "dr/dr_res_mdo_lod_obj.h"

namespace ml {

DrResMdoLodObj::~DrResMdoLodObj() {}

void DrResMdoLodObj::release(DrResMdoLodObj *&lodObj) {
  if (lodObj != nullptr) {
    lodObj = nullptr;
  }
}

} // namespace ml
