#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace anm {

struct InterpolateInfo;
class AsmListener;
class AsmState;

enum StartFrameType {};
enum InterpolateType {};
enum InterpolateCurve {};

class StateMachine {
public:
  StateMachine();
  ~StateMachine();
  void cleanup();
  void resetInterpolate();
  bool executeCmd(const char *command);
  bool setState(const char *state, StartFrameType startFrame = static_cast<StartFrameType>(0));
  void clearState();
  bool resetState(const char *state, StartFrameType startFrame = static_cast<StartFrameType>(0));
  const char *getStateName() const;
  u64 getAttribute(u32 index) const;
  bool isEnd() const;
  bool isLoop() const;
  void setLocalTime(f32 time);
  f32 getLocalTime() const;
  void setSpeed(f32 speed);
  f32 getSpeed() const;
  bool doEaseInAdditive(const char *state, f32 time, f32 weight = 1.0f, InterpolateType type = static_cast<InterpolateType>(1), InterpolateCurve curve = static_cast<InterpolateCurve>(0));
  bool doEaseOutAdditive(const char *state, f32 time, InterpolateType type = static_cast<InterpolateType>(1), InterpolateCurve curve = static_cast<InterpolateCurve>(0));
  void clearAdditiveState();
  bool setAdditiveStateWeight(const char *state, f32 weight);
  bool setAdditiveStateSpeed(const char *state, f32 speed);

  mm::mtl::IntrusivePtr<AsmState> m_state;
  mm::mtl::IntrusivePtr<AsmState> m_nextState;
  u8 _10[0x28 - 0x10];
  const InterpolateInfo *m_pInterpolateInfo;
  f32 m_interpolateTime;
  u8 _34[0x50 - 0x34];
  AsmListener *m_listener;
  u8 _58[0x70 - 0x58];
};

static_assert(offsetof(StateMachine, m_pInterpolateInfo) == 0x28, "");
static_assert(offsetof(StateMachine, m_interpolateTime) == 0x30, "");
static_assert(offsetof(StateMachine, m_listener) == 0x50, "");
static_assert(sizeof(StateMachine) == 0x70, "");

} // namespace anm
