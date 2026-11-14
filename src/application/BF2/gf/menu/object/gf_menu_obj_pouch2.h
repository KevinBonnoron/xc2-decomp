#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
class UIObjectAcc;
class UIStr;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuItemList;
class GfMenuReferenceNumber;
struct GAME_VOICE_HANDLE;

class GfMenuObjPouch2 : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjPouch2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjPouch2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SlotListener : public ui::UIObjectListener {
  public:
    SlotListener(GfMenuObjPouch2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjPouch2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemListListener : public ui::UIObjectListener {
  public:
    ItemListListener(GfMenuObjPouch2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjPouch2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class FilterListener2 : public ui::UIObjectListener {
  public:
    FilterListener2(GfMenuObjPouch2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjPouch2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class PartyInfoListener : public ui::UIObjectListener {
  public:
    PartyInfoListener(GfMenuObjPouch2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjPouch2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ResultListener : public ui::UIObjectListener {
  public:
    ResultListener(GfMenuObjPouch2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjPouch2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  // Layout from setFavFlag: a blade, its slot and its four favorite stats; original member names unknown.
  struct FavoriteFlag {
    u32 unknown00;    // Inferred role: driver or blade; original member name unknown.
    u32 unknown04;    // Inferred role: item; original member name unknown.
    u32 unknown08[4]; // Inferred role: favorite stats of the category and item favorites; original member name unknown.
  };

  GfMenuObjPouch2(u32 handle);
  ~GfMenuObjPouch2() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 type);
  static int setFadeOut(u32 handle, u32 type);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupSlot(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number);
  static void getFilterText(u32 filter, ui::UIStr &text);
  bool seqFavOpen();
  static void setupFilter(ui::UIObjectAcc &acc, u32 filter);
  static void setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list);
  static void setupResult(ui::UIObjectAcc &acc);
  static void refreshResult(ui::UIObjectAcc &acc, const GfMenuBladeList *list);
  static void setupPartyInfo(ui::UIObjectAcc &acc);
  static void updateItemList(GfMenuItemList *list, ui::UISelectObjList *selectList, u32 filter, u32 sort);
  static void refreshSlot(ui::UIObjectAcc &acc, u32 index);
  bool seqFavPouchIn();
  bool seqFavLoop();
  static GAME_VOICE_HANDLE *procFavFlag(ui::UIObjectAcc &acc, FavoriteFlag &flag, u32 index, u32 favorite);
  static void setFavFlag(u32 driver, u32 item, mm::mtl::FixedArray<FavoriteFlag, 4> &flags, const GfMenuBladeList *list);
  static void updateSlotList(GfMenuItemList *list);
  bool seqFavClose();

  u8 _24[0x28 - 0x24];
  GfMenuItemList *unknown28;                              // Inferred role: items; original member name unknown.
  ui::UICtrlCursorSelect *unknown30;                      // Inferred role: item cursor; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown38; // Inferred role: reference number; original member name unknown.
  GfMenuItemList *unknown40;                              // Inferred role: filtered items; original member name unknown.
  ui::UISelectObjList *unknown48;                         // Inferred role: item objects; original member name unknown.
  GfMenuCallContext *unknown50;                           // Inferred role: call context; original member name unknown.
  u8 _58[0x5c - 0x58];
  u32 unknown5c;                                  // Inferred role: item filter; original member name unknown.
  u32 unknown60;                                  // Inferred role: previous item filter; original member name unknown.
  u32 unknown64;                                  // Role and original member name unknown, cleared by the constructor.
  GfMenuCallContext *unknown68;                   // Inferred role: call context; original member name unknown.
  mm::mtl::FixedArray<FavoriteFlag, 4> unknown70; // Inferred role: favorite flags; original member name unknown.
  mm::mtl::FixedArray<FavoriteFlag, 4> unknownd0; // Inferred role: favorite flags; original member name unknown.
  GfMenuSequence<GfMenuObjPouch2, 8> unknown130;  // Inferred role: queued steps; original member name unknown.
  u32 unknown3c0;                                 // Inferred role: current favorite flag; original member name unknown.
  u32 unknown3c4;                                 // Inferred role: current favorite; original member name unknown.
  bool unknown3c8;                                // Role and original member name unknown.
  bool unknown3c9;                                // Role and original member name unknown, cleared by the constructor.
  u8 _3ca[0x3d0 - 0x3ca];
  GAME_VOICE_HANDLE *unknown3d0; // Inferred role: playing voice; original member name unknown.
  u32 unknown3d8;                // Role and original member name unknown, cleared by the constructor.
  u8 _3dc[0x3e0 - 0x3dc];
  GfMenuBladeList *unknown3e0; // Inferred role: blades; original member name unknown.
  bool unknown3e8;             // Role and original member name unknown, cleared by the constructor.
  u8 _3e9[0x3f0 - 0x3e9];
};

static_assert(offsetof(GfMenuObjPouch2::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch2::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch2::SlotListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch2::SlotListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch2::ItemListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch2::ItemListListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch2::FilterListener2, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch2::FilterListener2) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch2::PartyInfoListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch2::PartyInfoListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch2::ResultListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch2::ResultListener) == 0x28, "");
static_assert(sizeof(GfMenuObjPouch2::FavoriteFlag) == 0x18, "");
static_assert(offsetof(GfMenuObjPouch2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjPouch2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjPouch2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjPouch2, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjPouch2, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjPouch2, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuObjPouch2, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjPouch2, unknown64) == 0x64, "");
static_assert(offsetof(GfMenuObjPouch2, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjPouch2, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjPouch2, unknownd0) == 0xd0, "");
static_assert(offsetof(GfMenuObjPouch2, unknown130) == 0x130, "");
static_assert(offsetof(GfMenuObjPouch2, unknown3c9) == 0x3c9, "");
static_assert(offsetof(GfMenuObjPouch2, unknown3d0) == 0x3d0, "");
static_assert(offsetof(GfMenuObjPouch2, unknown3d8) == 0x3d8, "");
static_assert(offsetof(GfMenuObjPouch2, unknown3e0) == 0x3e0, "");
static_assert(offsetof(GfMenuObjPouch2, unknown3e8) == 0x3e8, "");
static_assert(sizeof(GfMenuObjPouch2) == 0x3f0, "");

} // namespace gf
