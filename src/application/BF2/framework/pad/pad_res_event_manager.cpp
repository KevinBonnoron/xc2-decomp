#include "framework/pad/pad_res_event_manager.h"

#include "framework/pad/pad_res_event.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {

PadResEventManager::PadResEventManager() {}

PadResEventManager::~PadResEventManager() {}

void PadResEventManager::cleanup() {
  unknown08.clear();
  unknown08.setAllocator(nullptr);
}

void PadResEventManager::setResource(u32 index, const PadResEvent *event) {
  PadResEventManager *manager = get();
  if (manager != nullptr) {
    manager->unknown08[index] = event;
  }
}

} // namespace fw
