#pragma once
#include <stddef.h>

#include "types.h"

namespace ptlib {

struct FxHeader;

namespace emitter {

struct EmitterParam;
class EmitterObj;

class EmitterManager {
public:
  static EmitterManager *get();
  static EmitterManager *&getPtr();
  void emitter_update(u32 category, f32 speed, bool isSkipDraw);
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
};

static_assert(offsetof(EmitterManager, unknown1700) == 0x1700, "");
static_assert(offsetof(EmitterManager, unknown1750) == 0x1750, "");

} // namespace emitter
} // namespace ptlib
