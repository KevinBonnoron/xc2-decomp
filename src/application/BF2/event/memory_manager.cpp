#include "event/memory_manager.h"

#include <string.h>

#include "event/manager.h"
#include "framework/framework.h"
#include "gf/game/event/gf_game_event.h"
#include "grlib/cglib_gpu_cache.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/mem_manager.h"

namespace event {

MemoryManager::MemoryManager() : unknown10(0), unknown14(0), unknown18(0), unknown2c(0), m_sysMemSize(0), m_resMemSize(0), unknown38(0), unknown1048(0), unknown1050(0), unknown1058(0) {}

void MemoryManager::checkMemory(mtl::ALLOC_HANDLE handle) {
  if (handle.isValid()) {
    mtl::MemoryInfo info;
    mtl::MemManager::getMemoryInfo(handle, &info);
  }
}

bool MemoryManager::isEnough() const {
  if (unknown24.isValid()) {
    mtl::MemoryInfo info;
    if (mtl::MemManager::getMemoryInfo(unknown24, &info) && static_cast<f32>(info.unknown10) / static_cast<f32>(info.unknown00) > 0.96f) {
      return false;
    }
  }
  return true;
}

bool MemoryManager::isActive() const {
  if (unknown28.isValid()) {
    mtl::MemoryInfo info;
    mtl::MemManager::getMemoryInfo(unknown28, &info);
    if (info.unknown28 != 0) {
      return true;
    }
  }
  if (unknown24.isValid()) {
    mtl::MemoryInfo info;
    mtl::MemManager::getMemoryInfo(unknown24, &info);
    if (info.unknown28 != 0) {
      return true;
    }
  }
  return false;
}

void MemoryManager::create() {
  unknown2c = 0x10000;
  m_sysMemSize = 0x4eb000;
  m_resMemSize = 0x1600000;
  unknown38 = 0x800000;
  unknown1c = heapMemory("EvStatic", gf::GfGameEvent::getEventMem(), unknown2c, mtl::ALLOCATOR_TYPE_RESOURCE);
  unknown20 = heapMemory("EvSys", gf::GfGameEvent::getEventMem(), m_sysMemSize, mtl::ALLOCATOR_TYPE_PROGRAM);
  unknown24 = heapMemory("EvRes", gf::GfGameEvent::getEventMem(), m_resMemSize, mtl::ALLOCATOR_TYPE_RESOURCE);
  unknown28 = heapMemory("EvMotstm", gf::GfGameEvent::getEventMem(), unknown38, mtl::ALLOCATOR_TYPE_RESOURCE);
  unknown18 = 0;
  grlib::CGLibGPUCache::setMemPoolMemHandle(unknown24);
}

void MemoryManager::login() {
  bool isLarge = __builtin_strcmp(mm::mtl::PtrSingleton<Manager>::get()->unknown230.c_str(), "bf07380100") == 0;
  if (unknown18 != isLarge) {
    if (unknown24.isValid()) {
      grlib::CGLibGPUCache::releaseMemPoolMemHandle(unknown24);
    }
    checkMemory(unknown28);
    checkMemory(unknown24);
    if (unknown28.isValid()) {
      mtl::MemManager::erase(unknown28);
      unknown28 = mtl::ALLOC_HANDLE();
    }
    if (unknown24.isValid()) {
      mtl::MemManager::erase(unknown24);
      unknown24 = mtl::ALLOC_HANDLE();
    }
    if (isLarge) {
      m_resMemSize = 0xf00000;
      unknown38 = 0xf00000;
    } else {
      m_resMemSize = 0x1600000;
      unknown38 = 0x800000;
    }
    unknown24 = heapMemory("EvRes", gf::GfGameEvent::getEventMem(), m_resMemSize, mtl::ALLOCATOR_TYPE_RESOURCE);
    unknown28 = heapMemory("EvMotstm", gf::GfGameEvent::getEventMem(), unknown38, mtl::ALLOCATOR_TYPE_RESOURCE);
    unknown18 = isLarge;
    grlib::CGLibGPUCache::setMemPoolMemHandle(unknown24);
  }
  clear();
}

char *MemoryManager::createTxtbuf(const char *text) {
  if (text == nullptr) {
    return nullptr;
  }
  if (*text == '\0') {
    return "";
  }
  size_t length = strlen(text);
  char *buffer = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) char[length + 16];
  strcpy(buffer, text);
  unknown40.push_back(buffer);
  return buffer;
}

void MemoryManager::destroy() {
  if (unknown24.isValid()) {
    grlib::CGLibGPUCache::releaseMemPoolMemHandle(unknown24);
  }
  checkMemory(unknown28);
  checkMemory(unknown24);
  checkMemory(unknown20);
  checkMemory(unknown1c);
  if (unknown28.isValid()) {
    mtl::MemManager::erase(unknown28);
    unknown28 = mtl::ALLOC_HANDLE();
  }
  if (unknown24.isValid()) {
    mtl::MemManager::erase(unknown24);
    unknown24 = mtl::ALLOC_HANDLE();
  }
  if (unknown20.isValid()) {
    mtl::MemManager::erase(unknown20);
    unknown20 = mtl::ALLOC_HANDLE();
  }
  if (unknown1c.isValid()) {
    mtl::MemManager::erase(unknown1c);
    unknown1c = mtl::ALLOC_HANDLE();
  }
}

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

void MemoryManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT_BEGIN:
    login();
    break;
  case MSG_TYPE_UPDATE_SEQUENCE:
    clear();
    break;
  case MSG_TYPE_INIT:
    clearHighestMemHeap();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  default:
    break;
  }
}

mtl::ALLOC_HANDLE MemoryManager::getFwProcMem() { return fw::Framework::getMemHandle(); }

mtl::ALLOC_HANDLE MemoryManager::heapMemory(const char *name, mtl::ALLOC_HANDLE parent, u32 size, mtl::AllocatorType type) {
  return mtl::MemManager::create(parent, size, name, true, type, 0x1000, "no name", 0);
}

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
