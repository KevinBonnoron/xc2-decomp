#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ptlib {
namespace emitter {

class EmitterObj;

class ExtObj {
public:
  ~ExtObj();

  u8 _00[0x08 - 0x00];
  EmitterObj *unknown08; // Inferred role: emitter parent; original member name unknown.
  mm::Vec3 unknown10;    // Inferred role: accumulated force; original member name unknown.
  f32 unknown20;         // Inferred role: force rate; original member name unknown.
  u8 _24[0xfc - 0x24];
  f32 unknownfc; // Inferred role: flow map speed; original member name unknown.
  u8 _100[0x108 - 0x100];
  void *unknown108; // Inferred role: light; original member name unknown.
  union {
    void *unknown110; // Inferred role: model; original member name unknown.
    u8 unknown110_u8; // Inferred role: light type, shares its storage with the model; original member name unknown.
  };
  void *unknown118; // Inferred role: cleared with the model; original member name unknown.
  void *unknown120; // Inferred role: cleared with the model; original member name unknown.
  u8 _128[0x22c - 0x128];
  f32 unknown22c; // Inferred role: flow map position; original member name unknown.
  u32 unknown230; // Inferred role: flow map active; original member name unknown.
  u8 _234[0x240 - 0x234];
};

static_assert(offsetof(ExtObj, unknown08) == 0x08, "");
static_assert(offsetof(ExtObj, unknown10) == 0x10, "");
static_assert(offsetof(ExtObj, unknown20) == 0x20, "");
static_assert(offsetof(ExtObj, unknownfc) == 0xfc, "");
static_assert(offsetof(ExtObj, unknown108) == 0x108, "");
static_assert(offsetof(ExtObj, unknown110) == 0x110, "");
static_assert(offsetof(ExtObj, unknown118) == 0x118, "");
static_assert(offsetof(ExtObj, unknown120) == 0x120, "");
static_assert(offsetof(ExtObj, unknown22c) == 0x22c, "");
static_assert(offsetof(ExtObj, unknown230) == 0x230, "");
static_assert(sizeof(ExtObj) == 0x240, "");

} // namespace emitter
} // namespace ptlib
