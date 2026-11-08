#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjNameSelect : public GfMenuObject {
public:
  GfMenuObjNameSelect(u32 handle);
  ~GfMenuObjNameSelect() override;
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GfMenuCallContext *unknown28; // Inferred role: call context; original member name unknown.
  u8 _30[0x30 - 0x30];
};

static_assert(offsetof(GfMenuObjNameSelect, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjNameSelect) == 0x30, "");

} // namespace gf
