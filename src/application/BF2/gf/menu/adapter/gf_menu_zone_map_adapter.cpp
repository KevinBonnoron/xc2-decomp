#include "gf/menu/adapter/gf_menu_zone_map_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

static GfMenuZoneMapAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuZoneMapAdapter::update_ZoneMapName, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuZoneMapAdapter::update_ZonePointName, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
};

GfMenuZoneMapAdapter::GfMenuZoneMapAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), converter(nullptr), mapId(0), param(0), _60(), isGroupMode(false) {}

GfMenuZoneMapAdapter::~GfMenuZoneMapAdapter() {
  if (converter != nullptr) {
    delete converter;
    converter = nullptr;
  }
}

GfMenuZoneMapAdapter *GfMenuZoneMapAdapter::create(u32 handle, u32 type, u32 mapId, u32 param, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 195 as in the original source: it is the line argument of operator new.
#line 195
      GfMenuZoneMapAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuZoneMapAdapter(plugin, isUpdateAlways);
      adapter->updater.bind(adapter, info.update);
      adapter->mapId = mapId;
      adapter->param = param;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuZoneMapAdapter::update_ZoneMapName() {
  u8 *bdat = isGroupMode ? GfDataBdat::getFP(BDAT_MNU_MAP_GROUP) : GfDataBdat::getFP(BDAT_MNU_MAP_INFO);
  u32 nameId = Bdat::getVal(bdat, "disp_name", mapId).valueU16;
  setText(ui::UIStr(GfDataBdat::getFP(BDAT_MNU_MAP_LEVEL_NAME_MS), nameId));
  return true;
}

bool GfMenuZoneMapAdapter::update_ZonePointName() {
  setText(ui::UIStr(GfDataBdat::getFP(BDAT_FLD_LANDMARK), param));
  return true;
}

GfMenuZoneMapAdapter *GfMenuZoneMapAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  u32 mapId = converter->getMapId();
  GfMenuZoneMapAdapter *adapter = create(handle, type, mapId, converter->getParam(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->converter = converter;
  }
  return adapter;
}

GfMenuZoneMapAdapter *GfMenuZoneMapAdapter::createFromList(u32 handle, u32 type, GfMenuZoneMapList *list, u32 listIndex, bool isPageIndex, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 231 as in the original source: it is the line argument of operator new.
#line 231
  ListConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ListConverter(list, listIndex, isPageIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

void GfMenuZoneMapAdapter::update(const fw::UpdateInfo &info) {
  if (converter != nullptr) {
    u32 newMapId = converter->getMapId();
    u32 newParam = converter->getParam();
    bool newIsGroupMode = converter->isGroupMode();
    if (mapId != newMapId) {
      mapId = newMapId;
      setChange();
    }
    if (param != newParam) {
      param = newParam;
      setChange();
    }
    if (isGroupMode != newIsGroupMode) {
      isGroupMode = newIsGroupMode;
      setChange();
    }
  }

  if (updater.isValid() && (flags & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    if (mapId != 0) {
      setDisp(updater());
    } else {
      setDisp(false);
    }
    flags &= ~FLAG_CHANGED;
  }
}

bool GfMenuZoneMapAdapter::ListConverter::isGroupMode() { return list->isGroupMode; }

} // namespace gf
