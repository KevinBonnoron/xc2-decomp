#include "event/bou_manager.h"

#include "event/i_bou_callback.h"
#include "event/manager.h"
#include "ml/scn.h"
#include "ml/win_view.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"

namespace event {

BouManager::BouManager() : unknown18(), unknown1c() {}

void BouManager::create() {
  if (!unknown18.test(FLAG_ATTACHED)) {
    Manager::get()->getScn()->getView(-1)->attachWorkEvent(this, false);
    unknown18.set(FLAG_ATTACHED);
  }
}

void BouManager::clear() {
  unknown18.set(FLAG_ACTIVE, false);
  if (unknown18.test(FLAG_ATTACHED)) {
    Manager::get()->getScn()->getView(-1)->detachWorkEvent(this);
    unknown18.set(FLAG_ATTACHED, false);
  }
  unknown2040.clear();
  unknown38.clear();
  unknown18.clear();
}

void BouManager::endActive() { unknown18.set(FLAG_ACTIVE, false); }

void BouManager::startActive(const mm::Pnt<int> &point) {
  unknown20.x = point.x;
  unknown20.y = point.y;
  // The target reloads +0x28 before subtracting. This read preserves that
  // instruction; it does not establish a volatile original member type.
  unknown20.width = point.x - *reinterpret_cast<volatile int *>(&unknown20.x);
  unknown20.height = point.y - unknown20.y;
  unknown2040.clear();
  unknown18.set(FLAG_ACTIVE);
}

void BouManager::render() {
  if (!isEnable() || !isDebugEnable()) {
    return;
  }
  if (unknown18.test(FLAG_ACTIVE)) {
    unknown20.render();
  }
  for (IBouCallback **it = unknown2040.begin(); it != unknown2040.end(); ++it) {
    (*it)->OnBouRender(IBouCallback::RenderParam(mm::Col4(1.0f, 1.0f, 0.8f, 0.5f)));
  }
}

bool BouManager::OnKeyDown(ml::EventView *view) {
  if (isEnable() && isDebugEnable()) {
    unknown18.set(FLAG_KEY_DOWN);
  }
  return false;
}

bool BouManager::OnKeyUp(ml::EventView *view) {
  if (isEnable() && isDebugEnable()) {
    unknown18.set(FLAG_KEY_DOWN, false);
  }
  return false;
}

void BouManager::push(IBouCallback *callback) { unknown38.push_back(callback); }

void BouManager::pop(IBouCallback *callback) {
  for (IBouCallback **it = unknown38.begin(); it != unknown38.end(); ++it) {
    if (*it == callback) {
      unknown38.erase(it);
      return;
    }
  }
}

void BouManager::setEnable(bool isEnable) {
  if (isEnable) {
    unknown18.set(FLAG_ENABLE);
  } else {
    unknown2040.clear();
    unknown18.set(FLAG_ENABLE, false);
    unknown18.set(FLAG_ACTIVE, false);
  }
}

void BouManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_RENDER:
    render();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  default:
    break;
  }
}

void BouManager::setDebugEnable(bool isEnable) { unknown1c.set(DEBUG_FLAG_ENABLE, isEnable); }

} // namespace event
