#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjTutorial : public GfMenuObject {
public:
  static void closeAll();
  static void closeText(u32 param);
  static void closeFocus(u32 param);
  static void closeIcon(u32 param);
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool isWaiting();
  bool seqTelopStart();
  bool seqTelopEnd();
  bool seqEnd();

  GfMenuSequence<GfMenuObjTutorial, 8> unknown28; // Inferred role: telop steps; original member name unknown.
  bool unknown2b8;                                // Inferred role: animation started flag; original member name unknown.
  int unknown2bc;                                 // Inferred role: frames left before the call context ends; original member name unknown.
};

static_assert(offsetof(GfMenuObjTutorial, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjTutorial, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfMenuObjTutorial, unknown2bc) == 0x2bc, "");
static_assert(sizeof(GfMenuObjTutorial) == 0x2c0, "");

} // namespace gf
