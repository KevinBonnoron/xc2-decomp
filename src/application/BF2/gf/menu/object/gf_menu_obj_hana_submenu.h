#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjHanaSubmenu : public GfMenuObject {
public:
  GfMenuObjHanaSubmenu(u32 handle);
  ~GfMenuObjHanaSubmenu() override;
  static void returnHanaSubMenu();
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GfMenuCallContext *unknown28; // Inferred role: call context, only released by the destructor (class type inferred); original member name unknown.
  u32 unknown30;                // Inferred role: unused; original member name unknown.
};

static_assert(offsetof(GfMenuObjHanaSubmenu, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaSubmenu, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjHanaSubmenu) == 0x38, "");

} // namespace gf
