#pragma once
#include "mm/mm_std_base.h"
#include "types.h"

namespace ai {

static const u32 INVALID_STATE_ID = 0xffffffff;

class State {
public:
  State() : stateID(INVALID_STATE_ID), m_reqState(INVALID_STATE_ID), childState(nullptr) {}
  virtual ~State() {}
  virtual const char *getName() const = 0;
  virtual void onEnter(void *owner, State *previous) = 0;
  virtual void onLeave(void *owner, State *next) = 0;
  virtual void onStep(void *owner, const void *param) = 0;
  virtual void onEvent(void *owner, void *event);

  // __LINE__ must be 51 as in the original header: it is the line argument of the assert.
#line 50
  void reqState(u32 state) {
    MM_ASSERT(m_reqState == INVALID_STATE_ID);
    m_reqState = state;
  }

  u32 stateID;
  u32 m_reqState;
  State *childState;
};

} // namespace ai
