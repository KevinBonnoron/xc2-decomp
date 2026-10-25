#include "ml/dev_touch.h"

#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_system.h"

namespace ml {

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
