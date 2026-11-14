#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjMainMenu2BG : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjMainMenu2BG *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjMainMenu2BG *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct OpenMainMenuBg {
    u32 unknown00; // Inferred role: first event parameter; original member name unknown.
    u32 unknown04; // Inferred role: third event parameter; original member name unknown.
    u32 unknown08; // Inferred role: second event parameter; original member name unknown.
  };

  GfMenuObjMainMenu2BG(u32 handle);
  ~GfMenuObjMainMenu2BG() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupMainMenuBG(ui::UIObjectAcc &);
  static void move(GfMenuCallContext *context, u32 index, const OpenMainMenuBg &param);

  static int s_ThemaIndex; // Game symbol _ZN2gf20GfMenuObjMainMenu2BG12s_ThemaIndexE.

  u32 unknown24;                  // Role and original member name unknown, cleared by the constructor.
  ui::UISelectObjList *unknown28; // Inferred role: background objects; original member name unknown.
  ui::UISelectObjList *unknown30; // Inferred role: far background objects; original member name unknown.
};

static_assert(offsetof(GfMenuObjMainMenu2BG::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainMenu2BG::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2BG, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMainMenu2BG, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2BG, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjMainMenu2BG) == 0x38, "");

} // namespace gf
