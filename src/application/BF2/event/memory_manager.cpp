#include "event/memory_manager.h"

#include "framework/framework.h"

namespace event {

MemoryManager::MemoryManager() : flags(0), mTxtbufState(0), mIsLargeEvent(0), mStaticSize(0), mSysSize(0), mResSize(0), mMotstmSize(0), mHighestSysHeap(0), mHighestResHeap(0), mTxtbufTotalSize(0) {}

void MemoryManager::clear() {
  clearHighestMemHeap();
  while (!mTxtbufs.empty()) {
    destroyTxtbuf(mTxtbufs.front());
  }
  mTxtbufState = 0;
}

void MemoryManager::destroyTxtbuf(const char *txtbuf) {
  if (txtbuf == nullptr || *txtbuf == '\0') {
    return;
  }
  for (char **it = mTxtbufs.begin(); it != mTxtbufs.end(); it++) {
    if (*it == txtbuf) {
      delete[] txtbuf;
      mTxtbufs.erase(it);
      return;
    }
  }
}

void MemoryManager::clearHighestMemHeap() {
  mHighestSysHeap = 0;
  mHighestResHeap = 0;
}

void MemoryManager::update() {}

mtl::ALLOC_HANDLE MemoryManager::getFwProcMem() { return fw::Framework::getMemHandle(); }

u32 MemoryManager::getSysMemSize() const { return mSysSize; }

u32 MemoryManager::getResMemSize() const { return mResSize; }

void MemoryManager::setDisp(bool isDisp) {
  if (isDisp) {
    flags |= FLAG_DISP;
  } else {
    flags &= ~FLAG_DISP;
  }
}

bool MemoryManager::isDisp() const { return (flags & FLAG_DISP) != 0; }

} // namespace event
