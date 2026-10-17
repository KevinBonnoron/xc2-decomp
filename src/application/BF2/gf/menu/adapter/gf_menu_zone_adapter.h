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

class GfMenuZoneAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuZoneAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getZoneId() = 0;
  };

  class ReferenceZoneConverter : public IConverter {
  public:
    u32 getZoneId() override { return GfMenuReference::getReferenceZoneID(); }
  };

  class ReferenceNumberConverter : public IConverter {
  public:
    ReferenceNumberConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) : number(number) {}
    ~ReferenceNumberConverter() override { number = nullptr; }
    u32 getZoneId() override { return number->number; }

    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
  };

  GfMenuZoneAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuZoneAdapter() override;
  static GfMenuZoneAdapter *create(u32 handle, u32 type, u16 zone, bool isUpdateAlways);
  bool update_ZoneName();
  bool update_ZoneLv();
  bool update_ZoneIcon();
  bool update_ZoneLvIcon();
  bool update_ZoneStatColor();
  bool update_ZoneNoticeDisp();
  bool update_ZoneNotice();
  static GfMenuZoneAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuZoneAdapter *createFromReferenceZone(u32 handle, u32 type, bool isUpdateAlways);
  static GfMenuZoneAdapter *createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool()> updater;
  IConverter *converter;
  u16 zone;
  u32 team;
};

static_assert(offsetof(GfMenuZoneAdapter, updater) == 0x30, "");
static_assert(offsetof(GfMenuZoneAdapter, converter) == 0x50, "");
static_assert(offsetof(GfMenuZoneAdapter, zone) == 0x58, "");
static_assert(offsetof(GfMenuZoneAdapter, team) == 0x5c, "");
static_assert(sizeof(GfMenuZoneAdapter) == 0x60, "");

} // namespace gf
