#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjArtsPalette : public GfMenuObject {
public:
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

  int unknown24[3]; // Inferred role: arts slot controls, -1 when none; original member name unknown.
  u32 unknown30[3]; // Inferred role: arts slot state flags; original member name unknown.
  u8 _3c[0x40 - 0x3c];
  GfMenuSequence<GfMenuObjArtsPalette, 8> unknown40;   // Inferred role: arts slot 1 steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 8> unknown2d0;  // Inferred role: arts slot 2 steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 8> unknown560;  // Inferred role: arts slot 3 steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 8> *unknown7f0; // Inferred role: arts slot 1 steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 8> *unknown7f8; // Inferred role: arts slot 2 steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 8> *unknown800; // Inferred role: arts slot 3 steps; original member name unknown.
  GfMenuSequence<GfMenuObjArtsPalette, 4> unknown808;  // Inferred role: range effect steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjArtsPalette, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown2d0) == 0x2d0, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown560) == 0x560, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown7f0) == 0x7f0, "");
static_assert(offsetof(GfMenuObjArtsPalette, unknown808) == 0x808, "");
static_assert(sizeof(GfMenuObjArtsPalette) == 0x968, "");

} // namespace gf
