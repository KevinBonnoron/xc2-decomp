#include "framework/dynamics/dynamics_manager.h"

namespace fw {

const char *DyanmicsManager::getName() const { return "DyanmicsManager"; }

void DyanmicsManager::update(const UpdateInfo &info) {}

void DyanmicsManager::addColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater) { unknown18[layer].unknown18.push_back(&updater); }

void DyanmicsManager::removeColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater) { unknown18[layer].unknown18.erase(&updater); }

void DyanmicsManager::addUpdater(u32 layer, DynamicsUpdaterInterface &updater) { unknown18[layer].unknown00.push_back(&updater); }

void DyanmicsManager::removeUpdater(u32 layer, DynamicsUpdaterInterface &updater) { unknown18[layer].unknown00.erase(&updater); }

} // namespace fw
