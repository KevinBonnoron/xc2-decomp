#include "anm/anm_state_machine.h"

#include "anm/anm_asm_state.h"
#include "anm/anm_res_state_data.h"

namespace anm {

void StateMachine::resetInterpolate() {
  unknown28 = nullptr;
  unknown30 = 0.0f;
}

const char *StateMachine::getStateName() const {
  if (unknown00.get() == nullptr) {
    return nullptr;
  }
  return unknown00.get()->unknown18->unknown00->name;
}

u64 StateMachine::getAttribute(u32 index) const {
  if (unknown00.get() == nullptr) {
    return 0;
  }
  const ResStateData *resStateData = unknown00.get()->unknown18;
  if (index == 0) {
    return resStateData->unknown00->attribute;
  }
  return resStateData->unknown30[index - 1];
}

bool StateMachine::isEnd() const {
  if (unknown00.get() == nullptr) {
    return false;
  }
  bool isOver = unknown00.get()->unknown2c >= unknown00.get()->unknown28;
  bool isFinite = unknown00.get()->unknown28 != 0;
  return isFinite & isOver;
}

bool StateMachine::isLoop() const {
  if (unknown00.get() == nullptr) {
    return false;
  }
  return unknown00.get()->unknown28 == 0;
}

void StateMachine::setLocalTime(f32 time) {
  if (unknown00.get() != nullptr) {
    unknown00.get()->setLocalTime(time);
  }
}

f32 StateMachine::getLocalTime() const {
  if (unknown00.get() == nullptr) {
    return 0.0f;
  }
  return unknown00.get()->getLocalTime();
}

void StateMachine::setSpeed(f32 speed) {
  if (unknown00.get() != nullptr) {
    unknown00.get()->setSpeed(speed);
  }
  if (unknown08.get() != nullptr) {
    unknown08.get()->setSpeed(speed);
  }
}

f32 StateMachine::getSpeed() const {
  if (unknown00.get() == nullptr) {
    return 0.0f;
  }
  return unknown00.get()->unknown20;
}

} // namespace anm
