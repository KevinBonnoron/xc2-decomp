#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
#include "types.h"

namespace layer {

struct LayerResParmInfo;

struct LayerAnimeInfo {
  u32 unknown00; // Inferred role: flags; original member name unknown.
  f32 unknown04; // Inferred role: duration; original member name unknown.
  f32 unknown08; // Inferred role: target pos x; original member name unknown.
  f32 unknown0c; // Inferred role: target pos y; original member name unknown.
  f32 unknown10; // Inferred role: target rot; original member name unknown.
  f32 unknown14; // Inferred role: target scl x; original member name unknown.
  f32 unknown18; // Inferred role: target scl y; original member name unknown.
  f32 unknown1c; // Inferred role: target anchor x; original member name unknown.
  f32 unknown20; // Inferred role: target anchor y; original member name unknown.
  f32 unknown24; // Inferred role: target mul col r; original member name unknown.
  f32 unknown28; // Inferred role: target mul col g; original member name unknown.
  f32 unknown2c; // Inferred role: target mul col b; original member name unknown.
  f32 unknown30; // Inferred role: target mul col a; original member name unknown.
  f32 unknown34; // Inferred role: target add col r; original member name unknown.
  f32 unknown38; // Inferred role: target add col g; original member name unknown.
  f32 unknown3c; // Inferred role: target add col b; original member name unknown.
};

static_assert(offsetof(LayerAnimeInfo, unknown04) == 0x04, "");
static_assert(offsetof(LayerAnimeInfo, unknown3c) == 0x3c, "");
static_assert(sizeof(LayerAnimeInfo) == 0x40, "");

class LayerAnimeObj {
public:
  LayerAnimeObj(int count);
  ~LayerAnimeObj();
  void release();
  void setAnimeLoop(bool loop);
  void setAnimeCorrection(bool correction);
  void setSelectNumber(bool selectNumber);
  bool update(LayerResParmInfo &parm, f32 frame);
  void calcParm(LayerResParmInfo &parm, const LayerAnimeInfo &info, f32 rate);
  static LayerAnimeObj *createAnimObj(int id);

  f32 unknown00;               // Inferred role: elapsed time; original member name unknown.
  u16 unknown04;               // Inferred role: current anime index; original member name unknown.
  u16 unknown06;               // Inferred role: flags; original member name unknown.
  u16 unknown08[2];            // Inferred role: select idx; original member name unknown.
  LayerAnimeInfo *unknown10;   // Inferred role: anime infos; original member name unknown.
  s32 unknown18;               // Inferred role: anime info count; original member name unknown.
  s32 unknown1c;               // Inferred role: anime info capacity; original member name unknown.
  mtl::ALLOC_HANDLE unknown20; // Inferred role: memory handle; original member name unknown.
  u8 _24[0x28 - 0x24];
  u64 unknown28; // Inferred role: zero initialised by the constructor; original member name unknown.
  u32 unknown30; // Inferred role: zero initialised by the constructor; original member name unknown.
};

static_assert(offsetof(LayerAnimeObj, unknown04) == 0x04, "");
static_assert(offsetof(LayerAnimeObj, unknown06) == 0x06, "");
static_assert(offsetof(LayerAnimeObj, unknown08) == 0x08, "");
static_assert(offsetof(LayerAnimeObj, unknown10) == 0x10, "");
static_assert(offsetof(LayerAnimeObj, unknown18) == 0x18, "");
static_assert(offsetof(LayerAnimeObj, unknown20) == 0x20, "");

} // namespace layer
