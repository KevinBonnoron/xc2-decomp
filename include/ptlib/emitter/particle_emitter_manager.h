#pragma once
#include <stddef.h>

#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/particle_intrusive_list.h"
#include "types.h"

namespace ptlib {

struct FxHeader;

namespace emitter {

class EmitterSetNode;
class ParticleObj;
struct EmitterParam;

class EmitterManager {
public:
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
  void addFreeParticleFront(ParticleObj *particle);
  void addFreeParticleBack(ParticleObj *particle);
  void emitter_update(u32 category, f32 speed, bool isSkipDraw);
  static void *createFunc(EmitterObj *emitter, ParticleObj *particle, f32 frame, int param);
  static void *create_local01(EmitterObj *emitter, ParticleObj *particle, f32 frame, int param);
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
  void emitter_pack_free(u64 pack);
  void emitter_set_free(FxHeader *header, int frame);
  void emitter_set_fadeout(u32 handle, int frame);
  void emitter_set_fadeout(FxHeader *header, int frame);
  void emitter_set_fadeout(void *owner, int frame);
  bool emitter_set_check(FxHeader *header);
  void move();
  FxHeader *emitter_set_search(int type, const char *name, void *owner, u32 category);

  u8 _0000[0x1700 - 0x0000];
  f32 unknown1700[(0x1750 - 0x1700) / sizeof(f32)]; // Inferred role: category speed; original member name unknown.
  EmitterObj *unknown1750;                          // Inferred role: p emitter top; original member name unknown.
  u8 _1758[0x17a8 - 0x1758];
  IntrusiveList<EmitterObj> unknown17a8;     // Inferred role: active emitters; original member name unknown.
  IntrusiveList<EmitterObj> unknown17c0;     // Inferred role: free emitters; original member name unknown.
  IntrusiveList<ParticleObj> unknown17d8;    // Inferred role: free particles; original member name unknown.
  IntrusiveList<EmitterSetNode> unknown17f0; // Inferred role: emitter sets; original member name unknown.
  IntrusiveList<EmitterSetNode> unknown1808; // Inferred role: free emitter sets; original member name unknown.
};

static_assert(offsetof(EmitterManager, unknown1700) == 0x1700, "");
static_assert(offsetof(EmitterManager, unknown1750) == 0x1750, "");
static_assert(offsetof(EmitterManager, unknown17a8) == 0x17a8, "");
static_assert(offsetof(EmitterManager, unknown17c0) == 0x17c0, "");
static_assert(offsetof(EmitterManager, unknown17d8) == 0x17d8, "");
static_assert(offsetof(EmitterManager, unknown17f0) == 0x17f0, "");
static_assert(offsetof(EmitterManager, unknown1808) == 0x1808, "");
static_assert(sizeof(EmitterManager) == 0x1820, "");

} // namespace emitter
} // namespace ptlib
