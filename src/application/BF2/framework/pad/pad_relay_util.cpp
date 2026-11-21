#include "framework/pad/pad_relay_util.h"

#include <string.h>

#include "framework/pad/pad_res_event.h"
#include "framework/pad/pad_res_event_manager.h"
#include "fw/fw_pad.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"

namespace fw {

// findAction (1.0.0: 0x7100195ab8) and getFwPadKey (0x7100195b14) are adjacent between the PadRelay code and PadResEventManager::setup, so they
// share one unit: the game inlines findAction into getFwPadKey (75 instructions). Defined in another unit it is a call (62 instructions).
const ResActionInfo *findAction(const PadResEvent *event, const char *name) {
  for (u32 i = 0; i < event->unknown20; i++) {
    if (strcmp(event->unknown18[i].unknown00, name) == 0) {
      return &event->unknown18[i];
    }
  }

  return nullptr;
}

bool PadRelayUtil::getFwPadKey(u32 padIndex, const char *name, u32 arg2, u32 arg3, u32 *key) {
  PadResEventManager *manager = PadResEventManager::get();
  if (manager != nullptr) {
    const PadResEvent *event = manager->unknown08[padIndex].get();
    if (event != nullptr) {
      const ResActionInfo *info = findAction(event, name);
      if (info == nullptr || arg2 >= info->unknown10) {
        return false;
      }
      const ResAction &action = info->unknown08[arg2];
      if (arg3 >= action.unknown08) {
        return false;
      }
      *key = getPadKey(action.unknown00[arg3].unknown04);
      return true;
    }
  }
  return false;
}

} // namespace fw
