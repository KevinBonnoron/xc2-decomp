#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjLocationTelop : public GfMenuObject {
public:
  struct OpenParam {
    u8 *unknown00;  // Inferred role: bdat; original member name unknown.
    u32 unknown08;  // Inferred role: text id; original member name unknown.
    u16 unknown0c;  // Inferred role: type; original member name unknown.
    u16 unknown0e;  // Inferred role: map id; original member name unknown.
    bool unknown10; // Inferred role: new; original member name unknown.
  };

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjLocationTelop *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjLocationTelop *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjLocationTelop(u32 handle);
  ~GfMenuObjLocationTelop() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void open(const OpenParam &param);
  static void close();
  static void cancel();
};

static_assert(offsetof(GfMenuObjLocationTelop::OpenParam, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjLocationTelop::OpenParam, unknown0e) == 0x0e, "");
static_assert(offsetof(GfMenuObjLocationTelop::OpenParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjLocationTelop::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjLocationTelop::MainListener) == 0x28, "");

} // namespace gf
