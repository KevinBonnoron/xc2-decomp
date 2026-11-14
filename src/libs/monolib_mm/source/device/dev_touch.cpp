#include "ml/dev_touch.h"

#include "ml/dev_clock.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_system.h"

namespace ml {

DevTouchInfo::DevTouchInfo() { initialize(); }

void DevTouchInfo::initialize() {
  unknown00 = 0;
  unknown08 = 0;
  unknown0c = -1;
  unknown10 = 0;
  unknown20 = dev_touch_detail::s_initPos;
  unknown30 = dev_touch_detail::s_initPos;
  unknown40 = dev_touch_detail::s_initPos;
  unknown50 = mm::Vec2::zero;
}

DevTouch::DevTouch(const char *name, WorkObj *parent) : WorkObj(name, parent, 0) {}

int DevTouch::getContactIndex(u32 contactId) {
  for (u32 i = 0; i < unknown1c0.size(); i++) {
    if (unknown1c0[i].unknown0c == contactId) {
      return i;
    }
  }

  if (unknown1c0.size() >= unknown1c0.capacity()) {
    return -1;
  }

  DevTouchInfo info;
  info.unknown0c = contactId;
  int index = unknown1c0.size();
  unknown1c0.push_back(info);
  return index;
}

void DevTouch::releseContact(u32 contactId) {
  for (DevTouchInfo *it = unknown1c0.begin(); it != unknown1c0.end(); ++it) {
    if (it->unknown0c == contactId) {
      unknown1c0.erase(it);
      return;
    }
  }
}

DevTouchInfo *DevTouch::getInfo(u32 index) { return &get()->unknown1c0[index]; }

void DevTouch::itMove(u32 index, f32 x, f32 y) {
  int i = getContactIndex(index);
  if (i < 0) {
    return;
  }

  unknown1c0[i].unknown50.x = x - unknown1c0[i].unknown30.x;
  unknown1c0[i].unknown50.y = y - unknown1c0[i].unknown30.y;
  unknown1c0[i].unknown30.x = x;
  unknown1c0[i].unknown30.y = y;
}

void DevTouch::itUp(u32 index, f32 x, f32 y) { releseContact(index); }

int DevTouch::getTouchCount() { return get()->unknown1c0.size(); }

void DevTouch::updateDevice() {}

void DevTouch::wkUpdate() {
  updateDevice();
  long now;
  if (DevClock::getClockNow(now)) {
    for (DevTouchInfo *it = unknown1c0.begin(); it != unknown1c0.end(); ++it) {
      if (it->unknown00 == 0) {
        it->unknown00 = now;
      } else {
        long elapsed = now - it->unknown00;
        it->unknown08 = DevClock::getClock2Sec(elapsed);
      }
    }
  }
}

bool DevTouch::isInitialized() {
  DevTouch *touch = get();
  if (touch->wkIsWaitException()) {
    return false;
  }

  return touch->wkIsActive();
}

bool DevTouch::wkStandbyLogin() {
  if (!createDevice()) {
    return false;
  }

  return WorkObj::wkStandbyLogin();
}

bool DevTouch::wkStandbyLogout() {
  if (unknown60.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
    releaseDevice();
    return WorkObj::wkStandbyLogout();
  }

  return false;
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevTouch>::~PtrSingleton();
