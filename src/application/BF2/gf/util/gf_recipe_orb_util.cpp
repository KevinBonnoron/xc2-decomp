#include "gf/util/gf_recipe_orb_util.h"
#include "gf/data/gf_bdat_item.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

u32 GfRecipeOrbUtil::getRecipeID(u32 id) { return GfBdatItem::get()->getEmptyOrbRecipe(id); }

u32 GfRecipeOrbUtil::getEquipOrb(u32 id) { return GfBdatItem::get()->getEmptyOrbEquipItemID(id); }

bool GfRecipeOrbUtil::isEnableRecipe(u32 id) {
  mm::mtl::FixedVector<OrbRecipe, 128> items;
  return getRecipeItemsByItemBox(items, id);
}

} // namespace gf
