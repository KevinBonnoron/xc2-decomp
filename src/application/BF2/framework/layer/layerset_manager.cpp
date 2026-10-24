#include "framework/layer/layerset_manager.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "layer/layer_manager.h"
#include "mtl/alloc_handle.h"

namespace fw {

LayerSetManager::LayerSetManager() : unknown18(nullptr) {}

bool LayerSetManager::initialize() {
  if (unknown18 == nullptr) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 31
    unknown18 = new (Framework::getAllocator(), 16, __FILE__, __LINE__) layer::LayerManager(Framework::get()->unknown58, FrameworkMemory::getMem(1), 0xe00000);
  }

  return true;
}

bool LayerSetManager::finalize() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }

  return true;
}

void LayerSetManager::tail() {
  if (isFinalized()) {
    return;
  }

  if (unknown18 != nullptr) {
    unknown18->tail();
  }
}

void LayerSetManager::openDebugWindow() {
  if (unknown18 != nullptr) {
    unknown18->openDebugWindow(Framework::get()->unknown50);
  }
}

} // namespace fw
