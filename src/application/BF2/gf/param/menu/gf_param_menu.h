#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Field names and offsets from the reflection built by gf::MenuParam::createReflection (gf_param_menu.cpp).
struct MenuParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 fadeTimeHUD;
  f32 fadeTimeFS;
  f32 artsPaletteDisableScale;
  f32 moveBGTime;
  f32 charSelectScale;
  f32 fsWaitTime;
  f32 chainAttackStartTime;
};

static_assert(offsetof(MenuParam, artsPaletteDisableScale) == 0x08, "");
static_assert(offsetof(MenuParam, charSelectScale) == 0x10, "");
static_assert(offsetof(MenuParam, chainAttackStartTime) == 0x18, "");
static_assert(sizeof(MenuParam) == 0x1c, "");

} // namespace gf
