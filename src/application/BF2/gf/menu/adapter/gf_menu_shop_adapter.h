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

class GfMenuShopAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuShopAdapter::*update)(u32 shop);
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getShopID() = 0;
  };

  class ReferenceConverter : public IConverter {
  public:
    u32 getShopID() override;
  };

  class ReferenceNumberConverter : public IConverter {
  public:
    ReferenceNumberConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) : number(number) {}
    ~ReferenceNumberConverter() override { number = nullptr; }
    u32 getShopID() override;

    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
  };

  GfMenuShopAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuShopAdapter() override;
  static GfMenuShopAdapter *create(u32 handle, u32 type, u32 shop, bool isUpdateAlways);
  bool update_Name(u32 shop);
  bool update_CategoryName(u32 shop);
  bool update_Icon(u32 shop);
  bool update_CategoryIcon(u32 shop);
  bool update_Owner(u32 shop);
  static GfMenuShopAdapter *createFromReference(u32 handle, u32 type, bool isUpdateAlways);
  static GfMenuShopAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuShopAdapter *createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool(u32)> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *m_iConverter;               // Inferred role: converter; original member name unknown.
  u32 unknown58;                          // Inferred role: shop; original member name unknown.
  u32 unknown5c;                          // Role and original member name unknown.
};

static_assert(offsetof(GfMenuShopAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuShopAdapter, m_iConverter) == 0x50, "");
static_assert(offsetof(GfMenuShopAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuShopAdapter, unknown5c) == 0x5c, "");
static_assert(sizeof(GfMenuShopAdapter) == 0x60, "");

} // namespace gf
