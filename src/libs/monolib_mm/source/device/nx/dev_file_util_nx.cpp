#include "device/nx/dev_file_util_nx.h"

#include <string.h>

#include "ml/work_root.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nn/fs.h"
#include "nn/result.h"

namespace ml {

s64 DevFileUtilNx::getFileSize(nn::fs::FileHandle &handle) {
  s64 size = 0;
  nn::Result result = nn::fs::GetFileSize(&size, handle);
  return result.IsSuccess() ? size : -1;
}

namespace {

// Inferred role: file handle closed on scope exit; original type name unknown.
struct unknown002 {
  ~unknown002() {
    if (isOpen) {
      isOpen = false;
      nn::fs::CloseFile(handle);
    }
  }

  nn::fs::FileHandle handle;
  bool isOpen;
};

} // namespace

s64 DevFileUtilNx::getFileSize(const char *path) {
  unknown002 file;
  file.isOpen = nn::fs::OpenFile(&file.handle, path, 1).IsSuccess();
  s64 size;
  if (file.isOpen) {
    size = getFileSize(file.handle);
  } else {
    size = -1;
  }
  return size;
}

void *DevFileUtilNx::zlibAlloc(void *opaque, u32 items, u32 size) {
  u32 total = size * items;
  void *address = mtl::MemManager::allocate(WorkRoot::getMemTMP(), total, 4, false, "no name", 0);
  if (size != 0 && address != nullptr) {
    memset(address, 0, size);
  }
  return address;
}

bool DevFileUtilNx::getTimeStamp(nn::fs::FileHandle &handle, u32 &first, u32 &second) {
  first = 0;
  second = 0;
  return false;
}

bool DevFileUtilNx::getTimeStamp(const char *path, u32 &first, u32 &second) {
  first = 0;
  second = 0;
  return false;
}

void DevFileUtilNx::zlibFree(void *opaque, void *address) { mtl::MemManager::deallocate(address, 0, false); }

} // namespace ml
