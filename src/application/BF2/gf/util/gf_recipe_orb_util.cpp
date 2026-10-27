#include "gf/util/gf_recipe_orb_util.h"
#include "gf/data/gf_bdat_item.h"

namespace gf {

u32 GfRecipeOrbUtil::getRecipeID(u32 id) { return GfBdatItem::get()->getEmptyOrbRecipe(id); }

u32 GfRecipeOrbUtil::getEquipOrb(u32 id) { return GfBdatItem::get()->getEmptyOrbEquipItemID(id); }

} // namespace gf
