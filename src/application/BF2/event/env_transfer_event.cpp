#include "event/env_transfer_event.h"

namespace event {

EnvTransferEvent::EnvTransferEvent() : unknown18(0), unknown1c(0) {}

void EnvTransferEvent::clear() {
  EnvTransfer::clear();
  unknown18 = 0;
  unknown1c = 0;
}

void EnvTransferEvent::save(u32 fromEventID, u32 toEventID) {
  EnvTransfer::save();
  unknown18 = fromEventID;
  unknown1c = toEventID;
}

bool EnvTransferEvent::has(u32 eventID) const { return unknown1c == eventID; }

void EnvTransferEvent::load(u32 eventID) {
  if (has(eventID)) {
    EnvTransfer::load();
    unknown18 = 0;
    unknown1c = 0;
  }
}

} // namespace event
