#include "framework/layer/layerset_manager.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "layer/layer_manager.h"
#include "mtl/alloc_handle.h"

namespace fw {

LayerSetManager::LayerSetManager() : layerManager(nullptr) {}

bool LayerSetManager::initialize() {
  if (layerManager == nullptr) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 30
    layerManager =
        new (Framework::getAllocator(), 16, __FILE__, __LINE__) layer::LayerManager(Framework::get()->scn, FrameworkMemory::getMem(1), 0xe00000);
  }

  return true;
}

bool LayerSetManager::finalize() {
  if (layerManager != nullptr) {
    delete layerManager;
    layerManager = nullptr;
  }

  return true;
}

void LayerSetManager::tail() {
  if (isFinalized()) {
    return;
  }

  if (layerManager != nullptr) {
    layerManager->tail();
  }
}

void LayerSetManager::openDebugWindow() {
  if (layerManager != nullptr) {
    layerManager->openDebugWindow(Framework::get()->winProc);
  }
}

} // namespace fw
