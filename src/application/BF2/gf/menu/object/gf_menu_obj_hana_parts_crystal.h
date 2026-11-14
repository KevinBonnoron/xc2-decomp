#pragma once
#include <stddef.h>

#include "gf/data/gf_data_item.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorColor;
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuIDList;
class GfMenuItemList;
class GfMenuReferenceNumber;

class GfMenuObjHanaPartsCrystal : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjHanaPartsCrystal *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];                  // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjHanaPartsCrystal *unknown20; // Inferred role: owner; original member name unknown.
  };

  class PartsListListener : public ui::UIObjectListener {
  public:
    PartsListListener(GfMenuObjHanaPartsCrystal *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];                  // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjHanaPartsCrystal *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemListListener : public ui::UIObjectListener {
  public:
    ItemListListener(GfMenuObjHanaPartsCrystal *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];                  // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjHanaPartsCrystal *unknown20; // Inferred role: owner; original member name unknown.
  };

  class NumSelectListener : public ui::UIObjectListener {
  public:
    NumSelectListener(GfMenuObjHanaPartsCrystal *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];                  // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjHanaPartsCrystal *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjHanaPartsCrystal(u32 handle);
  ~GfMenuObjHanaPartsCrystal() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 getCrystalItemCount(u32 item);
  static RESULT_HANA crystalParts(u32 type, u32 parts);
  static void setupNumSelect(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> price);
  static void setupPartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects);
  static void setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *objects);
  static void updatePartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects);
  static void refreshItemList(GfMenuItemList *list, ui::UISelectObjList *objects, u32 unknown);
  static void updateItemList(GfMenuItemList *list, ItemType::Type type);
  static void makeCategoryItemList(GfMenuIDList *idList, GfMenuItemList *itemList);

  u8 _24[0x28 - 0x24];
  GfMenuIDList *unknown28;                                // Inferred role: crystal types; original member name unknown.
  ui::UISelectObjList *unknown30;                         // Inferred role: crystal type objects; original member name unknown.
  ui::UICtrlCursorColor *unknown38;                       // Inferred role: crystal type cursor; original member name unknown.
  GfMenuItemList *unknown40;                              // Inferred role: crystal items; original member name unknown.
  ui::UISelectObjList *unknown48;                         // Inferred role: crystal item objects; original member name unknown.
  ui::UICtrlCursorColor *unknown50;                       // Inferred role: crystal item cursor; original member name unknown.
  GfMenuCallContext *unknown58;                           // Inferred role: call context; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown60; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown68; // Inferred role: reference number; original member name unknown.
};

static_assert(offsetof(GfMenuObjHanaPartsCrystal, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjHanaPartsCrystal::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal::PartsListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjHanaPartsCrystal::PartsListListener) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal::ItemListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjHanaPartsCrystal::ItemListListener) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaPartsCrystal::NumSelectListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjHanaPartsCrystal::NumSelectListener) == 0x28, "");

} // namespace gf
