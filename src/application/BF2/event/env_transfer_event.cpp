#include "event/env_transfer_event.h"

namespace event {

EnvTransferEvent::EnvTransferEvent() : mFromEventID(0), mToEventID(0) {}

void EnvTransferEvent::clear() {
  EnvTransfer::clear();
  mFromEventID = 0;
  mToEventID = 0;
}

void EnvTransferEvent::save(u32 fromEventID, u32 toEventID) {
  EnvTransfer::save();
  mFromEventID = fromEventID;
  mToEventID = toEventID;
}

bool EnvTransferEvent::has(u32 eventID) const { return mToEventID == eventID; }

void EnvTransferEvent::load(u32 eventID) {
  if (has(eventID)) {
    EnvTransfer::load();
    mFromEventID = 0;
    mToEventID = 0;
  }
}

} // namespace event
