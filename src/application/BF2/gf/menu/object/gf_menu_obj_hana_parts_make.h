#pragma once
#include <stddef.h>

#include "gf/data/gf_data_item.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UICtrlCursorColor;
class UICtrlCursorSelect;
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuIDList;
class GfMenuItemList;
class GfMenuReferenceNumber;

class GfMenuObjHanaPartsMake : public GfMenuObject {
public:
  GfMenuObjHanaPartsMake(u32 handle);
  ~GfMenuObjHanaPartsMake() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 unknown);
  static int setFadeOut(u32 handle, u32 unknown);
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 getCrystalItemCount(u32 item);
  static u16 getFirstSortTableId(u32 type, u32 isEquip);
  static u32 getMakeItemCount(u32 parts);
  static RESULT_HANA makeParts(u32 type, u32 parts);
  static RESULT_HANA crystalParts(u32 type, u32 parts);
  static void setupMain(ui::UIObjectAcc &acc);
  static void setupNumSelect(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> price);
  static void updatePartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects);
  static void setupPartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects);
  static void makeCategoryItemList(GfMenuIDList *idList, GfMenuItemList *itemList, u32 isEquip, u32 sort);
  static void updateItemList(GfMenuItemList *list, ItemType::Type type, u32 isEquip);

  u8 _24[0x28 - 0x24];
  GfMenuIDList *unknown28;                                // Inferred role: parts types; original member name unknown.
  ui::UISelectObjList *unknown30;                         // Inferred role: parts type objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown38;                      // Inferred role: parts type cursor; original member name unknown.
  GfMenuItemList *unknown40;                              // Inferred role: parts items; original member name unknown.
  ui::UISelectObjList *unknown48;                         // Inferred role: parts item objects; original member name unknown.
  ui::UICtrlCursorColor *unknown50;                       // Inferred role: parts item cursor; original member name unknown.
  GfMenuCallContext *unknown58;                           // Inferred role: call context; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown60; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown68; // Inferred role: reference number; original member name unknown.
  u32 unknown70;                                          // Role and original member name unknown, cleared by the constructor.
  u32 unknown74;                                          // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjHanaPartsMake, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjHanaPartsMake, unknown74) == 0x74, "");
static_assert(sizeof(GfMenuObjHanaPartsMake) == 0x78, "");

} // namespace gf
