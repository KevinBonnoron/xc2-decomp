#pragma once
#include <stddef.h>

#include "gf/game/gf_game_util_hana.h"
#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

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
  static void updatePartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects);
  static void refreshItemList(GfMenuItemList *list, ui::UISelectObjList *objects, u32 unknown);

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

} // namespace gf
