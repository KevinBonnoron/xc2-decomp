#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UICtrlRevolveSelect;
class UIListInfoBase;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuObjLinkJump : public GfMenuObject {
public:
  // Inferred role: list shown on one side of the screen; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: UI object handle; original member name unknown.
    u8 _04[0x08 - 0x04];
    ui::UIListInfoBase *unknown08;     // Inferred role: referenced list; original member name unknown.
    ui::UISelectObjList *unknown10;    // Inferred role: list objects; original member name unknown.
    ui::UICtrlCursorSelect *unknown18; // Inferred role: list cursor; original member name unknown.
  };

  GfMenuObjLinkJump(u32 handle);
  ~GfMenuObjLinkJump() override;
  static void open();
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close();

  u8 _24[0x28 - 0x24];
  unknown002 unknown28[2];
  ui::UISelectObjList *unknown68;     // Inferred role: category objects; original member name unknown.
  ui::UICtrlRevolveSelect *unknown70; // Inferred role: category revolve cursor; original member name unknown.
  bool unknown78;                     // Inferred role: category list shown flag; original member name unknown.
  u8 _79[0x80 - 0x79];
};

static_assert(offsetof(GfMenuObjLinkJump::unknown002, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjLinkJump::unknown002, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjLinkJump::unknown002, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuObjLinkJump::unknown002) == 0x20, "");
static_assert(offsetof(GfMenuObjLinkJump, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjLinkJump, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjLinkJump, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjLinkJump, unknown78) == 0x78, "");
static_assert(sizeof(GfMenuObjLinkJump) == 0x80, "");

} // namespace gf
