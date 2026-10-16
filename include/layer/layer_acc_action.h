#pragma once
#include "types.h"

namespace layer {

class LayerActBase;
class LayerBase;

class LayerAccAction {
public:
  LayerAccAction(LayerBase *layer);
  bool isActionData() const;
  bool isRunning() const;
  const char *getRunningActName() const;
  u32 getRunningActID() const;
  s32 getRunningActIdx() const;
  f32 getRunningActSec() const;
  void setRunningActSec(f32 sec);
  u32 getActionMax() const;
  u32 getActionID(u32 index) const;
  const char *getActionName(u32 index) const;
  f32 getActionSec(u32 index) const;
  bool actionIdx(u32 index);
  bool actionID(u32 id);
  bool actionName(const char *name);
  void actionEnd();

  LayerActBase *m_layer;
};

} // namespace layer
