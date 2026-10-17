#pragma once
#include <stddef.h>

#include "anm/anm_asm_state.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace anm {

struct InterpolateInfo;

class StateMachine {
public:
  void resetInterpolate();
  const char *getStateName() const;
  u64 getAttribute(u32 index) const;
  bool isEnd() const;
  bool isLoop() const;
  void setLocalTime(f32 time);
  f32 getLocalTime() const;
  void setSpeed(f32 speed);
  f32 getSpeed() const;

  mm::mtl::IntrusivePtr<AsmState> m_state;
  mm::mtl::IntrusivePtr<AsmState> m_nextState;
  u8 _10[0x28 - 0x10];
  const InterpolateInfo *m_pInterpolateInfo;
  f32 m_interpolateTime;
};

static_assert(offsetof(StateMachine, m_pInterpolateInfo) == 0x28, "");
static_assert(offsetof(StateMachine, m_interpolateTime) == 0x30, "");

} // namespace anm
