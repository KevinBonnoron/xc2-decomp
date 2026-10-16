#include "framework/dynamics/dynamics_manager.h"

namespace fw {

void DyanmicsManager::addColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater) { groups[layer].colUpdaters.push_back(&updater); }

void DyanmicsManager::removeColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater) { groups[layer].colUpdaters.erase(&updater); }

void DyanmicsManager::addUpdater(u32 layer, DynamicsUpdaterInterface &updater) { groups[layer].updaters.push_back(&updater); }

void DyanmicsManager::removeUpdater(u32 layer, DynamicsUpdaterInterface &updater) { groups[layer].updaters.erase(&updater); }

} // namespace fw
