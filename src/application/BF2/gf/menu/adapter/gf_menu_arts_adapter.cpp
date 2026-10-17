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
  GfMenuArtsAdapter *adapter = create(handle, type, info.arts, driver, info.level, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->converter = converter;
    return adapter;
  }
  return nullptr;
}

GfMenuArtsAdapter *GfMenuArtsAdapter::createFromListReferenceDriver(u32 handle, u32 type, GfMenuArtsList *list, int listIndex, u32 driverIndex,
                                                                    bool isUpdateAlways) {
  // __LINE__ must be 296 as in the original source: it is the line argument of operator new.
#line 296
  ListReferenceDriverConverter *converter =
      new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ListReferenceDriverConverter(list, listIndex, driverIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuArtsAdapter *GfMenuArtsAdapter::createFromReferenceDriverSlot(u32 handle, u32 type, u32 driverIndex, u32 slot, bool isUpdateAlways) {
  // __LINE__ must be 314 as in the original source: it is the line argument of operator new.
#line 314
  ReferenceDriverSlotConverter *converter =
      new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceDriverSlotConverter(driverIndex, slot);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuArtsAdapter::GfMenuArtsAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), converter(nullptr), arts(0), level(0) {}

GfMenuArtsAdapter::~GfMenuArtsAdapter() {
  if (converter != nullptr) {
    delete converter;
    converter = nullptr;
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
      adapter->updater.bind(adapter, info.update);
      adapter->arts = arts;
      adapter->driver = driver;
      adapter->level = level;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuArtsAdapter::update_ArtsName() {
  u8 *bdat = GfDataDriverArts::getNameFP();
  u32 textId = GfDataDriverArts::getNameID(arts);
  if (textId != 0) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsDescription() {
  u8 *bdat = GfDataDriverArts::getCaptionFP();
  u32 textId = GfDataDriverArts::getCaptionID(arts);
  if (textId != 0) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsIconType() {
  if (driver != 0) {
    if (arts == 0) {
      return false;
    }
    if (level != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(arts, level, iconInfo)) {
        setNumber(iconInfo.iconType);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsIconEnhance() {
  if (driver != 0) {
    if (arts == 0) {
      return false;
    }
    if (level != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(arts, level, iconInfo)) {
        setNumber(iconInfo.enhanceIcon);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsIconReact() {
  if (driver != 0) {
    if (arts == 0) {
      return false;
    }
    if (level != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(arts, level, iconInfo)) {
        setNumber(iconInfo.reactionIcon);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsIconRange() {
  if (driver != 0) {
    if (arts == 0) {
      return false;
    }
    if (level != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(arts, level, iconInfo)) {
        setNumber(iconInfo.rangeIcon);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsWp() {
  if (driver == 0 || arts == 0) {
    return false;
  }
  if (level >= GfDataDriverArts::getLevelMax(arts)) {
    return false;
  }
  setNumber(GfDataDriverArts::getNeedLevelupWp(driver, arts));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsIconLevel() {
  if (driver == 0 || arts == 0 || level == 0) {
    return false;
  }
  setNumber(level - 1);
  return true;
}

bool GfMenuArtsAdapter::update_ArtsNumLevel() {
  if (driver == 0 || arts == 0) {
    return false;
  }
  setNumber(level);
  return true;
}

bool GfMenuArtsAdapter::update_ArtsReleseLv() {
  if (driver == 0 || arts == 0) {
    return false;
  }
  setNumber(GfDataDriverArts::getLevelCap(arts, capLevel));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsTextRange() {
  if (driver == 0 || arts == 0 || level == 0) {
    return false;
  }
  GfMenuObjUtil::ArtsIconInfo iconInfo;
  if (!GfMenuObjUtil::getArtsIconInfo(arts, level, iconInfo)) {
    return false;
  }
  u16 textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ARTS_RANGE, iconInfo.rangeIcon + 1);
  if (textId == 0) {
    return false;
  }
  setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_RANGE_TYPE), textId));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsTextReact() {
  if (driver != 0) {
    if (arts == 0) {
      return false;
    }
    if (level != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (!GfMenuObjUtil::getArtsIconInfo(arts, level, iconInfo)) {
        return false;
      }
      u32 textId;
      if (iconInfo.reactionIcon == 0) {
        textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_REACTION_ALL, REACTION_MSG_NONE);
        if (textId == 0) {
          return false;
        }
      } else {
        textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_REACTION_ALL, iconInfo.reactionIcon);
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
  if (driver != 0) {
    if (arts == 0) {
      return false;
    }
    u32 currentLevel = level;
    if (currentLevel != 0) {
      u32 artsType = GfDataDriverArts::getArtsType(arts);
      u32 damage = GfDataDriverArts::getDamageMul(arts, currentLevel);
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
  if (driver == 0 || arts == 0 || level == 0) {
    return false;
  }
  setNumber(GfDataDriverArts::getRecast(arts, level));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsEnhanceDescription() {
  if (driver == 0 || arts == 0 || level == 0) {
    return false;
  }
  u32 enhance = GfDataDriverArts::getEnhance(arts, level);
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
  if (driver == 0 || arts == 0) {
    return false;
  }
  u32 cap = GfDataDriverArts::getLevelCap(arts, capLevel);
  DataParamAcc acc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  if (acc.isValid()) {
    setNumber(cap <= acc.getLevel(false));
    return true;
  }
  return false;
}

bool GfMenuArtsAdapter::update_ArtsNumDamageNextLv() {
  if (driver == 0 || arts == 0) {
    return false;
  }
  u32 nextLevel = level + 1;
  if (nextLevel > GfDataDriverArts::getLevelMax(arts)) {
    return false;
  }
  u32 artsType = GfDataDriverArts::getArtsType(arts);
  u32 damage = GfDataDriverArts::getDamageMul(arts, nextLevel);
  if (artsType == 11) {
    setNumber(damage / TALENT_ARTS_DAMAGE_DIVISOR);
  } else {
    setNumber(damage);
  }
  return true;
}

bool GfMenuArtsAdapter::update_ArtsNumRecastNextLv() {
  if (driver == 0 || arts == 0) {
    return false;
  }
  u32 nextLevel = level + 1;
  if (nextLevel > GfDataDriverArts::getLevelMax(arts)) {
    return false;
  }
  setNumber(GfDataDriverArts::getRecast(arts, nextLevel));
  return true;
}

bool GfMenuArtsAdapter::update_ArtsEnhanceDescriptionNextLv() {
  if (driver == 0 || arts == 0) {
    return false;
  }
  u32 nextLevel = level + 1;
  if (nextLevel > GfDataDriverArts::getLevelMax(arts)) {
    return false;
  }
  u32 enhance = GfDataDriverArts::getEnhance(arts, nextLevel);
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
  if (driver != 0) {
    if (arts == 0) {
      return false;
    }
    if (level != 0) {
      u32 artsType = GfDataDriverArts::getArtsType(arts);
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
  if (converter != nullptr) {
    MenuArtsInfo newInfo = {};
    converter->getArtsInfo(newInfo);
    if (arts != newInfo.arts) {
      arts = newInfo.arts;
      setChange();
    }
    if (driver != converter->getDriverId()) {
      driver = converter->getDriverId();
      setChange();
    }
    if (level != newInfo.level) {
      level = newInfo.level;
      setChange();
    }
  }

  if (updater.isValid() && (flags & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    if (arts != 0) {
      setDisp(updater());
    } else {
      setDisp(false);
    }
    flags &= ~FLAG_CHANGED;
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
  if (number->number == -1) {
    info = list->getContents(list->getIndex(false));
  } else {
    if (number->number >= static_cast<int>(list->getSize())) {
      info.arts = 0;
      return;
    }
    info = list->getContents(list->getPageIndex(number->number));
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
  info.arts = slotArts[slot];
  info.level = GfDataDriverArts::getArtsLevel(driver, info.arts);
}

u32 GfMenuArtsAdapter::ReferenceDriverSlotConverter::getDriverId() { return GfMenuReference::getReferenceDriverID(driverIndex); }

} // namespace gf
