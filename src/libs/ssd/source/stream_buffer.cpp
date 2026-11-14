#include "ssd/ssd_allocator.h"
#include "ssd/ssd_buffer.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_stream_buffer.h"
#include "types.h"

namespace ssd {
enum Result : long;

u32 StreamBuffer::GetDataSize() const { return m_dataSize; }

u64 StreamBuffer::GetFreeSize() const { return m_bufferSize - m_dataSize; }

u32 StreamBuffer::GetBufferSize() const { return m_bufferSize; }

int StreamBuffer::Alloc(u64 size, Allocator *allocator) {
  unknown08 = allocator;
  SSD_ASSERT(unknown10 == nullptr, u"Assert : \"%s\", %s:%d", u"buffer_ == NULL", u"D:/ssd/ssd51/ssd/sources/stream_buffer.cpp", 0x1d);
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

Result StreamBuffer::OutData8(void *buffer, u64 size, u64 *outSize, bool *isMark) {
  u32 length = m_dataSize;
  if (static_cast<u32>(size) <= length) {
    length = size;
  }
  if (outSize != nullptr) {
    *outSize = length;
  }
  m_dataSize -= length;
  u8 *source = unknown10 + unknown24;
  u32 space = m_bufferSize - unknown24;
  if (length <= space) {
    CopyMemory8(source, buffer, length);
    unknown24 += length;
    unknown24 = unknown24 >= m_bufferSize ? 0 : unknown24;
  } else {
    CopyMemory8(source, buffer, space);
    CopyMemory8(unknown10, static_cast<u8 *>(buffer) + space, length - space);
    unknown24 = length - space;
  }
  return static_cast<Result>(0);
}

Result StreamBuffer::OutData16(void *buffer, u64 size, u64 *outSize, bool *isMark) {
  if (m_dataSize == 0) {
    *outSize = 0;
    return static_cast<Result>(0);
  }
  u32 length = m_dataSize;
  if (static_cast<u32>(size) <= length) {
    length = size;
  }
  if (outSize != nullptr) {
    *outSize = length;
  }
  m_dataSize -= length;
  u8 *source = unknown10 + unknown24;
  u32 space = m_bufferSize - unknown24;
  if (length <= space) {
    CopyMemory16(source, buffer, length);
    unknown24 += length;
    if (unknown24 >= m_bufferSize) {
      unknown24 = 0;
    }
  } else {
    CopyMemory16(source, buffer, space);
    CopyMemory16(unknown10, static_cast<u8 *>(buffer) + space, length - space);
    unknown24 = length - space;
  }
  return static_cast<Result>(0);
}

Result StreamBuffer::OutData32(void *buffer, u64 size, u64 *outSize, bool *isMark) {
  if (m_dataSize == 0) {
    *outSize = 0;
    return static_cast<Result>(0);
  }
  u32 length = m_dataSize;
  if (static_cast<u32>(size) <= length) {
    length = size;
  }
  if (outSize != nullptr) {
    *outSize = length;
  }
  m_dataSize -= length;
  u8 *source = unknown10 + unknown24;
  u32 space = m_bufferSize - unknown24;
  if (length <= space) {
    CopyMemory32(source, buffer, length);
    unknown24 += length;
    if (unknown24 >= m_bufferSize) {
      unknown24 = 0;
    }
  } else {
    CopyMemory32(source, buffer, space);
    CopyMemory32(unknown10, static_cast<u8 *>(buffer) + space, length - space);
    unknown24 = length - space;
  }
  return static_cast<Result>(0);
}

Result StreamBuffer::OutData64(void *buffer, u64 size, u64 *outSize, bool *isMark) {
  if (m_dataSize == 0) {
    *outSize = 0;
    return static_cast<Result>(0);
  }
  u32 length = m_dataSize;
  if (static_cast<u32>(size) <= length) {
    length = size;
  }
  *isMark = false;
  if (unknown2c) {
    if (unknown28 == 0) {
      *isMark = true;
    } else {
      if (length > unknown28) {
        length = unknown28;
      }
      unknown28 -= length;
    }
  }
  if (outSize != nullptr) {
    *outSize = length;
  }
  m_dataSize -= length;
  u8 *source = unknown10 + unknown24;
  u32 space = m_bufferSize - unknown24;
  if (length <= space) {
    CopyMemory64(source, buffer, length);
    unknown24 += length;
    if (unknown24 >= m_bufferSize) {
      unknown24 = 0;
    }
  } else {
    CopyMemory64(source, buffer, space);
    CopyMemory64(unknown10, static_cast<u8 *>(buffer) + space, length - space);
    unknown24 = length - space;
  }
  return static_cast<Result>(0);
}

Result StreamBuffer::InData8(const void *buffer, u64 size, bool isMark) {
  if (static_cast<u32>(size) > GetFreeSize()) {
    return static_cast<Result>(-9);
  }
  if (isMark) {
    unknown28 = unknown20;
  }
  u8 *destination = unknown10 + unknown20;
  m_dataSize += static_cast<u32>(size);
  u32 space = m_bufferSize - unknown20;
  if (static_cast<u32>(size) <= space) {
    CopyMemory8(buffer, destination, static_cast<u32>(size));
    unknown20 += static_cast<u32>(size);
    if (unknown20 >= m_bufferSize) {
      unknown20 = 0;
    }
    return static_cast<Result>(0);
  }
  u32 remaining = static_cast<u32>(size) - space;
  CopyMemory8(buffer, destination, space);
  CopyMemory8(static_cast<const u8 *>(buffer) + space, unknown10, remaining);
  unknown20 = remaining;
  return static_cast<Result>(0);
}

Result StreamBuffer::InData16(const void *buffer, u64 size, bool isMark) {
  if (static_cast<u32>(size) > GetFreeSize()) {
    return static_cast<Result>(-9);
  }
  if (isMark) {
    unknown28 = unknown20;
  }
  u8 *destination = unknown10 + unknown20;
  m_dataSize += static_cast<u32>(size);
  u32 space = m_bufferSize - unknown20;
  if (static_cast<u32>(size) <= space) {
    CopyMemory16(buffer, destination, static_cast<u32>(size));
    unknown20 += static_cast<u32>(size);
    if (unknown20 >= m_bufferSize) {
      unknown20 = 0;
    }
    return static_cast<Result>(0);
  }
  u32 remaining = static_cast<u32>(size) - space;
  CopyMemory16(buffer, destination, space);
  CopyMemory16(static_cast<const u8 *>(buffer) + space, unknown10, remaining);
  unknown20 = remaining;
  return static_cast<Result>(0);
}

Result StreamBuffer::InData32(const void *buffer, u64 size, bool isMark) {
  if (static_cast<u32>(size) > GetFreeSize()) {
    return static_cast<Result>(-9);
  }
  if (isMark) {
    unknown28 = unknown20;
  }
  u8 *destination = unknown10 + unknown20;
  m_dataSize += static_cast<u32>(size);
  u32 space = m_bufferSize - unknown20;
  if (static_cast<u32>(size) <= space) {
    CopyMemory32(buffer, destination, static_cast<u32>(size));
    unknown20 += static_cast<u32>(size);
    if (unknown20 >= m_bufferSize) {
      unknown20 = 0;
    }
    return static_cast<Result>(0);
  }
  u32 remaining = static_cast<u32>(size) - space;
  CopyMemory32(buffer, destination, space);
  CopyMemory32(static_cast<const u8 *>(buffer) + space, unknown10, remaining);
  unknown20 = remaining;
  return static_cast<Result>(0);
}

Result StreamBuffer::InData64(const void *buffer, u64 size, bool isMark) {
  if (static_cast<u32>(size) > GetFreeSize()) {
    return static_cast<Result>(-9);
  }
  if (isMark) {
    unknown28 = unknown20;
  }
  u8 *destination = unknown10 + unknown20;
  m_dataSize += static_cast<u32>(size);
  u32 space = m_bufferSize - unknown20;
  if (static_cast<u32>(size) <= space) {
    CopyMemory64(buffer, destination, static_cast<u32>(size));
    unknown20 += static_cast<u32>(size);
    if (unknown20 >= m_bufferSize) {
      unknown20 = 0;
    }
    return static_cast<Result>(0);
  }
  u32 remaining = static_cast<u32>(size) - space;
  CopyMemory64(buffer, destination, space);
  CopyMemory64(static_cast<const u8 *>(buffer) + space, unknown10, remaining);
  unknown20 = remaining;
  return static_cast<Result>(0);
}

} // namespace ssd
