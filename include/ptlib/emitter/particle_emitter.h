#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ptlib {
namespace emitter {

struct EmitterArg {
  u8 _000[0x0fc - 0x000];
  u8 unknownfc; // Inferred role: blend mode; original member name unknown.
  u8 _0fd[0x100 - 0x0fd];
  int unknown100; // Inferred role: draw type; original member name unknown.
};

static_assert(offsetof(EmitterArg, unknownfc) == 0xfc, "");
static_assert(offsetof(EmitterArg, unknown100) == 0x100, "");

class EmitterObj {
public:
  bool isRenderCheck() const;

  u8 _000[0x098 - 0x000];
  EmitterArg *unknown98; // Inferred role: p arg; original member name unknown.
  u8 _0a0[0x0c8 - 0x0a0];
  EmitterObj *unknownc8; // Inferred role: p next; original member name unknown.
  u8 _0d0[0x110 - 0x0d0];
  mm::Vec3 unknown110; // Inferred role: pos; original member name unknown.
  u8 _120[0x12c - 0x120];
  f32 unknown12c; // Inferred role: alpha; original member name unknown.
  u8 _130[0x150 - 0x130];
  s8 unknown150;   // Inferred role: priority offset; original member name unknown.
  bool unknown151; // Inferred role: disp; original member name unknown.
  u8 _152[0x260 - 0x152];
  u8 unknown260; // Inferred role: priority; original member name unknown.
  u8 _261[0x274 - 0x261];
  u8 unknown274; // Inferred role: prio idx; original member name unknown.
};

static_assert(offsetof(EmitterObj, unknown98) == 0x98, "");
static_assert(offsetof(EmitterObj, unknownc8) == 0xc8, "");
static_assert(offsetof(EmitterObj, unknown110) == 0x110, "");
static_assert(offsetof(EmitterObj, unknown12c) == 0x12c, "");
static_assert(offsetof(EmitterObj, unknown150) == 0x150, "");
static_assert(offsetof(EmitterObj, unknown151) == 0x151, "");
static_assert(offsetof(EmitterObj, unknown260) == 0x260, "");
static_assert(offsetof(EmitterObj, unknown274) == 0x274, "");

} // namespace emitter
} // namespace ptlib
