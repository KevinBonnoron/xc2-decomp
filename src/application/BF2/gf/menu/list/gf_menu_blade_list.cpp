#include "gf/menu/list/gf_menu_blade_list.h"

#include <functional>

#include "gf/data/gf_data_blade.h"
#include "gf/gf_allocator.h"
#include "gf/menu/list/gf_menu_sort_type.h"
#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

GfMenuBladeList::GfMenuBladeList() {}

GfMenuBladeList::~GfMenuBladeList() { ; }

GfMenuBladeList *GfMenuBladeList::create() {
  // __LINE__ must be 49 as in the original source: it is the line argument of operator new.
#line 49
  GfMenuBladeList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuBladeList();
  list->addRef();
  return list;
}

void GfMenuBladeList::sort(u32 type, bool ascending) {
  if (getSize() == 0) {
    return;
  }
  std::function<bool(const MenuBladeInfo &, const MenuBladeInfo &)> compare;
  switch (type) {
  case SORT_TIME:
    compare = ascending ? sortTimeAscending : sortTimeDescending;
    break;
  case SORT_NAME:
    compare = ascending ? sortNameDescending : sortNameAscending;
    break;
  case SORT_RARITY:
    compare = ascending ? sortRarityAscending : sortRarityDescending;
    break;
  case SORT_WEAPON:
    compare = ascending ? sortWeaponAscending : sortWeaponDescending;
    break;
  case SORT_ATTR:
    compare = ascending ? sortAttrAscending : sortAttrDescending;
    break;
  case SORT_CREATOR:
    compare = ascending ? sortCreatorAscending : sortCreatorDescending;
    break;
  case SORT_GENDER:
    compare = ascending ? sortGenderDescending : sortGenderAscending;
    break;
  default:
    return;
  }
  UIListInfo<MenuBladeInfo>::sort(compare);
}

bool GfMenuBladeList::sortTimeAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u32 time = GfDataBlade::getBornTime(info.blade);
  u32 otherTime = GfDataBlade::getBornTime(other.blade);
  if (time == otherTime) {
    return info.blade < other.blade;
  }
  return time < otherTime;
}

bool GfMenuBladeList::sortTimeDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u32 time = GfDataBlade::getBornTime(info.blade);
  u32 otherTime = GfDataBlade::getBornTime(other.blade);
  if (time == otherTime) {
    return info.blade < other.blade;
  }
  return time > otherTime;
}

bool GfMenuBladeList::sortRarityAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u32 rarity = GfMenuObjUtil::getBladeRarity(info.blade);
  u32 otherRarity = GfMenuObjUtil::getBladeRarity(other.blade);
  if (rarity == otherRarity) {
    u32 rank = GfMenuObjUtil::getBladeRank(info.blade);
    u32 otherRank = GfMenuObjUtil::getBladeRank(other.blade);
    if (rank == otherRank) {
      return info.blade < other.blade;
    }
    return rank < otherRank;
  }
  return rarity < otherRarity;
}

bool GfMenuBladeList::sortRarityDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u32 rarity = GfMenuObjUtil::getBladeRarity(info.blade);
  u32 otherRarity = GfMenuObjUtil::getBladeRarity(other.blade);
  if (rarity == otherRarity) {
    u32 rank = GfMenuObjUtil::getBladeRank(info.blade);
    u32 otherRank = GfMenuObjUtil::getBladeRank(other.blade);
    if (rank == otherRank) {
      return info.blade < other.blade;
    }
    return rank > otherRank;
  }
  return rarity > otherRarity;
}

bool GfMenuBladeList::sortWeaponAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 weaponType = GfDataBlade::getSDataBlade(info.blade)->unknown821;
  u8 otherWeaponType = GfDataBlade::getSDataBlade(other.blade)->unknown821;
  if (weaponType == otherWeaponType) {
    return info.blade < other.blade;
  }
  return weaponType < otherWeaponType;
}

bool GfMenuBladeList::sortWeaponDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 weaponType = GfDataBlade::getSDataBlade(info.blade)->unknown821;
  u8 otherWeaponType = GfDataBlade::getSDataBlade(other.blade)->unknown821;
  if (weaponType == otherWeaponType) {
    return info.blade < other.blade;
  }
  return weaponType > otherWeaponType;
}

bool GfMenuBladeList::sortAttrAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 attribute = GfDataBlade::getAttribute(info.blade);
  u8 otherAttribute = GfDataBlade::getAttribute(other.blade);
  if (attribute == otherAttribute) {
    return info.blade < other.blade;
  }
  return attribute < otherAttribute;
}

bool GfMenuBladeList::sortAttrDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 attribute = GfDataBlade::getAttribute(info.blade);
  u8 otherAttribute = GfDataBlade::getAttribute(other.blade);
  if (attribute == otherAttribute) {
    return info.blade < other.blade;
  }
  return attribute > otherAttribute;
}

bool GfMenuBladeList::sortCreatorAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  if (info.creator == other.creator) {
    return info.blade < other.blade;
  }
  return info.creator < other.creator;
}

bool GfMenuBladeList::sortCreatorDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  if (info.creator == other.creator) {
    return info.blade < other.blade;
  }
  return info.creator > other.creator;
}

bool GfMenuBladeList::sortGenderDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 gender = GfDataBlade::getSDataBlade(info.blade)->unknown709;
  u8 otherGender = GfDataBlade::getSDataBlade(other.blade)->unknown709;
  if (gender == otherGender) {
    return info.blade < other.blade;
  }
  return gender > otherGender;
}

bool GfMenuBladeList::sortGenderAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 gender = GfDataBlade::getSDataBlade(info.blade)->unknown709;
  u8 otherGender = GfDataBlade::getSDataBlade(other.blade)->unknown709;
  if (gender == otherGender) {
    return info.blade < other.blade;
  }
  return gender < otherGender;
}

void GfMenuBladeList::updateOwner() {
  for (u32 i = 0; i < getSize(); i++) {
    MenuBladeInfo &info = getContents(i);
    info.creator = GfDataBlade::getCreator(info.blade);
  }
}

} // namespace gf
