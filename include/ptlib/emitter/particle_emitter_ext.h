#pragma once
#include <stddef.h>

#include "types.h"

namespace ptlib {
namespace emitter {

class EmitterObj;

class ExtObj {
public:
  u8 _00[0x08 - 0x00];
  EmitterObj *unknown08; // Inferred role: emitter parent; original member name unknown.
  u8 _10[0x110 - 0x10];
  void *unknown110; // Inferred role: model; original member name unknown.
  u8 _118[0x240 - 0x118];
};

static_assert(offsetof(ExtObj, unknown08) == 0x08, "");
static_assert(offsetof(ExtObj, unknown110) == 0x110, "");
static_assert(sizeof(ExtObj) == 0x240, "");

} // namespace emitter
} // namespace ptlib
