#include "event/areaeff_manager.h"

namespace event {

AreaeffManager::AreaeffManager() { unknown10.unknown00 = 0; }

void AreaeffManager::clear() { unknown10.unknown00 = 0; }

void AreaeffManager::exec(f32 deltaFrame) {
  if (unknown10.isOn(FLAG_SLEEP_LIGHT)) {
    if ((unknown14 -= deltaFrame) < 0.0f) {
      unknown10.set(FLAG_SLEEP_LIGHT, false);
      updateDisable();
    }
  }
}

void AreaeffManager::updateDisable() {
  bool isDisableLight = unknown10.isOn(FLAG_HIDE_LIGHT | FLAG_SLEEP_LIGHT);
  if (unknown10.isOn(FLAG_DISABLE_LIGHT) != isDisableLight) {
    unknown10.set(FLAG_DISABLE_LIGHT, isDisableLight);
  }
  bool isDisableSe = unknown10.isOn(FLAG_HIDE_SE | FLAG_PAUSE);
  if (unknown10.isOn(FLAG_DISABLE_SE) != isDisableSe) {
    unknown10.set(FLAG_DISABLE_SE, isDisableSe);
  }
}

void AreaeffManager::pause(bool isPause) {
  unknown10.set(FLAG_PAUSE, isPause);
  updateDisable();
}

void AreaeffManager::setup() { clear(); }

void AreaeffManager::start() {}

void AreaeffManager::setDispLight(bool isDisp) {
  unknown10.set(FLAG_HIDE_LIGHT, !isDisp);
  updateDisable();
}

void AreaeffManager::sleepLight(bool isSleep, f32 sleepTime) {
  unknown10.set(FLAG_SLEEP_LIGHT, isSleep);
  unknown14 = sleepTime;
  updateDisable();
}

void AreaeffManager::setDispSe(bool isDisp) {
  unknown10.set(FLAG_HIDE_SE, !isDisp);
  updateDisable();
}

} // namespace event
