#include "event/bou_manager.h"

#include "event/i_bou_callback.h"
#include "event/manager.h"
#include "ml/event_view.h"
#include "ml/scn.h"
#include "ml/win_view.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"

namespace event {

BouManager::BouManager() : unknown18(), unknown1c() {}

void BouManager::create() {
  if (!unknown18.test(FLAG_UNKNOWN_1)) {
    Manager::get()->getScn()->getView(-1)->attachWorkEvent(this, false);
    unknown18.set(FLAG_UNKNOWN_1);
  }
}

void BouManager::clear() {
  unknown18.set(FLAG_UNKNOWN_2, false);
  if (unknown18.test(FLAG_UNKNOWN_1)) {
    Manager::get()->getScn()->getView(-1)->detachWorkEvent(this);
    unknown18.set(FLAG_UNKNOWN_1, false);
  }
  unknown2040.clear();
  unknown38.clear();
  unknown18.clear();
}

void BouManager::endActive() { unknown18.set(FLAG_UNKNOWN_2, false); }

void BouManager::render() {
  if (!isEnable() || !isDebugEnable()) {
    return;
  }
  if (unknown18.test(FLAG_UNKNOWN_2)) {
    unknown20.render();
  }
  for (IBouCallback **it = unknown2040.begin(); it != unknown2040.end(); ++it) {
    (*it)->OnBouRender(IBouCallback::RenderParam(mm::Col4(1.0f, 1.0f, 0.8f, 0.5f)));
  }
}

void BouManager::startActive(const mm::Pnt<int> &point) {
  unknown20.x = point.x;
  unknown20.y = point.y;
  unknown003(point);
  unknown2040.clear();
  unknown18.set(FLAG_UNKNOWN_2);
}

bool BouManager::OnMouseButtonDown(ml::EventView *view) {
  if (isEnable() && isDebugEnable() && unknown002() && (view->buttons & ml::EventView::BUTTON_UNKNOWN_0) != 0) {
    startActive(view->pos);
    updateActive(view->pos);
  }
  return false;
}

bool BouManager::OnMouseMove(ml::EventView *view) {
  if (unknown001()) {
    unknown003(view->pos);
    updateActive(view->pos);
  }
  return false;
}

bool BouManager::OnMouseButtonUp(ml::EventView *view) {
  if (unknown001()) {
    unknown18.set(FLAG_UNKNOWN_2, false);
  }
  return false;
}

bool BouManager::OnKeyDown(ml::EventView *view) {
  if (isEnable() && isDebugEnable()) {
    unknown18.set(FLAG_UNKNOWN_3);
  }
  return false;
}

bool BouManager::OnKeyUp(ml::EventView *view) {
  if (isEnable() && isDebugEnable()) {
    unknown18.set(FLAG_UNKNOWN_3, false);
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
    unknown18.set(FLAG_UNKNOWN_0);
  } else {
    unknown2040.clear();
    unknown18.set(FLAG_UNKNOWN_0, false);
    unknown18.set(FLAG_UNKNOWN_2, false);
  }
}

void BouManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_16:
    render();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  default:
    break;
  }
}

void BouManager::setDebugEnable(bool isEnable) { unknown1c.set(DEBUG_FLAG_UNKNOWN_0, isEnable); }

} // namespace event
