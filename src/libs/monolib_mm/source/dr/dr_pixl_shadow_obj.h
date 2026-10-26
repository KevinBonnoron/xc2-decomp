#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrPixlShadowObj {
public:
  void afterUpdate();
  bool dispChk();
  void renderLight();
  void debugInfo();
  void stockTile();
  void update();
  bool clipChk(const mm::Vec3 &position, f32 value, bool flag);
  bool clipTypeChk(const mm::Vec3 &position, f32 value);
  bool setSptCalcPos(const mm::Vec3 &position, f32 value);
  void setInstSelMapShadow(bool value);
  void releaseWork();

  u8 _00[0x08 - 0x00];
  grlib::CGLibDblUniformBlock unknown08; // Inferred role: shadow uniform; original member name unknown.
  u8 _40[0x50 - 0x40];
  u32 unknown50; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrPixlShadowObj, unknown08) == 0x08, "");
static_assert(offsetof(DrPixlShadowObj, unknown50) == 0x50, "");

} // namespace ml
