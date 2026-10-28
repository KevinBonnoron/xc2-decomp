#include "device/nx/dev_mouse_nx.h"

namespace ml {

DevMouseNx::~DevMouseNx() {}

bool DevMouseNx::createDevice() { return true; }

void DevMouseNx::releaseDevice() {}

} // namespace ml
