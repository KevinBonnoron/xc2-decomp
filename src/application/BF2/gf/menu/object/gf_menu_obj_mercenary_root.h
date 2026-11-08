#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjMercenaryRoot : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjMercenaryRoot *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjMercenaryRoot *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjMercenaryRoot(u32 handle);
  ~GfMenuObjMercenaryRoot() override;
  static void openBg(int bg);
  static void closeBg();
  bool seqWaitBGStream();
  void initialize() override;
  void finalize() override;
  void update() override;

  int unknown24;                                       // Inferred role: unused, -1 at start; original member name unknown.
  GfMenuSequence<GfMenuObjMercenaryRoot, 4> unknown28; // Inferred role: queued steps; original member name unknown.
  u32 unknown188;                                      // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjMercenaryRoot::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMercenaryRoot::MainListener) == 0x28, "");

static_assert(offsetof(GfMenuObjMercenaryRoot, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMercenaryRoot, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMercenaryRoot, unknown188) == 0x188, "");
static_assert(sizeof(GfMenuObjMercenaryRoot) == 0x190, "");

} // namespace gf
