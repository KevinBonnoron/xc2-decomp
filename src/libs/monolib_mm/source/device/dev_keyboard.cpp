#include "ml/dev_keyboard.h"

#include "ml/reslist.h"
#include "ml/work_root.h"

namespace ml {

bool DevKeyboard::isInitialized() {
  DevKeyboard *keyboard = get();
  if (keyboard == nullptr || keyboard->wkIsWaitException()) {
    return false;
  }

  return keyboard->wkIsActive();
}

u32 DevKeyboard::getVkDown() {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    return keyboard->m_vkDown;
  }

  return 0;
}

u32 DevKeyboard::getVkUp() {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    return keyboard->m_vkUp;
  }

  return 0;
}

u32 DevKeyboard::getVkHold() {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    return keyboard->m_hold;
  }

  return 0;
}

bool DevKeyboard::isVkDown(u32 key) {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    return (keyboard->m_vkDown & key) != 0;
  }

  return false;
}

bool DevKeyboard::isVkUp(u32 key) {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    return (keyboard->m_vkUp & key) != 0;
  }

  return false;
}

int DevKeyboard::getCharDownNum() {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    return keyboard->m_charDownNum;
  }

  return 0;
}

u8 DevKeyboard::getCodeDown(u32 index) {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    return keyboard->m_charDown[index];
  }

  return 0;
}

int DevKeyboard::getCharUpNum() {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    return keyboard->m_charUpNum;
  }

  return 0;
}

u8 DevKeyboard::getCodeUp(u32 index) {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    return keyboard->m_charUp[index];
  }

  return 0;
}

void DevKeyboard::updateKey() {
  u32 up = m_upAccum;
  m_prevHold = m_hold;
  m_hold = (m_hold | m_downAccum) & ~up;
  m_vkDown = (m_prevHold ^ m_hold) & m_downAccum;
  m_vkUp = (m_prevHold ^ m_hold) & up;
  m_downAccum = 0;
  m_upAccum = 0;
}

void DevKeyboard::ikReturnUp() {
  m_upAccum |= VK_RETURN;
  updateKey();
}

void DevKeyboard::ikTabUp() {
  m_upAccum |= VK_TAB;
  updateKey();
}

void DevKeyboard::ikDeleteUp() {
  if (!(m_vkUp & VK_DELETE)) {
    m_upAccum |= VK_DELETE;
    updateKey();
  }
}

void DevKeyboard::ikShiftUp() {
  m_upAccum |= VK_SHIFT;
  updateKey();
}

void DevKeyboard::ikCtrlUp() {
  m_upAccum |= VK_CTRL;
  updateKey();
}

void DevKeyboard::ikAltUp() {
  m_upAccum |= VK_ALT;
  updateKey();
}

void DevKeyboard::ikFuncUp(u8 index) {
  m_upAccum |= 1 << (index + VK_FUNC_SHIFT);
  updateKey();
}

bool DevKeyboard::ikIsAltDown() const { return (m_downAccum & VK_ALT) || (m_hold & VK_ALT); }

bool DevKeyboard::ikIsAltUp() const { return (m_upAccum & VK_ALT) || !(m_hold & VK_ALT); }

bool DevKeyboard::ikIsHomeDown() const { return (m_downAccum & VK_HOME) || (m_hold & VK_HOME); }

bool DevKeyboard::ikIsHomeUp() const { return (m_upAccum & VK_HOME) || !(m_hold & VK_HOME); }

bool DevKeyboard::ikIsEndDown() const { return (m_downAccum & VK_END) || (m_hold & VK_END); }

bool DevKeyboard::ikIsEndUp() const { return (m_upAccum & VK_END) || !(m_hold & VK_END); }

void DevKeyboard::ikHomeUp() {
  m_upAccum |= VK_HOME;
  updateKey();
}

void DevKeyboard::ikEndUp() {
  m_upAccum |= VK_END;
  updateKey();
}

void DevKeyboard::ikPageUpUp() {
  m_upAccum |= VK_PAGE_UP;
  updateKey();
}

void DevKeyboard::ikPageDownUp() {
  m_upAccum |= VK_PAGE_DOWN;
  updateKey();
}

void DevKeyboard::ikPauseUp() {
  m_upAccum |= VK_PAUSE;
  updateKey();
}

void DevKeyboard::ikScrollUp() {
  m_upAccum |= VK_SCROLL;
  updateKey();
}

void DevKeyboard::wkFrameEnd() {
  for (int i = 0; i < m_charDownNumAccum; i++) {
    m_charDown[i] = m_charDownAccum[i];
  }

  for (int i = 0; i < m_charUpNumAccum; i++) {
    m_charUp[i] = m_charUpAccum[i];
  }

  m_charDownNum = m_charDownNumAccum;
  m_charUpNum = m_charUpNumAccum;
  m_charDownNumAccum = 0;
  m_charUpNumAccum = 0;
  m_vkDown = 0;
  m_vkUp = 0;
  m_keyMsgOn.clear();
  m_keyMsgOff.clear();
}

bool DevKeyboard::wkStandbyLogin() {
  WorkRootState::addFrameEnd(this);
  return WorkObj::wkStandbyLogin();
}

bool DevKeyboard::wkStandbyLogout() {
  if (m_children.size() != 0) {
    return false;
  }

  WorkRootState::removeFrameEnd(this);
  return WorkObj::wkStandbyLogout();
}

void DevKeyboard::clearKey() {
  DevKeyboard *keyboard = get();
  if (keyboard != nullptr) {
    keyboard->m_hold = 0;
    keyboard->m_prevHold = 0;
    keyboard->m_vkDown = 0;
    keyboard->m_vkUp = 0;
    keyboard->m_downAccum = 0;
    keyboard->m_upAccum = 0;
    keyboard->m_charDownNum = 0;
    keyboard->m_charUpNum = 0;
    keyboard->m_charDownNumAccum = 0;
    keyboard->m_charUpNumAccum = 0;
  }
}

void DevKeyboard::ikKeyMsgOn(u32 message) { m_keyMsgOn.push_back(message); }

void DevKeyboard::ikKeyMsgOff(u32 message) { m_keyMsgOff.push_back(message); }

} // namespace ml
