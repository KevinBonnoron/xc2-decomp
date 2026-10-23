#include "event/mdlstm_manager.h"

namespace event {

bool MdlstmManager::isReuseEnable() const { return (mReuseFlags & REUSE_FLAG_ENABLE) != 0; }

bool MdlstmManager::isLoadingPrio(f32 priority) const {
  for (MdlstmObj *const *it = mActiveObjs.begin(); it != mActiveObjs.end(); ++it) {
    if ((*it)->isLoading(priority))
      return true;
  }
  return false;
}

bool MdlstmManager::searchByHandle(gf::GF_OBJ_HANDLE *handle) const {
  for (MdlstmObj *const *it = mActiveObjs.begin(); it != mActiveObjs.end(); ++it) {
    if ((*it)->checkByHandle(handle))
      return true;
  }
  return false;
}

MdlstmManager::MdlstmManager() : flags(0), mReuseFlags(0), mObjCount(0) {}

void MdlstmManager::render() {}

void MdlstmManager::start() {
  if (flags & FLAG_CREATE) {
    flags |= FLAG_START;
  }
}

void MdlstmManager::setReuseEnable(bool isReuseEnable) {
  if (isReuseEnable) {
    mReuseFlags |= REUSE_FLAG_ENABLE;
  } else {
    mReuseFlags &= ~REUSE_FLAG_ENABLE;
  }
}

void MdlstmManager::setReuseFlag(int reuseFlag) { mReuseFlag = reuseFlag; }

} // namespace event
