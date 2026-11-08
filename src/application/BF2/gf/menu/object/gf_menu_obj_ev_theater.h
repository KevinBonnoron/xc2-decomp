#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuIDList;
class GfMenuMsgList;

class GfMenuObjEvTheater : public GfMenuObject {
public:
  GfMenuObjEvTheater(u32 handle);
  ~GfMenuObjEvTheater() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool attach(GfMenuCallContext *context);
  static void fadeout(GfMenuCallContext *context);
  static void fadein(GfMenuCallContext *context);
  static void dispOffScreen(bool isDisp);

  int unknown24;                  // Role and original member name unknown, 1 at start.
  GfMenuMsgList *unknown28;       // Inferred role: event messages; original member name unknown.
  ui::UISelectObjList *unknown30; // Inferred role: message objects; original member name unknown.
  GfMenuIDList *unknown38;        // Inferred role: event ids; original member name unknown.
  ui::UISelectObjList *unknown40; // Inferred role: event objects; original member name unknown.
};

static_assert(offsetof(GfMenuObjEvTheater, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown40) == 0x40, "");
static_assert(sizeof(GfMenuObjEvTheater) == 0x48, "");

} // namespace gf
