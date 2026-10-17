#include "anm/anm_state_machine.h"

#include "anm/anm_res_state_data.h"

namespace anm {

void StateMachine::resetInterpolate() {
  m_pInterpolateInfo = nullptr;
  m_interpolateTime = 0.0f;
}

const char *StateMachine::getStateName() const {
  if (m_state.get() == nullptr) {
    return nullptr;
  }
  return m_state.get()->m_pResStateData->m_pResState->name;
}

u64 StateMachine::getAttribute(u32 index) const {
  if (m_state.get() == nullptr) {
    return 0;
  }
  const ResStateData *resStateData = m_state.get()->m_pResStateData;
  if (index == 0) {
    return resStateData->m_pResState->attribute;
  }
  return resStateData->m_attributes[index - 1];
}

bool StateMachine::isEnd() const {
  if (m_state.get() == nullptr) {
    return false;
  }
  bool isOver = m_state.get()->m_loopCount >= m_state.get()->m_loopNum;
  bool isFinite = m_state.get()->m_loopNum != 0;
  return isFinite & isOver;
}

bool StateMachine::isLoop() const {
  if (m_state.get() == nullptr) {
    return false;
  }
  return m_state.get()->m_loopNum == 0;
}

void StateMachine::setLocalTime(f32 time) {
  if (m_state.get() != nullptr) {
    m_state.get()->setLocalTime(time);
  }
}

f32 StateMachine::getLocalTime() const {
  if (m_state.get() == nullptr) {
    return 0.0f;
  }
  return m_state.get()->getLocalTime();
}

void StateMachine::setSpeed(f32 speed) {
  if (m_state.get() != nullptr) {
    m_state.get()->setSpeed(speed);
  }
  if (m_nextState.get() != nullptr) {
    m_nextState.get()->setSpeed(speed);
  }
}

f32 StateMachine::getSpeed() const {
  if (m_state.get() == nullptr) {
    return 0.0f;
  }
  return m_state.get()->m_speed;
}

} // namespace anm
