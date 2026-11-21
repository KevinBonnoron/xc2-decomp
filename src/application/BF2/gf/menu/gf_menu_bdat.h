#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ui {
class UIStr;
} // namespace ui

namespace gf {

// The offset holds a Vec3, which makes the struct 16-byte aligned and 0x20 bytes long: the OpenSymbolParam slot of
// GfMenuObjTargetInfo::openOther (1.0.0: 0x71004dc238) is 16-byte aligned and its copy of the offset is a 64-bit load of x and y stored as
// two 32-bit words, a 32-bit copy of z and a pointer copy, which three f32 members at 8-byte alignment do not give.
struct MenuOffset {
  MenuOffset() : unknown00(0.0f, 0.0f, 0.0f), unknown10(nullptr) {}

  mm::Vec3 unknown00;    // Inferred role: offset; original member name unknown.
  const char *unknown10; // Inferred role: bone name; original member name unknown.
};

static_assert(offsetof(MenuOffset, unknown10) == 0x10, "");
static_assert(sizeof(MenuOffset) == 0x20, "");

class GfMenuBdat {
public:
  static u8 *s_BdatArray[7];

  static u8 *getFP(u32 bdat);
  static bool isValidBdatID(u8 *bdat, int id);
  static u8 *getItemDataFP(u8 itemType, u16 item);
  static u8 *getItemTextFP(u8 itemType, u16 item);
  static const char *getSortKeyName();
  static void getMenuOffset(int id, MenuOffset &offset);
  static u32 getIconImageIndex(int icon);
  static void initialize();
  static u32 getTopDriverIconID();
  static u32 getTopBladeIconID();
  static int getFieldSkillTypeMax();
  static u8 *getBladeDataFP(u32 blade, u32 &id);
  static u32 getValueLevel(u8 *bdat, u32 value);
  static u32 getIconIDFromArtsID(u16 arts);
  static void getFieldSkillName(u16 skill, ui::UIStr &name);
  static int getIconIDFromWeatherType(u32 weatherType);
};

} // namespace gf
