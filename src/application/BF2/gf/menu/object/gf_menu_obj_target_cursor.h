#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuAdapter;

class GfMenuObjTargetCursor : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: cursor opened flag; original member name unknown.
    u8 _10[0x20 - 0x10];
    GfMenuObjTargetCursor *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjTargetCursor(u32 handle);
  ~GfMenuObjTargetCursor() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void disp(bool disp);
  void refreshDisp(u32 kind);
  void startCursorAnimation(const char *name);
  bool seqEnCursorOpen();
  bool seqEnCursorLock();
  bool seqEnCursorInTarget();
  bool seqEnCursorInBattle();
  bool seqEnCursorInScreen();
  bool seqEnCursorOutScreen();
  bool seqCursorClose();

  u32 unknown24; // Role and original member name unknown, cleared by the constructor.
  s64 unknown28; // Role and original member name unknown, -1 at start.
  u32 unknown30; // Role and original member name unknown, cleared by the constructor.
  u8 _34[0x38 - 0x34];
  GfMenuAdapter *unknown38;                            // Inferred role: position adapter; original member name unknown.
  GfMenuSequence<GfMenuObjTargetCursor, 8> unknown40;  // Inferred role: queued steps; original member name unknown.
  GfMenuSequence<GfMenuObjTargetCursor, 8> unknown2d0; // Inferred role: queued steps; original member name unknown.
  bool unknown560;                                     // Role and original member name unknown, cleared by the constructor.
  u8 _561[0x564 - 0x561];
  u32 unknown564;  // Role and original member name unknown, cleared by the constructor.
  bool unknown568; // Role and original member name unknown, cleared by the constructor.
  u8 _569[0x56c - 0x569];
  u32 unknown56c; // Inferred role: cursor kind, 0 for the field cursor and 1 for the battle cursor; original member name unknown.
};

static_assert(offsetof(GfMenuObjTargetCursor::MainListener, unknown0c) == 0xc, "");
static_assert(offsetof(GfMenuObjTargetCursor::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown2d0) == 0x2d0, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown560) == 0x560, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown564) == 0x564, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown568) == 0x568, "");
static_assert(offsetof(GfMenuObjTargetCursor, unknown56c) == 0x56c, "");
static_assert(sizeof(GfMenuObjTargetCursor) == 0x570, "");

} // namespace gf
