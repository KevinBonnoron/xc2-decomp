#include "gf/menu/adapter/gf_menu_hana_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_hana.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

namespace {

// Inferred role: sort table id of a parts type; original type name unknown.
struct unknown003 {
  u32 type;
  u32 id;
};

} // namespace

static GfMenuHanaAdapter::unknown001 unknown002[] = {
    {&GfMenuHanaAdapter::update_ether, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuHanaAdapter::update_equipPower, {GfMenuAdapter::unknown004_0, 0, 9999}},
    {&GfMenuHanaAdapter::update_maxPower, {GfMenuAdapter::unknown004_0, 0, 9999}},
    {&GfMenuHanaAdapter::update_roleText, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuHanaAdapter::update_atrText, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuHanaAdapter::update_atrIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuHanaAdapter::update_bustupIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuHanaAdapter::update_equipIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuHanaAdapter::update_rankPower, {GfMenuAdapter::unknown004_0, 0, 20}},
    {&GfMenuHanaAdapter::update_maxRankPower, {GfMenuAdapter::unknown004_0, 0, 20}},
    {&GfMenuHanaAdapter::update_partsExpandIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuHanaAdapter::update_equipColor, {GfMenuAdapter::unknown004_8, 0, 0}},
};

// Inferred role: sort table id of each parts type of the equip list; original name unknown.
static const unknown003 unknown006[] = {
    {1, 18},
    {2, 19},
    {3, 20},
    {4, 20},
    {5, 20},
    {6, 21},
    {7, 21},
    {8, 21},
    {9, 22},
    {10, 22},
    {11, 22},
    {12, 21},
    {13, 21},
    {14, 21},
};

// Inferred role: sort table id of each parts type of the make list; original name unknown.
static const unknown003 unknown007[] = {
    {1, 23},
    {2, 24},
    {3, 25},
    {6, 26},
    {9, 27},
};

GfMenuHanaAdapter::GfMenuHanaAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0) {}

GfMenuHanaAdapter::~GfMenuHanaAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuHanaAdapter *GfMenuHanaAdapter::create(u32 handle, u32 type, u32 blade, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    unknown001 &info = unknown002[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 119 as in the original source: it is the line argument of operator new.
#line 119
      GfMenuHanaAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuHanaAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown5c = blade;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuHanaAdapter::update_ether() {
  setNumber(GfDataHana::getEther());
  return true;
}

bool GfMenuHanaAdapter::update_equipPower() {
  setNumber(GfDataHana::getEquipPower(unknown5c));
  setNumberMax(GfDataHana::getPowerCapacity(unknown5c));
  return true;
}

bool GfMenuHanaAdapter::update_maxPower() {
  setNumber(GfDataHana::getPowerCapacity(unknown5c));
  return true;
}

bool GfMenuHanaAdapter::update_roleText() {
  u32 role = GfDataHana::getRole(unknown5c);
  if (role != 0) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MENU_ROLE_NAME_MS);
    setText(ui::UIStr(bdat, role));
    return true;
  }
  return false;
}

bool GfMenuHanaAdapter::update_atrText() {
  u32 attribute = GfDataHana::getAttribute(unknown5c);
  u8 *bdat = GfDataBdat::getFP(BDAT_MENU_ATTR_MS);
  setText(ui::UIStr(bdat, attribute + 1));
  return true;
}

bool GfMenuHanaAdapter::update_atrIcon() {
  setNumber(GfDataHana::getAttribute(unknown5c));
  return true;
}

bool GfMenuHanaAdapter::update_bustupIcon() {
  u32 index = unknown5c - BLADE_UNKNOWN_1005;
  if (index < 3) {
    setNumber(index + 1);
    return true;
  }
  return false;
}

bool GfMenuHanaAdapter::update_equipIcon() {
  if (unknown58 != 0) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_HANA_SET);
    setNumber(Bdat::getVal(bdat, "icon", unknown58).valueU16);
    return true;
  }
  return false;
}

bool GfMenuHanaAdapter::update_rankPower() {
  setNumber(GfGameUtilHana::getPowerRank(unknown5c));
  return true;
}

bool GfMenuHanaAdapter::update_maxRankPower() {
  setNumber(20);
  return true;
}

bool GfMenuHanaAdapter::update_equipColor() {
  if (unknown58 == 0) {
    return false;
  }
  const char *color;
  if (getEquipParts(unknown5c, unknown58) == 0 && unknown58 != 15) {
    color = "hana_parts_icon_disable";
  } else {
    color = "hana_parts_icon";
  }
  setMulColor(color);
  return true;
}

GfMenuHanaAdapter *GfMenuHanaAdapter::createFromReferenceIndex(u32 handle, u32 type, u32 index, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 137 as in the original source: it is the line argument of operator new.
#line 137
  ReferenceIndexConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceIndexConverter(index);
  GfMenuHanaAdapter *adapter = create(handle, type, converter->getHanaId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuHanaAdapter *GfMenuHanaAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  GfMenuHanaAdapter *adapter = create(handle, type, converter->getHanaId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

void GfMenuHanaAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newBlade = unknown50->getHanaId();
    if (unknown5c != newBlade) {
      unknown5c = newBlade;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) != 0) {
    setDisp(unknown30());
    unknown20 &= ~FLAG_UNKNOWN_0;
  }
}

u32 GfMenuHanaAdapter::getEquipParts(u32 blade, u32 type) {
  EquipHana equip;
  GfGameUtilHana::getEquip(equip, blade);
  switch (type) {
  case 1:
    return equip.unknown00;
  case 2:
    return equip.unknown02;
  case 3:
  case 4:
  case 5:
    return equip.unknown28[type - 3].unknown04;
  case 6:
  case 7:
  case 8:
    return equip.unknown4c[type - 6];
  case 9:
  case 10:
  case 11:
    return equip.unknown04[type - 9].unknown04;
  case 12:
  case 13:
  case 14:
    return equip.unknown52[type - 12];
  }
  return 0;
}

bool GfMenuHanaAdapter::isEquipParts(u32 blade, u32 type, u32 parts, RESULT_HANA &result) {
  switch (type) {
  case 1:
    result = GfGameUtilHana::isEnableEquipRoleParts(blade, parts);
    break;
  case 2:
    result = GfGameUtilHana::isEnableEquipAttributeParts(blade, parts);
    break;
  case 3:
  case 4:
  case 5:
    result = GfGameUtilHana::isEnableEquipNArtsParts(blade, parts, type - 3);
    break;
  case 6:
  case 7:
  case 8:
    result = GfGameUtilHana::isEnableEquipCondenserParts(blade, parts, type - 6);
    break;
  case 9:
  case 10:
  case 11:
    result = GfGameUtilHana::isEnableEquipArtsParts(blade, parts, type - 9);
    break;
  case 12:
  case 13:
  case 14:
    result = GfGameUtilHana::isEnableEquipExtendCondenserParts(blade, parts, type - 12);
    break;
  default:
    return false;
  }
  u32 count = GfItemUtil::getItemBoxCount(parts);
  bool isEnable;
  if (count != 0) {
    isEnable = result == RESULT_HANA_UNKNOWN_0;
  } else {
    isEnable = false;
    result = RESULT_HANA_UNKNOWN_8;
  }
  return count != 0 && isEnable;
}

bool GfMenuHanaAdapter::chkEquipPartsGroup(u32 blade, u32 type, u32 parts) {
  EquipHana equip;
  GfGameUtilHana::getEquip(equip, blade);
  switch (type) {
  case 1:
    if (equip.unknown00 == parts) {
      return true;
    }
    break;
  case 2:
    if (equip.unknown02 == parts) {
      return true;
    }
    break;
  case 3:
  case 4:
  case 5:
    if (equip.unknown28[0].unknown04 == parts || equip.unknown28[1].unknown04 == parts || equip.unknown28[2].unknown04 == parts) {
      return true;
    }
    break;
  case 6:
  case 7:
  case 8:
    if (equip.unknown4c[0] == parts || equip.unknown4c[1] == parts || equip.unknown4c[2] == parts) {
      return true;
    }
    break;
  case 9:
  case 10:
  case 11:
    if (equip.unknown04[0].unknown04 == parts || equip.unknown04[1].unknown04 == parts || equip.unknown04[2].unknown04 == parts) {
      return true;
    }
    break;
  case 12:
  case 13:
  case 14:
    if (equip.unknown52[0] == parts || equip.unknown52[1] == parts || equip.unknown52[2] == parts) {
      return true;
    }
    break;
  }
  return false;
}

bool GfMenuHanaAdapter::isMakeParts(u32 type, u32 parts, RESULT_HANA &result) {
  switch (type) {
  case 1:
    result = GfGameUtilHana::isExchangeRoleParts(parts);
    break;
  case 2:
    result = GfGameUtilHana::isExchangeAttributeParts(parts);
    break;
  case 3:
  case 4:
  case 5:
    result = GfGameUtilHana::isExchangeNArtsParts(parts);
    break;
  case 6:
  case 7:
  case 8:
    result = GfGameUtilHana::isExchangeCondenserParts(parts);
    break;
  case 9:
  case 10:
  case 11:
    result = GfGameUtilHana::isExchangeArtsParts(parts);
    break;
  default:
    return false;
  }
  ItemProperty property;
  GfItemUtil::getProperty(property, parts, 0);
  if (property.unknown70 != 0 && !GfGameCond::isGameCond(property.unknown70)) {
    result = RESULT_HANA_UNKNOWN_5;
    return false;
  }
  return result == RESULT_HANA_UNKNOWN_0;
}

bool GfMenuHanaAdapter::isCrystalParts(u32 type, u32 parts, RESULT_HANA &result) {
  result = RESULT_HANA_UNKNOWN_0;
  return true;
}

int GfMenuHanaAdapter::getHanaCount() {
  mm::mtl::FixedVector<u16, 16> drivers;
  GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_2, 0);
  mm::mtl::FixedVector<u16, 422> blades;
  for (u16 *driver = drivers.begin(); driver != drivers.end(); ++driver) {
    GfMenuBladeList::getBladeFromDriver(*driver, blades, false);
  }
  int count = 0;
  for (u16 *blade = blades.begin(); blade != blades.end(); ++blade) {
    count += GfDataHana::isValid(*blade);
  }
  return count;
}

u32 GfMenuHanaAdapter::getSortTableId(u32 type) {
  for (u32 i = 0; i < 14; i++) {
    if (unknown006[i].type == type) {
      return unknown006[i].id;
    }
  }
  return 0;
}

u32 GfMenuHanaAdapter::getMakeSortTableId(u32 type) {
  for (u32 i = 0; i < 5; i++) {
    if (unknown007[i].type == type) {
      return unknown007[i].id;
    }
  }
  return 0;
}

} // namespace gf
