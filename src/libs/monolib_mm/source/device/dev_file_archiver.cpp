#include <stddef.h>
#include <string.h>

#include "device/dev_file_archiver.h"
#include "device/dev_file_dic_allocator.h"
#include "mm_mtl/singleton.h" // IWYU pragma: keep
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

bool DevFileArchiver::getFileInfo(MEDIA media, const char *path, FileInfoResult &result) const {
  const mm::mtl::FixedVector<unknown002 *, 16> &archives = unknown10[media].unknown08;
  for (unknown002 *const *it = archives.begin(); it != archives.end(); ++it) {
    const unknown002 *archive = *it;
    int index = archive->unknown190.unknown001(path);
    if (index >= 0) {
      result.unknown00 = media;
      result.unknown88 = archive->unknown1e8[index];
      result.unknown04 = archive->unknown84;
      return true;
    }
  }
  return false;
}

bool DevFileArchiver::removeArchive(MEDIA media, const char *name) {
  mm::mtl::FixedVector<unknown002 *, 16> &archives = unknown10[media].unknown08;
  for (unknown002 **it = archives.begin(); it != archives.end(); ++it) {
    unknown002 *archive = *it;
    if (strcmp(archive->unknown00.c_str(), name) == 0) {
      delete archive;
      archives.erase(it);
      return true;
    }
  }
  return false;
}

DevFileDicAllocator::DevFileDicAllocator(mtl::ALLOC_HANDLE mem) : m_mem(mem) {}

void DevFileDicAllocator::setMemHandle(mtl::ALLOC_HANDLE mem) { m_mem = mem; }

void *DevFileDicAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(m_mem, size, alignment, false, "no name", 0); }

void DevFileDicAllocator::deallocate(void *pointer) { mtl::MemManager::deallocate(pointer, 0, false); }

void *DevFileDicAllocator::reallocate(void *pointer, size_t size) {
  if (pointer != nullptr) {
    return mtl::MemManager::reallocate(pointer, size, false);
  }
  return mtl::MemManager::allocate(m_mem, size, 4, false, "no name", 0);
}

DevFileArchiver::DevFileArchiver(mtl::ALLOC_HANDLE mem) : unknown0c(mem), unknown490(mem) { initialize(); }

void DevFileArchiver::initialize() {
  for (int i = 0; i < 8; i++) {
    unknown10[i].unknown00 = static_cast<MEDIA>(i);
    unknown10[i].unknown04 = true;
  }
}

DevFileArchiver::~DevFileArchiver() { finalize(); }

void DevFileArchiver::finalize() {
  for (int i = 0; i < 8; i++) {
    mm::mtl::FixedVector<unknown002 *, 16> &archives = unknown10[i].unknown08;
    for (unknown002 **it = archives.begin(); it != archives.end(); ++it) {
      delete *it;
    }
    archives.clear();
  }
}

} // namespace ml

template class ml::DevFileDictionary<int, ml::DevFileDicAllocator, -1, -2, true>;

template void ml::DevFileDictionary<int, ml::DevFileDicAllocator, -1, -2, true>::reallocArray(block *&array, int size, int from);

template mm::mtl::PtrSingleton<ml::DevFileArchiver>::~PtrSingleton();
