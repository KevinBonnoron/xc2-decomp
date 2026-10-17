#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_arts_list.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuArtsAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuArtsAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual void getArtsInfo(MenuArtsInfo &info) = 0;
    virtual u32 getDriverId() = 0;
  };

  class ListConverter : public IConverter {
  public:
    ListConverter(GfMenuArtsList *list, int listIndex, u32 driver) : list(list), listIndex(listIndex), driver(driver) { list->addRef(); }
    ~ListConverter() override { mm::mtl::safeRelease(list); }
    void getArtsInfo(MenuArtsInfo &info) override;
    u32 getDriverId() override;

    GfMenuArtsList *list;
    int listIndex;
    u32 driver;
  };

  class ListReferenceDriverConverter : public IConverter {
  public:
    ListReferenceDriverConverter(GfMenuArtsList *list, int listIndex, u32 driverIndex) : list(list), listIndex(listIndex), driverIndex(driverIndex) {
      list->addRef();
    }
    ~ListReferenceDriverConverter() override { mm::mtl::safeRelease(list); }
    void getArtsInfo(MenuArtsInfo &info) override;
    u32 getDriverId() override;

    GfMenuArtsList *list;
    int listIndex;
    u32 driverIndex;
  };

  class ListReferenceDriverConverterReferenceIndex : public IConverter {
  public:
    ListReferenceDriverConverterReferenceIndex(GfMenuArtsList *list, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driverIndex)
        : list(list), number(number), driverIndex(driverIndex) {
      list->addRef();
    }
    ~ListReferenceDriverConverterReferenceIndex() override {
      mm::mtl::safeRelease(list);
      number = nullptr;
    }
    void getArtsInfo(MenuArtsInfo &info) override;
    u32 getDriverId() override;

    GfMenuArtsList *list;
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
    u32 driverIndex;
  };

  class ReferenceDriverSlotConverter : public IConverter {
  public:
    ReferenceDriverSlotConverter(u32 driverIndex, u32 slot) : driverIndex(driverIndex), slot(slot) {}
    ~ReferenceDriverSlotConverter() override { ; }
    void getArtsInfo(MenuArtsInfo &info) override;
    u32 getDriverId() override;

    u32 driverIndex;
    u32 slot;
  };

  static GfMenuArtsAdapter *createFromList(u32 handle, u32 type, GfMenuArtsList *list, int listIndex, u32 driver, bool isUpdateAlways);
  static GfMenuArtsAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuArtsAdapter *createFromListReferenceDriver(u32 handle, u32 type, GfMenuArtsList *list, int listIndex, u32 driverIndex,
                                                          bool isUpdateAlways);
  static GfMenuArtsAdapter *createFromListReferenceDriverReferenceIndex(u32 handle, u32 type, GfMenuArtsList *list,
                                                                        mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driverIndex,
                                                                        bool isUpdateAlways);
  static GfMenuArtsAdapter *createFromReferenceDriverSlot(u32 handle, u32 type, u32 driverIndex, u32 slot, bool isUpdateAlways);
  GfMenuArtsAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuArtsAdapter() override;
  static GfMenuArtsAdapter *create(u32 handle, u32 type, u32 arts, u32 driver, u32 level, bool isUpdateAlways);
  bool update_ArtsName();
  bool update_ArtsDescription();
  bool update_ArtsIconType();
  bool update_ArtsIconEnhance();
  bool update_ArtsIconReact();
  bool update_ArtsIconRange();
  bool update_ArtsWp();
  bool update_ArtsIconLevel();
  bool update_ArtsNumLevel();
  bool update_ArtsReleseLv();
  bool update_ArtsTextType();
  bool update_ArtsTextRange();
  bool update_ArtsTextReact();
  bool update_ArtsNumDamage();
  bool update_ArtsNumRecast();
  bool update_ArtsEnhanceDescription();
  bool update_ArtsIconReleseLv();
  bool update_ArtsNumDamageNextLv();
  bool update_ArtsNumRecastNextLv();
  bool update_ArtsEnhanceDescriptionNextLv();
  bool update_ArtsDispLvMax();
  bool update_ArtsTextIndex();
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool()> updater;
  IConverter *converter;
  u32 arts;
  u32 driver;
  u32 level;
  u32 capLevel;
};

static_assert(offsetof(GfMenuArtsAdapter, updater) == 0x30, "");
static_assert(offsetof(GfMenuArtsAdapter, converter) == 0x50, "");
static_assert(offsetof(GfMenuArtsAdapter, arts) == 0x58, "");
static_assert(offsetof(GfMenuArtsAdapter, driver) == 0x5c, "");
static_assert(offsetof(GfMenuArtsAdapter, level) == 0x60, "");
static_assert(offsetof(GfMenuArtsAdapter, capLevel) == 0x64, "");
static_assert(sizeof(GfMenuArtsAdapter) == 0x68, "");

} // namespace gf
