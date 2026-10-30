#include "gf/menu/adapter/gf_menu_world_map_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_develop.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_reference.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: map id to nation table read by convMap2Zone; original type, table and member names unknown.
struct unknown001 {
  u32 unknown00; // Inferred role: map id; original member name unknown.
  u32 unknown04; // Inferred role: nation; original member name unknown.
};

static const unknown001 unknown002[] = {
    {3, NATION_FIRST},
    {6, 2},
    {9, 3},
    {10, 4},
    {14, NATION_IYASAKI},
    {12, NATION_ARCADIA},
    {13, 7},
};

static GfMenuWorldMapAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuWorldMapAdapter::update_WorldMapName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuWorldMapAdapter::update_DevelopPoint, {GfMenuAdapter::unknown004_0, 0, 20000}},
    {&GfMenuWorldMapAdapter::update_DevelopLvIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuWorldMapAdapter::update_CurrentDisp, {GfMenuAdapter::unknown004_3, 0, 0}},
};

GfMenuWorldMapAdapter::GfMenuWorldMapAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), unknown5c(0) {}

GfMenuWorldMapAdapter::~GfMenuWorldMapAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuWorldMapAdapter *GfMenuWorldMapAdapter::create(u32 handle, u32 type, u16 mapId, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 165 as in the original source: it is the line argument of operator new.
#line 165
      GfMenuWorldMapAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuWorldMapAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown58 = mapId;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuWorldMapAdapter::update_WorldMapName() {
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_MAPLIST);
  u32 nameId = Bdat::getVal(bdat, "nameID", unknown58).valueU16;
  setText(ui::UIStr(GfDataBdat::getFP(BDAT_FLD_MAPINFO), nameId));
  return true;
}

bool GfMenuWorldMapAdapter::update_DevelopPoint() {
  u32 nation = convMap2Zone(unknown58);
  if (nation == 0) {
    return false;
  }
  setNumber(GfDataDevelop::getPoint(nation));
  return true;
}

bool GfMenuWorldMapAdapter::update_DevelopLvIcon() {
  u32 nation = convMap2Zone(unknown58);
  if (nation == 0) {
    return false;
  }
  setNumber(GfDataDevelop::getLevel(nation));
  return true;
}

bool GfMenuWorldMapAdapter::update_CurrentDisp() { return unknown58 == GfGameManager::getMapID(); }

GfMenuWorldMapAdapter *GfMenuWorldMapAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  GfMenuWorldMapAdapter *adapter = create(handle, type, converter->getMapId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuWorldMapAdapter *GfMenuWorldMapAdapter::createFromReference(u32 handle, u32 type, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 207 as in the original source: it is the line argument of operator new.
#line 207
  ReferenceConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceConverter();
  GfMenuWorldMapAdapter *adapter = create(handle, type, GfMenuReference::getReferenceWorldMapID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

void GfMenuWorldMapAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newMapId = unknown50->getMapId();
    if (unknown58 != newMapId) {
      unknown58 = newMapId;
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

u32 GfMenuWorldMapAdapter::convMap2Zone(u32 mapId) {
  for (u32 i = 0; i < sizeof(unknown002) / sizeof(unknown002[0]); i++) {
    if (unknown002[i].unknown00 == mapId) {
      return unknown002[i].unknown04;
    }
  }
  return 0;
}

u32 GfMenuWorldMapAdapter::ReferenceConverter::getMapId() { return GfMenuReference::getReferenceWorldMapID(); }

} // namespace gf
