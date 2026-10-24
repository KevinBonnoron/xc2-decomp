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

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  u16 unknown50;                       // Inferred role: flag bits; original member name unknown.
  u16 unknown52;                       // Inferred role: flag index; original member name unknown.
  u32 unknown54;                       // Inferred role: flag value; original member name unknown.
};

static_assert(offsetof(GfMenuFlagAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuFlagAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuFlagAdapter, unknown52) == 0x52, "");
static_assert(offsetof(GfMenuFlagAdapter, unknown54) == 0x54, "");
static_assert(sizeof(GfMenuFlagAdapter) == 0x58, "");

} // namespace gf
