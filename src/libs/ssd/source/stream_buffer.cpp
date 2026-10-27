#include "ssd/ssd_allocator.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_stream_buffer.h"
#include "types.h"

namespace ssd {

u32 StreamBuffer::GetDataSize() const { return m_dataSize; }

u64 StreamBuffer::GetFreeSize() const { return m_bufferSize - m_dataSize; }

u32 StreamBuffer::GetBufferSize() const { return m_bufferSize; }

int StreamBuffer::Alloc(u64 size, Allocator *allocator) {
  unknown08 = allocator;
  if (unknown10 != nullptr) {
    log_message(u"Assert : \"%s\", %s:%d", u"buffer_ == NULL", get_logfilename(u"D:/ssd/ssd51/ssd/sources/stream_buffer.cpp"), 0x1d);
    abort();
  }
  Allocator::Block *block = allocator->NewStreamImpl(size, 16);
  if (block == nullptr) {
    unknown10 = nullptr;
  } else {
    unknown10 = static_cast<u8 *>(block->unknown08);
    if (unknown10 != nullptr) {
      unknown08 = allocator;
      unknown24 = 0;
      unknown20 = 0;
      m_bufferSize = size;
      m_dataSize = 0;
      return 0;
    }
  }
  return -8;
}

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
