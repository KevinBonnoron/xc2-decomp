#include "device/nx/dev_file_util_nx.h"

#include "mtl/mem_manager.h"

namespace ml {

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
