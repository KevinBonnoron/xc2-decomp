#include "gf/menu/adapter/gf_menu_pouch_adapter.h"

#include "gf/data/gf_data_driver.h"
#include "gf/game/item/gf_pouch_util.h"
#include "gf/gf_allocator.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"

namespace gf {

static GfMenuPouchAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuPouchAdapter::update_PouchRemainTime, {GfMenuAdapter::PLUGIN_TYPE_TIME, 3, 0}},
};

GfMenuPouchAdapter::GfMenuPouchAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), _58(), unknown5c(0.0f), unknown60(0) {}

GfMenuPouchAdapter::~GfMenuPouchAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuPouchAdapter *GfMenuPouchAdapter::create(u32 handle, u32 type, u16 pouchIndex, u32 driver, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 183 as in the original source: it is the line argument of operator new.
#line 183
      GfMenuPouchAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuPouchAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown60 = pouchIndex;
      adapter->unknown64 = driver;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

GfMenuPouchAdapter *GfMenuPouchAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  u16 pouchIndex = converter->getPouchIndex();
  u32 driver = converter->getDriverId();
  GfMenuPouchAdapter *adapter = create(handle, type, pouchIndex, driver, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuPouchAdapter *GfMenuPouchAdapter::createFromReferenceDriver(u32 handle, u32 type, u32 pouchIndex, u32 driverIndex, bool isUpdateAlways) {
  // __LINE__ must be 207 as in the original source: it is the line argument of operator new.
#line 207
  ReferenceDriverConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceDriverConverter(pouchIndex, driverIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

void GfMenuPouchAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newPouchIndex = unknown50->getPouchIndex();
    if (unknown60 != newPouchIndex) {
      unknown60 = newPouchIndex;
      setChange();
    }
    u32 newDriver = unknown50->getDriverId();
    if (unknown64 != newDriver) {
      unknown64 = newDriver;
      setChange();
    }
  }
  SDataPouch *pouch = GfPouchUtil::getPouch(unknown64, unknown60);
  if (unknown5c != pouch->unknown00) {
    unknown5c = pouch->unknown00;
    setChange();
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    setDisp(unknown30());
    unknown20 &= ~FLAG_CHANGED;
  }
}

} // namespace gf
