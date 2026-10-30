#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

// Inferred role: menu blade data receiver; original type name unknown.
class unknown069 {
public:
  virtual void changeBladeData(u32 blade, u32 driver) = 0;
};

class GfMenuBladeDataAdapter : public GfMenuAdapter, public unknown069 {
public:
  struct TypeInfo {
    bool (GfMenuBladeDataAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual void getID(u32 &blade, u32 &driver) = 0;
  };

  class ReferenceConverter : public IConverter {
  public:
    ReferenceConverter(u32 bladeIndex, u32 driverIndex) : bladeIndex(bladeIndex), driverIndex(driverIndex) {}
    void getID(u32 &blade, u32 &driver) override;

    u32 bladeIndex;
    u32 driverIndex;
  };

  class BladeSetConverter : public IConverter {
  public:
    BladeSetConverter(u32 driver, int slot) : driver(driver), slot(slot) {}
    void getID(u32 &blade, u32 &driver) override;

    u32 driver;
    int slot;
  };

  class ReferenceBladeSetConverter : public IConverter {
  public:
    ReferenceBladeSetConverter(u32 driverIndex, int slot) : driverIndex(driverIndex), slot(slot) {}
    void getID(u32 &blade, u32 &driver) override;

    u32 driverIndex;
    int slot;
  };

  GfMenuBladeDataAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuBladeDataAdapter() override;
  static GfMenuBladeDataAdapter *create(u32 handle, u32 type, u32 blade, u32 driver, bool isUpdateAlways);
  bool update_DrArtsName();
  bool update_DrArtsIcon();
  bool update_DrArtsLv();
  bool update_AffinityIcon();
  static GfMenuBladeDataAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuBladeDataAdapter *createFromReference(u32 handle, u32 type, u32 bladeIndex, u32 driverIndex, bool isUpdateAlways);
  static GfMenuBladeDataAdapter *createFromBladeSet(u32 handle, u32 type, u32 driver, int slot, bool isUpdateAlways);
  static GfMenuBladeDataAdapter *createFromReferenceBladeSet(u32 handle, u32 type, u32 driverIndex, int slot, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;
  void changeBladeData(u32 blade, u32 driver) override;

  mm::mtl::Delegate<bool()> unknown38; // Inferred role: updater; original member name unknown.
  IConverter *unknown58;               // Inferred role: converter; original member name unknown.
  u32 unknown60;                       // Inferred role: blade; original member name unknown.
  u32 unknown64;                       // Inferred role: driver; original member name unknown.
  u32 unknown68;                       // Inferred role: arts slot; original member name unknown.
};

static_assert(offsetof(GfMenuBladeDataAdapter, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuBladeDataAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuBladeDataAdapter, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuBladeDataAdapter, unknown64) == 0x64, "");
static_assert(offsetof(GfMenuBladeDataAdapter, unknown68) == 0x68, "");
static_assert(sizeof(GfMenuBladeDataAdapter) == 0x70, "");

} // namespace gf
