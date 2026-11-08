#pragma once
#include <stddef.h>

#include "gf/field/gf_field_time.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
class UIObjectTimePlugin;
} // namespace ui

namespace gf {

class GfMenuObjSkipTime : public GfMenuObject {
public:
  GfMenuObjSkipTime(u32 handle);
  ~GfMenuObjSkipTime() override;
  static void rotHand(ui::UIObjectAcc &acc, u32 value);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static void setTime(ui::UIObjectTimePlugin *plugin, GameTime &time);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  ui::UIObjectTimePlugin *unknown28; // Inferred role: time display of the changed time; original member name unknown.
  GameTime unknown30;                // Inferred role: current time; original member name unknown.
  GameTime unknown34;                // Inferred role: time after the skip; original member name unknown.
};

static_assert(offsetof(GfMenuObjSkipTime, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjSkipTime, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjSkipTime, unknown34) == 0x34, "");
static_assert(sizeof(GfMenuObjSkipTime) == 0x38, "");

} // namespace gf
