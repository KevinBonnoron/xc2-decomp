#include "event/env_transfer_field.h"

namespace event {

EnvTransferField::EnvTransferField() {}

void EnvTransferField::clear() { EnvTransfer::clear(); }

void EnvTransferField::save() { EnvTransfer::save(); }

void EnvTransferField::load() { EnvTransfer::load(); }

} // namespace event
