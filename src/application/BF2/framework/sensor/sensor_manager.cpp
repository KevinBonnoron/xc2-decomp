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

const char *SensorUpdateJob::_TYPE_NAME = "SensorUpdateJob";

SensorUpdateJob::SensorUpdateJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(SensorUpdateJob), 0), unknown20(count) {
  unknown10[0] = nullptr;
  unknown10[1] = nullptr;
}

void SensorUpdateJob::exec(anm::Job &job) {
  SensorUpdateJob &updateJob = static_cast<SensorUpdateJob &>(job);
  for (int i = 0; i < updateJob.unknown20; i++) {
    updateJob.unknown10[i]->unknown10();
  }
}

} // namespace fw
