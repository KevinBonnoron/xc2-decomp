#include "framework/dynamics/dynamics_manager.h"

namespace fw {

const char *DyanmicsManager::getName() const { return "DyanmicsManager"; }

void DyanmicsManager::update(const UpdateInfo &info) {}

void DyanmicsManager::addColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater) { unknown18[layer].unknown18.push_back(&updater); }

void DyanmicsManager::removeColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater) { unknown18[layer].unknown18.erase(&updater); }

void DyanmicsManager::addUpdater(u32 layer, DynamicsUpdaterInterface &updater) { unknown18[layer].unknown00.push_back(&updater); }

void DyanmicsManager::removeUpdater(u32 layer, DynamicsUpdaterInterface &updater) { unknown18[layer].unknown00.erase(&updater); }

const char *DynamicsColUpdateJob::_TYPE_NAME = "DynamicsColUpdateJob";

DynamicsColUpdateJob::DynamicsColUpdateJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(DynamicsColUpdateJob), 0), unknown18(count) {}

void DynamicsColUpdateJob::exec(anm::Job &job) {
  DynamicsColUpdateJob &colUpdateJob = static_cast<DynamicsColUpdateJob &>(job);
  for (int i = 0; i < colUpdateJob.unknown18; i++) {
    colUpdateJob.unknown10[i]->update();
  }
}

const char *DynamicsUpdateJob::_TYPE_NAME = "DynamicsUpdateJob";

DynamicsUpdateJob::DynamicsUpdateJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(DynamicsUpdateJob), 1), unknown18(count), unknown20(nullptr) {}

void DynamicsUpdateJob::exec(anm::Job &job) {
  DynamicsUpdateJob &updateJob = static_cast<DynamicsUpdateJob &>(job);
  for (int i = 0; i < updateJob.unknown18; i++) {
    updateJob.unknown10[i]->update(*updateJob.unknown20);
  }
}

} // namespace fw
