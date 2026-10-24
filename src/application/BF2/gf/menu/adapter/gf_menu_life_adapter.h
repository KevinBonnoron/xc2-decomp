#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuLifeAdapter : public GfMenuAdapter {
public:
  GfMenuLifeAdapter(ui::UIObjectPlugin *plugin);
  ~GfMenuLifeAdapter() override;
  static GfMenuLifeAdapter *create_Time_EffTime(u32 handle, const char *name, u8 index);
  static GfMenuLifeAdapter *create(ui::UIObjectPlugin *plugin, u8 index, void (GfMenuLifeAdapter::*update)(u8));
  void update_Time_EffTime(u8 index);
  static GfMenuLifeAdapter *create_Text_BonusName(u32 handle, const char *name, u8 index);
  void update_Text_BonusName(u8 index);
  static GfMenuLifeAdapter *create_Number_Bonus(u32 handle, const char *name, u8 index);
  void update_Number_Bonus(u8 index);
  void update(const fw::UpdateInfo &info) override;

  u8 unknown30;                          // Inferred role: index; original member name unknown.
  mm::mtl::Delegate<void(u8)> unknown38; // Inferred role: updater; original member name unknown.
  bool unknown58;                        // Inferred role: update requested; original member name unknown.
};

static_assert(offsetof(GfMenuLifeAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuLifeAdapter, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuLifeAdapter, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuLifeAdapter) == 0x60, "");

} // namespace gf
