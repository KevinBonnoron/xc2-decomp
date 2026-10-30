#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec3_na.h"
#include "ptlib/emitter/particle_emitter_param.h"
#include "ptlib/particle_intrusive_list.h"
#include "types.h"

namespace ml {
class DrGpuCheckBase;
} // namespace ml

namespace ptlib {

struct DrDrawWorkInfoEF;
struct FxHeader;

namespace renderer {
class RenderSet;
class StreamObj;
} // namespace renderer

namespace math {
struct Vec3r;
class KeyFrameIP;
struct EPkey;
} // namespace math

namespace emitter {

class ParticleObj;

struct EmitterArg {
  void get_kf(math::KeyFrameIP *ip, u16 offset, int num, f32 frame, s16 &loopFrame, math::EPkey *epkey, f32 **ppKey, f32 *pLoopTop);
  // Inferred role: keyframe data at an offset of the keyframe block, null for the offset 0; original name unknown.
  f32 *unknown003(u16 offset) {
    if (offset == 0) {
      return nullptr;
    }
    return &unknown24c[offset];
  }

  u8 unknown00; // Inferred role: emitter type; original member name unknown.
  u8 _001[0x009 - 0x001];
  u8 unknown09; // Inferred role: follows the fit direction of the parent particle; original member name unknown.
  u8 _00a[0x014 - 0x00a];
  mm::Vec3NA unknown14; // Inferred role: bound start point; original member name unknown.
  u8 _020[0x044 - 0x020];
  mm::Vec3NA unknown44; // Inferred role: bound end point; original member name unknown.
  u8 _050[0x08c - 0x050];
  u16 unknown8c; // Inferred role: life base; original member name unknown.
  u16 unknown8e; // Inferred role: life; original member name unknown.
  u16 unknown90; // Inferred role: life random range; original member name unknown.
  u8 _092[0x094 - 0x092];
  u8 unknown94; // Inferred role: draw parameter; original member name unknown.
  u8 _095[0x09c - 0x095];
  f32 unknown9c; // Inferred role: bound extent; original member name unknown.
  f32 unknowna0; // Inferred role: bound extent; original member name unknown.
  u8 _0a4[0x0c4 - 0x0a4];
  u8 unknownc4;  // Inferred role: fit mode flags, bit 3 set for the fitting modes; original member name unknown.
  u8 unknownc5;  // Inferred role: rotation mode, 0 for a set rotation, 1 to add it, 2 to add it with a random sign; original member name unknown.
  u16 unknownc6; // Inferred role: rotation keyframe offset; original member name unknown.
  u8 _0c8[0x0e0 - 0x0c8];
  u8 unknowne0; // Inferred role: draw parameter; original member name unknown.
  u8 _0e1[0x0e2 - 0x0e1];
  u16 unknowne2; // Inferred role: pivot keyframe offset; original member name unknown.
  u8 _0e4[0x0fc - 0x0e4];
  u8 unknownfc; // Inferred role: blend mode; original member name unknown.
  u8 unknownfd; // Inferred role: fadeout mode; original member name unknown.
  u8 _0fe[0x100 - 0x0fe];
  int unknown100; // Inferred role: draw type; original member name unknown.
  u8 _104[0x109 - 0x104];
  u8 unknown109; // Inferred role: color mode, 0xff for a color block; original member name unknown.
  u8 _10a[0x120 - 0x10a];
  f32 unknown120; // Inferred role: draw parameter; original member name unknown.
  u8 _124[0x128 - 0x124];
  f32 unknown128; // Inferred role: draw parameter; original member name unknown.
  u8 _12c[0x24c - 0x12c];
  f32 unknown24c[1]; // Inferred role: keyframe data; original member name unknown.
};

static_assert(offsetof(EmitterArg, unknown00) == 0x00, "");
static_assert(offsetof(EmitterArg, unknown09) == 0x09, "");
static_assert(offsetof(EmitterArg, unknown14) == 0x14, "");
static_assert(offsetof(EmitterArg, unknown44) == 0x44, "");
static_assert(offsetof(EmitterArg, unknown8c) == 0x8c, "");
static_assert(offsetof(EmitterArg, unknown9c) == 0x9c, "");
static_assert(offsetof(EmitterArg, unknowna0) == 0xa0, "");
static_assert(offsetof(EmitterArg, unknownc4) == 0xc4, "");
static_assert(offsetof(EmitterArg, unknownc6) == 0xc6, "");
static_assert(offsetof(EmitterArg, unknown90) == 0x90, "");
static_assert(offsetof(EmitterArg, unknown94) == 0x94, "");
static_assert(offsetof(EmitterArg, unknowne0) == 0xe0, "");
static_assert(offsetof(EmitterArg, unknowne2) == 0xe2, "");
static_assert(offsetof(EmitterArg, unknownfc) == 0xfc, "");
static_assert(offsetof(EmitterArg, unknown120) == 0x120, "");
static_assert(offsetof(EmitterArg, unknown128) == 0x128, "");
static_assert(offsetof(EmitterArg, unknownfd) == 0xfd, "");
static_assert(offsetof(EmitterArg, unknown100) == 0x100, "");
static_assert(offsetof(EmitterArg, unknown109) == 0x109, "");
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

// Inferred role: gravity parameters of an emitter; original name unknown.
struct unknown004 {
  u16 unknown00; // Inferred role: first frame; original member name unknown.
  u16 unknown02; // Inferred role: last frame, 0 for no limit; original member name unknown.
  u16 unknown04; // Inferred role: frame source; original member name unknown.
  u8 _06[0x08 - 0x06];
  f32 unknown08; // Inferred role: direction x; original member name unknown.
  f32 unknown0c; // Inferred role: direction y; original member name unknown.
  f32 unknown10; // Inferred role: direction z; original member name unknown.
};

static_assert(offsetof(unknown004, unknown04) == 0x04, "");
static_assert(offsetof(unknown004, unknown10) == 0x10, "");

// Inferred role: newton force parameters of an emitter; original name unknown.
struct unknown005 {
  u16 unknown00; // Inferred role: first frame; original member name unknown.
  u16 unknown02; // Inferred role: last frame, 0 for no limit; original member name unknown.
  u16 unknown04; // Inferred role: frame source; original member name unknown.
  u8 _06[0x14 - 0x06];
  f32 unknown14; // Inferred role: minimum distance; original member name unknown.
  f32 unknown18; // Inferred role: strength; original member name unknown.
  f32 unknown1c; // Inferred role: distance exponent; original member name unknown.
};

static_assert(offsetof(unknown005, unknown04) == 0x04, "");
static_assert(offsetof(unknown005, unknown14) == 0x14, "");
static_assert(offsetof(unknown005, unknown1c) == 0x1c, "");

// Inferred role: speed parameters of an emitter; original name unknown.
struct unknown006 {
  u8 _00[0x0c - 0x00];
  u16 unknown0c; // Inferred role: speed keyframe offset; original member name unknown.
};

static_assert(offsetof(unknown006, unknown0c) == 0x0c, "");

class EmitterObj : public IntrusiveListNode {
public:
  bool isRenderCheck() const;
  void releaseParticleAll();
  void remove_particle_free_tbl(ParticleObj *particle);
  void emitter_set_param_sub(EmitterParam *param);
  void emitter_set_param_sub_pos_only(EmitterParam *param);
  void emitter_set_param_sub_pos_only2(EmitterParam *param);
  void emitter_alloc01_set_move(FxHeader *header, EmitterArg *arg);
  int getParentParticleState() const;
  static void calc_scale(mm::Vec3 *result, math::Vec3r *range, f32 scale, u32 &seed);
  f32 getEmitterScale();
  EmitterObj *emitter_free();
  void emitter_dead(u8 value);
  f32 calc_fade();
  f32 getCateSpd();
  void *lockStream(const DrDrawWorkInfoEF *info);
  void unlockStream(const DrDrawWorkInfoEF *info, u32 count);
  void renderStreamNum(renderer::RenderSet &renderSet, const DrDrawWorkInfoEF *info);
  void releaseStream();
  bool localUpdateParticleObj(ParticleObj *&particle, IntrusiveList<ParticleObj>::iterator &it, f32 speed, int isMove, int &count);
  bool localUpdateParticleObjLgt(ParticleObj *&particle, IntrusiveList<ParticleObj>::iterator &it, f32 speed, int isMove, int &count);
  bool localUpdateParticleObjMdl(ParticleObj *&particle, IntrusiveList<ParticleObj>::iterator &it, f32 speed, int isMove, int &count);

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
  u32 unknownd0;         // Inferred role: move type; original member name unknown.
  u32 unknownd4;         // Inferred role: move flag; original member name unknown.
  u8 _0d8[0x0e0 - 0x0d8];
  unknown001 unknowne0; // Inferred role: transform; original member name unknown.
  mm::Col4 unknown120;  // Inferred role: color, the alpha is read by the draw sort; original member name unknown.
  mm::Col3 unknown130;  // Inferred role: copied from the emitter parameter; original member name unknown.
  u8 _13c[0x140 - 0x13c];
  mm::Vec2 unknown140; // Inferred role: copied from the emitter parameter; original member name unknown.
  u8 _148[0x14c - 0x148];
  f32 unknown14c; // Inferred role: scale; original member name unknown.
  s8 unknown150;  // Inferred role: priority offset; original member name unknown.
  u8 unknown151;  // Inferred role: disp; original member name unknown.
  u8 unknown152;  // Inferred role: no wait; original member name unknown.
  u8 unknown153;  // Original member name unknown.
  u16 unknown154; // Inferred role: copied from the emitter parameter; original member name unknown.
  u8 unknown156;  // Inferred role: copied from the emitter parameter; original member name unknown.
  u8 unknown157;  // Inferred role: copied from the emitter parameter; original member name unknown.
  f32 unknown158; // Inferred role: speed; original member name unknown.
  f32 unknown15c; // Inferred role: copied from the emitter parameter; original member name unknown.
  f32 unknown160; // Inferred role: copied from the emitter parameter; original member name unknown.
  f32 unknown164; // Inferred role: copied from the emitter parameter; original member name unknown.
  f32 unknown168; // Inferred role: copied from the emitter parameter; original member name unknown.
  f32 unknown16c; // Inferred role: copied from the emitter parameter; original member name unknown.
  u32 unknown170; // Inferred role: category; original member name unknown.
  u8 unknown174;  // Inferred role: copied from the emitter parameter; original member name unknown.
  u8 _175[0x180 - 0x175];
  u8 unknown180; // Inferred role: fadeout state; original member name unknown.
  u8 unknown181; // Inferred role: fadeout count; original member name unknown.
  u8 unknown182; // Inferred role: fadeout frame; original member name unknown.
  u8 _183[0x188 - 0x183];
  u32 unknown188; // Inferred role: dead value; original member name unknown.
  f32 unknown18c; // Inferred role: frame; original member name unknown.
  u8 _190[0x1c0 - 0x190];
  unknown006 *unknown1c0; // Inferred role: speed; original member name unknown.
  unknown004 *unknown1c8; // Inferred role: gravity; original member name unknown.
  unknown005 *unknown1d0; // Inferred role: newton; original member name unknown.
  u8 _1d8[0x1e0 - 0x1d8];
  mm::Vec3 unknown1e0; // Inferred role: newton center; original member name unknown.
  u8 _1f0[0x260 - 0x1f0];
  u8 unknown260; // Inferred role: priority; original member name unknown.
  u8 _261[0x264 - 0x261];
  u32 unknown264; // Inferred role: handle; original member name unknown.
  u32 unknown268; // Inferred role: random seed; original member name unknown.
  u16 _26c_0 : 4;
  u16 unknown26c_4 : 1; // Inferred role: dead; original member name unknown.
  u16 _26c_5 : 11;
  u8 _26e[0x274 - 0x26e];
  u8 unknown274; // Inferred role: prio idx; original member name unknown.
  u8 _275[0x27a - 0x275];
  u16 unknown27a; // Inferred role: compute particle offset; original member name unknown.
  u16 unknown27c; // Inferred role: compute particle count; original member name unknown.
  u16 unknown27e; // Inferred role: compute block offset; original member name unknown.
  u8 _280[0x2b8 - 0x280];
  f32 *unknown2b8[11]; // Inferred role: loop start key of each keyframe channel; original member name unknown.
  // Evidence: name from the assertion string "m_pGpuCheck == nullptr" in emitter_alloc01; vtable +0x10 (release) and +0x18 (isRender) called in emitter_free_core and isRenderCheck.
  ml::DrGpuCheckBase *m_pGpuCheck;
  f32 unknown318; // Inferred role: gpu check radius; original member name unknown.
  f32 unknown31c; // Inferred role: gpu check bounding size; original member name unknown.
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
static_assert(offsetof(EmitterObj, unknownd0) == 0xd0, "");
static_assert(offsetof(EmitterObj, unknownd4) == 0xd4, "");
static_assert(offsetof(EmitterObj, unknowne0) == 0xe0, "");
static_assert(offsetof(EmitterObj, unknown120) == 0x120, "");
static_assert(offsetof(EmitterObj, unknown130) == 0x130, "");
static_assert(offsetof(EmitterObj, unknown140) == 0x140, "");
static_assert(offsetof(EmitterObj, unknown14c) == 0x14c, "");
static_assert(offsetof(EmitterObj, unknown150) == 0x150, "");
static_assert(offsetof(EmitterObj, unknown151) == 0x151, "");
static_assert(offsetof(EmitterObj, unknown152) == 0x152, "");
static_assert(offsetof(EmitterObj, unknown153) == 0x153, "");
static_assert(offsetof(EmitterObj, unknown158) == 0x158, "");
static_assert(offsetof(EmitterObj, unknown154) == 0x154, "");
static_assert(offsetof(EmitterObj, unknown15c) == 0x15c, "");
static_assert(offsetof(EmitterObj, unknown160) == 0x160, "");
static_assert(offsetof(EmitterObj, unknown16c) == 0x16c, "");
static_assert(offsetof(EmitterObj, unknown170) == 0x170, "");
static_assert(offsetof(EmitterObj, unknown174) == 0x174, "");
static_assert(offsetof(EmitterObj, unknown1c0) == 0x1c0, "");
static_assert(offsetof(EmitterObj, unknown2b8) == 0x2b8, "");
static_assert(offsetof(EmitterObj, unknown180) == 0x180, "");
static_assert(offsetof(EmitterObj, unknown188) == 0x188, "");
static_assert(offsetof(EmitterObj, unknown18c) == 0x18c, "");
static_assert(offsetof(EmitterObj, unknown1c8) == 0x1c8, "");
static_assert(offsetof(EmitterObj, unknown1d0) == 0x1d0, "");
static_assert(offsetof(EmitterObj, unknown1e0) == 0x1e0, "");
static_assert(offsetof(EmitterObj, unknown260) == 0x260, "");
static_assert(offsetof(EmitterObj, unknown264) == 0x264, "");
static_assert(offsetof(EmitterObj, unknown268) == 0x268, "");
static_assert(offsetof(EmitterObj, unknown274) == 0x274, "");
static_assert(offsetof(EmitterObj, unknown27a) == 0x27a, "");
static_assert(offsetof(EmitterObj, unknown27c) == 0x27c, "");
static_assert(offsetof(EmitterObj, unknown27e) == 0x27e, "");
static_assert(offsetof(EmitterObj, m_pGpuCheck) == 0x310, "");
static_assert(offsetof(EmitterObj, unknown318) == 0x318, "");
static_assert(offsetof(EmitterObj, unknown31c) == 0x31c, "");
static_assert(sizeof(EmitterObj) == 0x320, "");

} // namespace emitter
} // namespace ptlib
