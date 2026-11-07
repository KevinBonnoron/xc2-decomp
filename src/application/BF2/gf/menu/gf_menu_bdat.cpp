#include "gf/menu/gf_menu_bdat.h"

#include "bdat.h"
#include "framework/lang_util.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_item.h"
#include "ui/ui_str.h"

namespace gf {

namespace {

struct unknown001 {
  u32 unknown00;         // Inferred role: language type; original member name unknown.
  const char *unknown08; // Inferred role: sort key column name of the language; original member name unknown.
};

const unknown001 s_sortKeyNames[] = {
    {0, "sortJP"},
    {3, "sortGE"},
    {2, "sortFR"},
    {5, "sortSP"},
    {4, "sortIT"},
    {12, "sortGB"},
    {6, "sortCN"},
    {11, "sortTW"},
};

} // namespace

u8 *GfMenuBdat::s_BdatArray[7];

u8 *GfMenuBdat::getFP(u32 bdat) {
  if (bdat < 7) {
    return s_BdatArray[bdat];
  }
  return nullptr;
}

void GfMenuBdat::initialize() {
  static const char *const names[] = {"MNU_OffsetList", "MNU_IconList", "MNU_Layer", "FLD_FieldSkillList", "ITM_CollectionList", "itm_collection", "BTL_Arts_Dr"};

  for (u32 i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
    s_BdatArray[i] = Bdat::getFP(names[i]);
  }
}

u32 GfMenuBdat::getValueLevel(u8 *bdat, u32 value) {
  int top = Bdat::getIdTop(bdat);
  if (Bdat::getIdCount(bdat) < 2) {
    return 1;
  }

  u32 first = Bdat::getVal(bdat, "value", top).valueU32;
  u32 second = Bdat::getVal(bdat, "value", top + 1).valueU32;
  if (first > second) {
    for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
      if (Bdat::getVal(bdat, "value", top + i).valueU32 <= value) {
        return i + 1;
      }
    }
  } else {
    for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
      if (Bdat::getVal(bdat, "value", top + i).valueU32 >= value) {
        return i + 1;
      }
    }
  }
  return Bdat::getIdCount(bdat);
}

bool GfMenuBdat::isValidBdatID(u8 *bdat, int id) {
  if (bdat == nullptr || id < Bdat::getIdTop(bdat)) {
    return false;
  }

  return id < Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat);
}

void GfMenuBdat::getMenuOffset(int id, MenuOffset &offset) {
  u8 *bdat = s_BdatArray[0];
  if (isValidBdatID(bdat, id)) {
    offset.unknown00 = Bdat::getVal(bdat, "offs_x", id).valueF32;
    offset.unknown04 = Bdat::getVal(bdat, "offs_y", id).valueF32;
    offset.unknown08 = Bdat::getVal(bdat, "offs_z", id).valueF32;
    offset.unknown10 = Bdat::getVal(bdat, "bone_name", id).valueString;
    if (*offset.unknown10 == '\0') {
      offset.unknown10 = nullptr;
    }
  }
}

u32 GfMenuBdat::getIconImageIndex(int icon) {
  u8 *bdat = s_BdatArray[1];
  if (isValidBdatID(bdat, icon)) {
    return Bdat::getVal(bdat, "icon_index", icon).valueU8;
  }

  return 0;
}

u32 GfMenuBdat::getTopDriverIconID() { return 199; }

u32 GfMenuBdat::getTopBladeIconID() { return 207; }

int GfMenuBdat::getFieldSkillTypeMax() { return Bdat::getIdCount(s_BdatArray[3]); }

u8 *GfMenuBdat::getItemDataFP(u8 itemType, u16 item) {
  switch (itemType) {
  case ItemType::PC_WPN_CHIP:
    return GfDataBdat::getFP(BDAT_ITM_PC_WPN_CHIP);
  case ItemType::PC_EQUIP:
    return GfDataBdat::getFP(BDAT_ITM_PC_EQUIP);
  case ItemType::EQUIP_ORB:
    return GfDataBdat::getFP(BDAT_ITM_ORB_EQUIP);
  case ItemType::SALVAGE:
    return GfDataBdat::getFP(BDAT_ITM_SALVAGE_LIST);
  case ItemType::PRECIOUS:
    return GfDataBdat::getFP(BDAT_ITM_PRECIOUS_LIST);
  case ItemType::COLLECTION_LIST:
    return GfDataBdat::getFP(BDAT_ITM_COLLECTION_LIST);
  case ItemType::TRESURE:
    return GfDataBdat::getFP(BDAT_ITM_TRESURE_LIST);
  case ItemType::EMPTY_ORB:
    return GfDataBdat::getFP(BDAT_ITM_ORB);
  case ItemType::FAVORITE:
    return GfDataBdat::getFP(BDAT_ITM_FAVORITE_LIST);
  case ItemType::CRYSTAL_LIST:
    return GfDataBdat::getFP(BDAT_ITM_CRYSTAL_LIST);
  case ItemType::BOOSTER:
    return GfDataBdat::getFP(BDAT_ITM_BOOSTER_LIST);
  case ItemType::INFO:
    return GfDataBdat::getFP(BDAT_ITM_INFO_LIST);
  case ItemType::EVENT:
    return GfDataBdat::getFP(BDAT_ITM_EVENT_LIST);
  case ItemType::HANA_ROLE:
    return GfDataBdat::getFP(BDAT_ITM_HANA_ROLE);
  case ItemType::HANA_ATR:
    return GfDataBdat::getFP(BDAT_ITM_HANA_ATR);
  case ItemType::HANA_ARTS_ENH:
    return GfDataBdat::getFP(BDAT_ITM_HANA_ARTS_ENH);
  case ItemType::HANA_N_ARTS_SET:
    return GfDataBdat::getFP(BDAT_ITM_HANA_NARTS_SET);
  case ItemType::HANA_ASSIST:
    return GfDataBdat::getFP(BDAT_ITM_HANA_ASSIST);
  default:
    return nullptr;
  }
}

u8 *GfMenuBdat::getItemTextFP(u8 itemType, u16 item) {
  switch (itemType) {
  case ItemType::PC_WPN_CHIP:
    return GfDataBdat::getFP(BDAT_ITM_PCWPNCHIP_MS);
  case ItemType::PC_EQUIP:
    return GfDataBdat::getFP(BDAT_ITM_PCEQUIP);
  case ItemType::EQUIP_ORB:
    return GfDataBdat::getFP(BDAT_ITM_ORB_MS);
  case ItemType::SALVAGE:
    return GfDataBdat::getFP(BDAT_ITM_SALVAGE);
  case ItemType::PRECIOUS:
    return GfDataBdat::getFP(BDAT_ITM_PRECIOUS);
  case ItemType::COLLECTION_LIST:
    return GfDataBdat::getFP(BDAT_ITM_COLLECTION);
  case ItemType::TRESURE:
    return GfDataBdat::getFP(BDAT_ITM_TRESURE);
  case ItemType::EMPTY_ORB:
    return GfDataBdat::getFP(BDAT_ITM_ORB_MS);
  case ItemType::FAVORITE:
    return GfDataBdat::getFP(BDAT_ITM_FAVORITE);
  case ItemType::CRYSTAL_LIST:
    return GfDataBdat::getFP(BDAT_ITM_CRYSTAL);
  case ItemType::BOOSTER:
    return GfDataBdat::getFP(BDAT_ITM_BOOSTER);
  case ItemType::INFO:
    return GfDataBdat::getFP(BDAT_ITM_INFO);
  case ItemType::EVENT:
    return GfDataBdat::getFP(BDAT_ITM_EVT);
  case ItemType::HANA_ROLE:
    return GfDataBdat::getFP(BDAT_ITM_HANA_ROLE_MS);
  case ItemType::HANA_ATR:
    return GfDataBdat::getFP(BDAT_ITM_HANA_ATR_MS);
  case ItemType::HANA_ARTS_ENH:
    return GfDataBdat::getFP(BDAT_ITM_ORB_MS);
  case ItemType::HANA_N_ARTS_SET:
    return GfDataBdat::getFP(BDAT_ITM_HANA_NARTS_SET_MS);
  case ItemType::HANA_ASSIST:
    return GfDataBdat::getFP(BDAT_ITM_ORB_MS);
  default:
    return nullptr;
  }
}

void GfMenuBdat::getFieldSkillName(u16 skill, ui::UIStr &name) {
  u8 *list = GfDataBdat::getFP(BDAT_FLD_FIELD_SKILL_LIST);
  u8 *text = GfDataBdat::getFP(BDAT_FLD_FIELDSKILLTXT);
  if (list != nullptr && text != nullptr) {
    ui::UIStr str(text, Bdat::getVal(list, "Name", skill).valueU16);
    name.copy(str);
  }
}

int GfMenuBdat::getIconIDFromWeatherType(u32 weatherType) { return weatherType + 167; }

const char *GfMenuBdat::getSortKeyName() {
  u32 lang = fw::LangUtil::getLangType();
  for (u32 i = 0; i < sizeof(s_sortKeyNames) / sizeof(s_sortKeyNames[0]); i++) {
    if (s_sortKeyNames[i].unknown00 == lang) {
      return s_sortKeyNames[i].unknown08;
    }
  }
  return nullptr;
}

u8 *GfMenuBdat::getBladeDataFP(u32 blade, u32 &id) {
  u8 *bdat;
  if (GfDataBlade::isCommonBlade(blade)) {
    bdat = GfDataBdat::getFP(BDAT_BLD_NAME_LIST);
    blade = GfDataBlade::getBLD_NameList(blade);
  } else {
    bdat = GfDataBdat::getFP(BDAT_CHR_BL);
  }

  id = blade;
  return bdat;
}

} // namespace gf
