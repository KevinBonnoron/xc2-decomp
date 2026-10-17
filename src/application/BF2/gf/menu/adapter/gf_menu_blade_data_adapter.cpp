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
    {&GfMenuBladeDataAdapter::update_DrArtsName, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuBladeDataAdapter::update_DrArtsIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuBladeDataAdapter::update_DrArtsLv, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 9}},
    {&GfMenuBladeDataAdapter::update_AffinityIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
};

GfMenuBladeDataAdapter::GfMenuBladeDataAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), converter(nullptr), blade(0), driver(0), artsSlot(0) {}

GfMenuBladeDataAdapter::~GfMenuBladeDataAdapter() {
  if (converter != nullptr) {
    delete converter;
    converter = nullptr;
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
        adapter->updater.bind(adapter, info.update);
        adapter->blade = blade;
        adapter->driver = driver;
        plugin->release();
        return adapter;
      }
    }
  }
  return nullptr;
}

bool GfMenuBladeDataAdapter::update_DrArtsName() {
  u32 arts = GfDataDriver::getDriverArtsID(driver, blade, artsSlot);
  if (arts == 0) {
    return false;
  }
  ui::UIStr text(GfDataDriverArts::getName(arts), false);
  setText(text);
  return text.isValid();
}

bool GfMenuBladeDataAdapter::update_DrArtsIcon() {
  u32 arts = GfDataDriver::getDriverArtsID(driver, blade, artsSlot);
  if (arts == 0) {
    return false;
  }
  setNumber(GfMenuBdat::getIconImageIndex(GfDataDriver::getDriverArtsIcon(arts)));
  return true;
}

bool GfMenuBladeDataAdapter::update_DrArtsLv() {
  if (GfDataDriver::getDriverArtsID(driver, blade, artsSlot) == 0) {
    return false;
  }
  setNumber(GfDataDriver::getDriverArtsLevel(driver, blade, artsSlot));
  return true;
}

bool GfMenuBladeDataAdapter::update_AffinityIcon() {
  u16 icon = GfMenuObjUtil::getBladeCompatibilityIconID(driver, blade);
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
    adapter->converter = converter;
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
  if (converter != nullptr) {
    u32 newDriver;
    u32 newBlade;
    converter->getID(newBlade, newDriver);
    if (blade != newBlade) {
      blade = newBlade;
      setChange();
    }
    if (driver != newDriver) {
      driver = newDriver;
      setChange();
    }
  }

  if ((flags & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0 && updater.isValid()) {
    setDisp(blade != 0 && driver != 0 && updater());
    flags &= ~FLAG_CHANGED;
  }
}

void GfMenuBladeDataAdapter::changeBladeData(u32 blade, u32 driver) {
  if (this->blade != blade) {
    this->blade = blade;
    setChange();
  }
  if (this->driver != driver) {
    this->driver = driver;
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
