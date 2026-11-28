#include "gf/menu/list/gf_menu_blade_list.h"

#include <functional>

#include "bdat.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/list/gf_menu_sort_type.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/algorithm.h"
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
  u8 weaponType = GfDataBlade::getSDataBlade(info.unknown00).m_weaponType;
  u8 otherWeaponType = GfDataBlade::getSDataBlade(other.unknown00).m_weaponType;
  if (weaponType == otherWeaponType) {
    return info.unknown00 < other.unknown00;
  }
  return weaponType < otherWeaponType;
}

bool GfMenuBladeList::sortWeaponDescending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 weaponType = GfDataBlade::getSDataBlade(info.unknown00).m_weaponType;
  u8 otherWeaponType = GfDataBlade::getSDataBlade(other.unknown00).m_weaponType;
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
  u8 gender = GfDataBlade::getSDataBlade(info.unknown00).m_gender;
  u8 otherGender = GfDataBlade::getSDataBlade(other.unknown00).m_gender;
  if (gender == otherGender) {
    return info.unknown00 < other.unknown00;
  }
  return gender > otherGender;
}

bool GfMenuBladeList::sortGenderAscending(const MenuBladeInfo &info, const MenuBladeInfo &other) {
  u8 gender = GfDataBlade::getSDataBlade(info.unknown00).m_gender;
  u8 otherGender = GfDataBlade::getSDataBlade(other.unknown00).m_gender;
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

void GfMenuBladeList::setMercenaries(mm::mtl::FixedVector<u16, 422> &blades) {
  for (u32 i = 0; i < GfDataMercenaries::getTeamNum(); i++) {
    unknown120 *team = GfDataMercenaries::getTeamMember(i + 1);
    if (team != nullptr) {
      for (u32 j = 0; j < 6; j++) {
        u16 blade = team->unknown00[j];
        if (blade == 0) {
          continue;
        }
        // The game computes the end once (0x71003d2f34): `find(blades.begin(), blades.end(), blade) == blades.end()` gives 63 instructions
        // instead of 61.
        u16 *end = blades.end();
        if (mm::mtl::find(blades.begin(), end, blade) == end) {
          blades.push_back(blade);
        }
      }
    }
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

// 1.0.0: 0x71003d3a04, 506 instructions. The 6 blade loops of the cases 0 and 2 are written out (ruling 8, genuine duplication): a file-local helper holding the loop is not inlined (233
// instructions, 334 differing lines, also with `inline`) and with the helper for case 0 only the function has 522 instructions.
void GfMenuBladeList::setupFromTeam(const TeamSetup &setup) {
  SetupParam param = setup.m_setupParam;
  mm::mtl::FixedVector<u16, 422> blades;
  switch (setup.unknown14) {
  case 0: {
    unknown120 *team = GfDataMercenaries::getTeamMember(setup.unknown18);
    if (team == nullptr) {
      return;
    }
    // The loop body of case 2 (0x71003d3cf0), with its null test of `team` although the return above makes it redundant: without the test the function has 492 instructions (the game
    // pushes a `mov w8, wzr` at 0x71003d3a88 and reloads m_size after the first push, 0x71003d3a90).
    for (u32 i = 0; i < 6; i++) {
      u32 blade = 0;
      if (team != nullptr) {
        blade = team->unknown00[i];
      }
      if (blade != 0 || setup.unknown1c) {
        blades.push_back(blade);
      }
    }
    break;
  }
  case 1: {
    unknown124 *party = GfDataParty::getSDataParty();
    for (u32 member = 0; member < 10; member++) {
      u32 driver = party->m_partyMember[member].m_driver;
      if (driver != 0) {
        for (u32 slot = 0; slot < 6; slot++) {
          u32 blade = 0;
          if (slot < 3) {
            blade = GfDataDriver::getBlade(driver, slot);
          }
          if (blade != 0 || setup.unknown1c) {
            blades.push_back(blade);
          }
        }
      }
    }
    break;
  }
  case 2:
    for (u32 i = 0; i < GfDataMercenaries::getTeamNum(); i++) {
      unknown120 *team = GfDataMercenaries::getTeamMember(i + 1);
      // One loop for a missing team and a present one (the null copy at 0x71003d3e5c is the unswitched loop); two separate loops give 479 instructions.
      for (u32 j = 0; j < 6; j++) {
        u32 blade = 0;
        if (team != nullptr) {
          blade = team->unknown00[j];
        }
        if (blade != 0 || setup.unknown1c) {
          blades.push_back(blade);
        }
      }
    }
    break;
  case 3: {
    if (!GfDataBlade::getListParty(blades)) {
      return;
    }
    if (!GfDataMercenaries::getReserver(blades)) {
      return;
    }
    // The game reads end() and calls isClearGame() at the top of each iteration, in this order (0x71003d4064, 0x71003d412c:
    // `ldr x19, [sp, #0x370]` before `bl isClearGame`, the comparison after it) and tests the element after calls
    // (three loads of *it). With the call at the top of the body 507 instructions, with the call at the end of the body 504
    // (also with a cached end), against 506.
    u16 *it = blades.begin();
    for (;;) {
      u16 *end = blades.end();
      bool isClear = GfGameManager::isClearGame();
      if (it == end) {
        break;
      }
      if ((!isClear && *it != BLADE_SUZAKU && *it != BLADE_WADATSUMI && GfMenuObjUtil::isScenarioBlade(*it)) || (GfDataBlade::isActivateDriver(*it) && !GfMenuObjUtil::canRemoveBlade(*it, nullptr))) {
        it = blades.erase(it);
      } else {
        it++;
      }
    }
    if (setup.unknown1c) {
      for (size_t count = blades.size(); count < GfDataMercenaries::getReserverMax(); count++) {
        blades.push_back(0);
      }
    }
    break;
  }
  }
  // The creation of the list repeats the tail of setupFromBladeList and setupFromBook (ruling 8). Those read the creator with `blades.unknown001(i)`; here the game reads `blades[i]`
  // (with `unknown001(i)` 505 instructions), so the three cannot share a helper. A file-local helper holding this tail for this function only gives 506 instructions and 74 differing
  // lines (first difference at 0x71003d3a30).
  UIListInfo<MenuBladeInfo>::setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
  if (isValid()) {
    MenuBladeInfo info = {};
    for (u32 i = 0; i < blades.size(); i++) {
      info.unknown00 = *blades.at(i);
      info.unknown04 = GfDataBlade::getCreator(blades[i]);
      addContents(info);
    }
  }
}

void GfMenuBladeList::setupFromBladeList(const BladeListSetup &setup) {
  SetupParam param = setup.m_setupParam;
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
  SetupParam param = setup.m_setupParam;
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
