#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuIDList;
class GfMenuMsgList;

class GfMenuObjEvTheater : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjEvTheater *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjEvTheater(u32 handle);
  ~GfMenuObjEvTheater() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool attach(GfMenuCallContext *context);
  static void fadeout(GfMenuCallContext *context);
  static void fadein(GfMenuCallContext *context);
  static void dispOffScreen(bool isDisp);
  void refreshSelctList();
  void updateSubMsgList();

  int unknown24;                  // Role and original member name unknown, 1 at start.
  GfMenuMsgList *unknown28;       // Inferred role: event messages; original member name unknown.
  ui::UISelectObjList *unknown30; // Inferred role: message objects; original member name unknown.
  GfMenuIDList *unknown38;        // Inferred role: event ids; original member name unknown.
  ui::UISelectObjList *unknown40; // Inferred role: event objects; original member name unknown.
};

static_assert(offsetof(GfMenuObjEvTheater::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown40) == 0x40, "");
static_assert(sizeof(GfMenuObjEvTheater) == 0x48, "");

} // namespace gf
