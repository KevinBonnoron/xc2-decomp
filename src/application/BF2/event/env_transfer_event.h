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
  u32 mFromEventID;
  u32 mToEventID;
};

static_assert(sizeof(EnvTransferEvent) == 0x20, "");

} // namespace event
