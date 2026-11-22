#include "device/nx/dev_file_nx_th.h"

#include "device/nx/dev_file_util_nx.h"
#include "ml/critical_section.h"
#include "ml/dev_file_th.h"
#include "ml/file_handle_th.h"
#include "ml/thread.h"
#include "ml/work_cpu.h"
#include "ml/work_root.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/internal/heap_allocator.h"
#include "mm_thread/mm_thread_csection.h"
#include "mtl/mem_manager.h"
#include "nn/account.h"
#include "nn/fs.h"
#include "nn/os.h"
#include "nn/result.h"
#include "nn/time_span.h"

namespace ml {

namespace dfn_detail {

mm::mtl::HeapAllocator g_allocator;

} // namespace dfn_detail

bool DevFileNxTh::m_mountRom;
bool DevFileNxTh::m_mountSave;
bool DevFileNxTh::m_validuser;
nn::account::UserHandle DevFileNxTh::m_appuser;
mm::mtl::FixStr<256> DevFileNxTh::m_rootPath;

void DevFileNxTh::finalizeSDK() {
  if (m_mountSave) {
    nn::fs::Unmount("save");
  }
  if (m_mountRom) {
    nn::fs::Unmount("rom");
  }
  if (m_validuser) {
    nn::account::CloseUser(m_appuser);
  }
}

void DevFileNxTh::flushSave() {
  if (m_mountSave) {
    nn::fs::CommitSaveData("save");
  }
}

CriticalSection &DevFileNxTh::getLocker() {
  static CriticalSection sect;
  return sect;
}

void *DevFileNxTh::allocate(size_t size) {
  CS cs(getLocker());
  return dfn_detail::g_allocator.allocate(size, 16);
}

void DevFileNxTh::deallocate(void *pointer, size_t size) {
  CS cs(getLocker());
  dfn_detail::g_allocator.deallocate(pointer);
}

int DevFileNxTh::getFileSize(const char *path, mm::VAL64 *size, const char *archive) {
  mm::mtl::FixStr<256> fileName;
  DevFileTh::makeMediaFileName(fileName, archive, path);
  if (!DevFileBlackListNxTh::get()->check(path)) {
    return -1;
  }
  unknown002 file;
  file.isOpen = nn::fs::OpenFile(&file.handle, fileName.c_str(), 1).IsSuccess();
  if (!file.isOpen) {
    return -1;
  }
  s64 fileSize = DevFileUtilNx::getFileSize(file.handle);
  if (size != nullptr && fileSize >= 0) {
    size->unknown00 = 0;
  }
  return fileSize;
}

u32 DevFileNxTh::addressAlignment() { return 16; }

bool DevFileNxTh::rfIsUsedChannel(u32 channel) { return unknown20->unknown00[channel].unknown10c; }

void DevFileNxTh::setMediaRootPath(const char *path) { m_rootPath = path; }

DevFileJobTh *DevFileNxTh::createLoader(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobTh(); }

DevFileJobTh *DevFileNxTh::createWriter(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileWriterNx; }

DevFileJobTh *DevFileNxTh::createFileValid(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobValidNxTh(); }

bool DevFileNxTh::readBlock(FileHandleTh *handle, const char *path) {
  void *buffer = mtl::MemManager::allocate(WorkRoot::getMemTMP(), 0x20000, 4, false, "no name", 0);
  bool isRead = readBlockSlice(handle, path, buffer, 0x20000);
  if (buffer != nullptr) {
    mtl::MemManager::deallocate(buffer, 0, false);
  }
  return isRead;
}

// 1.0.0: 0x710072c194. The same body as DevFileArchiveNx::rfIsBusy (0x710072f290); the comment there gives the forms the loop and the guard need.
bool DevFileNxTh::rfIsBusy(FileHandleTh *handle) {
  DevFileNxTh *file = get();
  if (handle == nullptr) {
    for (u32 i = 0; i < file->unknown20->unknown00.size(); i++) {
      OpenReadParam *channel = &file->unknown20->unknown00[i];
      mm::threading::ReadLockGuard guard(channel->unknown1a8);
      if (!channel->unknown10d || !channel->unknown10c) {
        continue;
      }
      return true;
    }
  } else {
    OpenReadParam *channel = &file->unknown20->unknown00[handle->unknown1d4];
    mm::threading::ReadLockGuard guard(channel->unknown1a8);
    if (channel->unknown10c) {
      return channel->unknown10d;
    }
  }
  return false;
}

bool DevFileNxTh::rfClose(FileHandleTh *handle) {
  OpenReadParam *channel = &get()->unknown20->unknown00[handle->unknown1d4];
  mm::threading::WriteLockGuard guard(channel->unknown1a8);
  bool isClosed = false;
  if (channel->unknown10f) {
    handle->unknown94 |= 0x10000;
    handle->m_iWorkEvent = nullptr;
    channel->unknown110 = true;
  } else {
    if (channel->unknown10d) {
      channel->unknown10d = false;
    }
    nn::fs::CloseFile(channel->unknown00);
    isClosed = true;
    channel->unknown10c = false;
  }
  return isClosed;
}

CriticalSection &DevFileNxTh::getWriteLock() {
  DevFileNxTh *self = get();
  if (self == nullptr) {
    static CriticalSection sect;
    return sect;
  }
  return self->unknown20->m_criticalSection;
}

bool DevFileNxTh::rfOpen(FileHandleTh *handle, const char *path) {
  OpenReadParam &channel = get()->unknown20->unknown00[handle->unknown1d4];
  mm::threading::WriteLockGuard guard(channel.unknown1a8);
  DevFileTh::makeMediaFileName(channel.unknown08, path, handle->unknown98.c_str());
  bool isOpened = true;
  if (!channel.unknown10c) {
    if (nn::fs::OpenFile(&channel.unknown00, channel.unknown08.c_str(), 1).IsSuccess()) {
      channel.unknown10c = true;
      channel.unknown10d = false;
      channel.unknown10e = false;
      channel.unknown110 = false;
    } else {
      isOpened = false;
    }
  }
  return isOpened;
}

DevFileNxTh::DevFileNxTh(mtl::ALLOC_HANDLE handle) : m_ALLOC_HANDLE(handle), unknown18(0), unknown20(new (handle) unknown001()) {
  __atomic_store_n(&unknown20->unknown17fc, 0, __ATOMIC_SEQ_CST);
  __atomic_store_n(&unknown20->unknown17f8, false, __ATOMIC_SEQ_CST);
}

DevFileNxTh::~DevFileNxTh() {}

bool DevFileNxTh::initialize() {
  if (unknown18 == 0) {
    for (size_t i = 1; i < unknown20->unknown00.size(); i++) {
      unknown20->unknown00[i].m_devFileAccessor = this;
      Thread *thread = Thread::create("rfLoadThread", false, thFileLoader, &unknown20->unknown00[i], 0x10000, WorkCpu::getSubWorkCPUID(), -2);
      if (thread != nullptr) {
        unknown20->unknown00[i].m_thread = thread;
        thread->resume();
      }
    }
    unknown18 = 1;
  }
  return true;
}

u32 DevFileNxTh::thFileLoader(void *argument) {
  OpenReadParam *channel = static_cast<OpenReadParam *>(argument);
  DevFileNxTh *accessor = static_cast<DevFileNxTh *>(channel->m_devFileAccessor);
  __atomic_fetch_add(&accessor->unknown20->unknown17fc, 1, __ATOMIC_SEQ_CST);
  while (!DevFileTh::isInitialized()) {
    nn::os::SleepThread(nn::TimeSpan::FromNanoSeconds(100000000));
  }
  accessor->thUpdate(argument);
  __atomic_fetch_sub(&accessor->unknown20->unknown17fc, 1, __ATOMIC_SEQ_CST);
  return 0;
}

void DevFileNxTh::thUpdate(void *argument) {
  OpenReadParam *channel = static_cast<OpenReadParam *>(argument);
  DevFileNxTh *accessor = static_cast<DevFileNxTh *>(channel->m_devFileAccessor);
  while (!__atomic_load_n(&accessor->unknown20->unknown17f8, __ATOMIC_SEQ_CST)) {
    channel->m_thread->waitSignalEvent();
    if (__atomic_load_n(&accessor->unknown20->unknown17f8, __ATOMIC_SEQ_CST)) {
      break;
    }
    void *buffer;
    u32 offset;
    int size;
    bool reading = false;
    {
      mm::threading::ReadLockGuard guard(channel->unknown1a8);
      buffer = channel->m_devFileParamTh.unknown40;
      offset = channel->m_devFileParamTh.unknown4c;
      size = channel->m_devFileParamTh.unknown50;
      if (channel->unknown10d) {
        reading = (channel->m_fileHandleTh->unknown94 & 0x10000) == 0;
      }
    }
    if (reading) {
      FileReadResult result;
      channel->unknown10f = true;
      if (DevFileUtilNx::readFile(channel->m_fileHandleTh, channel->unknown00, size, offset, buffer, size, result)) {
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

bool DevFileNxTh::finalize() {
  if (unknown18 == 1) {
    __atomic_store_n(&unknown20->unknown17f8, true, __ATOMIC_SEQ_CST);
    for (size_t i = 1; i < unknown20->unknown00.size(); i++) {
      if (unknown20->unknown00[i].m_thread != nullptr) {
        unknown20->unknown00[i].m_thread->setSignalEvent(true);
      }
    }
    unknown18 = 2;
  } else if (unknown18 == 2) {
    if (__atomic_load_n(&unknown20->unknown17fc, __ATOMIC_SEQ_CST) == 0) {
      unknown18 = 3;
    }
  } else if (unknown18 == 3) {
    for (size_t i = 1; i < unknown20->unknown00.size(); i++) {
      if (unknown20->unknown00[i].m_thread != nullptr) {
        unknown20->unknown00[i].m_thread->release();
      }
    }
    unknown18 = 4;
  }
  return unknown18 == 4;
}

bool DevFileNxTh::rfRead(FileHandleTh *handle, const DevFileParamTh &param) {
  if (handle == nullptr) {
    return false;
  }
  OpenReadParam &channel = get()->unknown20->unknown00[handle->unknown1d4];
  mm::threading::WriteLockGuard guard(channel.unknown1a8);
  if (!channel.unknown10c) {
    return false;
  }
  handle->m_currentPtr = 0;
  handle->setReadAdr(param.unknown50, param.unknown40, param.unknown50);
  handle->unknown001(param.unknown4c, param.unknown50);
  handle->unknown94 &= 0xfff0ffff;
  channel.m_devFileParamTh = param;
  channel.unknown10d = true;
  channel.m_fileHandleTh = handle;
  channel.unknown10e = false;
  channel.unknown110 = false;
  channel.m_thread->setSignalEvent(true);
  return true;
}

void DevFileNxTh::tail() {
  for (OpenReadParam *channel = unknown20->unknown00.begin(); channel != unknown20->unknown00.end(); channel++) {
    if (channel->unknown10d && channel->m_fileHandleTh != nullptr) {
      mm::threading::WriteLockGuard guard(channel->unknown1a8);
      if ((channel->m_fileHandleTh->unknown94 & 0x10000) == 0) {
        if (channel->m_fileHandleTh->m_currentPtr != 0 && channel->m_fileHandleTh->m_currentPtr == channel->m_fileHandleTh->unknown18) {
          channel->unknown10d = false;
          channel->m_fileHandleTh->call(CBM_UNKNOWN_2);
          channel->m_fileHandleTh = nullptr;
        }
      } else if (!channel->unknown10f) {
        if (channel->unknown110) {
          nn::fs::CloseFile(channel->unknown00);
          channel->unknown110 = false;
        }
        channel->unknown10c = false;
        channel->unknown10d = false;
        channel->m_fileHandleTh->call(CBM_UNKNOWN_4);
        channel->m_fileHandleTh = nullptr;
      }
    }
  }
}

bool DevFileBlackListNxTh::check(const char *path) {
  const char *pattern = unknown08;
  if (pattern == nullptr) {
    return true;
  }
  while (*path == '/' || *path == '\\') {
    path++;
  }
  while (*pattern != '\0') {
    const char *src = path;
    const char *dst = pattern;
    // Inferred codes: 0 same character, 1 end of the pattern, 6 wildcard matched, 7 mismatch.
    int result;
    for (;;) {
      char c = *src++;
      char t = *dst++;
      if (t == '\0') {
        result = 1;
      } else if (c == '\0') {
        result = 7;
      } else if (t == '*') {
        t = *dst++;
        while (t != c) {
          c = *src++;
          if (c == '\\') {
            c = '/';
          } else if (c == '\0') {
            break;
          } else if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
          }
        }
        if (t != c) {
          result = 7;
        } else if (t != '\0') {
          result = 6;
        } else {
          result = 1;
        }
      } else {
        if (c == '\\') {
          c = '/';
        }
        if (c >= 'A' && c <= 'Z') {
          c += 'a' - 'A';
        }
        result = t == c ? 0 : 7;
      }
      switch (result) {
      case 0:
      case 6:
        continue;
      case 7:
        while (*pattern++ != '\0') {
        }
        result = 0;
        break;
      }
      break;
    }
    if (result != 0) {
      return false;
    }
  }
  return true;
}

DevFileBlackListNxTh::DevFileBlackListNxTh(mtl::ALLOC_HANDLE handle) : unknown08(nullptr) {}

DevFileBlackListNxTh::~DevFileBlackListNxTh() {
  if (unknown08 != nullptr) {
    mtl::MemManager::deallocate(unknown08, 0, false);
    unknown08 = nullptr;
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileNxTh>::~PtrSingleton();
template mm::mtl::PtrSingleton<ml::DevFileBlackListNxTh>::~PtrSingleton();
