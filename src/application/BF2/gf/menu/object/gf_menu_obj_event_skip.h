#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjEventSkip : public GfMenuObject {
public:
  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjEventSkip *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjEventSkip *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjEventSkip(u32 handle);
  ~GfMenuObjEventSkip() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close();
  static u32 setupScreen(u32 screen);
  static void open(GfMenuCallContext *context);
};

static_assert(offsetof(GfMenuObjEventSkip::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEventSkip::ListListener) == 0x28, "");

} // namespace gf
