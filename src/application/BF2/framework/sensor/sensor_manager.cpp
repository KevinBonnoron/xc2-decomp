#include "framework/sensor/sensor_manager.h"

namespace fw {

void SensorManager::addUpdaterBeforeGame(u32 layer, SensorUpdater &updater) {
  unknown18[layer].unknown00.push_back(&updater);
  updater.unknown30 = true;
}

void SensorManager::removeUpdaterBeforeGame(u32 layer, SensorUpdater &updater) {
  unknown18[layer].unknown00.erase(&updater);
  updater.unknown30 = false;
}

void SensorManager::addUpdaterAfterAnimation(u32 layer, SensorUpdater &updater) {
  unknown18[layer].unknown18.push_back(&updater);
  updater.unknown30 = true;
}

void SensorManager::removeUpdaterAfterAnimation(u32 layer, SensorUpdater &updater) {
  unknown18[layer].unknown18.erase(&updater);
  updater.unknown30 = false;
}

} // namespace fw
