#pragma once
#include <stddef.h>

#include "gf/field/gf_field_time.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
class UIObjectTimePlugin;
} // namespace ui

namespace gf {

class GfMenuObjSkipTime : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjSkipTime *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjSkipTime *unknown20; // Inferred role: owner; original member name unknown.
  };

  class TimeChangeListener : public ui::UIObjectListener {
  public:
    TimeChangeListener(GfMenuObjSkipTime *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjSkipTime *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjSkipTime(u32 handle);
  ~GfMenuObjSkipTime() override;
  static void rotHand(ui::UIObjectAcc &acc, u32 value);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static void setTime(ui::UIObjectTimePlugin *plugin, GameTime &time);
  static ui::UIObjectTimePlugin *setupTimeChange(ui::UIObjectAcc &acc, GameTime &time, GameTime &afterTime);
  static void refreshSelect(ui::UIObjectAcc &acc, u32 select);
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
static_assert(offsetof(GfMenuObjSkipTime::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjSkipTime::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjSkipTime::TimeChangeListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjSkipTime::TimeChangeListener) == 0x28, "");
static_assert(sizeof(GfMenuObjSkipTime) == 0x38, "");

} // namespace gf
