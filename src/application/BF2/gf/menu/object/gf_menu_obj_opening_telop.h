#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuObjOpeningTelop : public GfMenuObject {
public:
  GfMenuObjOpeningTelop(u32 handle);
  ~GfMenuObjOpeningTelop() override;
  void initialize() override;
  void finalize() override;
  static void openCenter(u32 telop);
  static void closeCenter();
  static void openLeft(u32 telop);
  static void closeLeft();
  static void openRight(u32 telop);
  static void closeRight();
  static void ctrlFadeIn(u32 handle, u32 type);
  static void ctrlFadeOut(u32 handle, u32 type);

  u32 unknown24;                  // Inferred role: unused; original member name unknown.
  u32 unknown28;                  // Inferred role: unused; original member name unknown.
  u32 unknown2c;                  // Inferred role: unused; original member name unknown.
  ui::UISelectObjList *unknown30; // Inferred role: telop objects; original member name unknown.
};

static_assert(offsetof(GfMenuObjOpeningTelop, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjOpeningTelop, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjOpeningTelop, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjOpeningTelop, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjOpeningTelop) == 0x38, "");

} // namespace gf
