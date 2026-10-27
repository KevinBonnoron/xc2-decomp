#include "gf/field/gf_dropitem_params.h"

namespace gf {

void GfDropitemParams::create() {
  dispose();
  update();
}

void GfDropitemParams::dispose() {
  unknown30 = 0;
  unknown08.clear();
}

bool GfDropitemParams::isBdatIdValid(u32 bdatId) const {
  if (bdatId < unknown30) {
    return false;
  }
  return bdatId - unknown30 < unknown08.size();
}

} // namespace gf
