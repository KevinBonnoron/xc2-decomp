#include "device/nx/dev_pad_nx.h"

namespace ml {

int DevPadNx::getLocalUserSelectPadID() const {
  const Impl *impl = unknown548.operator->();
  return impl->unknown4544 != impl->unknown4540 ? impl->unknown4544 : 4;
}

void DevPadNx::setUserSelectControllerID(u32 id) {
  DevPadNx *pad = static_cast<DevPadNx *>(get());
  if (pad == nullptr) {
    return;
  }
  Impl *impl = pad->unknown548.operator->();
  impl->unknown4544 = -1;
  for (int i = 0; i < 4; i++) {
    if (impl->unknown24[i] == id) {
      impl->unknown4544 = i;
      break;
    }
  }
}

bool DevPadNx::createDevice() { return true; }

void DevPadNx::releaseDevice() { unknown548->release(); }

} // namespace ml
