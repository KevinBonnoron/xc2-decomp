#include "gf/menu/gf_menu_bdat.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "ui/ui_str.h"

namespace gf {

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

void GfMenuBdat::getFieldSkillName(u16 skill, ui::UIStr &name) {
  u8 *list = GfDataBdat::getFP(BDAT_FLD_FIELD_SKILL_LIST);
  u8 *text = GfDataBdat::getFP(BDAT_FLD_FIELDSKILLTXT);
  if (list != nullptr && text != nullptr) {
    ui::UIStr str(text, Bdat::getVal(list, "Name", skill).valueU16);
    name.copy(str);
  }
}

int GfMenuBdat::getIconIDFromWeatherType(u32 weatherType) { return weatherType + 167; }

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
