#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "ptlib/math/particle_keyframe_ip.h"
#include "ptlib/particle_math.h"
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
  u8 _24[0x30 - 0x24];
  mm::Vec3 unknown30; // Inferred role: cleared when a force field hits the particle; original member name unknown.
  u8 _40[0x50 - 0x40];
  mm::Vec3 unknown50; // Inferred role: cleared when a force field hits the particle; original member name unknown.
  u8 _60[0x70 - 0x60];
  mm::Vec3 unknown70; // Inferred role: cleared when a force field hits the particle; original member name unknown.
  u8 _80[0x90 - 0x80];
  mm::Vec3 unknown90; // Inferred role: accumulated newton force; original member name unknown.
  u8 _a0[0xb2 - 0xa0];
  u8 unknownb2; // Inferred role: force field timer, counted down by FfManager::moveForce; original member name unknown.
  u8 unknownb3; // Inferred role: force field timer, set with unknownb2; original member name unknown.
  u8 _b4[0xc0 - 0xb4];
  vec2f unknownc0; // Inferred role: draw parameter passed to the shader; original member name unknown.
  vec2f unknownc8; // Inferred role: draw parameter passed to the shader; original member name unknown.
  f32 unknownd0;   // Inferred role: draw parameter passed to the shader; original member name unknown.
  f32 unknownd4;   // Inferred role: draw parameter of the draw type 14; original member name unknown.
  f32 unknownd8;   // Inferred role: draw parameter of the draw type 14; original member name unknown.
  f32 unknowndc;   // Inferred role: draw parameter of the draw type 14; original member name unknown.
  f32 unknowne0;   // Inferred role: draw parameter of the draw type 14; original member name unknown.
  vec2f unknowne4; // Inferred role: draw parameter passed to the shader; original member name unknown.
  vec2f unknownec; // Inferred role: draw parameter passed to the shader; original member name unknown.
  f32 unknownf4;   // Inferred role: draw parameter passed to the shader; original member name unknown.
  f32 unknownf8;   // Inferred role: draw size, divided by the screen size for the tails; original member name unknown.
  f32 unknownfc;   // Inferred role: flow map speed; original member name unknown.
  u8 _100[0x108 - 0x100];
  union {
    struct {
      void *unknown108; // Inferred role: light; original member name unknown.
      union {
        void *unknown110; // Inferred role: model; original member name unknown.
        u8 unknown110_u8; // Inferred role: light type, shares its storage with the model; original member name unknown.
      };
      void *unknown118; // Inferred role: cleared with the model; original member name unknown.
      void *unknown120; // Inferred role: cleared with the model; original member name unknown.
    };
    // Inferred role: draw parameters of the draw types 10 and 15, sharing the storage of the light and the model (cleared by ParticleObj::particle_clear_union); original member name unknown.
    f32 unknown108_f32[8];
  };
  u8 _128[0x17c - 0x128];
  f32 unknown17c; // Inferred role: draw parameter passed to the shader; original member name unknown.
  f32 unknown180; // Inferred role: draw parameter passed to the shader, cleared by the constructor; original member name unknown.
  u8 _184[0x190 - 0x184];
  math::EPkey unknown190[11]; // Inferred role: random keys of each keyframe channel; original member name unknown.
  s16 unknown214[12];         // Inferred role: loop frame of each keyframe channel; original member name unknown.
  f32 unknown22c;             // Inferred role: flow map position; original member name unknown.
  u32 unknown230;             // Inferred role: flow map active; original member name unknown.
  u8 _234[0x240 - 0x234];
};

static_assert(offsetof(ExtObj, m_emParent) == 0x08, "");
static_assert(offsetof(ExtObj, unknown10) == 0x10, "");
static_assert(offsetof(ExtObj, unknown20) == 0x20, "");
static_assert(offsetof(ExtObj, unknown30) == 0x30, "");
static_assert(offsetof(ExtObj, unknown50) == 0x50, "");
static_assert(offsetof(ExtObj, unknown70) == 0x70, "");
static_assert(offsetof(ExtObj, unknownb2) == 0xb2, "");
static_assert(offsetof(ExtObj, unknownb3) == 0xb3, "");
static_assert(offsetof(ExtObj, unknown90) == 0x90, "");
static_assert(offsetof(ExtObj, unknownc0) == 0xc0, "");
static_assert(offsetof(ExtObj, unknownc8) == 0xc8, "");
static_assert(offsetof(ExtObj, unknownd0) == 0xd0, "");
static_assert(offsetof(ExtObj, unknownd4) == 0xd4, "");
static_assert(offsetof(ExtObj, unknowne0) == 0xe0, "");
static_assert(offsetof(ExtObj, unknowne4) == 0xe4, "");
static_assert(offsetof(ExtObj, unknownec) == 0xec, "");
static_assert(offsetof(ExtObj, unknownf4) == 0xf4, "");
static_assert(offsetof(ExtObj, unknownf8) == 0xf8, "");
static_assert(offsetof(ExtObj, unknownfc) == 0xfc, "");
static_assert(offsetof(ExtObj, unknown108) == 0x108, "");
static_assert(offsetof(ExtObj, unknown110) == 0x110, "");
static_assert(offsetof(ExtObj, unknown118) == 0x118, "");
static_assert(offsetof(ExtObj, unknown120) == 0x120, "");
static_assert(offsetof(ExtObj, unknown108_f32) == 0x108, "");
static_assert(offsetof(ExtObj, unknown17c) == 0x17c, "");
static_assert(offsetof(ExtObj, unknown180) == 0x180, "");
static_assert(offsetof(ExtObj, unknown190) == 0x190, "");
static_assert(offsetof(ExtObj, unknown214) == 0x214, "");
static_assert(offsetof(ExtObj, unknown22c) == 0x22c, "");
static_assert(offsetof(ExtObj, unknown230) == 0x230, "");
static_assert(sizeof(ExtObj) == 0x240, "");

} // namespace emitter
} // namespace ptlib
