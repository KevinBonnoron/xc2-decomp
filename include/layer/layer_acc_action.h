#pragma once
#include "types.h"

namespace layer {

class LayerBase;

class LayerAccAction {
public:
  LayerAccAction(LayerBase *layer);
  bool isActionData() const;
  bool isRunning() const;
  u32 getRunningActIdx() const;
  f32 getRunningActSec() const;
  void setRunningActSec(f32 sec);
  u32 getActionMax() const;
  const char *getActionName(u32 index) const;
  f32 getActionSec(u32 index) const;
  void actionIdx(u32 index);
  void actionID(u32 id);
  void actionName(const char *name);
  void actionEnd();

  LayerBase *layer;
};

} // namespace layer
