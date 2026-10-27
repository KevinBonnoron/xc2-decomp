#pragma once
#include <stddef.h>

#include "ptlib/particle_intrusive_list.h"
#include "types.h"

namespace ptlib {
namespace emitter {

class ExtObj;

class ParticleObj : public IntrusiveListNode {
public:
  u8 _010[0x0c0 - 0x010];
  u16 unknownc0; // Inferred role: life; original member name unknown.
  u8 _0c2[0x0d4 - 0x0c2];
  int unknownd4; // Inferred role: create type; original member name unknown.
  u8 _0d8[0x130 - 0x0d8];
  ExtObj *unknown130; // Inferred role: extended parameters; original member name unknown.
  int unknown138;     // Inferred role: id; original member name unknown.
  u8 _13c[0x13e - 0x13c];
  u8 unknown13e; // Inferred role: model particle; original member name unknown.
  u8 _13f[0x150 - 0x13f];
};

static_assert(offsetof(ParticleObj, unknownc0) == 0xc0, "");
static_assert(offsetof(ParticleObj, unknownd4) == 0xd4, "");
static_assert(offsetof(ParticleObj, unknown130) == 0x130, "");
static_assert(offsetof(ParticleObj, unknown138) == 0x138, "");
static_assert(offsetof(ParticleObj, unknown13e) == 0x13e, "");
static_assert(sizeof(ParticleObj) == 0x150, "");

} // namespace emitter
} // namespace ptlib
