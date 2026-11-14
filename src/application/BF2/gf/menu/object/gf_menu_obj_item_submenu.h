#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjItemSubmenu : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjItemSubmenu *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjItemSubmenu *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SubmenuListener : public ui::UIObjectListener {
  public:
    SubmenuListener(GfMenuObjItemSubmenu *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjItemSubmenu *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjItemSubmenu(u32 handle);
  ~GfMenuObjItemSubmenu() override;
  static void returnItemSubMenu();
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle, bool unknown);
  static void setupSubmenu(ui::UIObjectAcc &acc);
  void initialize() override;
  void finalize() override;
  void update() override;

  f32 unknown24; // Inferred role: icon scale; original member name unknown.
  f32 unknown28; // Inferred role: selected icon scale; original member name unknown.
  u32 unknown2c; // Role and original member name unknown, zeroed by the constructor.
};

static_assert(offsetof(GfMenuObjItemSubmenu::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjItemSubmenu::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjItemSubmenu::SubmenuListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjItemSubmenu::SubmenuListener) == 0x28, "");
static_assert(offsetof(GfMenuObjItemSubmenu, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjItemSubmenu, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjItemSubmenu, unknown2c) == 0x2c, "");

} // namespace gf
