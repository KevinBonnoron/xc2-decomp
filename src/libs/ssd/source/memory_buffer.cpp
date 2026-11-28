#include <stddef.h>

#include "ssd/ssd_allocator.h"
#include "ssd/ssd_buffer.h"
#include "ssd/ssd_memory_buffer.h"
#include "types.h"

namespace ssd {

// Inferred role: copy size bytes in units of T, then the bytes left over; original name unknown. CopyMemory8/16/32/64
// share this body: they only match as this body optimized on its own, then inlined.
template <typename T> inline void unknown001(const void *source, void *destination, unsigned long size) {
  const T *src = static_cast<const T *>(source);
  T *dst = static_cast<T *>(destination);
  // Unrolled by hand in the original (the game copies four units per iteration while four units remain, then copies
  // one unit per iteration in a loop the compiler unrolled separately).
  while (size >= sizeof(T) * 4) {
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    size -= sizeof(T) * 4;
    src += 4;
    dst += 4;
  }
  while (size >= sizeof(T)) {
    *dst = *src;
    size -= sizeof(T);
    src++;
    dst++;
  }
  if (size > 0) {
    const u8 *srcByte = reinterpret_cast<const u8 *>(src);
    u8 *dstByte = reinterpret_cast<u8 *>(dst);
    while (size > 0) {
      *dstByte = *srcByte;
      size--;
      srcByte++;
      dstByte++;
    }
  }
}

// Inferred role: clear size bytes in units of T, then the bytes left over; original name unknown. ClearMemory8/16/32/64 share
// this body: it only matches as this body optimized on its own, then inlined. The parameter is a T *: with a void * parameter
// the exit pointer of the loop is expanded as one byte-addressed sum (ClearMemory32: `add x21, x0, x2` and `mov x0, x21`, 4
// lines off), while the game has the pointer of type T * (`add x21, x0, x20` before the memset, `add x0, x21, #0x10` after it).
template <typename T> inline void unknown002(T *dst, unsigned long size) {
  // Unrolled by hand in the original (the game clears four units per iteration, then the bytes left over).
  while (size >= sizeof(T) * 4) {
    dst[0] = 0;
    dst[1] = 0;
    dst[2] = 0;
    dst[3] = 0;
    size -= sizeof(T) * 4;
    dst += 4;
  }
  u8 *dstByte = reinterpret_cast<u8 *>(dst);
  while (size > 0) {
    *dstByte = 0;
    size--;
    dstByte++;
  }
}

// Inferred role: the byte repeated over a unit of T; original name unknown. A 64-bit unit repeats the 32-bit pattern: the game
// multiplies by 0x01010101 in 32 bits (`umull`) and joins the two words (`bfxil`), while the general form, a single 64-bit
// multiply by 0x0101010101010101, is 37 against 32 instructions, 45 lines off, in FillMemory64.
template <typename T> inline T unknown004(unsigned char value) { return static_cast<T>(value) * (static_cast<T>(~static_cast<T>(0)) / 0xff); }

template <> inline u64 unknown004<u64>(unsigned char value) {
  u32 pattern = value * 0x01010101u;
  return (static_cast<u64>(pattern) << 32) | pattern;
}

// Inferred role: fill size bytes in units of T with a repeated byte, then the bytes left over; original name unknown.
// FillMemory8/16/32/64 share this body: it only matches as this body optimized on its own, then inlined, with a T * parameter
// like unknown002.
template <typename T> inline void unknown003(T *dst, unsigned long size, unsigned char value) {
  T pattern = unknown004<T>(value);
  while (size >= sizeof(T) * 4) {
    dst[0] = pattern;
    dst[1] = pattern;
    dst[2] = pattern;
    dst[3] = pattern;
    size -= sizeof(T) * 4;
    dst += 4;
  }
  u8 *dstByte = reinterpret_cast<u8 *>(dst);
  while (size > 0) {
    *dstByte = static_cast<u8>(pattern);
    size--;
    dstByte++;
  }
}

void FillMemory8(void *buffer, unsigned long size, unsigned char value) { unknown003(static_cast<u8 *>(buffer), size, value); }

void FillMemory16(void *buffer, unsigned long size, unsigned char value) { unknown003(static_cast<u16 *>(buffer), size, value); }

void FillMemory32(void *buffer, unsigned long size, unsigned char value) { unknown003(static_cast<u32 *>(buffer), size, value); }

void FillMemory64(void *buffer, unsigned long size, unsigned char value) { unknown003(static_cast<u64 *>(buffer), size, value); }

void ClearMemory8(void *buffer, unsigned long size) { unknown002(static_cast<u8 *>(buffer), size); }

void ClearMemory16(void *buffer, unsigned long size) { unknown002(static_cast<u16 *>(buffer), size); }

void ClearMemory32(void *buffer, unsigned long size) { unknown002(static_cast<u32 *>(buffer), size); }

void ClearMemory64(void *buffer, unsigned long size) { unknown002(static_cast<u64 *>(buffer), size); }

void CopyMemory8(const void *source, void *destination, unsigned long size) { unknown001<u8>(source, destination, size); }

void CopyMemory16(const void *source, void *destination, unsigned long size) { unknown001<u16>(source, destination, size); }

void CopyMemory32(const void *source, void *destination, unsigned long size) { unknown001<u32>(source, destination, size); }

void CopyMemory64(const void *source, void *destination, unsigned long size) { unknown001<u64>(source, destination, size); }

void MemoryBuffer::Alloc(size_t size, size_t alignment, Allocator *allocator) {
  Allocator *buffer = SoundMemory::allocator_;
  if (allocator != nullptr) {
    buffer = allocator;
  }
  m_allocator = buffer;
  Allocator::Block *block = buffer->NewBufferImpl(size, 1, alignment);
  void *data;
  if (block != nullptr) {
    data = block->unknown08;
  } else {
    data = nullptr;
  }
  unknown08 = data;
  unknown10 = size;
}

void MemoryBuffer::Free() {
  if (unknown08 != nullptr) {
    Allocator *allocator = m_allocator;
    Allocator::Block *block = allocator->GetMemoryBlock(unknown08);
    allocator->DeleteBufferImpl(block);
    unknown10 = 0;
    m_allocator = nullptr;
    unknown08 = nullptr;
  }
}

} // namespace ssd
