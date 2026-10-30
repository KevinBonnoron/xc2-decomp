#include "gf/menu/adapter/gf_menu_blade_data_adapter.h"

#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

static GfMenuBladeDataAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuBladeDataAdapter::update_DrArtsName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuBladeDataAdapter::update_DrArtsIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuBladeDataAdapter::update_DrArtsLv, {GfMenuAdapter::unknown004_0, 0, 9}},
    {&GfMenuBladeDataAdapter::update_AffinityIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
};

GfMenuBladeDataAdapter::GfMenuBladeDataAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), unknown58(nullptr), unknown60(0), unknown64(0), unknown68(0) {}

GfMenuBladeDataAdapter::~GfMenuBladeDataAdapter() {
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
}

GfMenuBladeDataAdapter *GfMenuBladeDataAdapter::create(u32 handle, u32 type, u32 blade, u32 driver, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 162 as in the original source: it is the line argument of operator new.
#line 162
      GfMenuBladeDataAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuBladeDataAdapter(plugin, isUpdateAlways);
      if (adapter != nullptr) {
        adapter->unknown38.bind(adapter, info.update);
        adapter->unknown60 = blade;
        adapter->unknown64 = driver;
        plugin->release();
        return adapter;
      }
    }
  }
  return nullptr;
}

bool GfMenuBladeDataAdapter::update_DrArtsName() {
  u32 arts = GfDataDriver::getDriverArtsID(unknown64, unknown60, unknown68);
  if (arts == 0) {
    return false;
  }
  ui::UIStr text(GfDataDriverArts::getName(arts), false);
  setText(text);
  return text.isValid();
}

bool GfMenuBladeDataAdapter::update_DrArtsIcon() {
  u32 arts = GfDataDriver::getDriverArtsID(unknown64, unknown60, unknown68);
  if (arts == 0) {
    return false;
  }
  setNumber(GfMenuBdat::getIconImageIndex(GfDataDriver::getDriverArtsIcon(arts)));
  return true;
}

bool GfMenuBladeDataAdapter::update_DrArtsLv() {
  if (GfDataDriver::getDriverArtsID(unknown64, unknown60, unknown68) == 0) {
    return false;
  }
  setNumber(GfDataDriver::getDriverArtsLevel(unknown64, unknown60, unknown68));
  return true;
}

bool GfMenuBladeDataAdapter::update_AffinityIcon() {
  u16 icon = GfMenuObjUtil::getBladeCompatibilityIconID(unknown64, unknown60);
  if (icon == 0) {
    return false;
  }
  setNumber(GfMenuBdat::getIconImageIndex(icon));
  return true;
}

GfMenuBladeDataAdapter *GfMenuBladeDataAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  u32 blade;
  u32 driver;
  converter->getID(blade, driver);
  GfMenuBladeDataAdapter *adapter = create(handle, type, blade, driver, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown58 = converter;
  }
  return adapter;
}

GfMenuBladeDataAdapter *GfMenuBladeDataAdapter::createFromReference(u32 handle, u32 type, u32 bladeIndex, u32 driverIndex, bool isUpdateAlways) {
  // __LINE__ must be 198 as in the original source: it is the line argument of operator new.
#line 198
  ReferenceConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceConverter(bladeIndex, driverIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuBladeDataAdapter *GfMenuBladeDataAdapter::createFromBladeSet(u32 handle, u32 type, u32 driver, int slot, bool isUpdateAlways) {
  // __LINE__ must be 207 as in the original source: it is the line argument of operator new.
#line 207
  BladeSetConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) BladeSetConverter(driver, slot);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuBladeDataAdapter *GfMenuBladeDataAdapter::createFromReferenceBladeSet(u32 handle, u32 type, u32 driverIndex, int slot, bool isUpdateAlways) {
  // __LINE__ must be 216 as in the original source: it is the line argument of operator new.
#line 216
  ReferenceBladeSetConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceBladeSetConverter(driverIndex, slot);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

void GfMenuBladeDataAdapter::update(const fw::UpdateInfo &info) {
  if (unknown58 != nullptr) {
    u32 newDriver;
    u32 newBlade;
    unknown58->getID(newBlade, newDriver);
    if (unknown60 != newBlade) {
      unknown60 = newBlade;
      setChange();
    }
    if (unknown64 != newDriver) {
      unknown64 = newDriver;
      setChange();
    }
  }

  if ((unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0 && unknown38.isValid()) {
    setDisp(unknown60 != 0 && unknown64 != 0 && unknown38());
    unknown20 &= ~FLAG_CHANGED;
  }
}

void GfMenuBladeDataAdapter::changeBladeData(u32 blade, u32 driver) {
  if (this->unknown60 != blade) {
    this->unknown60 = blade;
    setChange();
  }
  if (this->unknown64 != driver) {
    this->unknown64 = driver;
    setChange();
  }
}

void GfMenuBladeDataAdapter::ReferenceConverter::getID(u32 &blade, u32 &driver) {
  blade = GfMenuReference::getReferenceBladeID(bladeIndex);
  driver = GfMenuReference::getReferenceDriverID(driverIndex);
}

void GfMenuBladeDataAdapter::BladeSetConverter::getID(u32 &blade, u32 &driver) {
  DataParamAcc acc(OBJECT_TYPE_DRIVER, this->driver, GIMMICK_TYPE_NONE);
  if (acc.isValid()) {
    blade = acc.getBlade(slot, false);
    driver = this->driver;
  }
}

void GfMenuBladeDataAdapter::ReferenceBladeSetConverter::getID(u32 &blade, u32 &driver) {
  u32 referenceDriver = GfMenuReference::getReferenceDriverID(driverIndex);
  blade = 0;
  driver = 0;
  DataParamAcc acc(OBJECT_TYPE_DRIVER, referenceDriver, GIMMICK_TYPE_NONE);
  if (acc.isValid()) {
    blade = acc.getBlade(slot, false);
    driver = referenceDriver;
  }
}

} // namespace gf
