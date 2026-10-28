#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/particle_intrusive_list.h"
#include "types.h"

namespace ptlib {
namespace emitter {

class ExtObj;

class ParticleObj : public IntrusiveListNode {
public:
  ~ParticleObj();
  void free_plight();
  void freeUtilObj();
  void particle_clear_union();
  void addCalcTbl(mm::Vec3 &vector, f32 scale);
  void calcGravity(EmitterObj *emitter, f32 speed, mm::Vec3 &result);
  void calcNewton(EmitterObj *emitter, mm::Vec3 &result);
  bool move_common_check_begin_end(EmitterObj *emitter, u16 begin, u16 end, int mode) {
    f32 frame;
    if (static_cast<u32>(mode) < 2) {
      frame = emitter->unknown18c;
    } else {
      frame = unknownb8 * unknownbc;
    }
    u32 current = static_cast<int>(frame);
    if (current < begin) {
      return false;
    }
    bool inRange = true;
    if (end != 0 && current > end) {
      inRange = false;
    }
    return inRange;
  }
  void calc_fit(f32 &pitch, f32 &yaw, const mm::Vec3 *direction);
  bool move_common_wait(int isMove, f32 speed);
  bool move_common_life(int isMove, f32 speed) {
    if (isMove != 0 && unknownc0 != 0x7fff) {
      int step = 1;
      if (0 < static_cast<int>(speed)) {
        step = static_cast<int>(speed);
      }
      int diff = unknownc0 - step;
      s16 life = diff;
      if (life < 1) {
        unknownc0 = 0;
      } else {
        unknownc0 = diff;
      }
      return life < 1;
    }
    return false;
  }
  void move_common_check_begin_end_sub(EmitterObj *emitter, int mode, u16 &begin, u16 &end);
  void moveFlowMap(EmitterObj *emitter, int isMove);
  f32 move_common_keyframe_life(EmitterObj *emitter);

  mm::Vec3 unknown10; // Inferred role: position; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: previous position; original member name unknown.
  u8 _030[0x0b8 - 0x030];
  f32 unknownb8; // Inferred role: life base; original member name unknown.
  f32 unknownbc; // Inferred role: life scale; original member name unknown.
  u16 unknownc0; // Inferred role: life; original member name unknown.
  u8 _0c2[0x0c3 - 0x0c2];
  u8 unknownc3; // Inferred role: wait; original member name unknown.
  u8 _0c4[0x0d4 - 0x0c4];
  int unknownd4; // Inferred role: create type; original member name unknown.
  u8 _0d8[0x130 - 0x0d8];
  ExtObj *unknown130; // Inferred role: extended parameters; original member name unknown.
  int unknown138;     // Inferred role: id; original member name unknown.
  u8 _13c[0x13e - 0x13c];
  u8 unknown13e; // Inferred role: model particle; original member name unknown.
  u8 _13f[0x144 - 0x13f];
  u8 unknown144; // Inferred role: light particle; original member name unknown.
  u8 _145[0x150 - 0x145];
};

static_assert(offsetof(ParticleObj, unknown10) == 0x10, "");
static_assert(offsetof(ParticleObj, unknown20) == 0x20, "");
static_assert(offsetof(ParticleObj, unknownb8) == 0xb8, "");
static_assert(offsetof(ParticleObj, unknownbc) == 0xbc, "");
static_assert(offsetof(ParticleObj, unknownc0) == 0xc0, "");
static_assert(offsetof(ParticleObj, unknownc3) == 0xc3, "");
static_assert(offsetof(ParticleObj, unknownd4) == 0xd4, "");
static_assert(offsetof(ParticleObj, unknown130) == 0x130, "");
static_assert(offsetof(ParticleObj, unknown138) == 0x138, "");
static_assert(offsetof(ParticleObj, unknown13e) == 0x13e, "");
static_assert(offsetof(ParticleObj, unknown144) == 0x144, "");
static_assert(sizeof(ParticleObj) == 0x150, "");

} // namespace emitter
} // namespace ptlib
