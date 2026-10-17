#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuGameAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuGameAdapter::*update)();
    PluginSetup setup;
  };

  GfMenuGameAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuGameAdapter() override;
  static GfMenuAdapter *create(u32 handle, u32 type, bool isUpdateAlways);
  bool update_GamePlayTime();
  bool update_Money();
  bool update_FieldTime();
  bool update_WeatherIcon();
  bool update_CloudIcon();
  bool update_MapName();
  bool update_LocationName();
  bool update_TimeZoneName();
  bool update_TimeZoneIcon();
  bool update_ReferenceNum();
  bool update_MercenariesName();
  bool update_MercenariesLv();
  bool update_MercenariesPoint();
  bool update_MercenariesPointMax();
  bool update_RealYear();
  bool update_RealTime();
  bool update_Chapter();
  bool update_DispAccess();
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool()> updater;
  u32 referenceIndex;
};

static_assert(offsetof(GfMenuGameAdapter, updater) == 0x30, "");
static_assert(offsetof(GfMenuGameAdapter, referenceIndex) == 0x50, "");
static_assert(sizeof(GfMenuGameAdapter) == 0x58, "");

} // namespace gf
