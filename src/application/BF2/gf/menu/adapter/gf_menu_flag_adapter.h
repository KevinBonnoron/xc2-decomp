#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuFlagAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuFlagAdapter::*update)();
    PluginSetup setup;
  };

  GfMenuFlagAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuFlagAdapter() override;
  static GfMenuFlagAdapter *create(u32 handle, u32 type, u16 flagBits, u16 flagIndex, bool isUpdateAlways);
  bool update_FlagDisp();
  bool update_FlagNum();
  void update(const fw::UpdateInfo &info) override;
  bool getFlagValue(u32 &value);

  mm::mtl::Delegate<bool()> updater;
  u16 flagBits;
  u16 flagIndex;
  u32 flagValue;
};

static_assert(offsetof(GfMenuFlagAdapter, updater) == 0x30, "");
static_assert(offsetof(GfMenuFlagAdapter, flagBits) == 0x50, "");
static_assert(offsetof(GfMenuFlagAdapter, flagIndex) == 0x52, "");
static_assert(offsetof(GfMenuFlagAdapter, flagValue) == 0x54, "");
static_assert(sizeof(GfMenuFlagAdapter) == 0x58, "");

} // namespace gf
