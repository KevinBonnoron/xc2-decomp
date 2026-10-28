#include "device/nx/dev_keyboard_nx.h"

#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_obj.h"
#include "ml/work_root.h"
#include "ml/work_system.h"

namespace ml {

DevKeyboardNx::DevKeyboardNx(const char *name, WorkObj *parent) : DevKeyboard(name, parent) {
  for (int i = 0; i < 6; i++) {
    unknowna70[i] = 0;
  }
}

DevKeyboardNx::~DevKeyboardNx() {}

bool DevKeyboardNx::wkStandbyLogin() {
  WorkRootState::addFrameEnd(this);
  return WorkObj::wkStandbyLogin();
}

bool DevKeyboardNx::wkStandbyLogout() {
  if (unknown60.size() != 0 || WorkSystem::get() != nullptr || LibMain::get() != nullptr) {
    return false;
  }
  WorkRootState::removeFrameEnd(this);
  return WorkObj::wkStandbyLogout();
}

bool DevKeyboardNx::createDevice() { return true; }

void DevKeyboardNx::releaseDevice() {}

} // namespace ml
