#pragma once
#include "types.h"

namespace ai {

class State {
public:
  virtual ~State();
  virtual const char *getName() const = 0;
  virtual void onEnter(void *owner, State *previous) = 0;
  virtual void onLeave(void *owner, State *next) = 0;
  virtual void onStep(void *owner, const void *param) = 0;
  virtual void onEvent(void *owner, void *event);

private:
  u8 _08[0x18 - 0x08];
};

} // namespace ai
