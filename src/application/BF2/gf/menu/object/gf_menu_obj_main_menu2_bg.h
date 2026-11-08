#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuObjMainMenu2BG : public GfMenuObject {
public:
  GfMenuObjMainMenu2BG(u32 handle);
  ~GfMenuObjMainMenu2BG() override;
  void initialize() override;
  void finalize() override;
  static void setupMainMenuBG(ui::UIObjectAcc &);

  u32 unknown24;                  // Role and original member name unknown, cleared by the constructor.
  ui::UISelectObjList *unknown28; // Inferred role: background objects; original member name unknown.
  ui::UISelectObjList *unknown30; // Inferred role: far background objects; original member name unknown.
};

static_assert(offsetof(GfMenuObjMainMenu2BG, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMainMenu2BG, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2BG, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjMainMenu2BG) == 0x38, "");

} // namespace gf
