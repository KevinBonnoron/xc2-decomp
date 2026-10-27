#include "device/nx/dev_keyboard_nx.h"

#include "ml/work_obj.h"
#include "ml/work_root.h"

namespace ml {

bool DevKeyboardNx::wkStandbyLogin() {
  WorkRootState::addFrameEnd(this);
  return WorkObj::wkStandbyLogin();
}

bool DevKeyboardNx::createDevice() { return true; }

void DevKeyboardNx::releaseDevice() {}

} // namespace ml
