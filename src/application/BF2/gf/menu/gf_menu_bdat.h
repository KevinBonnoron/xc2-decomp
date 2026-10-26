#pragma once
#include <stddef.h>

#include "types.h"

namespace ui {
class UIStr;
} // namespace ui

namespace gf {

struct MenuOffset {
  MenuOffset() : unknown00(0.0f), unknown04(0.0f), unknown08(0.0f), unknown10(nullptr) {}

  f32 unknown00;         // Inferred role: x; original member name unknown.
  f32 unknown04;         // Inferred role: y; original member name unknown.
  f32 unknown08;         // Inferred role: z; original member name unknown.
  const char *unknown10; // Inferred role: bone name; original member name unknown.
};

static_assert(offsetof(MenuOffset, unknown10) == 0x10, "");
static_assert(sizeof(MenuOffset) == 0x18, "");

class GfMenuBdat {
public:
  static u8 *s_BdatArray[7];

  static u8 *getFP(u32 bdat);
  static bool isValidBdatID(u8 *bdat, int id);
  static void getMenuOffset(int id, MenuOffset &offset);
  static u32 getIconImageIndex(int icon);
  static void initialize();
  static u32 getTopDriverIconID();
  static u32 getTopBladeIconID();
  static int getFieldSkillTypeMax();
  static u8 *getBladeDataFP(u32 blade, u32 &id);
  static u32 getValueLevel(u8 *bdat, u32 value);
  static u16 getIconIDFromArtsID(u16 arts);
  static void getFieldSkillName(u16 skill, ui::UIStr &name);
  static int getIconIDFromWeatherType(u32 weatherType);
};

} // namespace gf
