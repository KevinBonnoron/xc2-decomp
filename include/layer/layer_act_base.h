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

struct LyrActionHeader {
  u8 _00[0xc];
  s32 actionNum;
};

struct LayerActWork {
  const u8 *data;
  const LyrActionData *actions;
  s32 actionNum;
  f32 sec;
  f32 deltaSec;
  f32 invDeltaSec;
  u32 actionIdx;
  u32 flags;
  u32 *actionWorks;
};

static_assert(offsetof(LayerActWork, actionIdx) == 0x20, "");
static_assert(sizeof(LayerActWork) == 0x30, "");

class LayerActBase : public LayerObj {
public:
  void startSetupAction();
  void checkActionEnd(const LyrActionData *action, bool isCmdEnd);
  u32 calcActionWorkSize(const u8 *data);
  void actionIdx(u32 index);
  void actionEnd();
  bool actcmd_no(const u8 *&cmd);
  bool actcmd_priority(const u8 *&cmd);
  bool actcmd_wait(const u8 *&cmd);
  bool actcmd_ctrlspd(const u8 *&cmd);
  bool actend_no(const LyrActionData *action, bool isCmdEnd);
  bool actend_cmdend(const LyrActionData *action, bool isCmdEnd);
  bool actend_on(const LyrActionData *action, bool isCmdEnd);

  static bool (LayerActBase::*s_pCallActEnd[])(const LyrActionData *action, bool isCmdEnd);

  LayerActWork *m_actWork;
};

static_assert(offsetof(LayerActBase, m_actWork) == 0x250, "");

} // namespace layer
