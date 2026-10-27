#include "framework/pad/pad_res_event.h"

#include <string.h>

namespace fw {

const ResAction *findAction(const PadResEvent *event, const char *name) {
  for (u32 i = 0; i < event->unknown20; i++) {
    if (strcmp(event->unknown18[i].unknown00, name) == 0) {
      return &event->unknown18[i];
    }
  }

  return nullptr;
}

} // namespace fw
