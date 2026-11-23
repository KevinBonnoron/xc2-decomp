#include "device/nx/dev_file_archive_nx.h"

#include <string.h>

#include "device/nx/dev_file_util_nx.h"
#include "ml/dev_file_th.h"
#include "ml/file_handle_th.h"
#include "ml/thread.h"
#include "ml/work_cpu.h"
#include "mm_mtl/fixstr.h" // IWYU pragma: keep
#include "mm_mtl/internal/fixed_object_allocator.h"
#include "mm_mtl/str_util.h"
#include "mm_mtl/tuple.h" // IWYU pragma: keep
#include "mm_thread/mm_thread_csection.h"
#include "mtl/mem_manager.h"
#include "nn/fs.h" // IWYU pragma: keep
#include "nn/os.h"
#include "nn/result.h"
#include "nn/time_span.h"

namespace ml {

void DevFileArchiveNx::Param::finalize() {
  CS cs(m_criticalSection);
  while (!unknown29b8.empty()) {
    unknown002 *file = unknown29b8.pop_back();
    nn::fs::CloseFile(file->unknown001);
    unknown1828.deallocate(file);
  }
}

DevFileArchiveNx::Param::unknown002 *DevFileArchiveNx::Param::findThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path) {
  CS cs(m_criticalSection);
  for (unknown002 *file : unknown29b8) {
    if (file->unknown00 == threadId && strcmp(file->unknown002.c_str(), path.c_str()) == 0) {
      return file;
    }
  }
  return nullptr;
}

nn::fs::FileHandle *DevFileArchiveNx::Param::addThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path) {
  CS cs(m_criticalSection);
  for (unknown002 *opened : unknown29b8) {
    if (opened->unknown00 == threadId && strcmp(opened->unknown002.c_str(), path.c_str()) == 0) {
      return &opened->unknown001;
    }
  }
  unknown002 *file = unknown1828.allocate();
  file->unknown00 = threadId;
  file->unknown002 = path;
  if (!nn::fs::OpenFile(&file->unknown001, path.c_str(), 1).IsSuccess()) {
    unknown1828.deallocate(file);
    return nullptr;
  }
  unknown29b8.push(file);
  return &file->unknown001;
}

void DevFileArchiveNx::Param::removeThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path) {
  CS cs(m_criticalSection);
  for (unknown003::iterator it = unknown29b8.begin(); it != unknown29b8.end(); ++it) {
    if ((*it)->unknown00 == threadId && strcmp((*it)->unknown002.c_str(), path.c_str()) == 0) {
      unknown29b8.erase(it);
      break;
    }
  }
}

DevFileArchiveNx::DevFileArchiveNx(mtl::ALLOC_HANDLE handle) : m_ALLOC_HANDLE(handle), unknown18(0), unknown20(new (handle) Param()) {
  unknown20->unknown17fc = 0;
  unknown20->unknown17f8 = false;
}

DevFileArchiveNx::~DevFileArchiveNx() { unknown20->finalize(); }

bool DevFileArchiveNx::initialize() {
  if (unknown18 == 0) {
    for (size_t i = 1; i < unknown20->unknown0000.size(); i++) {
      Thread *thread = Thread::create("rfLoadThread", false, thFileLoader, &unknown20->unknown0000[i], 0x10000, WorkCpu::getSubWorkCPUID(), -2);
      if (thread != nullptr) {
        unknown20->unknown0000[i].m_devFileAccessor = this;
        unknown20->unknown0000[i].m_thread = thread;
        thread->resume();
      }
    }
    unknown18 = 1;
  }
  return true;
}

bool DevFileArchiveNx::finalize() {
  if (unknown18 == 1) {
    unknown20->unknown17f8 = true;
    for (size_t i = 1; i < unknown20->unknown0000.size(); i++) {
      if (unknown20->unknown0000[i].m_thread != nullptr) {
        unknown20->unknown0000[i].m_thread->setSignalEvent(true);
      }
    }
    unknown18 = 2;
  } else if (unknown18 == 2) {
    if (unknown20->unknown17fc == 0) {
      unknown18 = 3;
    }
  } else if (unknown18 == 3) {
    for (size_t i = 1; i < unknown20->unknown0000.size(); i++) {
      if (unknown20->unknown0000[i].m_thread != nullptr) {
        unknown20->unknown0000[i].m_thread->release();
      }
    }
    unknown18 = 4;
  }
  return unknown18 == 4;
}

// thFileLoader and thUpdate repeat DevFileNxTh::thFileLoader and DevFileNxTh::thUpdate: the game has four separate functions
// (0x710072e1b8 / 0x710072a4bc and 0x710072f6e8 / 0x710072c5f4), and the two classes share no base holding the channels. The archive
// adds unknown190 to the read offset.
u32 DevFileArchiveNx::thFileLoader(void *argument) {
  OpenReadParam *channel = static_cast<OpenReadParam *>(argument);
  DevFileArchiveNx *accessor = static_cast<DevFileArchiveNx *>(channel->m_devFileAccessor);
  accessor->unknown20->unknown17fc++;
  while (!DevFileTh::isInitialized()) {
    nn::os::SleepThread(nn::TimeSpan::FromNanoSeconds(100000000));
  }
  accessor->thUpdate(argument);
  accessor->unknown20->unknown17fc--;
  return 0;
}

void DevFileArchiveNx::thUpdate(void *argument) {
  OpenReadParam *channel = static_cast<OpenReadParam *>(argument);
  DevFileArchiveNx *accessor = static_cast<DevFileArchiveNx *>(channel->m_devFileAccessor);
  while (!accessor->unknown20->unknown17f8) {
    channel->m_thread->waitSignalEvent();
    if (accessor->unknown20->unknown17f8) {
      break;
    }
    void *buffer;
    u32 offset;
    int size;
    u64 base;
    bool reading = false;
    {
      mm::threading::ReadLockGuard guard(channel->unknown1a8);
      buffer = channel->m_devFileParamTh.unknown40;
      offset = channel->m_devFileParamTh.unknown4c;
      size = channel->m_devFileParamTh.unknown50;
      base = channel->unknown190;
      if (channel->unknown10d) {
        reading = (channel->m_fileHandleTh->unknown94 & 0x10000) == 0;
      }
    }
    if (reading) {
      FileReadResult result;
      channel->unknown10f = true;
      if (DevFileUtilNx::readFile(channel->m_fileHandleTh, channel->unknown00, size, base + offset, buffer, size, result)) {
        mm::threading::WriteLockGuard guard(channel->unknown1a8);
        FileHandleTh *handle = channel->m_fileHandleTh;
        if (handle != nullptr) {
          int read = result.unknown00;
          if (result.unknown08) {
            handle->unknown18 = read;
            handle->m_currentPtr = read;
          } else {
            handle->m_currentPtr += read;
          }
        }
      }
      channel->unknown10f = false;
    }
  }
}

u32 DevFileArchiveNx::addressAlignment() { return 16; }

DevFileJobTh *DevFileArchiveNx::createLoader(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobTh(); }

DevFileJobTh *DevFileArchiveNx::createWriter(mtl::ALLOC_HANDLE handle) { return nullptr; }

DevFileJobTh *DevFileArchiveNx::createFileValid(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobValidArcNxTh(); }

// 1.0.0: 0x710072e640. Turns the backslashes into slashes, makes the path absolute and lower-cases it from its last separator (mm::mtl::unknown002).
void DevFileArchiveNx::normalizeFileName(mm::mtl::FixStr<256> &fileName) {
  for (int i = 0; i < fileName.length(); i++) {
    if (fileName[i] == '\\') {
      fileName[i] = '/';
    }
  }
  if (fileName[0] != '/') {
    fileName.insert(0, 1, '/');
  }
  mm::mtl::unknown002(fileName);
}

bool DevFileArchiveNx::rfRead(FileHandleTh *handle, const DevFileParamTh &param) {
  if (handle == nullptr) {
    return false;
  }
  OpenReadParam *channel = &get()->unknown20->unknown0000[handle->unknown1d4];
  mm::threading::WriteLockGuard guard(channel->unknown1a8);
  if (!channel->unknown10c) {
    return false;
  }
  handle->m_currentPtr = 0;
  handle->setReadAdr(param.unknown50, param.unknown40, param.unknown50);
  handle->unknown001(param.unknown4c, param.unknown50);
  handle->unknown94 &= 0xfff0ffff;
  channel->m_devFileParamTh = param;
  channel->unknown10d = true;
  channel->m_fileHandleTh = handle;
  channel->unknown10e = false;
  channel->unknown110 = false;
  channel->m_thread->setSignalEvent(true);
  return true;
}

// 1.0.0: 0x710072ea6c. The game builds `path + "/"` and never uses it (ruling 5), but keeps the named local: with a discarded temporary
// the two FixStr<256> objects swap their stack slots. The handle copy for the allocation is made before `num = 0` (`ldr w8, [x21]` before `str wzr, [x20]`), which only
// a local copy of the handle places (a direct argument gives `str wzr` first and the registers of `handle` and `num` swapped).
bool DevFileArchiveNx::getFilesBlock(char *&files, int &num, mtl::ALLOC_HANDLE handle, const char *path, const char *extension) {
  mm::mtl::FixStr<256> directory = mm::mtl::FixStr<256>(path) + "/";
  mtl::ALLOC_HANDLE memory = handle;
  num = 0;
  files = static_cast<char *>(mtl::MemManager::allocate(memory, 0x100000, 4, false, "no name", 0));
  files[0] = 0;
  return true;
}

// 1.0.0: 0x710072f290 (DevFileNxTh::rfIsBusy, 0x710072c194, has the same body). The loop body ends in `continue` or `return` only: with
// the single `if (channel->unknown10d && channel->unknown10c) { return true; }` the body can fall off its end, clang then gives the
// fall-through exit the destination 0, JumpThreading folds the cleanup dispatch into `(x | 4) & 7 != 4` and the function has 83
// instructions against the game's 92. The guard of the single-handle path lives in the scope of the `return`: the `return` expression
// is converted to bool before the destructor of the guard (the game's `cset w19, ne` before `bl ~ReadLockGuard`), where a copy read
// inside a scope and returned after it has its conversion sunk behind the destructor (88 instructions, `cset w0, ne` after the call).
bool DevFileArchiveNx::rfIsBusy(FileHandleTh *handle) {
  DevFileArchiveNx *archive = get();
  if (handle == nullptr) {
    for (u32 i = 0; i < archive->unknown20->unknown0000.size(); i++) {
      OpenReadParam *channel = &archive->unknown20->unknown0000[i];
      mm::threading::ReadLockGuard guard(channel->unknown1a8);
      if (!channel->unknown10d || !channel->unknown10c) {
        continue;
      }
      return true;
    }
  } else {
    OpenReadParam *channel = &archive->unknown20->unknown0000[handle->unknown1d4];
    mm::threading::ReadLockGuard guard(channel->unknown1a8);
    if (channel->unknown10c) {
      return channel->unknown10d;
    }
  }
  return false;
}

bool DevFileArchiveNx::rfClose(FileHandleTh *handle) {
  OpenReadParam *channel = &get()->unknown20->unknown0000[handle->unknown1d4];
  mm::threading::WriteLockGuard guard(channel->unknown1a8);
  if (channel->unknown10f) {
    handle->unknown94 |= 0x10000;
    handle->m_iWorkEvent = nullptr;
    channel->unknown110 = true;
  } else {
    if (channel->unknown10d) {
      channel->unknown10d = false;
    }
    nn::fs::CloseFile(channel->unknown00);
    channel->unknown10c = false;
  }
  return false;
}

bool DevFileArchiveNx::rfIsUsedChannel(u32 channel) { return unknown20->unknown0000[channel].unknown10c; }

void DevFileArchiveNx::tail() {
  for (OpenReadParam *it = unknown20->unknown0000.begin(); it != unknown20->unknown0000.end(); ++it) {
    if (it->unknown10d && it->m_fileHandleTh != nullptr) {
      mm::threading::WriteLockGuard guard(it->unknown1a8);
      if ((it->m_fileHandleTh->unknown94 & 0x10000) == 0) {
        if (it->m_fileHandleTh->m_currentPtr != 0 && it->m_fileHandleTh->m_currentPtr == it->m_fileHandleTh->unknown18) {
          it->unknown10d = false;
          it->m_fileHandleTh->call(CBM_UNKNOWN_2);
          it->m_fileHandleTh = nullptr;
        }
      } else if (!it->unknown10f) {
        if (it->unknown110) {
          nn::fs::CloseFile(it->unknown00);
          it->unknown110 = false;
        }
        it->unknown10d = false;
        it->m_fileHandleTh->call(CBM_UNKNOWN_4);
        it->m_fileHandleTh = nullptr;
      }
    }
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileArchiveNx>::~PtrSingleton();
template mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>> *
mm::mtl::FixedObjectAllocator<mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>>, 16>::allocate();
