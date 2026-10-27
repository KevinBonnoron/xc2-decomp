#pragma once
#include <stddef.h>

#include "ptlib/emitter/particle_emitter_param.h"
#include "ptlib/particle_intrusive_list.h"
#include "types.h"

namespace ptlib {

struct DrDrawWorkInfoEF;
struct FxHeader;

namespace renderer {
class RenderSet;
class StreamObj;
} // namespace renderer

namespace emitter {

class ParticleObj;

struct EmitterArg {
  u8 _000[0x0fc - 0x000];
  u8 unknownfc; // Inferred role: blend mode; original member name unknown.
  u8 unknownfd; // Inferred role: fadeout mode; original member name unknown.
  u8 _0fe[0x100 - 0x0fe];
  int unknown100; // Inferred role: draw type; original member name unknown.
  u8 _104[0x24c - 0x104];
  u8 unknown24c[1]; // Inferred role: keyframe data; original member name unknown.
};

static_assert(offsetof(EmitterArg, unknownfc) == 0xfc, "");
static_assert(offsetof(EmitterArg, unknownfd) == 0xfd, "");
static_assert(offsetof(EmitterArg, unknown100) == 0x100, "");
static_assert(offsetof(EmitterArg, unknown24c) == 0x24c, "");

// Inferred role: shared data of an emitter; original name unknown.
struct unknown002 {
  const void *unknown00; // Inferred role: owner; original member name unknown.
  u8 _08[0x70 - 0x08];
  char unknown70[0x10]; // Inferred role: name; original member name unknown.
  u8 _80[0x88 - 0x80];
  f32 unknown88; // Inferred role: scale; original member name unknown.
  u8 _8c[0x90 - 0x8c];
};

static_assert(offsetof(unknown002, unknown70) == 0x70, "");
static_assert(offsetof(unknown002, unknown88) == 0x88, "");
static_assert(sizeof(unknown002) == 0x90, "");

class EmitterObj : public IntrusiveListNode {
public:
  bool isRenderCheck() const;
  void releaseParticleAll();
  void emitter_set_param_sub(EmitterParam *param);
  void emitter_set_param_sub_pos_only(EmitterParam *param);
  int getParentParticleState() const;
  f32 getEmitterScale();
  EmitterObj *emitter_free();
  void emitter_dead(u8 value);
  f32 calc_fade();
  f32 getCateSpd();
  void lockStream(const DrDrawWorkInfoEF *info);
  void unlockStream(const DrDrawWorkInfoEF *info, u32 count);
  void renderStreamNum(renderer::RenderSet &renderSet, const DrDrawWorkInfoEF *info);
  void releaseStream();

  u8 _010[0x040 - 0x010];
  IntrusiveList<ParticleObj> unknown40; // Inferred role: particles; original member name unknown.
  FxHeader *unknown58;                  // Inferred role: effect header; original member name unknown.
  renderer::StreamObj *unknown60;       // Inferred role: render stream; original member name unknown.
  u8 _068[0x080 - 0x068];
  ParticleObj *unknown80; // Inferred role: parent particle; original member name unknown.
  int unknown88;          // Inferred role: parent particle id; original member name unknown.
  u8 _08c[0x090 - 0x08c];
  void *unknown90;       // Inferred role: group; original member name unknown.
  EmitterArg *unknown98; // Inferred role: p arg; original member name unknown.
  u8 _0a0[0x0c0 - 0x0a0];
  unknown002 *unknownc0; // Inferred role: shared data; original member name unknown.
  EmitterObj *unknownc8; // Inferred role: p next; original member name unknown.
  u8 _0d0[0x0e0 - 0x0d0];
  unknown001 unknowne0; // Inferred role: transform; original member name unknown.
  u8 _120[0x12c - 0x120];
  f32 unknown12c; // Inferred role: alpha; original member name unknown.
  u8 _130[0x14c - 0x130];
  f32 unknown14c; // Inferred role: scale; original member name unknown.
  s8 unknown150;  // Inferred role: priority offset; original member name unknown.
  u8 unknown151;  // Inferred role: disp; original member name unknown.
  u8 unknown152;  // Inferred role: no wait; original member name unknown.
  u8 unknown153;  // Original member name unknown.
  u8 _154[0x158 - 0x154];
  f32 unknown158; // Inferred role: speed; original member name unknown.
  u8 _15c[0x170 - 0x15c];
  u32 unknown170; // Inferred role: category; original member name unknown.
  u8 _174[0x180 - 0x174];
  u8 unknown180; // Inferred role: fadeout state; original member name unknown.
  u8 unknown181; // Inferred role: fadeout count; original member name unknown.
  u8 unknown182; // Inferred role: fadeout frame; original member name unknown.
  u8 _183[0x188 - 0x183];
  u32 unknown188; // Inferred role: dead value; original member name unknown.
  u8 _18c[0x260 - 0x18c];
  u8 unknown260; // Inferred role: priority; original member name unknown.
  u8 _261[0x264 - 0x261];
  u32 unknown264; // Inferred role: handle; original member name unknown.
  u8 _268[0x26c - 0x268];
  u16 _26c_0 : 4;
  u16 unknown26c_4 : 1; // Inferred role: dead; original member name unknown.
  u16 _26c_5 : 11;
  u8 _26e[0x274 - 0x26e];
  u8 unknown274; // Inferred role: prio idx; original member name unknown.
  u8 _275[0x320 - 0x275];
};

static_assert(offsetof(EmitterObj, unknown40) == 0x40, "");
static_assert(offsetof(EmitterObj, unknown58) == 0x58, "");
static_assert(offsetof(EmitterObj, unknown60) == 0x60, "");
static_assert(offsetof(EmitterObj, unknown80) == 0x80, "");
static_assert(offsetof(EmitterObj, unknown88) == 0x88, "");
static_assert(offsetof(EmitterObj, unknown90) == 0x90, "");
static_assert(offsetof(EmitterObj, unknown98) == 0x98, "");
static_assert(offsetof(EmitterObj, unknownc0) == 0xc0, "");
static_assert(offsetof(EmitterObj, unknownc8) == 0xc8, "");
static_assert(offsetof(EmitterObj, unknowne0) == 0xe0, "");
static_assert(offsetof(EmitterObj, unknown12c) == 0x12c, "");
static_assert(offsetof(EmitterObj, unknown14c) == 0x14c, "");
static_assert(offsetof(EmitterObj, unknown150) == 0x150, "");
static_assert(offsetof(EmitterObj, unknown151) == 0x151, "");
static_assert(offsetof(EmitterObj, unknown152) == 0x152, "");
static_assert(offsetof(EmitterObj, unknown153) == 0x153, "");
static_assert(offsetof(EmitterObj, unknown158) == 0x158, "");
static_assert(offsetof(EmitterObj, unknown170) == 0x170, "");
static_assert(offsetof(EmitterObj, unknown180) == 0x180, "");
static_assert(offsetof(EmitterObj, unknown188) == 0x188, "");
static_assert(offsetof(EmitterObj, unknown260) == 0x260, "");
static_assert(offsetof(EmitterObj, unknown264) == 0x264, "");
static_assert(offsetof(EmitterObj, unknown274) == 0x274, "");
static_assert(sizeof(EmitterObj) == 0x320, "");

} // namespace emitter
} // namespace ptlib
