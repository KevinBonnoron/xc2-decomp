#include "gf/menu/adapter/gf_menu_arts_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_enhance_adapter.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_array.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

constexpr u32 POUCH_MSG_NO_ENHANCE = 4;
constexpr u32 TALENT_ARTS_DAMAGE_DIVISOR = 30;
constexpr u16 REACTION_MSG_NONE = 7;

static GfMenuArtsAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuArtsAdapter::update_ArtsName, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsDescription, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconType, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconEnhance, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconReact, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconRange, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsWp, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99999}},
    {&GfMenuArtsAdapter::update_ArtsIconLevel, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsNumLevel, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 1, 5}},
    {&GfMenuArtsAdapter::update_ArtsReleseLv, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuArtsAdapter::update_ArtsTextType, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsTextRange, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsTextReact, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsNumDamage, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 999}},
    {&GfMenuArtsAdapter::update_ArtsNumRecast, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 999}},
    {&GfMenuArtsAdapter::update_ArtsEnhanceDescription, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconReleseLv, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsNumDamageNextLv, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 999}},
    {&GfMenuArtsAdapter::update_ArtsNumRecastNextLv, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 999}},
    {&GfMenuArtsAdapter::update_ArtsEnhanceDescriptionNextLv, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsDispLvMax, {GfMenuAdapter::PLUGIN_TYPE_DISP, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsTextIndex, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
};

GfMenuArtsAdapter *GfMenuArtsAdapter::createFromList(u32 handle, u32 type, GfMenuArtsList *list, int listIndex, u32 driver, bool isUpdateAlways) {
  // __LINE__ must be 287 as in the original source: it is the line argument of operator new.
#line 287
  ListConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ListConverter(list, listIndex, driver);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuArtsAdapter *GfMenuArtsAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  MenuArtsInfo info = {};
  converter->getArtsInfo(info);
  u32 driver = converter->getDriverId();
  GfMenuArtsAdapter *adapter = create(handle, type, info.unknown00, driver, info.unknown04, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
    return adapter;
  }
  return nullptr;
}

GfMenuArtsAdapter *GfMenuArtsAdapter::createFromListReferenceDriver(u32 handle, u32 type, GfMenuArtsList *list, int listIndex, u32 driverIndex, bool isUpdateAlways) {
  // __LINE__ must be 296 as in the original source: it is the line argument of operator new.
#line 296
  ListReferenceDriverConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ListReferenceDriverConverter(list, listIndex, driverIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuArtsAdapter *GfMenuArtsAdapter::createFromReferenceDriverSlot(u32 handle, u32 type, u32 driverIndex, u32 slot, bool isUpdateAlways) {
  // __LINE__ must be 314 as in the original source: it is the line argument of operator new.
#line 314
  ReferenceDriverSlotConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceDriverSlotConverter(driverIndex, slot);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuArtsAdapter::GfMenuArtsAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), unknown60(0) {}

GfMenuArtsAdapter::~GfMenuArtsAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuArtsAdapter *GfMenuArtsAdapter::create(u32 handle, u32 type, u32 arts, u32 driver, u32 level, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 374 as in the original source: it is the line argument of operator new.
#line 374
      GfMenuArtsAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuArtsAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown58 = arts;
      adapter->unknown5c = driver;
      adapter->unknown60 = level;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuArtsAdapter::update_ArtsName() {
  u8 *bdat = GfDataDriverArts::getNameFP();
  u32 textId = GfDataDriverArts::getNameID(unknown58);
  if (textId != 0) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsDescription() {
  u8 *bdat = GfDataDriverArts::getCaptionFP();
  u32 textId = GfDataDriverArts::getCaptionID(unknown58);
  if (textId != 0) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsIconType() {
  if (unknown5c != 0) {
    if (unknown58 == 0) {
      return false;
    }
    if (unknown60 != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(unknown58, unknown60, iconInfo)) {
        setNumber(iconInfo.unknown00);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsIconEnhance() {
  if (unknown5c != 0) {
    if (unknown58 == 0) {
      return false;
    }
    if (unknown60 != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(unknown58, unknown60, iconInfo)) {
        setNumber(iconInfo.unknown04);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsIconReact() {
  if (unknown5c != 0) {
    if (unknown58 == 0) {
      return false;
    }
    if (unknown60 != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(unknown58, unknown60, iconInfo)) {
        setNumber(iconInfo.unknown08);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsIconRange() {
  if (unknown5c != 0) {
    if (unknown58 == 0) {
      return false;
    }
    if (unknown60 != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(unknown58, unknown60, iconInfo)) {
        setNumber(iconInfo.unknown10);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsWp() {
  if (unknown5c == 0 || unknown58 == 0) {
    return false;
  }
  if (unknown60 >= GfDataDriverArts::getLevelMax(unknown58)) {
    return false;
  }
  setNumber(GfDataDriverArts::getNeedLevelupWp(unknown5c, unknown58));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsIconLevel() {
  if (unknown5c == 0 || unknown58 == 0 || unknown60 == 0) {
    return false;
  }
  setNumber(unknown60 - 1);
  return true;
}

bool GfMenuArtsAdapter::update_ArtsNumLevel() {
  if (unknown5c == 0 || unknown58 == 0) {
    return false;
  }
  setNumber(unknown60);
  return true;
}

bool GfMenuArtsAdapter::update_ArtsReleseLv() {
  if (unknown5c == 0 || unknown58 == 0) {
    return false;
  }
  setNumber(GfDataDriverArts::getLevelCap(unknown58, unknown64));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsTextRange() {
  if (unknown5c == 0 || unknown58 == 0 || unknown60 == 0) {
    return false;
  }
  GfMenuObjUtil::ArtsIconInfo iconInfo;
  if (!GfMenuObjUtil::getArtsIconInfo(unknown58, unknown60, iconInfo)) {
    return false;
  }
  u16 textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ARTS_RANGE, iconInfo.unknown10 + 1);
  if (textId == 0) {
    return false;
  }
  setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_RANGE_TYPE), textId));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsTextReact() {
  if (unknown5c != 0) {
    if (unknown58 == 0) {
      return false;
    }
    if (unknown60 != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (!GfMenuObjUtil::getArtsIconInfo(unknown58, unknown60, iconInfo)) {
        return false;
      }
      u32 textId;
      if (iconInfo.unknown08 == 0) {
        textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_REACTION_ALL, REACTION_MSG_NONE);
        if (textId == 0) {
          return false;
        }
      } else {
        textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_REACTION_ALL, iconInfo.unknown08);
        if (textId == 0) {
          return false;
        }
      }
      setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_ENEMY_REACTION), textId));
      return true;
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsNumDamage() {
  if (unknown5c != 0) {
    if (unknown58 == 0) {
      return false;
    }
    u32 currentLevel = unknown60;
    if (currentLevel != 0) {
      u32 artsType = GfDataDriverArts::getArtsType(unknown58);
      u32 damage = GfDataDriverArts::getDamageMul(unknown58, currentLevel);
      if (artsType == 11) {
        setNumber(damage / TALENT_ARTS_DAMAGE_DIVISOR);
      } else {
        setNumber(damage);
      }
      return true;
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsNumRecast() {
  if (unknown5c == 0 || unknown58 == 0 || unknown60 == 0) {
    return false;
  }
  setNumber(GfDataDriverArts::getRecast(unknown58, unknown60));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsEnhanceDescription() {
  if (unknown5c == 0 || unknown58 == 0 || unknown60 == 0) {
    return false;
  }
  u32 enhance = GfDataDriverArts::getEnhance(unknown58, unknown60);
  if (enhance == 0) {
    u32 textId = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_POUCH), "name", POUCH_MSG_NO_ENHANCE).valueU16;
    ui::UIStr caption(GfDataBdat::getFP(BDAT_MENU_MS), textId);
    setText(caption);
  } else {
    ui::UIStr caption;
    GfMenuEnhanceAdapter::getEnhanceCaption(enhance, caption);
    setText(caption);
  }
  return true;
}

bool GfMenuArtsAdapter::update_ArtsIconReleseLv() {
  if (unknown5c == 0 || unknown58 == 0) {
    return false;
  }
  u32 cap = GfDataDriverArts::getLevelCap(unknown58, unknown64);
  DataParamAcc acc(OBJECT_TYPE_DRIVER, unknown5c, GIMMICK_TYPE_NONE);
  if (acc.isValid()) {
    setNumber(cap <= acc.getLevel(false));
    return true;
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsNumDamageNextLv() {
  if (unknown5c == 0 || unknown58 == 0) {
    return false;
  }
  u32 nextLevel = unknown60 + 1;
  if (nextLevel > GfDataDriverArts::getLevelMax(unknown58)) {
    return false;
  }
  u32 artsType = GfDataDriverArts::getArtsType(unknown58);
  u32 damage = GfDataDriverArts::getDamageMul(unknown58, nextLevel);
  if (artsType == 11) {
    setNumber(damage / TALENT_ARTS_DAMAGE_DIVISOR);
  } else {
    setNumber(damage);
  }
  return true;
}

bool GfMenuArtsAdapter::update_ArtsNumRecastNextLv() {
  if (unknown5c == 0 || unknown58 == 0) {
    return false;
  }
  u32 nextLevel = unknown60 + 1;
  if (nextLevel > GfDataDriverArts::getLevelMax(unknown58)) {
    return false;
  }
  setNumber(GfDataDriverArts::getRecast(unknown58, nextLevel));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsEnhanceDescriptionNextLv() {
  if (unknown5c == 0 || unknown58 == 0) {
    return false;
  }
  u32 nextLevel = unknown60 + 1;
  if (nextLevel > GfDataDriverArts::getLevelMax(unknown58)) {
    return false;
  }
  u32 enhance = GfDataDriverArts::getEnhance(unknown58, nextLevel);
  if (enhance == 0) {
    u32 textId = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_POUCH), "name", POUCH_MSG_NO_ENHANCE).valueU16;
    ui::UIStr caption(GfDataBdat::getFP(BDAT_MENU_MS), textId);
    setText(caption);
  } else {
    ui::UIStr caption;
    GfMenuEnhanceAdapter::getEnhanceCaption(enhance, caption);
    setText(caption);
  }
  return true;
}

bool GfMenuArtsAdapter::update_ArtsTextIndex() {
  if (unknown5c != 0) {
    if (unknown58 == 0) {
      return false;
    }
    if (unknown60 != 0) {
      u32 artsType = GfDataDriverArts::getArtsType(unknown58);
      u16 index;
      if (artsType == 11) {
        index = 2;
      } else if (artsType == 3) {
        index = 3;
      } else if (artsType == 1 || artsType == 2) {
        index = 1;
      } else {
        return false;
      }
      u16 textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ARTS_TYPE_INDEX, index);
      if (textId != 0) {
        setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_MS), textId));
        return true;
      }
    }
  }
  return false;
}

void GfMenuArtsAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    MenuArtsInfo newInfo = {};
    unknown50->getArtsInfo(newInfo);
    if (unknown58 != newInfo.unknown00) {
      unknown58 = newInfo.unknown00;
      setChange();
    }
    if (unknown5c != unknown50->getDriverId()) {
      unknown5c = unknown50->getDriverId();
      setChange();
    }
    if (unknown60 != newInfo.unknown04) {
      unknown60 = newInfo.unknown04;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    if (unknown58 != 0) {
      setDisp(unknown30());
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_CHANGED;
  }
}

void GfMenuArtsAdapter::ListConverter::getArtsInfo(MenuArtsInfo &info) {
  if (listIndex == -1) {
    info = list->getContents(list->getIndex(false));
  } else {
    if (listIndex >= static_cast<int>(list->getSize())) {
      info = MenuArtsInfo();
      return;
    }
    info = list->getContents(list->getPageIndex(listIndex));
  }
}

u32 GfMenuArtsAdapter::ListConverter::getDriverId() { return driver; }

void GfMenuArtsAdapter::ListReferenceDriverConverter::getArtsInfo(MenuArtsInfo &info) {
  if (listIndex == -1) {
    info = list->getContents(list->getIndex(false));
  } else {
    if (listIndex >= static_cast<int>(list->getSize())) {
      info = MenuArtsInfo();
      return;
    }
    info = list->getContents(list->getPageIndex(listIndex));
  }
}

u32 GfMenuArtsAdapter::ListReferenceDriverConverter::getDriverId() { return GfMenuReference::getReferenceDriverID(driverIndex); }

void GfMenuArtsAdapter::ListReferenceDriverConverterReferenceIndex::getArtsInfo(MenuArtsInfo &info) {
  if (number->unknown0c == -1) {
    info = list->getContents(list->getIndex(false));
  } else {
    if (number->unknown0c >= static_cast<int>(list->getSize())) {
      info.unknown00 = 0;
      return;
    }
    info = list->getContents(list->getPageIndex(number->unknown0c));
  }
}

u32 GfMenuArtsAdapter::ListReferenceDriverConverterReferenceIndex::getDriverId() { return GfMenuReference::getReferenceDriverID(driverIndex); }

void GfMenuArtsAdapter::ReferenceDriverSlotConverter::getArtsInfo(MenuArtsInfo &info) {
  u32 driver = GfMenuReference::getReferenceDriverID(driverIndex);
  u32 weaponType;
  {
    DataParamAcc acc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
    if (!acc.isValid()) {
      return;
    }
    u32 blade = acc.getBlade(0, false);
    if (blade == 0) {
      return;
    }
    weaponType = GfDataBlade::getBladeWpnType(blade);
  }
  mm::mtl::FixedArray<u32, 3> slotArts;
  GfDataDriverArts::getSlotArts(slotArts, driver, weaponType);
  info.unknown00 = slotArts[slot];
  info.unknown04 = GfDataDriverArts::getArtsLevel(driver, info.unknown00);
}

u32 GfMenuArtsAdapter::ReferenceDriverSlotConverter::getDriverId() { return GfMenuReference::getReferenceDriverID(driverIndex); }

} // namespace gf
