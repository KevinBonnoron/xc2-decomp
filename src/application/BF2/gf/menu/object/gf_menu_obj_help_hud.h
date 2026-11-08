#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjHelpHud : public GfMenuObject {
public:
  GfMenuObjHelpHud(u32 handle);
  ~GfMenuObjHelpHud() override;
  void initialize() override;
  void finalize() override;
  void enable();
  void disable();
  static void ctrlFadeOut(u32 handle);
  static void ctrlFadeIn(u32 handle);
  bool seqPageFadeIn();
  bool seqPageFadeOut();

  u32 unknown24; // Inferred role: unused; original member name unknown.
  u8 _28[0x30 - 0x28];
  GfMenuSequence<GfMenuObjHelpHud, 8> unknown30; // Inferred role: page steps; original member name unknown.
  bool unknown2c0;                               // Inferred role: page fade control started flag; original member name unknown.
};

static_assert(offsetof(GfMenuObjHelpHud, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjHelpHud, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjHelpHud, unknown2c0) == 0x2c0, "");

} // namespace gf
