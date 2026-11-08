#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/particle_intrusive_list.h"
#include "types.h"

namespace ptlib {

struct CamParam;
struct FxHeader;
namespace math {
class KeyFrameIP;
} // namespace math

namespace emitter {

struct EmitterGroup;
class EmitterSetNode;
class ParticleObj;
struct EmitterParam;

class EmitterManager {
public:
  // Inferred role: per-parity kizuna work; the game names the type KizunaWork. The game's
  // FixedArray<KizunaWork, 8> constructor (0x710092dab8) initializes each entry's first 0x140 bytes with
  // FixedArray<Vec3, 20>::assign (0x710092dce4). This header does not declare or reconstruct a KizunaWork
  // constructor, and no retained function constructs it; the values below are game-side initialization
  // evidence for the objects copied by kizunaTail.
  struct KizunaWork {
    // FixedArray<Vec3, 20>::assign writes x/y/z of each Vec3; Vec3's copy assignment reads only x/y/z and
    // ignores the 4-byte padding inside each element.
    mm::mtl::FixedArray<mm::Vec3, 20> unknown000; // Inferred role: 20 Vec3s; original member name unknown.
    // The game's constructor stores 0 at +0x140, 0xff at +0x148..+0x14f, 0xff at +0x150, 0 at +0x151,
    // 1 at +0x152, four 1.0f at +0x154..+0x160, zero floats at +0x164/+0x168, and 0.3f at +0x16c.
    // +0x140 is an opaque 8-byte storage view: the constructor, updateKizunaPos and drawKizunaLine all use
    // 8-byte loads or copies. Its original semantic/pointer type is unknown. +0x16c is a 32-bit storage view;
    // u32 versus f32 is unresolved. +0x153 is natural padding before the 4-byte field at +0x154.
    u64 unknown140; // Opaque 8-byte storage; original semantic/pointer type unknown.
    u8 unknown148;  // Role and original member name unknown; u8 storage, not proven bool.
    u8 unknown149;  // Role and original member name unknown; u8 storage, not proven bool.
    u8 unknown14a;  // Role and original member name unknown; u8 storage, not proven bool.
    u8 unknown14b;  // Role and original member name unknown; u8 storage, not proven bool.
    u8 unknown14c;  // Role and original member name unknown; u8 storage, not proven bool.
    u8 unknown14d;  // Role and original member name unknown; u8 storage, not proven bool.
    u8 unknown14e;  // Role and original member name unknown; u8 storage, not proven bool.
    u8 unknown14f;  // Role and original member name unknown; u8 storage, not proven bool.
    u8 unknown150;  // Role and original member name unknown.
    u8 unknown151;  // Role and original member name unknown.
    u8 unknown152;  // Role and original member name unknown.
    f32 unknown154; // Role and original member name unknown.
    f32 unknown158; // Role and original member name unknown.
    f32 unknown15c; // Role and original member name unknown.
    f32 unknown160; // Role and original member name unknown.
    f32 unknown164; // Role and original member name unknown.
    f32 unknown168; // Role and original member name unknown.
    u32 unknown16c; // Role and original member name unknown; 32-bit storage view, u32 versus f32 unresolved.
  };

  // Inferred role: entry of the emitter table of unknown007; original type and member names unknown.
  struct unknown009 {
    u32 m_emitterForm; // Name from getEmitterForm; original member name unknown.
    u8 _04[0x20 - 0x04];
  };

  // Inferred role: per-parity update work, allocated by init_sub; original type and member names unknown.
  struct unknown007 {
    u8 _0000[0x4000];
    u64 unknown4000;                                    // Inferred role: draw count; original member name unknown.
    mm::mtl::FixedVector<unknown009, 2001> unknown4008; // Inferred role: emitter table; original member name unknown.
    u8 _13a30[0xea7b0 - 0x13a30];
    u64 unknownea7b0; // Inferred role: particle count; original member name unknown.
    u32 unknownea7b8; // Inferred role: emitter count; original member name unknown.
    u32 unknownea7bc; // Inferred role: particle count; original member name unknown.
    u32 unknownea7c0; // Inferred role: draw count; original member name unknown.
    u32 unknownea7c4; // Inferred role: work count; original member name unknown.
  };

  static EmitterManager *get();
  static EmitterManager *&getPtr();
  static void init();
  static void term();
  void moveAfter();
  IntrusiveList<EmitterObj> &getEmitterActiveList();
  IntrusiveList<EmitterObj>::iterator getEmitterActiveIt(EmitterObj *emitter);
  EmitterObj *getEmitterFree();
  void addEmitterFree(EmitterObj *emitter);
  void removeEmitterActive(EmitterObj *emitter);
  void addEmitterActive(EmitterObj *emitter);
  void addEmitterActiveAfterParent(EmitterObj *emitter, EmitterObj *parent);
  ParticleObj *particleAlloc(EmitterObj *emitter, bool isFront);
  ParticleObj *getFreeParticle();
  void addFreeParticleFront(ParticleObj *particle);
  void addFreeParticleBack(ParticleObj *particle);
  void emitter_update(u32 category, f32 speed, bool isSkipDraw);
  void emitter_update_sub(CamParam &camParam, mm::mtl::FixedVector<EmitterObj *, 2001> &freeEmitters, u32 handle, bool isNoWait, f32 speed, mm::mtl::FixedVector<EmitterObj *, 2001> &updateEmitters,
                          bool isUnknown);
  static void *createFunc(EmitterObj *emitter, ParticleObj *particle, f32 frame, int param);
  static void *create_local01(EmitterObj *emitter, ParticleObj *particle, f32 frame, int param);
  ParticleObj *createCommon(EmitterObj *emitter);
  void createSpd(EmitterObj *emitter, EmitterArg *arg, math::KeyFrameIP &keyFrame, f32 frame, ParticleObj *particle, bool isKeyframe);
  void emitter_set_param_pos_only(u32 handle, EmitterParam *param);
  void emitter_set_param_pos_only2(u32 handle, EmitterParam *param);
  void emitter_set_param(u32 handle, EmitterParam *param);
  void emitter_set_param(FxHeader *header, EmitterParam *param);
  void emitter_set_casname(u32 handle, const void *model, const char *name, int index, f32 frame, int flags);
  void emitter_set_casparam(u32 handle, const void *model, EmitterParam *param);
  void emitter_set_disp(u32 handle, int isDisp);
  void emitter_set_alpha(u32 handle, f32 alpha);
  void emitter_set_speed(u32 handle, f32 speed);
  void emitter_set_category(u32 handle, u32 category);
  void emitter_set_viewnum(u32 handle, int viewnum);
  void emitter_set_nowait(u32 handle, int isNoWait);
  void emitter_set_free_all_sub(bool isForce);
  void emitter_set_link(FxHeader *header);
  void emitter_create_local_common_life(EmitterObj *emitter, ParticleObj *particle, EmitterArg *arg);
  void emitter_create_local_common_update_kfinit(EmitterObj *emitter, ParticleObj *particle, EmitterArg *arg);
  void emitter_create_local_common_rgba(EmitterObj *emitter, ParticleObj *particle, EmitterArg *arg, mm::Vec3 &color, mm::Vec3 &color2, f32 &scale);
  void emitter_pack_free(u64 pack);
  EmitterObj *emitter_alloc01(FxHeader *header, EmitterGroup *group, u32 key, ParticleObj *parent, int index, bool option, EmitterParam *param, f32 scale, int flags);
  void emitter_set_free(FxHeader *header, int frame);
  void emitter_set_fadeout(u32 handle, int frame);
  void emitter_set_fadeout(FxHeader *header, int frame);
  void emitter_set_fadeout(void *owner, int frame);
  bool emitter_set_check(FxHeader *header);
  EmitterObj *emitter_free_core(EmitterObj *emitter);
  void updateFeedback(mm::mtl::FixedVector<EmitterObj *, 2001> &emitters, f32 speed);
  void move();
  FxHeader *emitter_set_search(int type, const char *name, void *owner, u32 category);

  mm::mtl::FixedArray<KizunaWork, 8> unknown00[2];  // Inferred role: kizuna works per update parity; original member name unknown.
  f32 unknown1700[(0x1750 - 0x1700) / sizeof(f32)]; // Inferred role: category speed; original member name unknown.
  EmitterObj *unknown1750;                          // Inferred role: p emitter top; original member name unknown.
  EmitterObj *unknown1758;                          // Inferred role: p emitter top of the type 4 and 5 emitters; original member name unknown.
  EmitterObj *unknown1760;                          // Inferred role: p emitter top of the type 2 emitters; original member name unknown.
  EmitterObj *unknown1768;                          // Inferred role: cleared by move; original member name unknown.
  u8 _1770[0x1778 - 0x1770];
  mm::mtl::FixedVector<unknown007 *, 2> unknown1778; // Inferred role: update works; original member name unknown.
  u32 unknown1790;                                   // Inferred role: update parity; original member name unknown.
  u8 _1794[0x17a8 - 0x1794];
  IntrusiveList<EmitterObj> unknown17a8;     // Inferred role: active emitters; original member name unknown.
  IntrusiveList<EmitterObj> unknown17c0;     // Inferred role: free emitters; original member name unknown.
  IntrusiveList<ParticleObj> unknown17d8;    // Inferred role: free particles; original member name unknown.
  IntrusiveList<EmitterSetNode> unknown17f0; // Inferred role: emitter sets; original member name unknown.
  IntrusiveList<EmitterSetNode> unknown1808; // Inferred role: free emitter sets; original member name unknown.
};

static_assert(offsetof(EmitterManager::KizunaWork, unknown140) == 0x140, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown148) == 0x148, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown149) == 0x149, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown14a) == 0x14a, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown14b) == 0x14b, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown14c) == 0x14c, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown14d) == 0x14d, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown14e) == 0x14e, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown14f) == 0x14f, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown150) == 0x150, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown151) == 0x151, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown152) == 0x152, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown154) == 0x154, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown158) == 0x158, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown15c) == 0x15c, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown160) == 0x160, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown164) == 0x164, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown168) == 0x168, "");
static_assert(offsetof(EmitterManager::KizunaWork, unknown16c) == 0x16c, "");
static_assert(sizeof(EmitterManager::KizunaWork) == 0x170, "");
static_assert(sizeof(EmitterManager::unknown009) == 0x20, "");
static_assert(offsetof(EmitterManager::unknown007, unknown4000) == 0x4000, "");
static_assert(offsetof(EmitterManager::unknown007, unknown4008) == 0x4008, "");
static_assert(offsetof(EmitterManager::unknown007, unknownea7b0) == 0xea7b0, "");
static_assert(sizeof(EmitterManager::unknown007) == 0xea7c8, "");
static_assert(offsetof(EmitterManager, unknown1700) == 0x1700, "");
static_assert(offsetof(EmitterManager, unknown1750) == 0x1750, "");
static_assert(offsetof(EmitterManager, unknown1758) == 0x1758, "");
static_assert(offsetof(EmitterManager, unknown1760) == 0x1760, "");
static_assert(offsetof(EmitterManager, unknown1768) == 0x1768, "");
static_assert(offsetof(EmitterManager, unknown1778) == 0x1778, "");
static_assert(offsetof(EmitterManager, unknown1790) == 0x1790, "");
static_assert(offsetof(EmitterManager, unknown17a8) == 0x17a8, "");
static_assert(offsetof(EmitterManager, unknown17c0) == 0x17c0, "");
static_assert(offsetof(EmitterManager, unknown17d8) == 0x17d8, "");
static_assert(offsetof(EmitterManager, unknown17f0) == 0x17f0, "");
static_assert(offsetof(EmitterManager, unknown1808) == 0x1808, "");
static_assert(sizeof(EmitterManager) == 0x1820, "");

} // namespace emitter
} // namespace ptlib
