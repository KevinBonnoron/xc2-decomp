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
  u32 time = GfDataBlade::getBornTime(info.unknown00);
  u32 otherTime = GfDataBlade::getBornTime(other.unknown00);
  if (time == otherTime) {
    return info.unknown00 < other.unknown00;
  }
  return time < otherTime;
}

bool GfMenuBladeList::sortTimeDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u32 time = GfDataBlade::getBornTime(info.unknown00);
  u32 otherTime = GfDataBlade::getBornTime(other.unknown00);
  if (time == otherTime) {
    return info.unknown00 < other.unknown00;
  }
  return time > otherTime;
}

bool GfMenuBladeList::sortRarityAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u32 rarity = GfMenuObjUtil::getBladeRarity(info.unknown00);
  u32 otherRarity = GfMenuObjUtil::getBladeRarity(other.unknown00);
  if (rarity == otherRarity) {
    u32 rank = GfMenuObjUtil::getBladeRank(info.unknown00);
    u32 otherRank = GfMenuObjUtil::getBladeRank(other.unknown00);
    if (rank == otherRank) {
      return info.unknown00 < other.unknown00;
    }
    return rank < otherRank;
  }
  return rarity < otherRarity;
}

bool GfMenuBladeList::sortRarityDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u32 rarity = GfMenuObjUtil::getBladeRarity(info.unknown00);
  u32 otherRarity = GfMenuObjUtil::getBladeRarity(other.unknown00);
  if (rarity == otherRarity) {
    u32 rank = GfMenuObjUtil::getBladeRank(info.unknown00);
    u32 otherRank = GfMenuObjUtil::getBladeRank(other.unknown00);
    if (rank == otherRank) {
      return info.unknown00 < other.unknown00;
    }
    return rank > otherRank;
  }
  return rarity > otherRarity;
}

bool GfMenuBladeList::sortWeaponAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 weaponType = GfDataBlade::getSDataBlade(info.unknown00)->unknown821;
  u8 otherWeaponType = GfDataBlade::getSDataBlade(other.unknown00)->unknown821;
  if (weaponType == otherWeaponType) {
    return info.unknown00 < other.unknown00;
  }
  return weaponType < otherWeaponType;
}

bool GfMenuBladeList::sortWeaponDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 weaponType = GfDataBlade::getSDataBlade(info.unknown00)->unknown821;
  u8 otherWeaponType = GfDataBlade::getSDataBlade(other.unknown00)->unknown821;
  if (weaponType == otherWeaponType) {
    return info.unknown00 < other.unknown00;
  }
  return weaponType > otherWeaponType;
}

bool GfMenuBladeList::sortAttrAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 attribute = GfDataBlade::getAttribute(info.unknown00);
  u8 otherAttribute = GfDataBlade::getAttribute(other.unknown00);
  if (attribute == otherAttribute) {
    return info.unknown00 < other.unknown00;
  }
  return attribute < otherAttribute;
}

bool GfMenuBladeList::sortAttrDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 attribute = GfDataBlade::getAttribute(info.unknown00);
  u8 otherAttribute = GfDataBlade::getAttribute(other.unknown00);
  if (attribute == otherAttribute) {
    return info.unknown00 < other.unknown00;
  }
  return attribute > otherAttribute;
}

bool GfMenuBladeList::sortCreatorAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  if (info.unknown04 == other.unknown04) {
    return info.unknown00 < other.unknown00;
  }
  return info.unknown04 < other.unknown04;
}

bool GfMenuBladeList::sortCreatorDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  if (info.unknown04 == other.unknown04) {
    return info.unknown00 < other.unknown00;
  }
  return info.unknown04 > other.unknown04;
}

bool GfMenuBladeList::sortGenderDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 gender = GfDataBlade::getSDataBlade(info.unknown00)->unknown709;
  u8 otherGender = GfDataBlade::getSDataBlade(other.unknown00)->unknown709;
  if (gender == otherGender) {
    return info.unknown00 < other.unknown00;
  }
  return gender > otherGender;
}

bool GfMenuBladeList::sortGenderAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 gender = GfDataBlade::getSDataBlade(info.unknown00)->unknown709;
  u8 otherGender = GfDataBlade::getSDataBlade(other.unknown00)->unknown709;
  if (gender == otherGender) {
    return info.unknown00 < other.unknown00;
  }
  return gender < otherGender;
}

void GfMenuBladeList::updateOwner() {
  for (u32 i = 0; i < getSize(); i++) {
    MenuBladeInfo &info = getContents(i);
    info.unknown04 = GfDataBlade::getCreator(info.unknown00);
  }
}

} // namespace gf

template gf::MenuBladeInfo *mm::mtl::Vector<gf::MenuBladeInfo>::erase(gf::MenuBladeInfo *);
