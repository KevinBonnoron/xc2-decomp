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

int DevTouch::getTouchCount() { return get()->m_touchCount; }

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
