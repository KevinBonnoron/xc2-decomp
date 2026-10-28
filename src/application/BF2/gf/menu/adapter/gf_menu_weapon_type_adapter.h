#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuWeaponTypeAdapter : public GfMenuAdapter {
public:
  struct DriverArts {
    u32 unknown00; // Inferred role: arts; original member name unknown.
    u32 unknown04; // Inferred role: level; original member name unknown.
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getDriverId() = 0;
    virtual u32 getWpnType() = 0;
    virtual u32 getArtsIndex() = 0;
  };

  GfMenuWeaponTypeAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuWeaponTypeAdapter() override;
  bool update_WpnTypeName();
  bool update_WpnTypeIcon();
  bool update_WpnTypeWP();
  bool update_ArtsName();
  bool update_ArtsIconType();
  bool update_ArtsIconEnhance();
  bool update_ArtsIconReact();
  bool update_ArtsIconRange();
  bool update_ArtsLevel();
  bool update_ArtsIconLevel();
  bool update_ArtsDescription();
  bool update_ArtsWp();
  bool update_ArtsDriverLevel();
  bool update_ArtsLevel0Disp();
  bool update_ArtsLevelMaxDisp();
  bool update_ArtsEnhanceDescription();
  bool update_ArtsReleseLv();
  void update(const fw::UpdateInfo &info) override;
  bool getDriverArts(DriverArts &driverArts);

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;               // Inferred role: converter; original member name unknown.
  u32 unknown58;                       // Inferred role: driver; original member name unknown.
  u32 unknown5c;                       // Inferred role: weapon type; original member name unknown.
  u32 unknown60;                       // Inferred role: arts index; original member name unknown.
  u32 unknown64;                       // Role and original member name unknown.
};

static_assert(offsetof(GfMenuWeaponTypeAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuWeaponTypeAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuWeaponTypeAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuWeaponTypeAdapter, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuWeaponTypeAdapter, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuWeaponTypeAdapter, unknown64) == 0x64, "");
static_assert(sizeof(GfMenuWeaponTypeAdapter) == 0x68, "");

} // namespace gf
