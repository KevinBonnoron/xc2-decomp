#include "event/areaeff_manager.h"

namespace event {

AreaeffManager::AreaeffManager() { flags.bits = 0; }

void AreaeffManager::clear() { flags.bits = 0; }

void AreaeffManager::exec(f32 deltaFrame) {
  if (flags.isOn(FLAG_SLEEP_LIGHT)) {
    if ((mSleepTime -= deltaFrame) < 0.0f) {
      flags.set(FLAG_SLEEP_LIGHT, false);
      updateDisable();
    }
  }
}

void AreaeffManager::updateDisable() {
  bool isDisableLight = flags.isOn(FLAG_HIDE_LIGHT | FLAG_SLEEP_LIGHT);
  if (flags.isOn(FLAG_DISABLE_LIGHT) != isDisableLight) {
    flags.set(FLAG_DISABLE_LIGHT, isDisableLight);
  }
  bool isDisableSe = flags.isOn(FLAG_HIDE_SE | FLAG_PAUSE);
  if (flags.isOn(FLAG_DISABLE_SE) != isDisableSe) {
    flags.set(FLAG_DISABLE_SE, isDisableSe);
  }
}

void AreaeffManager::pause(bool isPause) {
  flags.set(FLAG_PAUSE, isPause);
  updateDisable();
}

void AreaeffManager::setup() { clear(); }

void AreaeffManager::start() {}

void AreaeffManager::setDispLight(bool isDisp) {
  flags.set(FLAG_HIDE_LIGHT, !isDisp);
  updateDisable();
}

void AreaeffManager::sleepLight(bool isSleep, f32 sleepTime) {
  flags.set(FLAG_SLEEP_LIGHT, isSleep);
  mSleepTime = sleepTime;
  updateDisable();
}

void AreaeffManager::setDispSe(bool isDisp) {
  flags.set(FLAG_HIDE_SE, !isDisp);
  updateDisable();
}

} // namespace event
