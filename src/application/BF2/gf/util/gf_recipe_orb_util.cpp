#include "gf/util/gf_recipe_orb_util.h"

#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_data_item.h"
#include "gf/event/gf_event.h"
#include "gf/game/item/gf_item_box.h"
#include "gf/util/gf_util.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {

// Inferred role: predicate of isExistItem, an item with the same id and at least the count; original name unknown.
struct unknown001 {
  unknown001(u16 id, u16 count) : unknown00(id), unknown02(count) {}

  bool operator()(const OrbRecipe &item) const { return item.unknown00 == unknown00 && item.unknown02 >= unknown02; }

  u16 unknown00; // Inferred role: item id; original member name unknown.
  u16 unknown02; // Inferred role: item count; original member name unknown.
};

const OrbRecipe *RecipeInfo::getResultRarity() const { return &m_resultRarity; }

const OrbRecipe *RecipeInfo::getResultColleCategory() const { return &m_resultColleCategory; }

const mm::mtl::FixedVector<OrbRecipe, 8> *RecipeInfo::getResultItems() const { return &m_resultItems; }

bool GfRecipeOrbUtil::isEnabaleOrbRecipeCategory(u32 recipe, const mm::mtl::FixedVector<OrbRecipe, 128> &items) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 category = bdatItem->getOrbRecipeRscCat(recipe);
  u32 assort = bdatItem->getOrbRecipeAssortNumber(recipe);
  if (assort == 0) {
    return true;
  }
  u32 total = 0;
  for (const OrbRecipe *item = items.begin(); item != items.end(); item++) {
    if (bdatItem->getCollectionListCategory(item->unknown00) == category) {
      total += item->unknown02;
      if (total >= assort) {
        return true;
      }
    }
  }
  return false;
}

bool GfRecipeOrbUtil::isEnabaleOrbRecipeRare(u32 recipe, const mm::mtl::FixedVector<OrbRecipe, 128> &items) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 assort = bdatItem->getOrbRecipeAssortNumber(recipe);
  u32 rarity = bdatItem->getOrbRecipeRarity(recipe);
  u32 total = 0;
  for (const OrbRecipe *item = items.begin(); item != items.end(); item++) {
    if (bdatItem->getCollectionListRarity(item->unknown00) == rarity) {
      total += item->unknown02;
      if (total >= assort) {
        return true;
      }
    }
  }
  return false;
}

bool GfRecipeOrbUtil::isExistItem(const mm::mtl::FixedVector<OrbRecipe, 128> &items, u32 id, u32 count) {
  const OrbRecipe *item = mm::mtl::find_if(items.begin(), items.end(), unknown001(id, count));
  return item != items.end();
}

u32 GfRecipeOrbUtil::getRecipeID(u32 id) { return GfBdatItem::get()->getEmptyOrbRecipe(id); }

u32 GfRecipeOrbUtil::getEquipOrb(u32 id) { return GfBdatItem::get()->getEmptyOrbEquipItemID(id); }

bool GfRecipeOrbUtil::getRecipeInfo(RecipeInfo &info, u32 id) {
  if (id == 0) {
    return false;
  }

  GfBdatItem *bdatItem = GfBdatItem::get();
  info.unknown00 = 0;
  info.unknown04 = 0;
  info.m_resultRarity.unknown00 = 0;
  info.m_resultRarity.unknown02 = 0;
  info.m_resultColleCategory.unknown00 = 0;
  info.m_resultColleCategory.unknown02 = 0;
  info.m_resultItems.clear();
  info.unknown00 = id;
  info.unknown04 = bdatItem->getOrbRecipeRecipeType(id);
  switch (info.unknown04) {
  case 0:
    info.m_resultRarity.unknown00 = bdatItem->getOrbRecipeRarity(id);
    info.m_resultRarity.unknown02 = bdatItem->getOrbRecipeAssortNumber(id);
    break;
  case 1:
    info.m_resultColleCategory.unknown00 = bdatItem->getOrbRecipeRscCat(id);
    info.m_resultColleCategory.unknown02 = bdatItem->getOrbRecipeAssortNumber(id);
    break;
  case 2:
    for (u32 i = 0; i < 8; i++) {
      u32 item = bdatItem->getOrbRecipeItemID(id, i);
      if (item != 0) {
        info.m_resultItems.push_back(OrbRecipe{static_cast<u16>(item), static_cast<u16>(bdatItem->getOrbRecipeItemNumber(id, i))});
      }
    }
    break;
  default:
    return false;
  }
  return true;
}

void GfRecipeOrbUtil::execOrbRecipe(u32 item, const mm::mtl::FixedVector<OrbRecipe, 128> *items) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 recipe = bdatItem->getEmptyOrbRecipe(item);
  mm::mtl::FixStr<128> name;
  name = util::debugUTF8ToSJIS(GfDataItem::getName(item));
  mm::mtl::FixedVector<OrbRecipe, 128> boxItems;
  if (items == nullptr) {
    getRecipeItemsByItemBox(boxItems, recipe);
    items = &boxItems;
  }
  isEnabaleOrbRecipe(recipe, *items);
  u32 orb = bdatItem->getEmptyOrbEquipItemID(item);
  GfBdatItem *orbBdatItem = GfBdatItem::get();
  GfDataItem::getItemType(item);
  if (orbBdatItem->getEmptyOrbRecipe(item) != 0) {
    for (const OrbRecipe *recipeItem = items->begin(); recipeItem != items->end(); recipeItem++) {
      u32 recipeItemId = recipeItem->unknown00;
      if (recipeItemId != 0) {
        u32 recipeItemNumber = recipeItem->unknown02;
        if (recipeItemNumber != 0 && GfItemBox::decItem(recipeItemId, recipeItemNumber)) {
          GfEvent::callItemAdd(recipeItemId, -recipeItemNumber);
        }
      }
    }
  }
  if (GfItemBox::decItem(item, 1)) {
    GfEvent::callItemAdd(item, -1);
  }
  if (!GfDataItem::isNoMultiple(orb) && GfItemBox::addItem(orb, 1)) {
    GfDataItem::setNoMultiple(orb, true);
    GfEvent::callItemAdd(orb, 1);
  }
}

bool GfRecipeOrbUtil::isEnableRecipe(u32 id) {
  mm::mtl::FixedVector<OrbRecipe, 128> items;
  return getRecipeItemsByItemBox(items, id);
}

} // namespace gf
