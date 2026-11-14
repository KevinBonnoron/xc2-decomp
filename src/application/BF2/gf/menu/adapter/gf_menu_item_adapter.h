#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_reference_list.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuItemAdapter : public GfMenuAdapter, public unknown139 {
public:
  class ListConverter;
  class PouchConverter;
  class MissionConverter;

  struct TypeInfo {
    bool (GfMenuItemAdapter::*update)(const MenuItemInfo &info);
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual void getItemInfo(MenuItemInfo &info) = 0;
    virtual ListConverter *fromList();
    virtual PouchConverter *fromPouch();
    virtual MissionConverter *fromMission();
  };

  class ListConverter : public IConverter {
  public:
    ListConverter(GfMenuItemList *list, int listIndex) : list(list), listIndex(listIndex) { list->addRef(); }
    ~ListConverter() override { mm::mtl::safeRelease(list); }
    void getItemInfo(MenuItemInfo &info) override;
    ListConverter *fromList() override { return this; }

    GfMenuItemList *list;
    int listIndex;
  };

  class ReferenceListConverter : public IConverter {
  public:
    ReferenceListConverter(mm::mtl::IntrusivePtr<GfMenuReferenceList<GfMenuItemList>> list, u32 listIndex) : list(list), listIndex(listIndex) {}
    ~ReferenceListConverter() override { list = nullptr; }
    void getItemInfo(MenuItemInfo &info) override;

    mm::mtl::IntrusivePtr<GfMenuReferenceList<GfMenuItemList>> list;
    u32 listIndex;
  };

  class ReferenceItemConverter : public IConverter {
  public:
    ReferenceItemConverter(mm::mtl::IntrusivePtr<IGfMenuReferenceItem> item) : item(item) {}
    ~ReferenceItemConverter() override { item = nullptr; }
    void getItemInfo(MenuItemInfo &info) override;

    mm::mtl::IntrusivePtr<IGfMenuReferenceItem> item;
  };

  class PouchConverter : public IConverter {
  public:
    PouchConverter(u32 pouchIndex, u32 driver) : pouchIndex(pouchIndex), driver(driver) {}
    void getItemInfo(MenuItemInfo &info) override;
    PouchConverter *fromPouch() override { return this; }

    u32 pouchIndex;
    u32 driver;
  };

  class PouchReferenceIndexConverter : public IConverter {
  public:
    PouchReferenceIndexConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driver) : number(number), driver(driver) {}
    ~PouchReferenceIndexConverter() override { number = nullptr; }
    void getItemInfo(MenuItemInfo &info) override;

    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
    u32 driver;
  };

  class PouchReferenceDriverConverter : public IConverter {
  public:
    PouchReferenceDriverConverter(u32 pouchIndex, u32 driverIndex) : pouchIndex(pouchIndex), driverIndex(driverIndex) {}
    void getItemInfo(MenuItemInfo &info) override;

    u32 pouchIndex;
    u32 driverIndex;
  };

  class PouchReferenceIndexReferenceDriverConverter : public IConverter {
  public:
    PouchReferenceIndexReferenceDriverConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driverIndex) : number(number), driverIndex(driverIndex) {}
    ~PouchReferenceIndexReferenceDriverConverter() override { number = nullptr; }
    void getItemInfo(MenuItemInfo &info) override;

    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
    u32 driverIndex;
  };

  class MissionConverter : public IConverter {
  public:
    MissionConverter(u32 mission, u32 index) : mission(mission), index(index) {}
    void getItemInfo(MenuItemInfo &info) override;
    MissionConverter *fromMission() override { return this; }

    u32 mission;
    u32 index;
  };

  class ReferenceMissionConverter : public IConverter {
  public:
    ReferenceMissionConverter(u32 index) : index(index) {}
    void getItemInfo(MenuItemInfo &info) override;
    virtual ReferenceMissionConverter *fromReferenceMission() { return this; }

    u32 index;
  };

  class DriverEquipConverter : public IConverter {
  public:
    DriverEquipConverter(u32 driver, u32 slot) : driver(driver), slot(slot) {}
    void getItemInfo(MenuItemInfo &info) override;

    u32 driver;
    u32 slot;
  };

  class ReferenceDriverEquipConverter : public IConverter {
  public:
    ReferenceDriverEquipConverter(u32 driverIndex, u32 slot) : driverIndex(driverIndex), slot(slot) {}
    void getItemInfo(MenuItemInfo &info) override;

    u32 driverIndex;
    u32 slot;
  };

  class BladeEquipConverter : public IConverter {
  public:
    BladeEquipConverter(u32 blade, u32 slot) : blade(blade), slot(slot) {}
    void getItemInfo(MenuItemInfo &info) override;

    u32 blade;
    u32 slot;
  };

  class ReferenceBladeEquipConverter : public IConverter {
  public:
    ReferenceBladeEquipConverter(u32 bladeIndex, u32 slot) : bladeIndex(bladeIndex), slot(slot) {}
    void getItemInfo(MenuItemInfo &info) override;

    u32 bladeIndex;
    u32 slot;
  };

  GfMenuItemAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuItemAdapter() override;
  static GfMenuItemAdapter *create(u32 handle, u32 type, const MenuItemInfo &info, bool isUpdateAlways);
  bool update_Name(const MenuItemInfo &info);
  bool update_Icon(const MenuItemInfo &info);
  bool update_IconAll(const MenuItemInfo &info);
  bool update_Count(const MenuItemInfo &info);
  bool update_CountMax(const MenuItemInfo &info);
  bool update_Price(const MenuItemInfo &info);
  bool update_SellPrice(const MenuItemInfo &info);
  bool update_RareIcon(const MenuItemInfo &info);
  bool update_EquipableColor(const MenuItemInfo &info);
  bool update_Caption(const MenuItemInfo &info);
  bool update_CategoryIcon(const MenuItemInfo &info);
  bool update_GetAreaText(const MenuItemInfo &info);
  bool update_SubCategoryText(const MenuItemInfo &info);
  bool update_EffectTime(const MenuItemInfo &info);
  bool update_EffectText(const MenuItemInfo &info);
  bool update_useEnergy(const MenuItemInfo &info);
  bool update_needEther(const MenuItemInfo &info);
  bool update_dustEther(const MenuItemInfo &info);
  bool update_PArmor(const MenuItemInfo &info);
  bool update_EArmor(const MenuItemInfo &info);
  bool update_revise(const MenuItemInfo &info);
  bool update_dispRevise(const MenuItemInfo &info);
  bool update_roleText(const MenuItemInfo &info);
  bool update_canStack(const MenuItemInfo &info);
  static GfMenuItemAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromList(u32 handle, u32 type, GfMenuItemList *list, int listIndex, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<IGfMenuReferenceItem> item, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromRefernceList(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceList<GfMenuItemList>> list, u32 listIndex, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromPouch(u32 handle, u32 type, u32 pouchIndex, u32 driver, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromPouchReferenceIndex(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driver, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromPouchReferenceDriver(u32 handle, u32 type, u32 pouchIndex, u32 driverIndex, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromPouchReferenceIndexReferenceDriver(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driverIndex, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromMission(u32 handle, u32 type, u32 mission, u32 index, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromReferenceMission(u32 handle, u32 type, u32 index, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromDriverEquip(u32 handle, u32 type, u32 driver, u32 slot, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromReferenceDriverEquip(u32 handle, u32 type, u32 driverIndex, u32 slot, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromBladeEquip(u32 handle, u32 type, u32 blade, u32 slot, bool isUpdateAlways);
  static GfMenuItemAdapter *createFromReferenceBladeEquip(u32 handle, u32 type, u32 bladeIndex, u32 slot, bool isUpdateAlways);
  void changeItem(const MenuItemInfo &info) override;
  void update(const fw::UpdateInfo &info) override;

  MenuItemInfo unknown38;                                  // Inferred role: item; original member name unknown.
  mm::mtl::Delegate<bool(const MenuItemInfo &)> unknown48; // Inferred role: updater; original member name unknown.
  IConverter *unknown68;                                   // Inferred role: converter; original member name unknown.
  u32 unknown70;                                           // Inferred role: index of the shown parameter; original member name unknown.
};

static_assert(offsetof(GfMenuItemAdapter, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuItemAdapter, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuItemAdapter, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuItemAdapter, unknown70) == 0x70, "");
static_assert(sizeof(GfMenuItemAdapter) == 0x78, "");

} // namespace gf
