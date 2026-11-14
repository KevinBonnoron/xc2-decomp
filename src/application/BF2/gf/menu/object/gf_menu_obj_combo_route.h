#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjComboRoute : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjComboRoute *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: root shown flag; original member name unknown.
    u8 _10[0x1c - 0x10];
    GfMenuObjComboRoute *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjComboRoute(u32 handle);
  ~GfMenuObjComboRoute() override;
  static void close();
  static void disp(bool isDisp);
  static void open();
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupComboRoute(ui::UIObjectAcc &acc);

  int unknown24[8]; // Inferred role: control slots of the cursors, -1 at start; the last one is the root control; original member name unknown.
};

static_assert(offsetof(GfMenuObjComboRoute::MainListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjComboRoute::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjComboRoute, unknown24) == 0x24, "");
static_assert(sizeof(GfMenuObjComboRoute) == 0x48, "");

} // namespace gf
