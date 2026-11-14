#include "device/nx/dev_touch_nx.h"

#include "ml/work_util.h"
#include "mtl/alloc_handle.h"
#include "nn/hid.h"

namespace ml {

DevTouchNx::DevTouchNx(const char *name, WorkObj *parent) : DevTouch(name, parent), unknown7d0(new (WorkUtil::getWorkMem(), nullptr, 0, 8) Impl) {}

void DevTouchNx::updateDevice() { unknown7d0->update(this); }

bool DevTouchNx::createDevice() {
  nn::hid::InitializeTouchScreen();
  return true;
}

void DevTouchNx::releaseDevice() {}

} // namespace ml
