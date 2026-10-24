#include "event/stm_pack_memory.h"

#include "event/memory_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/mem_manager.h"

namespace event {

StmPackMemory::StmPackMemory(mtl::ALLOC_HANDLE handle)
    : unknown08(0), unknown0c(handle), unknown10(nullptr), unknown18(0), unknown20(0), unknown28(0), unknown5838(0), unknown5840(0), unknown5848(0), unknown5850(0), unknown5858(0), unknown58e8(0),
      unknown58f0(0) {}

void StmPackMemory::loadStream(const char *name, const char *headerPath, const char *dataPath) {
  Stream *stream = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) Stream(name);
  stream->unknown88.create(unknown0c, headerPath);
  stream->unknown98.create(dataPath);
  unknown5860.push_back(stream);
}

void StmPackMemory::changeStream(const char *name) {
  for (size_t i = 0; i < unknown5860.size(); i++) {
    if (__builtin_strcmp(unknown5860[i]->unknown00.c_str(), name) == 0) {
      unknown58f0 = i;
      return;
    }
  }
}

void StmPackMemory::stopStream() { unknown08 |= FLAG_STOP; }

bool StmPackMemory::isBusy() {
  for (size_t i = 0; i < unknown5860.size(); i++) {
    if (unknown5860[i]->unknown98.isBusy()) {
      return true;
    }
  }
  return false;
}

StmPackMemory::~StmPackMemory() {
  unknown5838 = 0;
  unknown20 = 0;
  unknown28 = 0;
  unknown30.clear();
  mtl::MemManager::deallocate(unknown10, 0, false);
  for (size_t i = 0; i < unknown5860.size(); i++) {
    Stream *stream = unknown5860[i];
    stream->unknown98.destroy();
    stream->unknown88.destroy();
    delete stream;
  }
  unknown5860.clear();
}

void StmPackMemory::update() {
  if (!(unknown08 & FLAG_ALLOCATED)) {
    for (size_t i = 0; i < unknown5860.size(); i++) {
      if (unknown5860[i]->unknown88.isLoading()) {
        return;
      }
    }
    if (!getCurrentStream()->unknown98.open()) {
      return;
    }
    unknown18 = mtl::MemManager::maxAllocSize(unknown0c) / PAGE_SIZE - 2;
    unknown10 = mtl::MemManager::allocate(unknown0c, unknown18 * PAGE_SIZE, PAGE_SIZE, false, "no name", 0);
    unknown08 |= FLAG_ALLOCATED;
  }
  if (!(unknown08 & FLAG_ALLOCATED)) {
    return;
  }
  freeCut();
  if (unknown08 & FLAG_WAIT_CUT) {
    if (waitCut()) {
      unknown08 &= ~FLAG_WAIT_CUT;
    }
  } else if (!(unknown08 & FLAG_STOP)) {
    if (loadCut()) {
      unknown08 |= FLAG_WAIT_CUT;
    }
  }
}

void StmPackMemory::freeCut() {
  if (unknown30.empty()) {
    return;
  }
  StmPackRes &res = unknown30.front();
  if (!(res.unknown04 & StmPackRes::FLAG_FREE) || res.unknown00 > 0 || (res.unknown08 >= 0 && res.unknown08-- != 0)) {
    if (res.unknown50 >= unknown58f0) {
      return;
    }
  }
  size_t lastPage = res.unknown40;
  unknown30.erase(unknown30.begin());
  if (unknown30.empty()) {
    unknown20 = lastPage;
  } else {
    unknown20 = unknown30.front().unknown38;
  }
}

bool StmPackMemory::waitCut() {
  if (getLoadStream()->unknown98.isBusy()) {
    return false;
  }
  for (size_t i = 0; i < unknown30.size(); i++) {
    unknown30[i].loadCompleate();
  }
  if (unknown5838 < getLoadStream()->unknown88.getCount()) {
    unknown5840 = getLoadStream()->unknown88.getPrio(unknown5838);
  } else {
    unknown5840 = 9999999;
  }
  return true;
}

void StmPackMemory::render(const mm::Rect<int> &rect, f32 frame) {}

void *StmPackMemory::adr(const char *path, size_t *size) {
  for (StmPackRes *res = unknown30.begin(); res != unknown30.end(); res++) {
    if (res->isLoading() || res->unknown50 != unknown58f0) {
      continue;
    }
    for (size_t i = res->unknown28; i <= res->unknown30; i++) {
      if (__builtin_strcmp(path, getCurrentStream()->unknown88.getPath(i)) == 0) {
        res->unknown00++;
        if (size != nullptr) {
          *size = getCurrentStream()->unknown88.getDataSize(i);
        }
        return res->getFileAdr(getCurrentStream()->unknown88.getDataOfs(i));
      }
    }
  }
  return nullptr;
}

void StmPackMemory::free(void *adr, int frame) {
  for (StmPackRes *res = unknown30.begin(); res != unknown30.end(); res++) {
    if (res->isLoading()) {
      continue;
    }
    if (reinterpret_cast<size_t>(res->unknown10) <= reinterpret_cast<size_t>(adr) && reinterpret_cast<size_t>(adr) < res->unknown18 + reinterpret_cast<size_t>(res->unknown10)) {
      res->unknown04 |= StmPackRes::FLAG_FREE;
      res->unknown00--;
      return;
    }
  }
}

bool StmPackMemory::isFailure() const { return getLoadStream()->unknown88.isFailure() || getLoadStream()->unknown98.isFailure(); }

// The symbol at 0x71000a4ec8 reads +0x58e8, +0x58f0 and +0x5840;
// check confirms the code match, while the original member names remain unknown.
bool StmPackMemory::isLoadingPrio(f32 prio) const {
  if (unknown58e8 <= unknown58f0) {
    if (static_cast<f32>(unknown5840) <= prio) {
      return true;
    }
  }
  return false;
}

} // namespace event
