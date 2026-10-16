#pragma once
#include "event/env_transfer.h"

namespace event {

class EnvTransferField : public EnvTransfer {
public:
  EnvTransferField();
  virtual ~EnvTransferField() {}
  void clear();
  void save();
  void load();
};

static_assert(sizeof(EnvTransferField) == 0x18, "");

} // namespace event
