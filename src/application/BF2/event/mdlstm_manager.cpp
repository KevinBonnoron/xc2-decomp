#include "event/mdlstm_manager.h"

namespace event {

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
