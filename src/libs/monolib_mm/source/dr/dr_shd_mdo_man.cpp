#include "dr/dr_shd_mdo_man.h"

#include "dr/dr_shd_mdo_dec_shd_obj.h"

namespace ml {

DrShdMdoMan::DrShdMdoMan() : unknown00(nullptr), unknown08(nullptr) {}

void DrShdMdoMan::update() {
  for (DrShdMdoDecShdObj *obj = unknown00; obj != nullptr; obj = obj->unknown08) {
    obj->update();
  }
}

} // namespace ml
