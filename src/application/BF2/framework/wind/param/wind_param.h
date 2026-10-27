#pragma once
#include "types.h"

namespace fw {

class Reflection;

struct GlobalWindParam {
  f32 powMaxFront;
  f32 powMinFront;
  f32 cycleFront;
  f32 offsetFront;
  f32 powMaxBack;
  f32 powMinBack;
  f32 cycleBack;
  f32 offsetBack;
  f32 powMaxLeft;
  f32 powMinLeft;
  f32 cycleLeft;
  f32 offsetLeft;
  f32 powMaxRight;
  f32 powMinRight;
  f32 cycleRight;
  f32 offsetRight;
  f32 powMaxUp;
  f32 powMinUp;
  f32 cycleRUp;
  f32 offsetUp;

  static void createReflection(Reflection *reflection, const char *name, u32 index);
};

static_assert(sizeof(GlobalWindParam) == 0x50, "");

Reflection *createGlobalWindReflection();

} // namespace fw
