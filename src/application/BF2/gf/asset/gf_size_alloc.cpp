#include "gf/asset/gf_size_alloc.h"

#include <string.h>

#include "mm_mtl/allocator.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace gf {

constexpr int SIZE_UNKNOWN_253 = 0xfd; // Inferred role: size alloc fill; original name unknown.

void GfSizeAlloc::setup(mm::mtl::IAllocator *allocator, u32 blockSize, void *buffer, size_t size) {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  m_blockSize = blockSize;
  unknown24 = size / blockSize;
  m_buffer = buffer;
  m_bufferSize = size;
  m_allocs = 0;
  memset(buffer, SIZE_UNKNOWN_253, size);
  unknown18 = static_cast<u32 *>(allocator->allocate(unknown24 * sizeof(u32), 4));
  memset(unknown18, 0, unknown24 * sizeof(u32));
  m_allocs = 0;
  unknown30.push_back(0);
  unknown18[0] = unknown24;
  unknown288 = allocator;
}

void GfSizeAlloc::destroy() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  m_allocs = 0;
  unknown24 = 0;
  m_buffer = nullptr;
  m_bufferSize = 0;
}

void GfSizeAlloc::resize(size_t size) {
  unknown24 = size / m_blockSize;
  m_bufferSize = size;
  memset(m_buffer, SIZE_UNKNOWN_253, size);
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  unknown18 = static_cast<u32 *>(unknown288->allocate(unknown24 * sizeof(u32), 4));
  memset(unknown18, 0, unknown24 * sizeof(u32));
  unknown18[0] = unknown24;
}

void *GfSizeAlloc::alloc(size_t size, bool isTail) {
  if (size != 0) {
    u32 blocks = size / m_blockSize;
    if (size % m_blockSize != 0) {
      blocks++;
    }
    if (unknown24 >= blocks) {
      if (isTail) {
        mm::mtl::FixedList<u32, BLOCK_UNKNOWN_64>::iterator it = unknown30.end();
        while (unknown30.begin() != unknown30.end()) {
          --it;
          u32 start = *it;
          u32 length = unknown18[start];
          if (blocks <= length) {
            u32 allocStart = start + length - blocks;
            void *pointer = static_cast<u8 *>(m_buffer) + m_blockSize * allocStart;
            if (length == blocks) {
              unknown30.erase(it);
            } else {
              unknown18[start] = length - blocks;
            }
            unknown18[allocStart] = blocks;
            m_allocs++;
            return pointer;
          }
          if (unknown30.begin() == it) {
            return nullptr;
          }
        }
      } else {
        for (mm::mtl::FixedList<u32, BLOCK_UNKNOWN_64>::iterator it = unknown30.begin(); it != unknown30.end(); ++it) {
          u32 start = *it;
          u32 length = unknown18[start];
          if (blocks <= length) {
            void *pointer = static_cast<u8 *>(m_buffer) + m_blockSize * start;
            if (length == blocks) {
              unknown30.erase(it);
            } else {
              u32 remainStart = *it + blocks;
              unknown18[remainStart] = length - blocks;
              *it = remainStart;
            }
            unknown18[start] = blocks;
            m_allocs++;
            return pointer;
          }
        }
      }
    }
  }
  return nullptr;
}

void GfSizeAlloc::logFreeBlock() {}

} // namespace gf

template mm::mtl::FixedList<unsigned int, 512>::iterator mm::mtl::FixedList<unsigned int, 512>::erase(mm::mtl::FixedList<unsigned int, 512>::iterator);
template mm::mtl::FixedList<unsigned int, 512>::~FixedList();
