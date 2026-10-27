#include "device/nx/dev_pad_nx.h"

namespace ml {

int DevPadNx::getLocalUserSelectPadID() const {
  const Impl *impl = unknown548.operator->();
  return impl->unknown4544 != impl->unknown4540 ? impl->unknown4544 : 4;
}

bool DevPadNx::createDevice() { return true; }

void DevPadNx::releaseDevice() { unknown548->release(); }

} // namespace ml
