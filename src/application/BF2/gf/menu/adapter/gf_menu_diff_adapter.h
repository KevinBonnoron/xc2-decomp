#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuDiffAdapter : public GfMenuAdapter {
public:
  enum Type {
    TYPE_ICON,
    TYPE_MUL_COL,
    TYPE_SUB,
    TYPE_DISP_SAME_ON,
    TYPE_DISP_SAME_OFF,
  };

  struct TypeInfo {
    bool (GfMenuDiffAdapter::*update)(int result);
    PluginSetup setup;
  };

  GfMenuDiffAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuDiffAdapter() override;
  static GfMenuAdapter *create(u32 handle, GfMenuAdapter *adapter, GfMenuAdapter *other, u32 type, bool isUpdateAlways);
  bool update_Icon(int result);
  bool update_MulCol(int result);
  bool update_Sub(int result);
  bool update_DispSameOn(int result);
  bool update_DispSameOff(int result);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool(int)> unknown30; // Inferred role: updater; original member name unknown.
  GfMenuAdapter *unknown50;               // Inferred role: adapter; original member name unknown.
  GfMenuAdapter *unknown58;               // Inferred role: other; original member name unknown.
};

static_assert(offsetof(GfMenuDiffAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuDiffAdapter, unknown50) == 0x50, "");
static_assert(sizeof(GfMenuDiffAdapter) == 0x60, "");

} // namespace gf
