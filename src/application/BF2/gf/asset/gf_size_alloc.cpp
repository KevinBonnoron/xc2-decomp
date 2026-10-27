#include "gf/asset/gf_size_alloc.h"

#include <string.h>

#include "mm_mtl/allocator.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace gf {

constexpr int SIZE_ALLOC_FILL = 0xfd;

void GfSizeAlloc::setup(mm::mtl::IAllocator *allocator, u32 blockSize, void *buffer, size_t size) {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  unknown28 = blockSize;
  unknown24 = size / blockSize;
  unknown08 = buffer;
  unknown10 = size;
  unknown20 = 0;
  memset(buffer, SIZE_ALLOC_FILL, size);
  unknown18 = static_cast<u32 *>(allocator->allocate(unknown24 * sizeof(u32), 4));
  memset(unknown18, 0, unknown24 * sizeof(u32));
  unknown20 = 0;
  unknown30.push_back(0);
  unknown18[0] = unknown24;
  unknown288 = allocator;
}

void GfSizeAlloc::destroy() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  unknown20 = 0;
  unknown24 = 0;
  unknown08 = nullptr;
  unknown10 = 0;
}

void GfSizeAlloc::resize(size_t size) {
  unknown24 = size / unknown28;
  unknown10 = size;
  memset(unknown08, SIZE_ALLOC_FILL, size);
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  unknown18 = static_cast<u32 *>(unknown288->allocate(unknown24 * sizeof(u32), 4));
  memset(unknown18, 0, unknown24 * sizeof(u32));
  unknown18[0] = unknown24;
}

void GfSizeAlloc::logFreeBlock() {}

} // namespace gf

template mm::mtl::FixedList<unsigned int, 512>::iterator mm::mtl::FixedList<unsigned int, 512>::erase(mm::mtl::FixedList<unsigned int, 512>::iterator);
template mm::mtl::FixedList<unsigned int, 512>::~FixedList();
