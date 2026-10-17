#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

struct MenuOffset {
  MenuOffset() : x(0.0f), y(0.0f), z(0.0f), boneName(nullptr) {}

  f32 x;
  f32 y;
  f32 z;
  const char *boneName;
};

static_assert(offsetof(MenuOffset, boneName) == 0x10, "");
static_assert(sizeof(MenuOffset) == 0x18, "");

class GfMenuBdat {
public:
  static bool isValidBdatID(u8 *bdat, int id);
  static void getMenuOffset(int id, MenuOffset &offset);
  static u32 getIconImageIndex(int icon);
  static u32 getTopBladeIconID();
  static int getIconIDFromWeatherType(u32 weatherType);
};

} // namespace gf
