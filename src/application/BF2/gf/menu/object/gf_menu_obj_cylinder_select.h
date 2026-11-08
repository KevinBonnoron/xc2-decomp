#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuItemList;

class GfMenuObjCylinderSelect : public GfMenuObject {
public:
  GfMenuObjCylinderSelect(u32 handle);
  ~GfMenuObjCylinderSelect() override;
  static void open(GfMenuCallContext *context, u32 cylinder);
  static void close(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;

  GfMenuItemList *unknown28;         // Inferred role: item list; original member name unknown.
  ui::UISelectObjList *unknown30;    // Inferred role: item objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown38; // Inferred role: item cursor; original member name unknown.
  GfMenuCallContext *unknown40;      // Inferred role: call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjCylinderSelect, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjCylinderSelect, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjCylinderSelect, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjCylinderSelect, unknown40) == 0x40, "");
static_assert(sizeof(GfMenuObjCylinderSelect) == 0x48, "");

} // namespace gf
