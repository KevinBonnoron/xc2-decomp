#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuItemList;
class GfMenuReferenceItem;

class GfMenuObjPouch : public GfMenuObject {
public:
  GfMenuObjPouch(u32 handle);
  ~GfMenuObjPouch() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupPouch(ui::UIObjectAcc &);

  u8 _24[0x28 - 0x24];
  GfMenuItemList *unknown28;                            // Inferred role: items; original member name unknown.
  ui::UICtrlCursorSelect *unknown30;                    // Inferred role: item cursor; original member name unknown.
  ui::UICtrlCursorSelect *unknown38;                    // Inferred role: pouch cursor; original member name unknown.
  GfMenuCallContext *unknown40;                         // Inferred role: call context; original member name unknown.
  u64 unknown48;                                        // Role and original member name unknown, cleared by the constructor.
  mm::mtl::IntrusivePtr<GfMenuReferenceItem> unknown50; // Inferred role: reference item; original member name unknown.
};

static_assert(offsetof(GfMenuObjPouch, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjPouch, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjPouch, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjPouch, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjPouch, unknown50) == 0x50, "");

} // namespace gf
