#include "dr/dr_pixl_mdl_sampler.h"

namespace ml {

DrPixlMdlSampler::DrPixlMdlSampler() : unknown00(4), unknown04(1), unknown08(false), unknown0c(4), unknown10(1), unknown14(false) {}

bool DrPixlMdlSampler::update() {
  if (unknown00 == unknown0c && unknown04 == unknown10 && unknown08 == unknown14) {
    return false;
  }
  unknown00 = unknown0c;
  unknown04 = unknown10;
  unknown08 = unknown14;
  return true;
}

} // namespace ml
