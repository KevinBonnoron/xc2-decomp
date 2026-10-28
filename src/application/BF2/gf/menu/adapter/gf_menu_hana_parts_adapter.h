#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuHanaPartsAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuHanaPartsAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getPartsId() = 0;
  };

  class ListConverter : public IConverter {
  public:
    ListConverter(GfMenuIDList *list, int listIndex) : list(list), listIndex(listIndex) { list->addRef(); }
    ~ListConverter() override { mm::mtl::safeRelease(list); }
    u32 getPartsId() override;

    GfMenuIDList *list;
    int listIndex;
  };

  class ReferenceNumberConverter : public IConverter {
  public:
    ReferenceNumberConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) : number(number) {}
    ~ReferenceNumberConverter() override { number = nullptr; }
    u32 getPartsId() override;

    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
  };

  GfMenuHanaPartsAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuHanaPartsAdapter() override;
  static GfMenuHanaPartsAdapter *create(u32 handle, u32 type, u32 partsId, bool isUpdateAlways);
  bool update_partsText();
  bool update_partsIcon();
  bool update_needEther();
  static GfMenuHanaPartsAdapter *createFromList(u32 handle, u32 type, GfMenuIDList *list, int listIndex, bool isUpdateAlways);
  static GfMenuHanaPartsAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuHanaPartsAdapter *createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;               // Inferred role: converter; original member name unknown.
  u32 unknown58;                       // Inferred role: blade; original member name unknown.
  u32 unknown5c;                       // Inferred role: parts id; original member name unknown.
};

static_assert(offsetof(GfMenuHanaPartsAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuHanaPartsAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuHanaPartsAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuHanaPartsAdapter, unknown5c) == 0x5c, "");
static_assert(sizeof(GfMenuHanaPartsAdapter) == 0x60, "");

} // namespace gf
