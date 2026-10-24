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

const mm::Pnt<int> &DevMouse::getPos() { return get()->unknown1b8; }

const mm::Pnt<int> &DevMouse::getMove() { return get()->unknown1c8; }

int DevMouse::getWheel() { return get()->unknown1d4; }

u32 DevMouse::buttonOn() { return get()->unknown1e0; }

u32 DevMouse::buttonOff() { return get()->unknown1e4; }

u32 DevMouse::button() { return get()->unknown1e8; }

u32 DevMouse::buttonDbl() { return get()->unknown1ec; }

void DevMouse::imPos(int x, int y) {
  imMove(x - unknown1b8.x, y - unknown1b8.y);
  unknown1b8.x = x;
  unknown1b8.y = y;
}

void DevMouse::imMove(int x, int y) {
  unknown1c0.x += x;
  unknown1c0.y += y;
}

void DevMouse::imWheel(int wheel) { unknown1d0 += wheel; }

void DevMouse::imLButtonUp() {
  unknown1dc |= 0x1;
  unknown1e8 &= ~0x1;
}

void DevMouse::imMButtonUp() {
  unknown1dc |= 0x2;
  unknown1e8 &= ~0x2;
}

void DevMouse::imRButtonUp() {
  unknown1dc |= 0x4;
  unknown1e8 &= ~0x4;
}

void DevMouse::imLButtonDown() {
  unknown1d8 |= 0x1;
  unknown1e8 |= 0x1;
}

void DevMouse::imMButtonDown() {
  unknown1d8 |= 0x2;
  unknown1e8 |= 0x2;
}

void DevMouse::imRButtonDown() {
  unknown1d8 |= 0x4;
  unknown1e8 |= 0x4;
}

void DevMouse::imLButtonDbl() { unknown1f0 |= 0x1; }

void DevMouse::imMButtonDbl() { unknown1f0 |= 0x2; }

void DevMouse::imRButtonDbl() { unknown1f0 |= 0x4; }

void DevMouse::updateDevice() {
  if (unknown1f4 && !unknown1fc) {
    if (!(DevPad::getBtn(9) & 0xf000)) {
      unknown1f8 = 0.7f;
    } else {
      unknown1f8 += 0.3f;
      if (unknown1f8 < 0.0f) {
        unknown1f8 = 0.0f;
      } else if (unknown1f8 > 8.0f) {
        unknown1f8 = 8.0f;
      }
    }
  }
}

void DevMouse::wkUpdate() {
  updateDevice();
  unknown1c8 = unknown1c0;
  unknown1c0 = mm::Pnt<int>(0, 0);
  unknown1d4 = unknown1d0;
  unknown1d0 = 0;
  unknown1e0 = unknown1d8;
  unknown1d8 = 0;
  unknown1e4 = unknown1dc;
  unknown1dc = 0;
  unknown1ec = unknown1f0;
  unknown1f0 = 0;
}

bool DevMouse::wkStandbyLogin() {
  if (!createDevice()) {
    return false;
  }

  return WorkObj::wkStandbyLogin();
}

bool DevMouse::wkStandbyLogout() {
  if (unknown60.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
    releaseDevice();
    return WorkObj::wkStandbyLogout();
  }

  return false;
}

void DevMouse::setPadMouse(bool isPadMouse) { get()->unknown1f4 = isPadMouse; }

bool DevMouse::isPadMouse() { return get()->unknown1f4; }

void DevMouse::resetMouse() { get()->imMove(700, 700); }

} // namespace ml
