#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjEventSubtitle : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjEventSubtitle *owner) : _0c(), owner(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjEventSubtitle *owner;
  };

  GfMenuObjEventSubtitle(u32 handle);
  ~GfMenuObjEventSubtitle() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void dispText(u8 *bdat, u32 textId, u32 position);
  static void hideText();
  static void endText();
};

static_assert(offsetof(GfMenuObjEventSubtitle::MainListener, owner) == 0x20, "");
static_assert(sizeof(GfMenuObjEventSubtitle::MainListener) == 0x28, "");

} // namespace gf
