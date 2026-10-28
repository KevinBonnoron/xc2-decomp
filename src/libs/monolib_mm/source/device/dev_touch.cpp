#include "ml/dev_touch.h"

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

void DevTouch::releseContact(u32 contactId) {
  for (DevTouchInfo *it = unknown1c0.begin(); it != unknown1c0.end(); ++it) {
    if (it->unknown0c == contactId) {
      unknown1c0.erase(it);
      return;
    }
  }
}

DevTouchInfo *DevTouch::getInfo(u32 index) { return &get()->unknown1c0[index]; }

void DevTouch::itUp(u32 index, f32 x, f32 y) { releseContact(index); }

int DevTouch::getTouchCount() { return get()->unknown1c0.size(); }

void DevTouch::updateDevice() {}

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
