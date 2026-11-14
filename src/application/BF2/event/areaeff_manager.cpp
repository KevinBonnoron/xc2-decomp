#include "event/areaeff_manager.h"

namespace event {

AreaeffManager::AreaeffManager() { unknown10.unknown00 = 0; }

void AreaeffManager::clear() { unknown10.unknown00 = 0; }

void AreaeffManager::exec(f32 deltaFrame) {
  if (unknown10.isOn(FLAG_UNKNOWN_1)) {
    if ((unknown14 -= deltaFrame) < 0.0f) {
      unknown10.set(FLAG_UNKNOWN_1, false);
      updateDisable();
    }
  }
}

void AreaeffManager::updateDisable() {
  bool isDisableLight = unknown10.isOn(FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1);
  if (unknown10.isOn(FLAG_UNKNOWN_2) != isDisableLight) {
    unknown10.set(FLAG_UNKNOWN_2, isDisableLight);
  }
  bool isDisableSe = unknown10.isOn(FLAG_UNKNOWN_3 | FLAG_UNKNOWN_4);
  if (unknown10.isOn(FLAG_UNKNOWN_5) != isDisableSe) {
    unknown10.set(FLAG_UNKNOWN_5, isDisableSe);
  }
}

void AreaeffManager::pause(bool isPause) {
  unknown10.set(FLAG_UNKNOWN_4, isPause);
  updateDisable();
}

void AreaeffManager::setup() { clear(); }

void AreaeffManager::start() {}

void AreaeffManager::setDispLight(bool isDisp) {
  unknown10.set(FLAG_UNKNOWN_0, !isDisp);
  updateDisable();
}

void AreaeffManager::sleepLight(bool isSleep, f32 sleepTime) {
  unknown10.set(FLAG_UNKNOWN_1, isSleep);
  unknown14 = sleepTime;
  updateDisable();
}

void AreaeffManager::setDispSe(bool isDisp) {
  unknown10.set(FLAG_UNKNOWN_3, !isDisp);
  updateDisable();
}

} // namespace event
