#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
class UIStr;
} // namespace ui

namespace gf {

class IGfMenuReferenceItem : public mm::mtl::ReferenceObject {
public:
  virtual void getItem(MenuItemInfo &info) const = 0;
};

class GfMenuEnhanceAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuEnhanceAdapter::*update)(u32 enhance);
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getEnhanceID() = 0;
  };

  class ItemConverter : public IConverter {
  public:
    ItemConverter(const MenuItemInfo &info) : info(info) {}
    ~ItemConverter() override {}
    u32 getEnhanceID() override;
    static u32 getItemEnhance(const MenuItemInfo &info);

    MenuItemInfo info;
  };

  class ItemListConverter : public IConverter {
  public:
    ItemListConverter(GfMenuItemList *list, int listIndex) : list(list), listIndex(listIndex) {}
    ~ItemListConverter() override {}
    u32 getEnhanceID() override;

    GfMenuItemList *list;
    int listIndex;
  };

  class ReferenceItemConverter : public IConverter {
  public:
    ReferenceItemConverter(mm::mtl::IntrusivePtr<IGfMenuReferenceItem> item) : item(item) {}
    ~ReferenceItemConverter() override { item = nullptr; }
    u32 getEnhanceID() override;

    mm::mtl::IntrusivePtr<IGfMenuReferenceItem> item;
  };

  class ArtsConverter : public IConverter {
  public:
    ArtsConverter(u32 arts, u32 level) : arts(arts), level(level) {}
    ~ArtsConverter() override {}
    u32 getEnhanceID() override;

    u32 arts;
    u32 level;
  };

  GfMenuEnhanceAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuEnhanceAdapter() override;
  static GfMenuEnhanceAdapter *create(u32 handle, u32 type, u32 enhance, bool isUpdateAlways);
  bool update_Caption(u32 enhance);
  static GfMenuEnhanceAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuEnhanceAdapter *createFromReferenceItem(u32 handle, u32 type, mm::mtl::IntrusivePtr<IGfMenuReferenceItem> item, bool isUpdateAlways);
  static GfMenuEnhanceAdapter *createFromArts(u32 handle, u32 type, u32 arts, u32 level, bool isUpdateAlways);
  static bool getEnhanceCaption(u32 enhance, ui::UIStr &caption);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool(u32)> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;                  // Inferred role: converter; original member name unknown.
  u32 unknown58;                          // Inferred role: enhance; original member name unknown.
  u8 _5c[0x60 - 0x5c];
};

static_assert(offsetof(GfMenuEnhanceAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuEnhanceAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuEnhanceAdapter, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuEnhanceAdapter) == 0x60, "");

} // namespace gf
