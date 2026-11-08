#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjSpecialGauge : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: fade control; original member name unknown.
    struct unknown006 {
      int unknown00; // Inferred role: open flag; original member name unknown.
      int unknown04; // Inferred role: shown flag; original member name unknown.
    } unknown10;
    int unknown18; // Inferred role: battle gauge flag; original member name unknown.
    u8 _1c[0x20 - 0x1c];
    GfMenuObjSpecialGauge *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjSpecialGauge(u32 handle);
  ~GfMenuObjSpecialGauge() override;
  static void close();
  static void open();
  static void reverse(bool isReverse);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void push();
};

static_assert(offsetof(GfMenuObjSpecialGauge::MainListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjSpecialGauge::MainListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjSpecialGauge::MainListener::unknown006, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjSpecialGauge::MainListener, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjSpecialGauge::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjSpecialGauge::MainListener) == 0x28, "");

} // namespace gf
