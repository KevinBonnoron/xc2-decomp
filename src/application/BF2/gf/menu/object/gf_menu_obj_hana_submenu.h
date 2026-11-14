#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {
class GfMenuCallContext;

class GfMenuObjHanaSubmenu : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjHanaSubmenu *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjHanaSubmenu *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SubmenuListener : public ui::UIObjectListener {
  public:
    SubmenuListener(GfMenuObjHanaSubmenu *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjHanaSubmenu *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjHanaSubmenu(u32 handle);
  ~GfMenuObjHanaSubmenu() override;
  static void returnHanaSubMenu();
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static void setupSubmenu(ui::UIObjectAcc &acc);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GfMenuCallContext *unknown28; // Inferred role: call context, only released by the destructor (class type inferred); original member name unknown.
  u32 unknown30;                // Inferred role: unused; original member name unknown.
  u8 _34[0x40 - 0x34];          // The game allocates 0x40 bytes for the object; no function touches the tail.
};

static_assert(offsetof(GfMenuObjHanaSubmenu::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjHanaSubmenu::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaSubmenu::SubmenuListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjHanaSubmenu::SubmenuListener) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaSubmenu, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaSubmenu, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjHanaSubmenu) == 0x40, "");

} // namespace gf
