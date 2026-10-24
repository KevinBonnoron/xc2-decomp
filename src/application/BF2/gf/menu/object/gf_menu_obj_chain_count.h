#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjChainCount : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjChainCount *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjChainCount *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjChainCount(u32 handle);
  ~GfMenuObjChainCount() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void open();
  static void close();
};

static_assert(offsetof(GfMenuObjChainCount::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjChainCount::MainListener) == 0x28, "");

} // namespace gf
