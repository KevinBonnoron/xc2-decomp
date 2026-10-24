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
    ListConverter(GfMenuZoneMapList *list, u32 listIndex, bool isPageIndex) : list(list), listIndex(listIndex), isPageIndex(isPageIndex) { list->addRef(); }
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

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;               // Inferred role: converter; original member name unknown.
  u32 unknown58;                       // Inferred role: map id; original member name unknown.
  u32 unknown5c;                       // Inferred role: param; original member name unknown.
  u8 _60[0x64 - 0x60];
  bool unknown64; // Inferred role: group mode; original member name unknown.
};

static_assert(offsetof(GfMenuZoneMapAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuZoneMapAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuZoneMapAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuZoneMapAdapter, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuZoneMapAdapter, unknown64) == 0x64, "");
static_assert(sizeof(GfMenuZoneMapAdapter) == 0x68, "");

} // namespace gf
