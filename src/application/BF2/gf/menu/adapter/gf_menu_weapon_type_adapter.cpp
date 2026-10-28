#include "gf/menu/adapter/gf_menu_weapon_type_adapter.h"

#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_array.h"
#include "ui/ui_str.h"

namespace gf {

constexpr u32 ARTS_SLOT_MAX = 4;

GfMenuWeaponTypeAdapter::GfMenuWeaponTypeAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), unknown5c(0), unknown60(0), unknown64(0) {}

GfMenuWeaponTypeAdapter::~GfMenuWeaponTypeAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
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

  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    if (unknown58 != 0) {
      setDisp(unknown30());
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_CHANGED;
  }
}

bool GfMenuWeaponTypeAdapter::getDriverArts(DriverArts &driverArts) {
  mm::mtl::FixedArray<u32, 4> arts;
  if (GfMenuObjUtil::getEnableArts(arts, unknown58, unknown5c)) {
    if (unknown60 < ARTS_SLOT_MAX) {
      driverArts.unknown00 = arts[unknown60];
      driverArts.unknown04 = GfDataDriverArts::getArtsLevel(unknown58, driverArts.unknown00);
      return true;
    }
    return false;
  }
  return false;
}

} // namespace gf
