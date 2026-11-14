#include "gf/menu/adapter/gf_menu_weapon_type_adapter.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_array.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: number of art slots; original name unknown.
constexpr u32 ARTS_SLOT_UNKNOWN_4 = 4;

static GfMenuWeaponTypeAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuWeaponTypeAdapter::update_WpnTypeName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_WpnTypeIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_WpnTypeWP, {GfMenuAdapter::unknown004_0, 0, 99999}},
    {&GfMenuWeaponTypeAdapter::update_ArtsName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconType, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconEnhance, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconReact, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconRange, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsTextType, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsTextReact, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsTextRange, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsNumDamage, {GfMenuAdapter::unknown004_0, 0, 999}},
    {&GfMenuWeaponTypeAdapter::update_ArtsNumRecast, {GfMenuAdapter::unknown004_0, 0, 999}},
    {&GfMenuWeaponTypeAdapter::update_ArtsLevel, {GfMenuAdapter::unknown004_0, 0, 99}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconLevel, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsDescription, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsWp, {GfMenuAdapter::unknown004_0, 0, 99999}},
    {&GfMenuWeaponTypeAdapter::update_ArtsDriverLevel, {GfMenuAdapter::unknown004_0, 1, 99}},
    {&GfMenuWeaponTypeAdapter::update_ArtsLevel0Disp, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsLevelMaxDisp, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsEnhanceDescription, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsReleseLv, {GfMenuAdapter::unknown004_0, 0, 99}},
};

GfMenuWeaponTypeAdapter::GfMenuWeaponTypeAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), unknown5c(0), unknown60(0), unknown64(0) {}

GfMenuWeaponTypeAdapter::~GfMenuWeaponTypeAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuWeaponTypeAdapter *GfMenuWeaponTypeAdapter::create(u32 handle, u32 type, u32 driver, u32 weaponType, u32 artsIndex, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 203 as in the original source: it is the line argument of operator new.
#line 203
      GfMenuWeaponTypeAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuWeaponTypeAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown58 = driver;
      adapter->unknown5c = weaponType;
      adapter->unknown60 = artsIndex;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuWeaponTypeAdapter::update_WpnTypeName() {
  u8 *bdat;
  u32 textId;
  if (GfDataWeapon::getWeaponTypeName(bdat, textId, unknown5c)) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_WpnTypeIcon() {
  if (unknown5c != 0) {
    setNumber(unknown5c - 1);
    return true;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_WpnTypeWP() {
  setNumber(GfDataDriverArts::getWp(unknown58, unknown5c));
  return true;
}

bool GfMenuWeaponTypeAdapter::update_ArtsTextType() {
  GfMenuObjUtil::ArtsIconInfo iconInfo;
  DriverArts driverArts;
  if (getDriverArts(driverArts)) {
    if (GfMenuObjUtil::getArtsIconInfo(driverArts.unknown00, driverArts.unknown04, iconInfo) && iconInfo.unknown00 != 0) {
      u16 textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ARTS_TYPE, iconInfo.unknown00);
      if (textId != 0) {
        setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_ARTS_TYPE), textId));
        return true;
      }
    }
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsTextReact() {
  GfMenuObjUtil::ArtsIconInfo iconInfo;
  DriverArts driverArts;
  if (getDriverArts(driverArts)) {
    if (GfMenuObjUtil::getArtsIconInfo(driverArts.unknown00, driverArts.unknown04, iconInfo) && iconInfo.unknown08 > 2) {
      u16 textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_REACTION, iconInfo.unknown08 - 2);
      if (textId != 0) {
        setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_ENEMY_REACTION), textId));
        return true;
      }
    }
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsTextRange() {
  GfMenuObjUtil::ArtsIconInfo iconInfo;
  DriverArts driverArts;
  if (getDriverArts(driverArts)) {
    if (GfMenuObjUtil::getArtsIconInfo(driverArts.unknown00, driverArts.unknown04, iconInfo)) {
      u16 textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ARTS_RANGE, iconInfo.unknown10 + 1);
      if (textId != 0) {
        setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_RANGE_TYPE), textId));
        return true;
      }
    }
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsNumDamage() {
  DriverArts driverArts;
  if (getDriverArts(driverArts)) {
    setNumber(GfDataDriverArts::getDamageMul(driverArts.unknown00, driverArts.unknown04));
    return true;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsNumRecast() {
  DriverArts driverArts;
  if (getDriverArts(driverArts)) {
    setNumber(GfDataDriverArts::getRecast(driverArts.unknown00, driverArts.unknown04));
    return true;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsName() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    u8 *bdat = GfDataDriverArts::getNameFP();
    u32 textId = GfDataDriverArts::getNameID(artsId);
    if (textId != 0) {
      setText(ui::UIStr(bdat, textId));
      return true;
    }
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconType() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    u32 level = GfDataDriverArts::getArtsLevel(unknown58, artsId);
    if (artsId != 0 && level != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(artsId, level, iconInfo)) {
        setNumber(iconInfo.unknown00);
        return true;
      }
    }
    return false;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconEnhance() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    u32 level = GfDataDriverArts::getArtsLevel(unknown58, artsId);
    if (artsId != 0 && level != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(artsId, level, iconInfo)) {
        setNumber(iconInfo.unknown04);
        return true;
      }
    }
    return false;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconReact() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    u32 level = GfDataDriverArts::getArtsLevel(unknown58, artsId);
    if (artsId != 0 && level != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(artsId, level, iconInfo)) {
        setNumber(iconInfo.unknown08);
        return true;
      }
    }
    return false;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconRange() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    u32 level = GfDataDriverArts::getArtsLevel(unknown58, artsId);
    if (artsId != 0 && level != 0) {
      GfMenuObjUtil::ArtsIconInfo iconInfo;
      if (GfMenuObjUtil::getArtsIconInfo(artsId, level, iconInfo)) {
        setNumber(iconInfo.unknown10);
        return true;
      }
    }
    return false;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsLevel() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    setNumber(GfDataDriverArts::getArtsLevel(unknown58, artsId));
    return true;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconLevel() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    setNumber(GfDataDriverArts::getArtsLevel(unknown58, artsId) - 1);
    return true;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsDescription() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    u8 *bdat = GfDataDriverArts::getCaptionFP();
    u32 textId = GfDataDriverArts::getCaptionID(artsId);
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsWp() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    setNumber(GfDataDriverArts::getNeedLevelupWp(unknown58, artsId));
    return true;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsDriverLevel() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    u32 level = GfDataDriverArts::getArtsLevel(unknown58, artsId);
    if (level < GfDataDriverArts::getLevelMax(artsId)) {
      u32 driverLevel = GfDataDriverArts::getLevelCap(artsId, level + 1);
      if (driverLevel - 1 < 99) {
        setNumber(driverLevel);
        return true;
      }
    }
    return false;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsLevel0Disp() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    if (GfDataDriverArts::getArtsLevel(unknown58, artsId) != 0) {
      return unknown64 == 0;
    }
  }
  return unknown64 != 0;
}

bool GfMenuWeaponTypeAdapter::update_ArtsLevelMaxDisp() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    u32 level = GfDataDriverArts::getArtsLevel(unknown58, artsId);
    if (level < GfDataDriverArts::getLevelMax(artsId)) {
      return unknown64 == 0;
    }
  }
  return unknown64 != 0;
}

bool GfMenuWeaponTypeAdapter::update_ArtsEnhanceDescription() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    u32 artsId = arts[unknown60];
    u32 level = GfDataDriverArts::getArtsLevel(unknown58, artsId);
    GfDataDriverArts::getEnhance(artsId, level);
    u8 *bdat = GfDataDriverArts::getCaptionFP();
    u32 textId = GfDataDriverArts::getCaptionID(artsId);
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsReleseLv() {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    setNumber(GfDataDriverArts::getLevelCap(arts[unknown60], unknown64));
    return true;
  }
  return false;
}

GfMenuWeaponTypeAdapter *GfMenuWeaponTypeAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  GfMenuWeaponTypeAdapter *adapter = create(handle, type, converter->getDriverId(), converter->getWpnType(), converter->getArtsIndex(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

void GfMenuWeaponTypeAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 driver = unknown50->getDriverId();
    if (unknown58 != driver) {
      unknown58 = driver;
      setChange();
    }
    u32 weaponType = unknown50->getWpnType();
    if (unknown5c != weaponType) {
      unknown5c = weaponType;
      setChange();
    }
    u32 artsIndex = unknown50->getArtsIndex();
    if (unknown60 != artsIndex) {
      unknown60 = artsIndex;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) != 0) {
    if (unknown58 != 0) {
      setDisp(unknown30());
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_UNKNOWN_0;
  }
}

bool GfMenuWeaponTypeAdapter::getDriverArts(DriverArts &driverArts) {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    if (unknown60 < ARTS_SLOT_UNKNOWN_4) {
      driverArts.unknown00 = arts[unknown60];
      driverArts.unknown04 = GfDataDriverArts::getArtsLevel(unknown58, driverArts.unknown00);
      return true;
    }
    return false;
  }
  return false;
}

GfMenuWeaponTypeAdapter *GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(u32 handle, u32 type, u16 driver, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> wpnType, u16 artsIndex,
                                                                                   bool isUpdateAlways) {
  // __LINE__ must be 234 as in the original source: it is the line argument of operator new.
#line 234
  ReferenceDriverConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceDriverConverter(driver, wpnType, artsIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuWeaponTypeAdapter *GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(u32 handle, u32 type, u16 driver, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> wpnType,
                                                                                            mm::mtl::IntrusivePtr<GfMenuReferenceNumber> artsIndex, bool isUpdateAlways) {
  // __LINE__ must be 242 as in the original source: it is the line argument of operator new.
#line 242
  ReferenceDriverWeaponTypeConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceDriverWeaponTypeConverter(driver, wpnType, artsIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

u32 GfMenuWeaponTypeAdapter::ReferenceDriverConverter::getDriverId() { return GfMenuReference::getReferenceDriverID(unknown08); }

u32 GfMenuWeaponTypeAdapter::ReferenceDriverConverter::getWpnType() { return unknown10->unknown0c; }

u32 GfMenuWeaponTypeAdapter::ReferenceDriverWeaponTypeConverter::getDriverId() { return GfMenuReference::getReferenceDriverID(unknown08); }

u32 GfMenuWeaponTypeAdapter::ReferenceDriverWeaponTypeConverter::getWpnType() { return unknown10->unknown0c; }

u32 GfMenuWeaponTypeAdapter::ReferenceDriverWeaponTypeConverter::getArtsIndex() { return unknown18->unknown0c; }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuWeaponTypeAdapter>(const mm::mtl::Delegate<bool()> *);
