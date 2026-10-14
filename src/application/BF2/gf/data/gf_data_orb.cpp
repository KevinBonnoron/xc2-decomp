#include "gf/data/gf_data_orb.h"
#include "gf/data/gf_bdat_item.h"

namespace gf {

u32 GfDataOrb::getEnhance(u32 orb) {
  if (orb == 0) {
    return 0;
  }

  return GfBdatItem::get()->getEquipOrbEnhance(orb);
}

} // namespace gf
