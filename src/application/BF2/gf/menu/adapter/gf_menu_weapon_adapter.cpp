#include "gf/menu/adapter/gf_menu_weapon_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_reference.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

constexpr int EQUIP_WEAPON_SLOT_CURRENT = -1;

static GfMenuWeaponAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuWeaponAdapter::update_Name, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuWeaponAdapter::update_Atk, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 1, 999}},
    {&GfMenuWeaponAdapter::update_Guard, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 100}},
    {&GfMenuWeaponAdapter::update_Critical, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 100}},
    {&GfMenuWeaponAdapter::update_Balance, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 1, 999}},
    {&GfMenuWeaponAdapter::update_TypeName, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuWeaponAdapter::update_Caption, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuWeaponAdapter::update_Image, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
};

GfMenuWeaponAdapter::GfMenuWeaponAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), unknown5c(0) {}

GfMenuWeaponAdapter::~GfMenuWeaponAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuWeaponAdapter *GfMenuWeaponAdapter::create(u32 handle, u32 type, u32 weapon, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 191 as in the original source: it is the line argument of operator new.
#line 191
      GfMenuWeaponAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuWeaponAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown58 = weapon;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuWeaponAdapter::update_Name(u32 weapon) {
  u8 *bdat;
  u32 textId;
  GfDataWeapon::getName(bdat, textId, weapon);
  setText(ui::UIStr(bdat, textId));
  return true;
}

bool GfMenuWeaponAdapter::update_Atk(u32 weapon) {
  setNumber(GfDataWeapon::getDamage(weapon));
  return true;
}

bool GfMenuWeaponAdapter::update_Guard(u32 weapon) {
  setNumber(GfDataWeapon::getGuardRatio(weapon));
  return true;
}

bool GfMenuWeaponAdapter::update_Critical(u32 weapon) {
  setNumber(GfDataWeapon::getCriticalRatio(weapon));
  return true;
}

bool GfMenuWeaponAdapter::update_Balance(u32 weapon) {
  setNumber(GfDataWeapon::getStability(weapon));
  return true;
}

bool GfMenuWeaponAdapter::update_TypeName(u32 weapon) {
  u8 *bdat;
  u32 textId;
  if (GfDataWeapon::getWeaponTypeNameByItem(bdat, textId, weapon) && GfMenuBdat::isValidBdatID(bdat, textId)) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuWeaponAdapter::update_Caption(u32 weapon) {
  u32 enhance = GfDataWeapon::getEnhance(weapon);
  if (enhance != 0) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_BTL_ENHANCE_CAP);
    u8 *bdat = GfDataBdat::getFP(BDAT_BTL_ENHANCE);
    if (GfMenuBdat::isValidBdatID(bdat, enhance)) {
      u8 caption = Bdat::getVal(bdat, "Caption", enhance).valueU8;
      if (GfMenuBdat::isValidBdatID(textBdat, caption)) {
        ui::UIStr text(textBdat, caption);
        text.unknown12 = enhance;
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuWeaponAdapter::update_Image(u32 weapon) {
  u16 rsc = GfBdatItem::get()->getPcWpnRscR(weapon);
  if (rsc != 0) {
    int image = GfBdatRsc::get()->getRSC_PcWpnMenuImageID(rsc);
    if (image != 0) {
      setNumber(image);
      return true;
    }
  }
  return false;
}

GfMenuWeaponAdapter *GfMenuWeaponAdapter::createFromBlade(u32 handle, u32 type, u32 blade, bool isUpdateAlways) {
  // __LINE__ must be 207 as in the original source: it is the line argument of operator new.
#line 207
  BladeConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) BladeConverter(blade);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuWeaponAdapter *GfMenuWeaponAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  GfMenuWeaponAdapter *adapter = create(handle, type, converter->getWeaponID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuWeaponAdapter *GfMenuWeaponAdapter::createFromReferenceBlade(u32 handle, u32 type, u32 index, bool isUpdateAlways) {
  // __LINE__ must be 216 as in the original source: it is the line argument of operator new.
#line 216
  ReferenceBladeConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceBladeConverter(index);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

u32 GfMenuWeaponAdapter::BladeConverter::getWeaponID() {
  DataParamAcc acc(OBJECT_TYPE_BLADE, unknown08, GIMMICK_TYPE_NONE);
  if (acc.isValid()) {
    return acc.getEquipWeapon(EQUIP_WEAPON_SLOT_CURRENT, false);
  }
  return 0;
}

u32 GfMenuWeaponAdapter::ReferenceBladeConverter::getWeaponID() {
  DataParamAcc acc(OBJECT_TYPE_BLADE, GfMenuReference::getReferenceBladeID(unknown08), GIMMICK_TYPE_NONE);
  if (acc.isValid()) {
    return acc.getEquipWeapon(EQUIP_WEAPON_SLOT_CURRENT, false);
  }
  return 0;
}

} // namespace gf
