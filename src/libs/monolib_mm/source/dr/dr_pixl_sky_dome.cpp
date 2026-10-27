#include "dr/dr_pixl_sky_dome.h"

#include "dr/dr_res_use_query_obj.h"

namespace ml {

DrPixlSkyDome::~DrPixlSkyDome() {
  if (unknown08 != nullptr) {
    delete unknown08;
    unknown08 = nullptr;
  }
}

void DrPixlSkyDome::renderBackgroundCube() {}

} // namespace ml
