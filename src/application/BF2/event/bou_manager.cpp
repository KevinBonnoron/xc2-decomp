#include "event/bou_manager.h"

#include "event/i_bou_callback.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"

namespace event {

BouManager::BouManager() : flags(), mDebugFlags() {}

void BouManager::endActive() { flags.set(FLAG_ACTIVE, false); }

void BouManager::startActive(const mm::Pnt<int> &point) {
  mRect.x = point.x;
  mRect.y = point.y;
  // The target reloads +0x28 before subtracting. This read preserves that
  // instruction; it does not establish a volatile original member type.
  mRect.width = point.x - *reinterpret_cast<volatile int *>(&mRect.x);
  mRect.height = point.y - mRect.y;
  mSelected.clear();
  flags.set(FLAG_ACTIVE);
}

void BouManager::render() {
  if (!isEnable() || !isDebugEnable()) {
    return;
  }
  if (flags.test(FLAG_ACTIVE)) {
    mRect.render();
  }
  for (IBouCallback **it = mSelected.begin(); it != mSelected.end(); ++it) {
    (*it)->OnBouRender(IBouCallback::RenderParam(mm::Col4(1.0f, 1.0f, 0.8f, 0.5f)));
  }
}

bool BouManager::OnKeyDown(ml::EventView *view) {
  if (isEnable() && isDebugEnable()) {
    flags.set(FLAG_KEY_DOWN);
  }
  return false;
}

bool BouManager::OnKeyUp(ml::EventView *view) {
  if (isEnable() && isDebugEnable()) {
    flags.set(FLAG_KEY_DOWN, false);
  }
  return false;
}

void BouManager::push(IBouCallback *callback) { mCallbacks.push_back(callback); }

void BouManager::pop(IBouCallback *callback) {
  for (IBouCallback **it = mCallbacks.begin(); it != mCallbacks.end(); ++it) {
    if (*it == callback) {
      mCallbacks.erase(it);
      return;
    }
  }
}

void BouManager::setEnable(bool isEnable) {
  if (isEnable) {
    flags.set(FLAG_ENABLE);
  } else {
    mSelected.clear();
    flags.set(FLAG_ENABLE, false);
    flags.set(FLAG_ACTIVE, false);
  }
}

void BouManager::setDebugEnable(bool isEnable) { mDebugFlags.set(DEBUG_FLAG_ENABLE, isEnable); }

} // namespace event
