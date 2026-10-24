#include "event/memory_manager.h"

#include "framework/framework.h"

namespace event {

MemoryManager::MemoryManager() : unknown10(0), unknown14(0), unknown18(0), unknown2c(0), m_sysMemSize(0), m_resMemSize(0), unknown38(0), unknown1048(0), unknown1050(0), unknown1058(0) {}

void MemoryManager::clear() {
  clearHighestMemHeap();
  while (!unknown40.empty()) {
    destroyTxtbuf(unknown40.front());
  }
  unknown14 = 0;
}

void MemoryManager::destroyTxtbuf(const char *txtbuf) {
  if (txtbuf == nullptr || *txtbuf == '\0') {
    return;
  }
  for (char **it = unknown40.begin(); it != unknown40.end(); it++) {
    if (*it == txtbuf) {
      delete[] txtbuf;
      unknown40.erase(it);
      return;
    }
  }
}

void MemoryManager::clearHighestMemHeap() {
  unknown1048 = 0;
  unknown1050 = 0;
}

void MemoryManager::update() {}

mtl::ALLOC_HANDLE MemoryManager::getFwProcMem() { return fw::Framework::getMemHandle(); }

u32 MemoryManager::getSysMemSize() const { return m_sysMemSize; }

u32 MemoryManager::getResMemSize() const { return m_resMemSize; }

void MemoryManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown10 |= FLAG_DISP;
  } else {
    unknown10 &= ~FLAG_DISP;
  }
}

bool MemoryManager::isDisp() const { return (unknown10 & FLAG_DISP) != 0; }

} // namespace event
