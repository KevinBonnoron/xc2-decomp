#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/list/gf_menu_zone_map_list.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuZoneMapAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuZoneMapAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getMapId() = 0;
    virtual u32 getParam() = 0;
    virtual bool isGroupMode() = 0;
  };

  class ListConverter : public IConverter {
  public:
    ListConverter(GfMenuZoneMapList *list, u32 listIndex, bool isPageIndex) : list(list), listIndex(listIndex), isPageIndex(isPageIndex) {
      list->addRef();
    }
    ~ListConverter() override { mm::mtl::safeRelease(list); }
    u32 getMapId() override;
    u32 getParam() override;
    bool isGroupMode() override;

    GfMenuZoneMapList *list;
    u32 listIndex;
    bool isPageIndex;
  };

  GfMenuZoneMapAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuZoneMapAdapter() override;
  static GfMenuZoneMapAdapter *create(u32 handle, u32 type, u32 mapId, u32 param, bool isUpdateAlways);
  bool update_ZoneMapName();
  bool update_ZonePointName();
  static GfMenuZoneMapAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuZoneMapAdapter *createFromList(u32 handle, u32 type, GfMenuZoneMapList *list, u32 listIndex, bool isPageIndex, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool()> updater;
  IConverter *converter;
  u32 mapId;
  u32 param;
  u8 _60[0x64 - 0x60];
  bool isGroupMode;
};

static_assert(offsetof(GfMenuZoneMapAdapter, updater) == 0x30, "");
static_assert(offsetof(GfMenuZoneMapAdapter, converter) == 0x50, "");
static_assert(offsetof(GfMenuZoneMapAdapter, mapId) == 0x58, "");
static_assert(offsetof(GfMenuZoneMapAdapter, param) == 0x5c, "");
static_assert(offsetof(GfMenuZoneMapAdapter, isGroupMode) == 0x64, "");
static_assert(sizeof(GfMenuZoneMapAdapter) == 0x68, "");

} // namespace gf
