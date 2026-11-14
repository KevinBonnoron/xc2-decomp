#include "gf/menu/list/gf_menu_item_list.h"

#include <functional>

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/list/gf_menu_sort_type.h"
#include "gf/request/gf_req_scom.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/vector.h"

namespace gf {

namespace {

// Inferred role: compares the key of two items of one type, ties broken by item id; original name unknown.
template <typename T> bool unknown001(const MenuItemInfo &info, const MenuItemInfo &other, ItemType::Type type, T ItemProperty::*key, bool ascending) {
  ItemProperty property;
  ItemProperty otherProperty;
  GfItemUtil::getProperty(property, info.unknown04, 0);
  GfItemUtil::getProperty(otherProperty, other.unknown04, 0);
  if (property.unknown08 == type) {
    if (otherProperty.unknown08 == type) {
      if (property.*key == otherProperty.*key) {
        return info.unknown04 < other.unknown04;
      }
      if (ascending) {
        return property.*key < otherProperty.*key;
      }
      return property.*key > otherProperty.*key;
    }
    return true;
  }
  return false;
}

// Inferred role: compares the enhance category of the equipped items of two empty orbs, ties broken by item id; original name unknown.
template <bool Ascending> bool unknown002(const MenuItemInfo &info, const MenuItemInfo &other) {
  ItemProperty property;
  ItemProperty otherProperty;
  GfItemUtil::getProperty(property, info.unknown04, 0);
  GfItemUtil::getProperty(otherProperty, other.unknown04, 0);
  if (property.unknown08 == ItemType::ITEM_TYPE_UNKNOWN_9) {
    if (otherProperty.unknown08 == ItemType::ITEM_TYPE_UNKNOWN_9) {
      GfItemUtil::getProperty(property, property.unknown56, 0);
      GfItemUtil::getProperty(otherProperty, otherProperty.unknown56, 0);
      if (property.unknown4c == otherProperty.unknown4c) {
        return info.unknown04 < other.unknown04;
      }
      if (Ascending) {
        return property.unknown4c < otherProperty.unknown4c;
      }
      return property.unknown4c > otherProperty.unknown4c;
    }
    return true;
  }
  return false;
}

// Inferred role: compares the sort key name column of two items, ties broken by item id; original name unknown.
template <bool Ascending> bool unknown003(const MenuItemInfo &info, const MenuItemInfo &other) {
  const char *name = GfMenuBdat::getSortKeyName();
  u32 key;
  u32 otherKey;
  if (name == nullptr) {
    key = info.unknown04;
    otherKey = other.unknown04;
  } else {
    key = Bdat::getVal(GfMenuBdat::getItemDataFP(info.unknown00, info.unknown04), name, info.unknown04).valueU32;
    otherKey = Bdat::getVal(GfMenuBdat::getItemDataFP(other.unknown00, other.unknown04), name, other.unknown04).valueU32;
  }
  if (key == otherKey) {
    return info.unknown04 < other.unknown04;
  }
  if (Ascending) {
    return key < otherKey;
  }
  return key > otherKey;
}

} // namespace

GfMenuItemList::GfMenuItemList() {}

GfMenuItemList::~GfMenuItemList() { ; }

GfMenuItemList *GfMenuItemList::create() {
  // __LINE__ must be 55 as in the original source: it is the line argument of operator new.
#line 55
  GfMenuItemList *list = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuItemList();
  list->addRef();
  return list;
}

void GfMenuItemList::sort(u32 type, bool ascending) {
  if (getSize() == 0) {
    return;
  }
  std::function<bool(const MenuItemInfo &, const MenuItemInfo &)> compare;
  switch (type) {
  case unknown093_1: {
    u32 *times = new (getAllocator(ALLOCATOR_UNKNOWN_0), nullptr, 0, 8) u32[getSize()];
    for (u32 i = 0; i < getSize(); i++) {
      times[i] = GfItemUtil::getItemTime(getContents(i).unknown04, getContents(i).unknown0c);
      getContents(i).unknown0a = i;
    }
    if (ascending) {
      UIListInfo<MenuItemInfo>::sort([times](const MenuItemInfo &info, const MenuItemInfo &other) {
        u32 time = times[info.unknown0a];
        u32 otherTime = times[other.unknown0a];
        if (time == otherTime) {
          return info.unknown04 < other.unknown04;
        }
        return time < otherTime;
      });
    } else {
      UIListInfo<MenuItemInfo>::sort([times](const MenuItemInfo &info, const MenuItemInfo &other) {
        u32 time = times[info.unknown0a];
        u32 otherTime = times[other.unknown0a];
        if (time == otherTime) {
          return info.unknown04 < other.unknown04;
        }
        return time > otherTime;
      });
    }
    delete[] times;
    return;
  }
  case unknown093_2:
    compare = ascending ? sortNameDescending : sortNameAscending;
    break;
  case unknown093_3:
    compare = ascending ? sortRareAscending : sortRareDescending;
    break;
  case unknown093_7:
    compare = ascending ? sortSellPriceAscending : sortSellPriceDescending;
    break;
  case unknown093_8:
    compare = ascending ? sortFavoriteTimeAscending : sortFavoriteTimeDescending;
    break;
  case unknown093_9:
    switch (GfItemUtil::getType(getContents(0).unknown04)) {
    case ItemType::ITEM_TYPE_UNKNOWN_3:
      compare = ascending ? sortTypeAsCoreEquipAscending : sortTypeAsCoreEquipDescending;
      break;
    case ItemType::ITEM_TYPE_UNKNOWN_7:
      compare = ascending ? sortTypeCollectionAscending : sortTypeCollectionDescending;
      break;
    case ItemType::ITEM_TYPE_UNKNOWN_8:
      compare = ascending ? sortTypeTreasureAscending : sortTypeTreasureDescending;
      break;
    case ItemType::ITEM_TYPE_UNKNOWN_9:
      compare = ascending ? sortTypeAsCoreAscending : sortTypeAsCoreDescending;
      break;
    case ItemType::ITEM_TYPE_UNKNOWN_10:
      compare = ascending ? sortTypeFavoriteAscending : sortTypeFavoriteDescending;
      break;
    case ItemType::ITEM_TYPE_UNKNOWN_12:
      compare = ascending ? sortTypeBoosterAscending : sortTypeBoosterDescending;
      break;
    default:
      break;
    }
    break;
  case unknown093_10:
    compare = ascending ? sortWpnRankAscending : sortWpnRankDescending;
    break;
  case unknown093_12:
    compare = ascending ? sortGetAreaAscending : sortGetAreaDescending;
    break;
  case unknown093_13:
    compare = ascending ? sortIdAscending : sortIdDescending;
    break;
  default:
    return;
  }
  UIListInfo<MenuItemInfo>::sort(compare);
}

bool GfMenuItemList::sortRareAscending(const MenuItemInfo &info, const MenuItemInfo &other) {
  u32 rarity = getSortRarity(info);
  u32 otherRarity = getSortRarity(other);
  if (rarity == otherRarity) {
    return info.unknown04 < other.unknown04;
  }
  return rarity < otherRarity;
}

bool GfMenuItemList::sortRareDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  u32 rarity = getSortRarity(info);
  u32 otherRarity = getSortRarity(other);
  if (rarity == otherRarity) {
    return info.unknown04 < other.unknown04;
  }
  return rarity > otherRarity;
}

bool GfMenuItemList::sortSellPriceAscending(const MenuItemInfo &info, const MenuItemInfo &other) {
  ItemPrice price;
  ItemPrice otherPrice;
  price.clear();
  otherPrice.clear();
  GfItemUtil::getPrice(price, info.unknown04, 0);
  GfItemUtil::getPrice(otherPrice, other.unknown04, 0);
  if (price.unknown08 == otherPrice.unknown08) {
    return info.unknown04 < other.unknown04;
  }
  return price.unknown08 < otherPrice.unknown08;
}

bool GfMenuItemList::sortSellPriceDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  ItemPrice price;
  ItemPrice otherPrice;
  price.clear();
  otherPrice.clear();
  GfItemUtil::getPrice(price, info.unknown04, 0);
  GfItemUtil::getPrice(otherPrice, other.unknown04, 0);
  if (price.unknown08 == otherPrice.unknown08) {
    return info.unknown04 < other.unknown04;
  }
  return price.unknown08 > otherPrice.unknown08;
}

bool GfMenuItemList::sortGetAreaAscending(const MenuItemInfo &info, const MenuItemInfo &other) {
  u32 area;
  u32 otherArea;
  if (info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_8) {
    u8 *bdat = GfDataBdat::getFP(BDAT_ITM_TRESURE_LIST);
    area = Bdat::getVal(bdat, "Zone", info.unknown04).valueU16;
    otherArea = Bdat::getVal(bdat, "Zone", other.unknown04).valueU16;
  } else {
    area = info.unknown04;
    otherArea = other.unknown04;
  }
  if (area == otherArea) {
    return info.unknown04 < other.unknown04;
  }
  return area < otherArea;
}

bool GfMenuItemList::sortGetAreaDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  u32 area;
  u32 otherArea;
  if (info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_8) {
    u8 *bdat = GfDataBdat::getFP(BDAT_ITM_TRESURE_LIST);
    area = Bdat::getVal(bdat, "Zone", info.unknown04).valueU16;
    otherArea = Bdat::getVal(bdat, "Zone", other.unknown04).valueU16;
  } else {
    area = info.unknown04;
    otherArea = other.unknown04;
  }
  if (area == otherArea) {
    return info.unknown04 < other.unknown04;
  }
  return area > otherArea;
}

bool GfMenuItemList::sortNameAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown003<true>(info, other); }

bool GfMenuItemList::sortNameDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown003<false>(info, other); }

bool GfMenuItemList::sortTypeAsCoreEquipAscending(const MenuItemInfo &info, const MenuItemInfo &other) {
  return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_3, &ItemProperty::unknown4c, true);
}

bool GfMenuItemList::sortTypeAsCoreEquipDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_3, &ItemProperty::unknown4c, false);
}

bool GfMenuItemList::sortTypeBoosterAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_12, &ItemProperty::unknown45, true); }

bool GfMenuItemList::sortTypeBoosterDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_12, &ItemProperty::unknown45, false); }

bool GfMenuItemList::sortWpnRankAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_1, &ItemProperty::unknown64, true); }

bool GfMenuItemList::sortWpnRankDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_1, &ItemProperty::unknown64, false); }

bool GfMenuItemList::sortTypeAsCoreAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown002<true>(info, other); }

bool GfMenuItemList::sortTypeAsCoreDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown002<false>(info, other); }

bool GfMenuItemList::sortTypeCollectionAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_7, &ItemProperty::unknown4d, true); }

bool GfMenuItemList::sortTypeCollectionDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_7, &ItemProperty::unknown4d, false);
}

bool GfMenuItemList::sortTypeFavoriteAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_10, &ItemProperty::unknown4e, true); }

bool GfMenuItemList::sortTypeFavoriteDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_10, &ItemProperty::unknown4e, false);
}

bool GfMenuItemList::sortTypeTreasureAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_8, &ItemProperty::unknown5d, true); }

bool GfMenuItemList::sortTypeTreasureDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_8, &ItemProperty::unknown5d, false); }

bool GfMenuItemList::sortFavoriteTimeAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_10, &ItemProperty::unknown52, true); }

bool GfMenuItemList::sortFavoriteTimeDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  return unknown001(info, other, ItemType::ITEM_TYPE_UNKNOWN_10, &ItemProperty::unknown52, false);
}

bool GfMenuItemList::sortIdAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return info.unknown04 < other.unknown04; }

bool GfMenuItemList::sortIdDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return info.unknown04 > other.unknown04; }

bool GfMenuItemList::isValidItem(const MenuItemInfo &info) { return info.unknown04 != 0 && info.unknown08 > 0; }

u32 GfMenuItemList::getSortRarity(const MenuItemInfo &info) {
  if (info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_6 || info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_14 || info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_15) {
    return 0;
  }
  return GfDataItem::getRarity(info.unknown04);
}

void GfMenuItemList::filterRarity(const FiltertInfo &filter) {
  for (u32 i = 0; i < getSize();) {
    MenuItemInfo info = getContents(i);
    if (GfDataItem::getRarity(info.unknown04) == filter.unknown04) {
      i++;
    } else {
      decItem(info, false);
    }
  }
}

void GfMenuItemList::filterRarityMore(const FiltertInfo &filter) {
  for (u32 i = 0; i < getSize();) {
    MenuItemInfo info = getContents(i);
    if (GfDataItem::getRarity(info.unknown04) < filter.unknown04) {
      i++;
    } else {
      decItem(info, false);
    }
  }
}

void GfMenuItemList::filterCollectionType(const FiltertInfo &filter) {
  for (u32 i = 0; i < getSize();) {
    MenuItemInfo info = getContents(i);
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    if (property.unknown08 == ItemType::ITEM_TYPE_UNKNOWN_7 && property.unknown4d == filter.unknown05) {
      i++;
    } else {
      decItem(info, false);
    }
  }
}

void GfMenuItemList::filterFavoriteType(const FiltertInfo &filter) {
  for (u32 i = 0; i < getSize();) {
    MenuItemInfo info = getContents(i);
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    if (property.unknown08 == ItemType::ITEM_TYPE_UNKNOWN_10 && property.unknown4e == filter.unknown06) {
      i++;
    } else {
      decItem(info, false);
    }
  }
}

void GfMenuItemList::updateCount() {
  for (u32 i = 0; i < getSize(); i++) {
    MenuItemInfo &info = getContents(i);
    if (GfMenuItemUtil::canCountStack(info.unknown00) && info.unknown04 != 0) {
      info.unknown08 = GfItemUtil::getItemBoxCount(info.unknown04);
    }
  }
}

int GfMenuItemList::findItem(ItemType::Type type, u32 item) {
  for (u32 i = 0; i < getSize(); i++) {
    const MenuItemInfo &info = getContents(i);
    if (info.unknown00 == type && info.unknown04 == item) {
      return i;
    }
  }
  return -1;
}

void GfMenuItemList::setupFromHanaParts(const HanaPartsSetup &setup) {
  SetupParam param = setup.unknown00;
  UIListInfo<MenuItemInfo>::setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
  if (isValid() && setup.unknown14 >= ItemType::ITEM_TYPE_UNKNOWN_16 && setup.unknown14 <= ItemType::ITEM_TYPE_UNKNOWN_20) {
    u8 *bdat = GfDataBdat::getFP(setup.unknown14 - ItemType::ITEM_TYPE_UNKNOWN_16 + BDAT_ITM_HANA_ROLE);
    u32 top = Bdat::getIdTop(bdat);
    u32 end = Bdat::getIdEnd(bdat);
    for (u32 id = top; id <= end; id++) {
      ItemProperty property;
      GfItemUtil::getProperty(property, id, 0);
      if (property.unknown68 != 0) {
        MenuItemInfo info;
        info.unknown00 = setup.unknown14;
        info.unknown04 = id;
        info.unknown08 = GfItemUtil::getItemBoxCount(id);
        addContents(info);
      }
    }
  }
}

void GfMenuItemList::setupFromQuestReward(const QuestRewardSetup &setup) {
  mm::mtl::FixedVector<MenuItemInfo, 4> items;
  GfQuestReward reward;
  if (setup.unknown14 != 0 && GfQuestUtil::getReward(reward, setup.unknown14, false)) {
    for (u32 slot = QUEST_REWARD_UNKNOWN_8; slot <= QUEST_REWARD_UNKNOWN_11; slot++) {
      u16 item = reward.unknown00[slot].unknown44;
      if (item != 0) {
        MenuItemInfo info;
        info.unknown00 = GfDataItem::getItemType(item);
        info.unknown04 = item;
        info.unknown08 = reward.unknown00[slot].m_developZone;
        items.push_back(info);
      }
    }
    if (items.size() == 0) {
      clear();
    } else {
      UIListInfo<MenuItemInfo>::setup(getAllocator(ALLOCATOR_UNKNOWN_0), setup.unknown00);
      if (isValid()) {
        for (u32 i = 0; i < items.size(); i++) {
          addContents(items[i]);
        }
      }
    }
  }
}

void GfMenuItemList::addItem(const MenuItemInfo &info, bool isAddItemBox) {
  int index = findItem(info.unknown00, info.unknown04);
  if (index != -1) {
    getContents(index).unknown08 += info.unknown08;
  } else {
    addContents(info);
  }
  if (isAddItemBox) {
    SCOM_ADD_ITEM::create(info.unknown04, info.unknown08);
  }
}

void GfMenuItemList::addItem(u32 index, u32 count, bool isAddItemBox) {
  if (index < getSize()) {
    MenuItemInfo &info = getContents(index);
    info.unknown08 += count;
    if (isAddItemBox) {
      SCOM_ADD_ITEM::create(info.unknown04, count);
    }
  }
}

void GfMenuItemList::decItem(const MenuItemInfo &info, bool isAddItemBox) {
  int index = findItem(info.unknown00, info.unknown04);
  if (index != -1) {
    decItem(index, info.unknown08, isAddItemBox);
  }
}

void GfMenuItemList::decItem(u32 index, u32 count, bool isAddItemBox) {
  if (index < getSize()) {
    MenuItemInfo &info = getContents(index);
    u32 item = info.unknown04;
    int num = info.unknown08 - count;
    if (num <= 0) {
      contents.erase(contents.begin() + index);
      subSize(1);
      contentsChanged = true;
    } else {
      info.unknown08 = num;
    }
    if (isAddItemBox) {
      SCOM_ADD_ITEM::create(item, -count);
    }
  }
}

} // namespace gf

template gf::MenuItemInfo *mm::mtl::Vector<gf::MenuItemInfo>::erase(gf::MenuItemInfo *);
