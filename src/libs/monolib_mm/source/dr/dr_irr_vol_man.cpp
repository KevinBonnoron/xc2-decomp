#include "dr/dr_irr_vol_man.h"

namespace ml {

bool DrIrrVolMan::isValid() const {
  if (unknown08 == nullptr) {
    return false;
  }
  return unknown98 != nullptr;
}

void DrIrrVolMan::debugRender() {}

} // namespace ml
