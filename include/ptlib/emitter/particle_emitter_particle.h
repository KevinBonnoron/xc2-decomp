#pragma once
#include <stddef.h>
#include <string.h>

#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec3_na.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/particle_intrusive_list.h"
#include "types.h"

namespace ptlib {
namespace emitter {

class ExtObj;

class ParticleObj : public IntrusiveListNode {
public:
  ParticleObj();
  ~ParticleObj();
  // Inferred role: resets the fields shared by the constructor and EmitterManager::getFreeParticle; original name unknown.
  // Evidence: both functions store the same values to 0x10..0x130 (Vec3::zero, Quat::identity, Vec3NA::zero, 1.0f at 0xcc..0xd4, memset of 0xd8..0x130).
  void unknown001() {
    unknown10 = mm::Vec3::zero;
    unknown20 = mm::Vec3::zero;
    unknown30 = mm::Vec3::zero;
    unknown40 = mm::Vec3::zero;
    unknown50 = mm::Vec3::zero;
    unknown60 = mm::Quat::identity;
    unknown7c = mm::Vec3NA::zero;
    unknown70 = mm::Vec3NA::zero;
    unknown88 = mm::Vec3NA::zero;
    unknown94 = mm::Vec3NA::zero;
    unknowna0 = mm::Vec3NA::zero;
    unknownac.x = 0.0f;
    unknownac.y = 0.0f;
    unknownac.z = 0.0f;
    unknownb8 = 0.0f;
    unknownbc = 0.0f;
    unknownc0 = 0;
    unknownc2 = 0;
    unknownc3 = 0;
    unknownc4 = 0.0f;
    unknownc8 = 0.0f;
    unknownd4 = 1.0f;
    unknowncc = 1.0f;
    unknownd0 = 1.0f;
    memset(unknownd8, 0, sizeof(unknownd8));
  }
  ExtObj &getExtParam() { return *m_extParam; }
  void initUtilObj() {
    static u32 idCounter;
    unknown14c = 0;
    unknown13f = 0;
    unknown138 = idCounter++;
    if (idCounter > 10000) {
      idCounter = 0;
    }
    unknown145 = 2;
  }
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
  void calcIsFit(int isFit, EmitterObj *emitter, mm::Vec3 &direction);
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

  mm::Vec3 unknown10;   // Inferred role: position; original member name unknown.
  mm::Vec3 unknown20;   // Inferred role: previous position; original member name unknown.
  mm::Vec3 unknown30;   // Inferred role: reset by the constructor; original member name unknown.
  mm::Vec3 unknown40;   // Inferred role: reset by the constructor; original member name unknown.
  mm::Vec3 unknown50;   // Inferred role: reset by the constructor; original member name unknown.
  mm::Quat unknown60;   // Inferred role: rotation, identity by default; original member name unknown.
  mm::Vec3NA unknown70; // Inferred role: reset by the constructor; original member name unknown.
  mm::Vec3NA unknown7c; // Inferred role: reset by the constructor; original member name unknown.
  mm::Vec3NA unknown88; // Inferred role: reset by the constructor; original member name unknown.
  mm::Vec3NA unknown94; // Inferred role: reset by the constructor; original member name unknown.
  mm::Vec3NA unknowna0; // Inferred role: reset by the constructor; original member name unknown.
  mm::Vec3NA unknownac; // Inferred role: reset by the constructor; original member name unknown.
  f32 unknownb8;        // Inferred role: life base; original member name unknown.
  f32 unknownbc;        // Inferred role: life scale; original member name unknown.
  u16 unknownc0;        // Inferred role: life; original member name unknown.
  u8 unknownc2;         // Inferred role: reset by the constructor; original member name unknown.
  u8 unknownc3;         // Inferred role: wait; original member name unknown.
  f32 unknownc4;        // Inferred role: reset by the constructor; original member name unknown.
  f32 unknownc8;        // Inferred role: reset by the constructor; original member name unknown.
  f32 unknowncc;        // Inferred role: scale multiplier x; original member name unknown.
  f32 unknownd0;        // Inferred role: scale multiplier y; original member name unknown.
  union {
    f32 unknownd4;     // Inferred role: scale multiplier z; original member name unknown.
    int unknownd4_int; // Inferred role: create type, read by createFunc; original member name unknown.
  };
  u8 unknownd8[0x130 - 0x0d8]; // Inferred role: cleared by the constructor; original member name unknown.
  // Evidence: name from the accessor getExtParam in the assertion string "et->getExtParam().getEmParent()" of particleAlloc.
  ExtObj *m_extParam;
  int unknown138; // Inferred role: id; original member name unknown.
  u8 _13c[0x13e - 0x13c];
  u8 unknown13e; // Inferred role: model particle; original member name unknown.
  u8 unknown13f; // Inferred role: reset by initUtilObj; original member name unknown.
  u8 _140[0x144 - 0x140];
  u8 unknown144; // Inferred role: light particle; original member name unknown.
  u8 unknown145; // Inferred role: reset by initUtilObj; original member name unknown.
  u8 _146[0x14c - 0x146];
  u32 unknown14c; // Inferred role: reset by initUtilObj; original member name unknown.
};

static_assert(offsetof(ParticleObj, unknown10) == 0x10, "");
static_assert(offsetof(ParticleObj, unknown20) == 0x20, "");
static_assert(offsetof(ParticleObj, unknown30) == 0x30, "");
static_assert(offsetof(ParticleObj, unknown60) == 0x60, "");
static_assert(offsetof(ParticleObj, unknown70) == 0x70, "");
static_assert(offsetof(ParticleObj, unknown7c) == 0x7c, "");
static_assert(offsetof(ParticleObj, unknown88) == 0x88, "");
static_assert(offsetof(ParticleObj, unknown94) == 0x94, "");
static_assert(offsetof(ParticleObj, unknowna0) == 0xa0, "");
static_assert(offsetof(ParticleObj, unknownac) == 0xac, "");
static_assert(offsetof(ParticleObj, unknownb8) == 0xb8, "");
static_assert(offsetof(ParticleObj, unknownbc) == 0xbc, "");
static_assert(offsetof(ParticleObj, unknownc0) == 0xc0, "");
static_assert(offsetof(ParticleObj, unknownc3) == 0xc3, "");
static_assert(offsetof(ParticleObj, unknownc4) == 0xc4, "");
static_assert(offsetof(ParticleObj, unknowncc) == 0xcc, "");
static_assert(offsetof(ParticleObj, unknownd4) == 0xd4, "");
static_assert(offsetof(ParticleObj, unknownd8) == 0xd8, "");
static_assert(offsetof(ParticleObj, m_extParam) == 0x130, "");
static_assert(offsetof(ParticleObj, unknown138) == 0x138, "");
static_assert(offsetof(ParticleObj, unknown13e) == 0x13e, "");
static_assert(offsetof(ParticleObj, unknown13f) == 0x13f, "");
static_assert(offsetof(ParticleObj, unknown144) == 0x144, "");
static_assert(offsetof(ParticleObj, unknown145) == 0x145, "");
static_assert(offsetof(ParticleObj, unknown14c) == 0x14c, "");
static_assert(sizeof(ParticleObj) == 0x150, "");

} // namespace emitter
} // namespace ptlib
