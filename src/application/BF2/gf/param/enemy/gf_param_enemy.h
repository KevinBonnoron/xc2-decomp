#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

// Names are the reflection names registered by EnemyMoveParam::createReflection (gf_param_enemy_reflection.cpp), in order.
struct EnemyMoveParam {
  f32 accel0;
  f32 accel1;
  f32 accel2;
  f32 brake0;
  f32 brake1;
  f32 brake2;
};

static_assert(offsetof(EnemyMoveParam, brake0) == 0x0c, "");
static_assert(sizeof(EnemyMoveParam) == 0x18, "");

const EnemyMoveParam *getEnemeyMoveParam(u32 index);

} // namespace gf
