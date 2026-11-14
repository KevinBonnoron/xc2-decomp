#include "gf/menu/list/gf_menu_blade_list.h"

#include <functional>

#include "bdat.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/list/gf_menu_sort_type.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

namespace {

// Inferred role: compares the sort key name column of two blades, ties broken by blade id; original name unknown.
template <bool Ascending> bool unknown001(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u32 row;
  u32 otherRow;
  u8 *bdat = GfMenuBdat::getBladeDataFP(info.unknown00, row);
  u8 *otherBdat = GfMenuBdat::getBladeDataFP(other.unknown00, otherRow);
  const char *name = GfMenuBdat::getSortKeyName();
  u32 key;
  u32 otherKey;
  if (bdat == nullptr || otherBdat == nullptr || row == 0 || otherRow == 0 || name == nullptr) {
    key = info.unknown00;
    otherKey = other.unknown00;
  } else {
    key = Bdat::getVal(bdat, name, row).valueU32;
    otherKey = Bdat::getVal(otherBdat, name, otherRow).valueU32;
  }
  if (key == otherKey) {
    return info.unknown00 < other.unknown00;
  }
  if (Ascending) {
    return key < otherKey;
  }
  return key > otherKey;
}

} // namespace

GfMenuBladeList::GfMenuBladeList() {}

GfMenuBladeList::~GfMenuBladeList() { ; }

GfMenuBladeList *GfMenuBladeList::create() {
  // __LINE__ must be 49 as in the original source: it is the line argument of operator new.
#line 49
  GfMenuBladeList *list = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuBladeList();
  list->addRef();
  return list;
}

void GfMenuBladeList::sort(u32 type, bool ascending) {
  if (getSize() == 0) {
    return;
  }
  std::function<bool(const MenuBladeInfo &, const MenuBladeInfo &)> compare;
  switch (type) {
  case unknown093_1:
    compare = ascending ? sortTimeAscending : sortTimeDescending;
    break;
  case unknown093_2:
    compare = ascending ? sortNameDescending : sortNameAscending;
    break;
  case unknown093_3:
    compare = ascending ? sortRarityAscending : sortRarityDescending;
    break;
  case unknown093_4:
    compare = ascending ? sortWeaponAscending : sortWeaponDescending;
    break;
  case unknown093_5:
    compare = ascending ? sortAttrAscending : sortAttrDescending;
    break;
  case unknown093_6:
    compare = ascending ? sortCreatorAscending : sortCreatorDescending;
    break;
  case unknown093_11:
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

bool GfMenuBladeList::sortNameDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) { return unknown001<false>(info, other); }

bool GfMenuBladeList::sortNameAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) { return unknown001<true>(info, other); }

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
  u8 weaponType = GfDataBlade::getSDataBlade(info.unknown00).unknown821;
  u8 otherWeaponType = GfDataBlade::getSDataBlade(other.unknown00).unknown821;
  if (weaponType == otherWeaponType) {
    return info.unknown00 < other.unknown00;
  }
  return weaponType < otherWeaponType;
}

bool GfMenuBladeList::sortWeaponDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 weaponType = GfDataBlade::getSDataBlade(info.unknown00).unknown821;
  u8 otherWeaponType = GfDataBlade::getSDataBlade(other.unknown00).unknown821;
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
  u8 gender = GfDataBlade::getSDataBlade(info.unknown00).unknown709;
  u8 otherGender = GfDataBlade::getSDataBlade(other.unknown00).unknown709;
  if (gender == otherGender) {
    return info.unknown00 < other.unknown00;
  }
  return gender > otherGender;
}

bool GfMenuBladeList::sortGenderAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 gender = GfDataBlade::getSDataBlade(info.unknown00).unknown709;
  u8 otherGender = GfDataBlade::getSDataBlade(other.unknown00).unknown709;
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

void GfMenuBladeList::getBladeFromDriver(u32 driver, mm::mtl::FixedVector<u16, 422> &blades, bool option) {
  DataParamAcc acc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
  if (acc.isValid()) {
    u32 blade = acc.getBlade(-1, false);
    u32 slotMax = GfMenuObjUtil::getBladeSlotMax();
    if (GfMenuObjUtil::isValidBlade(blade)) {
      blades.push_back(blade);
      for (u32 slot = 1; slot < slotMax; slot++) {
        u32 slotBlade = GfMenuObjUtil::getBladeIDFromDriverSlot(acc.getValidDriverId(), slot);
        if (option || GfMenuObjUtil::isValidBlade(slotBlade)) {
          blades.push_back(slotBlade);
        }
      }
    }
  }
}

void GfMenuBladeList::setupFromBladeList(const BladeListSetup &setup) {
  SetupParam param = setup.unknown00;
  const mm::mtl::FixedVector<u16, 422> *blades = setup.unknown18;
  UIListInfo<MenuBladeInfo>::setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
  if (isValid()) {
    MenuBladeInfo info = {};
    for (u32 i = 0; i < blades->size(); i++) {
      info.unknown00 = *blades->at(i);
      info.unknown04 = GfDataBlade::getCreator(blades->unknown001(i));
      addContents(info);
    }
  }
}

void GfMenuBladeList::setupFromBook(const BladeBookSetup &setup) {
  SetupParam param = setup.unknown00;
  mm::mtl::FixedVector<u16, 422> blades;
  for (u32 blade = BLADE_HOMURA; blade < BLADE_UNKNOWN_1012; blade++) {
    if (blade != BLADE_HOMURI) {
      blades.push_back(blade);
    }
  }
  for (u32 blade = BLADE_WADATSUMI; blade < 0x41b; blade++) {
    if (blade == 0x419 || blade == BLADE_UNKNOWN_1050) {
      continue;
    }
    if (!GfGameManager::isClearGame() && blade >= 0x412 && blade <= 0x418) {
      continue;
    }
    blades.push_back(blade);
  }
  UIListInfo<MenuBladeInfo>::setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
  if (isValid()) {
    MenuBladeInfo info = {};
    for (u32 i = 0; i < blades.size(); i++) {
      info.unknown00 = *blades.at(i);
      info.unknown04 = GfDataBlade::getCreator(blades.unknown001(i));
      addContents(info);
    }
  }
}

} // namespace gf

template gf::MenuBladeInfo *mm::mtl::Vector<gf::MenuBladeInfo>::erase(gf::MenuBladeInfo *);
