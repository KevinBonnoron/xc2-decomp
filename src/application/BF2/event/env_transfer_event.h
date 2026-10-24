#pragma once
#include "event/env_transfer.h"
#include "types.h"

namespace event {

class EnvTransferEvent : public EnvTransfer {
public:
  EnvTransferEvent();
  virtual ~EnvTransferEvent() {}
  void clear();
  void save(u32 fromEventID, u32 toEventID);
  bool has(u32 eventID) const;
  void load(u32 eventID);

private:
  u32 unknown18; // Inferred role: from event id; original member name unknown.
  u32 unknown1c; // Inferred role: to event id; original member name unknown.
};

static_assert(sizeof(EnvTransferEvent) == 0x20, "");

} // namespace event
