#include "framework/sensor/sensor_manager.h"

namespace fw {

void SensorManager::addUpdaterBeforeGame(u32 layer, SensorUpdater &updater) {
  groups[layer].beforeGameUpdaters.push_back(&updater);
  updater.isRegistered = true;
}

void SensorManager::removeUpdaterBeforeGame(u32 layer, SensorUpdater &updater) {
  groups[layer].beforeGameUpdaters.erase(&updater);
  updater.isRegistered = false;
}

void SensorManager::addUpdaterAfterAnimation(u32 layer, SensorUpdater &updater) {
  groups[layer].afterAnimationUpdaters.push_back(&updater);
  updater.isRegistered = true;
}

void SensorManager::removeUpdaterAfterAnimation(u32 layer, SensorUpdater &updater) {
  groups[layer].afterAnimationUpdaters.erase(&updater);
  updater.isRegistered = false;
}

} // namespace fw
