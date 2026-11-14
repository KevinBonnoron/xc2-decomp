#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjPartyGauge : public GfMenuObject {
public:
  class GaugeListener : public ui::UIObjectListener {
  public:
    GaugeListener(GfMenuObjPartyGauge *owner) : unknown0c(0), unknown10(0), _14(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: running control of the gauge layout, -1 after the layout is hidden; original member name unknown.
    int unknown10; // Inferred role: gauge layout shown flag; original member name unknown.
    u8 _14[0x1c - 0x14];
    GfMenuObjPartyGauge *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjPartyGauge(u32 handle);
  ~GfMenuObjPartyGauge() override;
  static void open();
  static void close();
  static void disp(bool isDisp);
  void initialize() override;
  void finalize() override;
  void update() override;

  int unknown24; // Inferred role: control of the gauge bar, -1 when idle; original member name unknown.
};

static_assert(offsetof(GfMenuObjPartyGauge::GaugeListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjPartyGauge::GaugeListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjPartyGauge::GaugeListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPartyGauge::GaugeListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyGauge, unknown24) == 0x24, "");
static_assert(sizeof(GfMenuObjPartyGauge) == 0x28, "");

} // namespace gf
