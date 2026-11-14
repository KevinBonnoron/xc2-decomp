#include "ml/file_handle_th.h"

#include "ml/dev_file_th.h"
#include "ml/work_event.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixed_array.h" // IWYU pragma: keep
#include "mm_mtl/internal/fixed_object_allocator.h"
#include "mtl/mem_manager.h"

namespace ml {

FileHandleTh::FileHandleTh() : unknown94(0), unknown1e0(0), unknown1ec(0), unknown1f0(0) { init(FTYPE_UNKNOWN_0); }

void FileHandleTh::init(FTYPE type) {
  unknown1f4 = type != FTYPE_UNKNOWN_0;
  unknown00 = type;
  unknown08 = nullptr;
  unknown10 = 0;
  unknown14 = 0;
  unknown18 = 0;
  unknown1c = 0;
  unknown20 = 0;
  m_currentPtr = 0;
  unknown2c = mtl::ALLOC_HANDLE();
  unknown30 = nullptr;
  unknown60 = nullptr;
  unknown68 = nullptr;
  unknown70 = nullptr;
  unknown78 = nullptr;
  unknown88 = 0;
  unknown90 = 0;
  unknown80 = 10;
  unknown94 = 0;
  m_time = 0;
  unknown1d0 = 0;
  unknown1d4 = 0;
  unknown1d8 = 0;
  unknown24 = 0;
  unknown1e8 = CBM_UNKNOWN_0;
}

void FileHandleTh::setup(const DevFileParamTh &param) {
  if (param.unknown40 != nullptr) {
    init(FTYPE_UNKNOWN_3);
    unknown08 = param.unknown40;
    unknown24 = param.unknown48;
  } else if (param._08.isValid()) {
    init(FTYPE_UNKNOWN_1);
    unknown2c = param._08;
    unknown38 = param._18;
  } else if (param._10 != nullptr) {
    init(FTYPE_UNKNOWN_2);
    unknown30 = param._10;
  } else if (param._6e) {
    init(FTYPE_UNKNOWN_7);
  } else {
    init(FTYPE_UNKNOWN_6);
  }
  unknown98 = param.unknown00;
  unknown60 = param.unknown60;
  unknown1d0 = param._54;
  unknown001(param.unknown4c, param.unknown50);
  unknown1d4 = 0;
  unknown1f4 = true;
  unknown1d8 = param._5c;
  if (param._6d) {
    unknown94 |= 2;
  } else {
    unknown94 &= ~2;
  }
  if (param._6e) {
    unknown94 |= 4;
  } else {
    unknown94 &= ~4;
  }
}

void FileHandleTh::initWriter(const char *path, void *data, int size, int offset, IWorkEvent *event) {
  init(FTYPE_UNKNOWN_4);
  unknown08 = data;
  unknown18 = size;
  unknown98 = path;
  unknown60 = event;
  unknown001(offset, 0);
}

FileHandleTh::FileHandleTh(const DevFileParamTh &param) : unknown94(0), unknown1ec(0), unknown1f0(0) { setup(param); }

FileHandleTh::~FileHandleTh() {
  releaseBuffer();
  unknown1f4 = false;
  unknown1e0 = 0;
}

void FileHandleTh::releaseBuffer() {
  if (unknown00 == FTYPE_UNKNOWN_1) {
    if (unknown08 != nullptr && unknown70 == nullptr) {
      if (mtl::MemManager::valid(unknown2c, true)) {
        if (unknown08 == nullptr) {
          return;
        }
        mtl::MemManager::deallocate(unknown08, 0, false);
      }
      unknown08 = nullptr;
    }
  } else if (unknown00 == FTYPE_UNKNOWN_2) {
    if (unknown08 != nullptr && unknown70 == nullptr) {
      if (unknown30 != nullptr) {
        static_cast<mm::mtl::IAllocator *>(unknown30)->deallocate(unknown08);
      }
      unknown08 = nullptr;
    }
  }
}

bool FileHandleTh::call(CBM cbm) {
  if (cbm == CBM_UNKNOWN_4 || cbm == CBM_UNKNOWN_6) {
    if (unknown70 != nullptr) {
      *unknown70 = nullptr;
    }
    if (unknown78 != nullptr) {
      *unknown78 = -1;
    }
  } else if (cbm == CBM_UNKNOWN_5 || cbm == CBM_UNKNOWN_2) {
    if (unknown70 != nullptr) {
      *unknown70 = unknown08;
    }
    if (unknown78 != nullptr) {
      *unknown78 = unknown18;
    }
  }
  if (unknown60 != nullptr) {
    EventFileTh event(cbm, this);
    return unknown60->OnFileEvent(&event);
  }
  return false;
}

bool FileHandleTh::addCurrentPtr(int offset) {
  m_currentPtr += offset;
  return true;
}

bool FileHandleTh::setCurrentPtr(int offset) {
  m_currentPtr = offset;
  return true;
}

void FileHandleTh::setReadAdr(int size, void *buffer, int alignedSize) {
  unknown18 = size;
  unknown08 = buffer;
  unknown10 = alignedSize;
}

bool FileHandleTh::setReadBuffer(int size, u32 alignment, u32 blockSize) {
  if (unknown1d0 != 0) {
    alignment = unknown1d0;
  }
  switch (unknown00) {
  case FTYPE_UNKNOWN_1: {
    releaseBuffer();
    void *buffer = mtl::MemManager::allocate(unknown2c, unknown002(unknown1d8 + size, blockSize), alignment, false, "no name", 0);
    for (u32 i = 0; i < unknown38.size(); i++) {
      if (buffer != nullptr) {
        break;
      }
      buffer = mtl::MemManager::allocate(unknown38[i], unknown003(size, blockSize), alignment, false, "no name", 0);
    }
    if (buffer == nullptr) {
      return false;
    }
    setReadAdr(size, buffer, unknown003(size, blockSize));
    break;
  }
  case FTYPE_UNKNOWN_2: {
    releaseBuffer();
    void *buffer = static_cast<mm::mtl::IAllocator *>(unknown30)->allocate(unknown002(unknown1d8 + size, blockSize), alignment);
    if (buffer == nullptr) {
      return false;
    }
    setReadAdr(size, buffer, unknown003(size, blockSize));
    break;
  }
  case FTYPE_UNKNOWN_5:
    setReadAdr(size, mtl::MemManager::allocate(unknown2c, unknown003(size, blockSize), alignment, false, "no name", 0), unknown003(size, blockSize));
    break;
  case FTYPE_UNKNOWN_3:
    unknown18 = size;
    unknown10 = blockSize;
    break;
  default:
    break;
  }
  return true;
}

void FileHandleTh::setTime(u64 time) { m_time = time; }

} // namespace ml

template void mm::mtl::FixedObjectAllocator<ml::FileHandleTh, 640>::deallocate(ml::FileHandleTh *p);
template void mm::mtl::FixedArray<ml::FileHandleTh, 13>::assign(const ml::FileHandleTh &value);
