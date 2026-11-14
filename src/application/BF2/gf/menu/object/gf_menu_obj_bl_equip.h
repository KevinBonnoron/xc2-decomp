#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuItemList;

class GfMenuObjBlEquip : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjBlEquip *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjBlEquip *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SlotListener : public ui::UIObjectListener {
  public:
    SlotListener(GfMenuObjBlEquip *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjBlEquip *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemSelectListener : public ui::UIObjectListener {
  public:
    ItemSelectListener(GfMenuObjBlEquip *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjBlEquip *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjBlEquip(u32 handle);
  ~GfMenuObjBlEquip() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupSlot(ui::UIObjectAcc &acc, GfMenuItemList *list);
  static void refreshSlot(ui::UIObjectAcc &acc);
  static void updateEquipItemList(GfMenuItemList *list);
  static void setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList);
  static void sortOrb(GfMenuItemList *list, u16 sort);
  static void refreshItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList, u32 slot);
  static bool removeItem(ui::UIObjectAcc &acc, GfMenuItemList *equipList, GfMenuItemList *list, ui::UISelectObjList *selectList, u32 blade, u32 slot, GfMenuCallContext *context);

  u8 _24[0x28 - 0x24];
  GfMenuItemList *unknown28;         // Inferred role: equipped items; original member name unknown.
  ui::UICtrlCursorSelect *unknown30; // Inferred role: slot cursor; original member name unknown.
  GfMenuItemList *unknown38;         // Inferred role: items; original member name unknown.
  ui::UISelectObjList *unknown40;    // Inferred role: item objects; original member name unknown.
  GfMenuCallContext *unknown48;      // Inferred role: call context; original member name unknown.
  u8 _50[0x58 - 0x50];
  GfMenuCallContext *unknown58; // Inferred role: call context; original member name unknown.
  u32 unknown60;                // Role and original member name unknown, cleared by the constructor.
  u8 _64[0x68 - 0x64];
};

static_assert(offsetof(GfMenuObjBlEquip::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBlEquip::SlotListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBlEquip::ItemSelectListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBlEquip, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBlEquip, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBlEquip, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBlEquip, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBlEquip, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBlEquip, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBlEquip, unknown60) == 0x60, "");
static_assert(sizeof(GfMenuObjBlEquip) == 0x68, "");

} // namespace gf
