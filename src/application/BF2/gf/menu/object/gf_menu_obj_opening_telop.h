#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuObjOpeningTelop : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjOpeningTelop *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjOpeningTelop *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjOpeningTelop(u32 handle);
  ~GfMenuObjOpeningTelop() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void openCenter(u32 telop);
  static void closeCenter();
  static void openLeft(u32 telop);
  static void closeLeft();
  static void openRight(u32 telop);
  static void closeRight();
  static void ctrlFadeIn(u32 handle, u32 type);
  static int ctrlFadeOut(u32 handle, u32 type);

  u32 unknown24[3];               // Inferred role: image counts of the center, left and right telops; original member name unknown.
  ui::UISelectObjList *unknown30; // Inferred role: telop objects; original member name unknown.
};

static_assert(offsetof(GfMenuObjOpeningTelop, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjOpeningTelop, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjOpeningTelop) == 0x38, "");

static_assert(offsetof(GfMenuObjOpeningTelop::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjOpeningTelop::MainListener) == 0x28, "");

} // namespace gf
