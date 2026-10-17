#include "ml/dev_mouse.h"

#include "ml/dev_pad.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_system.h"

namespace ml {

namespace {

mm::Pnt<int> s_clipMove;

} // namespace

bool DevMouse::isInitialized() {
  DevMouse *mouse = get();
  if (mouse->wkIsWaitException()) {
    return false;
  }

  return mouse->wkIsActive();
}

void DevMouse::setClipMove(int x, int y) {
  s_clipMove.x += x;
  s_clipMove.y += y;
}

void DevMouse::getClipMove(mm::Pnt<int> &move) {
  move = s_clipMove;
  s_clipMove = mm::Pnt<int>(0, 0);
}

const mm::Pnt<int> &DevMouse::getPos() { return get()->m_pos; }

const mm::Pnt<int> &DevMouse::getMove() { return get()->m_move; }

int DevMouse::getWheel() { return get()->m_wheel; }

u32 DevMouse::buttonOn() { return get()->m_buttonOn; }

u32 DevMouse::buttonOff() { return get()->m_buttonOff; }

u32 DevMouse::button() { return get()->m_button; }

u32 DevMouse::buttonDbl() { return get()->m_buttonDbl; }

void DevMouse::imPos(int x, int y) {
  imMove(x - m_pos.x, y - m_pos.y);
  m_pos.x = x;
  m_pos.y = y;
}

void DevMouse::imMove(int x, int y) {
  m_moveAccum.x += x;
  m_moveAccum.y += y;
}

void DevMouse::imWheel(int wheel) { m_wheelAccum += wheel; }

void DevMouse::imLButtonUp() {
  m_buttonOffAccum |= 0x1;
  m_button &= ~0x1;
}

void DevMouse::imMButtonUp() {
  m_buttonOffAccum |= 0x2;
  m_button &= ~0x2;
}

void DevMouse::imRButtonUp() {
  m_buttonOffAccum |= 0x4;
  m_button &= ~0x4;
}

void DevMouse::imLButtonDown() {
  m_buttonOnAccum |= 0x1;
  m_button |= 0x1;
}

void DevMouse::imMButtonDown() {
  m_buttonOnAccum |= 0x2;
  m_button |= 0x2;
}

void DevMouse::imRButtonDown() {
  m_buttonOnAccum |= 0x4;
  m_button |= 0x4;
}

void DevMouse::imLButtonDbl() { m_buttonDblAccum |= 0x1; }

void DevMouse::imMButtonDbl() { m_buttonDblAccum |= 0x2; }

void DevMouse::imRButtonDbl() { m_buttonDblAccum |= 0x4; }

void DevMouse::updateDevice() {
  if (m_isPadMouse && !m_isMouseInput) {
    if (!(DevPad::getBtn(9) & 0xf000)) {
      m_padMouseSpeed = 0.7f;
    } else {
      m_padMouseSpeed += 0.3f;
      if (m_padMouseSpeed < 0.0f) {
        m_padMouseSpeed = 0.0f;
      } else if (m_padMouseSpeed > 8.0f) {
        m_padMouseSpeed = 8.0f;
      }
    }
  }
}

void DevMouse::wkUpdate() {
  updateDevice();
  m_move = m_moveAccum;
  m_moveAccum = mm::Pnt<int>(0, 0);
  m_wheel = m_wheelAccum;
  m_wheelAccum = 0;
  m_buttonOn = m_buttonOnAccum;
  m_buttonOnAccum = 0;
  m_buttonOff = m_buttonOffAccum;
  m_buttonOffAccum = 0;
  m_buttonDbl = m_buttonDblAccum;
  m_buttonDblAccum = 0;
}

bool DevMouse::wkStandbyLogin() {
  if (!createDevice()) {
    return false;
  }

  return WorkObj::wkStandbyLogin();
}

bool DevMouse::wkStandbyLogout() {
  if (m_children.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
    releaseDevice();
    return WorkObj::wkStandbyLogout();
  }

  return false;
}

void DevMouse::setPadMouse(bool isPadMouse) { get()->m_isPadMouse = isPadMouse; }

bool DevMouse::isPadMouse() { return get()->m_isPadMouse; }

void DevMouse::resetMouse() { get()->imMove(700, 700); }

} // namespace ml
