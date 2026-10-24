#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuPouchAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuPouchAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getPouchIndex() = 0;
    virtual u32 getDriverId() = 0;
  };

  class ReferenceIndexConverter : public IConverter {
  public:
    ReferenceIndexConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driver) : number(number), driver(driver) {}
    ~ReferenceIndexConverter() override { number = nullptr; }
    u32 getPouchIndex() override { return number->number; }
    u32 getDriverId() override { return driver; }

    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
    u32 driver;
  };

  class ReferenceDriverConverter : public IConverter {
  public:
    ReferenceDriverConverter(u32 pouchIndex, u32 driverIndex) : pouchIndex(pouchIndex), driverIndex(driverIndex) {}
    u32 getPouchIndex() override { return pouchIndex; }
    u32 getDriverId() override { return GfMenuReference::getReferenceDriverID(driverIndex); }

    u32 pouchIndex;
    u32 driverIndex;
  };

  class ReferenceIndexReferenceDriverConverter : public IConverter {
  public:
    ReferenceIndexReferenceDriverConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driverIndex) : number(number), driverIndex(driverIndex) {}
    ~ReferenceIndexReferenceDriverConverter() override { number = nullptr; }
    u32 getPouchIndex() override { return number->number; }
    u32 getDriverId() override { return GfMenuReference::getReferenceDriverID(driverIndex); }

    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
    u32 driverIndex;
  };

  GfMenuPouchAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuPouchAdapter() override;
  static GfMenuPouchAdapter *create(u32 handle, u32 type, u16 pouchIndex, u32 driver, bool isUpdateAlways);
  bool update_PouchRemainTime();
  static GfMenuPouchAdapter *createFromReferenceIndex(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driver, bool isUpdateAlways);
  static GfMenuPouchAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuPouchAdapter *createFromReferenceDriver(u32 handle, u32 type, u32 pouchIndex, u32 driverIndex, bool isUpdateAlways);
  static GfMenuPouchAdapter *createFromReferenceIndexReferenceDriver(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driverIndex, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool()> updater;
  IConverter *converter;
  u8 _58[0x5c - 0x58];
  f32 time;
  u32 pouchIndex;
  u32 driver;
};

static_assert(offsetof(GfMenuPouchAdapter, updater) == 0x30, "");
static_assert(offsetof(GfMenuPouchAdapter, converter) == 0x50, "");
static_assert(offsetof(GfMenuPouchAdapter, time) == 0x5c, "");
static_assert(offsetof(GfMenuPouchAdapter, pouchIndex) == 0x60, "");
static_assert(offsetof(GfMenuPouchAdapter, driver) == 0x64, "");
static_assert(sizeof(GfMenuPouchAdapter) == 0x68, "");

} // namespace gf
