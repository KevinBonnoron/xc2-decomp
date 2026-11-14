#include "device/nx/dev_file_archive_nx.h"

#include <string.h>

#include "ml/file_handle_th.h"
#include "ml/thread.h"
#include "ml/work_cpu.h"
#include "mm_mtl/fixstr.h" // IWYU pragma: keep
#include "mm_mtl/internal/fixed_object_allocator.h"
#include "mm_mtl/tuple.h" // IWYU pragma: keep
#include "nn/fs.h"        // IWYU pragma: keep
#include "nn/result.h"

namespace ml {

void DevFileArchiveNx::Param::finalize() {
  CS cs(unknown1800);
  while (!unknown29b8.empty()) {
    unknown002 *file = unknown29b8.pop_back();
    nn::fs::CloseFile(file->unknown001);
    unknown1828.deallocate(file);
  }
}

DevFileArchiveNx::Param::unknown002 *DevFileArchiveNx::Param::findThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path) {
  CS cs(unknown1800);
  for (unknown002 *file : unknown29b8) {
    if (file->unknown00 == threadId && strcmp(file->unknown002.c_str(), path.c_str()) == 0) {
      return file;
    }
  }
  return nullptr;
}

nn::fs::FileHandle *DevFileArchiveNx::Param::addThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path) {
  CS cs(unknown1800);
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
  CS cs(unknown1800);
  for (unknown003::iterator it = unknown29b8.begin(); it != unknown29b8.end(); ++it) {
    if ((*it)->unknown00 == threadId && strcmp((*it)->unknown002.c_str(), path.c_str()) == 0) {
      unknown29b8.erase(it);
      break;
    }
  }
}

DevFileArchiveNx::DevFileArchiveNx(mtl::ALLOC_HANDLE handle) : unknown14(handle), unknown18(0), unknown20(new (handle) Param()) {
  unknown20->unknown17fc = 0;
  unknown20->unknown17f8 = false;
}

DevFileArchiveNx::~DevFileArchiveNx() { unknown20->finalize(); }

bool DevFileArchiveNx::initialize() {
  if (unknown18 == 0) {
    for (size_t i = 1; i < unknown20->unknown0000.size(); i++) {
      Thread *thread = Thread::create("rfLoadThread", false, thFileLoader, &unknown20->unknown0000[i], 0x10000, WorkCpu::getSubWorkCPUID(), -2);
      if (thread != nullptr) {
        unknown20->unknown0000[i].unknown1a0 = this;
        unknown20->unknown0000[i].unknown198 = thread;
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
      if (unknown20->unknown0000[i].unknown198 != nullptr) {
        unknown20->unknown0000[i].unknown198->setSignalEvent(true);
      }
    }
    unknown18 = 2;
  } else if (unknown18 == 2) {
    if (unknown20->unknown17fc == 0) {
      unknown18 = 3;
    }
  } else if (unknown18 == 3) {
    for (size_t i = 1; i < unknown20->unknown0000.size(); i++) {
      if (unknown20->unknown0000[i].unknown198 != nullptr) {
        unknown20->unknown0000[i].unknown198->release();
      }
    }
    unknown18 = 4;
  }
  return unknown18 == 4;
}

u32 DevFileArchiveNx::addressAlignment() { return 16; }

DevFileJobTh *DevFileArchiveNx::createLoader(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobTh(); }

DevFileJobTh *DevFileArchiveNx::createWriter(mtl::ALLOC_HANDLE handle) { return nullptr; }

DevFileJobTh *DevFileArchiveNx::createFileValid(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobValidArcNxTh(); }

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
  channel->unknown120 = param;
  channel->unknown10d = true;
  channel->unknown118 = handle;
  channel->unknown10e = false;
  channel->unknown110 = false;
  channel->unknown198->setSignalEvent(true);
  return true;
}

bool DevFileArchiveNx::rfClose(FileHandleTh *handle) {
  OpenReadParam *channel = &get()->unknown20->unknown0000[handle->unknown1d4];
  mm::threading::WriteLockGuard guard(channel->unknown1a8);
  if (channel->unknown10f) {
    handle->unknown94 |= 0x10000;
    handle->unknown60 = nullptr;
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
    if (it->unknown10d && it->unknown118 != nullptr) {
      mm::threading::WriteLockGuard guard(it->unknown1a8);
      if ((it->unknown118->unknown94 & 0x10000) == 0) {
        if (it->unknown118->m_currentPtr != 0 && it->unknown118->m_currentPtr == it->unknown118->unknown18) {
          it->unknown10d = false;
          it->unknown118->call(CBM_UNKNOWN_2);
          it->unknown118 = nullptr;
        }
      } else if (!it->unknown10f) {
        if (it->unknown110) {
          nn::fs::CloseFile(it->unknown00);
          it->unknown110 = false;
        }
        it->unknown10d = false;
        it->unknown118->call(CBM_UNKNOWN_4);
        it->unknown118 = nullptr;
      }
    }
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileArchiveNx>::~PtrSingleton();
template mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>> *
mm::mtl::FixedObjectAllocator<mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>>, 16>::allocate();
