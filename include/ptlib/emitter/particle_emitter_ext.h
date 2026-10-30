#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "ptlib/math/particle_keyframe_ip.h"
#include "types.h"

namespace ptlib {
namespace emitter {

class EmitterObj;

class ExtObj {
public:
  ~ExtObj();
  EmitterObj *getEmParent() { return m_emParent; }

  u8 _00[0x08 - 0x00];
  // Evidence: name from the accessor getEmParent in the assertion string "et->getExtParam().getEmParent()" of particleAlloc.
  EmitterObj *m_emParent;
  mm::Vec3 unknown10; // Inferred role: accumulated force; original member name unknown.
  f32 unknown20;      // Inferred role: force rate; original member name unknown.
  u8 _24[0x90 - 0x24];
  mm::Vec3 unknown90; // Inferred role: accumulated newton force; original member name unknown.
  u8 _a0[0xfc - 0xa0];
  f32 unknownfc; // Inferred role: flow map speed; original member name unknown.
  u8 _100[0x108 - 0x100];
  void *unknown108; // Inferred role: light; original member name unknown.
  union {
    void *unknown110; // Inferred role: model; original member name unknown.
    u8 unknown110_u8; // Inferred role: light type, shares its storage with the model; original member name unknown.
  };
  void *unknown118; // Inferred role: cleared with the model; original member name unknown.
  void *unknown120; // Inferred role: cleared with the model; original member name unknown.
  u8 _128[0x190 - 0x128];
  math::EPkey unknown190[11]; // Inferred role: random keys of each keyframe channel; original member name unknown.
  s16 unknown214[12];         // Inferred role: loop frame of each keyframe channel; original member name unknown.
  f32 unknown22c;             // Inferred role: flow map position; original member name unknown.
  u32 unknown230;             // Inferred role: flow map active; original member name unknown.
  u8 _234[0x240 - 0x234];
};

static_assert(offsetof(ExtObj, m_emParent) == 0x08, "");
static_assert(offsetof(ExtObj, unknown10) == 0x10, "");
static_assert(offsetof(ExtObj, unknown20) == 0x20, "");
static_assert(offsetof(ExtObj, unknown90) == 0x90, "");
static_assert(offsetof(ExtObj, unknownfc) == 0xfc, "");
static_assert(offsetof(ExtObj, unknown108) == 0x108, "");
static_assert(offsetof(ExtObj, unknown110) == 0x110, "");
static_assert(offsetof(ExtObj, unknown118) == 0x118, "");
static_assert(offsetof(ExtObj, unknown120) == 0x120, "");
static_assert(offsetof(ExtObj, unknown190) == 0x190, "");
static_assert(offsetof(ExtObj, unknown214) == 0x214, "");
static_assert(offsetof(ExtObj, unknown22c) == 0x22c, "");
static_assert(offsetof(ExtObj, unknown230) == 0x230, "");
static_assert(sizeof(ExtObj) == 0x240, "");

} // namespace emitter
} // namespace ptlib
