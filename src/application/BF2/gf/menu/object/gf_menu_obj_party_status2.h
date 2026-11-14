#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuRewriteNumber;

class GfMenuObjPartyStatus2 : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjPartyStatus2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjPartyStatus2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjPartyStatus2(u32 handle);
  ~GfMenuObjPartyStatus2() override;
  static void close();
  static void disp(bool isDisp);
  static void open();
  static void levelup(u32 member);
  static void movePartyFrameIn(ui::UIObjectAcc &acc, u32 index, int &ctrl);
  static void movePartyFrameInEnd(ui::UIObjectAcc &acc, u32 index);
  static void movePartyFrameOut(ui::UIObjectAcc &acc, u32 index, int &ctrl);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static void setupPartyStatus(ui::UIObjectAcc &acc, GfMenuRewriteNumber *number);
  void initialize() override;
  void finalize() override;
  void update() override;

  bool unknown24;                 // Role and original member name unknown, cleared by the constructor.
  GfMenuRewriteNumber *unknown28; // Inferred role: party status number; original member name unknown.
  int unknown30[3];               // Inferred role: controls of the party frames, -1 when idle; original member name unknown.
};

static_assert(offsetof(GfMenuObjPartyStatus2, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjPartyStatus2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyStatus2, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjPartyStatus2::unknown30) == 0x0c, "");
static_assert(sizeof(GfMenuObjPartyStatus2) == 0x40, "");
static_assert(offsetof(GfMenuObjPartyStatus2::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPartyStatus2::MainListener) == 0x28, "");

} // namespace gf
