#include "ssd/ssd_allocator.h"
#include "ssd/ssd_stream_buffer.h"
#include "types.h"

namespace ssd {

u32 StreamBuffer::GetDataSize() const { return m_dataSize; }

u64 StreamBuffer::GetFreeSize() const { return m_bufferSize - m_dataSize; }

u32 StreamBuffer::GetBufferSize() const { return m_bufferSize; }

void StreamBuffer::Clear() {
  unknown24 = 0;
  m_dataSize = 0;
  unknown20 = 0;
}

int StreamBuffer::Free() {
  if (unknown10 != nullptr) {
    Allocator *allocator = unknown08;
    Allocator::Block *block = allocator->GetMemoryBlock(unknown10);
    allocator->DeleteStreamImpl(block);
    unknown08 = nullptr;
    unknown10 = nullptr;
  }
  return 0;
}

} // namespace ssd
