#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuItemList;

class GfMenuObjCylinderSelect : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjCylinderSelect *owner) : _0c(), m_menuObjCylinderSelect(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjCylinderSelect *m_menuObjCylinderSelect; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjCylinderSelect(u32 handle);
  ~GfMenuObjCylinderSelect() override;
  static void open(GfMenuCallContext *context, u32 cylinder);
  static void close(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;

  GfMenuItemList *m_menuItemList;       // Inferred role: item list; original member name unknown.
  ui::UISelectObjList *unknown30;       // Inferred role: item objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown38;    // Inferred role: item cursor; original member name unknown.
  GfMenuCallContext *m_menuCallContext; // Inferred role: call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjCylinderSelect::MainListener, m_menuObjCylinderSelect) == 0x20, "");
static_assert(sizeof(GfMenuObjCylinderSelect::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjCylinderSelect, m_menuItemList) == 0x28, "");
static_assert(offsetof(GfMenuObjCylinderSelect, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjCylinderSelect, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjCylinderSelect, m_menuCallContext) == 0x40, "");
static_assert(sizeof(GfMenuObjCylinderSelect) == 0x48, "");

} // namespace gf
