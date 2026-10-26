#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuEvTherterAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuEvTherterAdapter::*update)(u32 evTheater);
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getEvTheaterID() = 0;
  };

  class ReferenceConverter : public IConverter {
  public:
    ReferenceConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) : number(number) {}
    ~ReferenceConverter() override { number = nullptr; }
    u32 getEvTheaterID() override;

    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
  };

  GfMenuEvTherterAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuEvTherterAdapter() override;
  static GfMenuEvTherterAdapter *create(u32 handle, u32 type, u32 evTheater, bool isUpdateAlways);
  bool update_Title(u32 evTheater);
  bool update_Thumb(u32 evTheater);
  static GfMenuEvTherterAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuEvTherterAdapter *createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool(u32)> unknown30; // Inferred role: updater; original member name unknown.
  u32 unknown50;                          // Inferred role: event theater id; original member name unknown.
  u8 _54[0x58 - 0x54];
  IConverter *unknown58; // Inferred role: converter; original member name unknown.
};

static_assert(offsetof(GfMenuEvTherterAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuEvTherterAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuEvTherterAdapter, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuEvTherterAdapter) == 0x60, "");

} // namespace gf
