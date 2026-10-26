#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuWorldMapAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuWorldMapAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getMapId() = 0;
  };

  class ReferenceConverter : public IConverter {
  public:
    u32 getMapId() override;
  };

  GfMenuWorldMapAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuWorldMapAdapter() override;
  static GfMenuWorldMapAdapter *create(u32 handle, u32 type, u16 mapId, bool isUpdateAlways);
  bool update_WorldMapName();
  bool update_DevelopPoint();
  bool update_DevelopLvIcon();
  bool update_CurrentDisp();
  static GfMenuWorldMapAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuWorldMapAdapter *createFromReference(u32 handle, u32 type, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;
  u32 convMap2Zone(u32 mapId);

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;               // Inferred role: converter; original member name unknown.
  u16 unknown58;                       // Inferred role: map id; original member name unknown.
  u8 _5a[0x5c - 0x5a];
  u32 unknown5c; // Inferred role: unused; original member name unknown.
};

static_assert(offsetof(GfMenuWorldMapAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuWorldMapAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuWorldMapAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuWorldMapAdapter, unknown5c) == 0x5c, "");
static_assert(sizeof(GfMenuWorldMapAdapter) == 0x60, "");

} // namespace gf
