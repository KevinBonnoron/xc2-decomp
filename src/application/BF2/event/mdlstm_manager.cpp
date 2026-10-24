#include "event/mdlstm_manager.h"

namespace event {

bool MdlstmManager::isReuseEnable() const { return (unknown14 & REUSE_FLAG_ENABLE) != 0; }

bool MdlstmManager::isLoadingPrio(f32 priority) const {
  for (MdlstmObj *const *it = unknown3c020.begin(); it != unknown3c020.end(); ++it) {
    if ((*it)->isLoading(priority))
      return true;
  }
  return false;
}

bool MdlstmManager::searchByHandle(gf::GF_OBJ_HANDLE *handle) const {
  for (MdlstmObj *const *it = unknown3c020.begin(); it != unknown3c020.end(); ++it) {
    if ((*it)->checkByHandle(handle))
      return true;
  }
  return false;
}

MdlstmManager::MdlstmManager() : unknown10(0), unknown14(0), unknown3c018(0) {}

void MdlstmManager::render() {}

void MdlstmManager::start() {
  if (unknown10 & FLAG_CREATE) {
    unknown10 |= FLAG_START;
  }
}

void MdlstmManager::setReuseEnable(bool isReuseEnable) {
  if (isReuseEnable) {
    unknown14 |= REUSE_FLAG_ENABLE;
  } else {
    unknown14 &= ~REUSE_FLAG_ENABLE;
  }
}

void MdlstmManager::setReuseFlag(int reuseFlag) { unknown3e030 = reuseFlag; }

} // namespace event
