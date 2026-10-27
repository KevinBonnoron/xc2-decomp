#include "gf/param/gf_param.h"

#include "framework/pad/pad_res_event_manager.h"
#include "types.h"

namespace gf {

void unbindPadResource() {
  fw::PadResEventManager *manager = fw::PadResEventManager::get();
  if (manager != nullptr) {
    for (u32 index = 0; index < 5; index++) {
      fw::PadResEventManager::setResource(index, nullptr);
    }
    manager->cleanup();
  }
}

} // namespace gf
