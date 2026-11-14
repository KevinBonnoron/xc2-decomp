#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjArtsPalette : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    // Inferred role: range effect state and arts info display flag; original type name unknown.
    struct unknown006 {
      int unknown00; // Inferred role: range effect state, 0 closed and 1 opened; original member name unknown.
      int unknown04; // Inferred role: arts info display flag; original member name unknown.
    };

    MainListener(GfMenuObjArtsPalette *owner) : unknown0c(0), unknown10(), _18(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: control of the range effect, -1 when none; original member name unknown.
    unknown006 unknown10;
    u8 _18[0x1c - 0x18];
    GfMenuObjArtsPalette *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ReverseListener : public ui::UIObjectListener {
  public:
    ReverseListener(GfMenuObjArtsPalette *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: number of reverse icons; original member name unknown.
    u8 _10[0x1c - 0x10];
    GfMenuObjArtsPalette *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjArtsPalette(u32 handle);
  ~GfMenuObjArtsPalette() override;
  static void startChainAttack();
  static void exitChainAttack();
  static void close();
  static void open();
  void initialize() override;
  void finalize() override;
  void update() override;
  static void push(unsigned int slot);
  static void pushReverseBtn(u32 button);
  static void reverse(bool isReverse);
  static void dispInfo(bool isDisp);
  void updateArtsIconDisp(u32 slot);
  int ctrlPalletteDisp(bool isDisp, u32 type);

  int unknown24[3]; // Inferred role: arts slot controls, -1 when none; original member name unknown.
  u32 unknown30[3]; // Inferred role: arts slot state flags; original member name unknown.
  u8 _3c[0x40 - 0x3c];
  GfMenuSequence<GfMenuObjArtsPalette, 8> unknown40;      // Inferred role: arts slot 1 steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 8> unknown2d0;     // Inferred role: arts slot 2 steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 8> unknown560;     // Inferred role: arts slot 3 steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 8> *unknown7f0[3]; // Inferred role: arts slot steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 4> unknown808;     // Inferred role: range effect steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjArtsPalette, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown2d0) == 0x2d0, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown560) == 0x560, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown7f0) == 0x7f0, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown808) == 0x808, "");
static_assert(sizeof(GfMenuObjArtsPalette) == 0x968, "");
static_assert(offsetof(GfMenuObjArtsPalette::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjArtsPalette::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjArtsPalette::ReverseListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjArtsPalette::ReverseListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjArtsPalette::ReverseListener) == 0x28, "");

} // namespace gf
