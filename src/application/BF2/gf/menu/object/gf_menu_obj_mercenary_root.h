#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjMercenaryRoot : public GfMenuObject {
public:
  GfMenuObjMercenaryRoot(u32 handle);
  ~GfMenuObjMercenaryRoot() override;
  static void closeBg();
  void initialize() override;
  void finalize() override;
  void update() override;

  int unknown24;                                       // Inferred role: unused, -1 at start; original member name unknown.
  GfMenuSequence<GfMenuObjMercenaryRoot, 4> unknown28; // Inferred role: queued steps; original member name unknown.
  u32 unknown188;                                      // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjMercenaryRoot, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMercenaryRoot, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMercenaryRoot, unknown188) == 0x188, "");
static_assert(sizeof(GfMenuObjMercenaryRoot) == 0x190, "");

} // namespace gf
