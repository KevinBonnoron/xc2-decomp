#pragma once
#include <stddef.h>

#include "layer/layer_obj.h"
#include "types.h"

namespace layer {

struct LyrActionData {
  u32 flags;
  u16 nextIdx;
  u16 endType;
  u32 id;
  u32 nameOffset;
  u8 _10[0x14 - 0x10];
  u16 nameIdx;
  u8 _16[0x18 - 0x16];
  f32 sec;
  u8 _1c[0x2c - 0x1c];
};

static_assert(sizeof(LyrActionData) == 0x2c, "");

struct LayerActWork {
  const u8 *data;
  const LyrActionData *actions;
  s32 actionNum;
  f32 sec;
  u8 _18[0x20 - 0x18];
  u32 actionIdx;
};

static_assert(offsetof(LayerActWork, actionIdx) == 0x20, "");

class LayerActBase : public LayerObj {
public:
  void actionIdx(u32 index);
  void actionEnd();

  LayerActWork *m_actWork;
};

static_assert(offsetof(LayerActBase, m_actWork) == 0x250, "");

} // namespace layer
