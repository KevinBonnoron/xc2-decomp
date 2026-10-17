#include "device/nx/th_dev_file_nx.h"

#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {
namespace device_detail {

mtl::ALLOC_HANDLE hMemFile;

void *allocateFile(size_t size) { return mtl::MemManager::allocate(hMemFile, size, 4, false, "no name", 0); }

void deallocateFile(void *pointer, size_t size) { mtl::MemManager::deallocate(pointer, 0, false); }

void *allocateDebug(size_t size) { return mtl::MemManager::allocate(hMemFile, size, 4, false, "no name", 0); }

void deallocateDebug(void *pointer, size_t size) { mtl::MemManager::deallocate(pointer, 0, false); }

} // namespace device_detail
} // namespace ml
