#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {
enum Result : long;

class Allocator;

class StreamBufferBase {
public:
  virtual u32 GetBufferSize() const = 0;
  virtual u32 GetDataSize() const = 0;
  virtual u64 GetFreeSize() const = 0;
};

class StreamBuffer : public StreamBufferBase {
public:
  ~StreamBuffer() { Free(); }
  u32 GetBufferSize() const override;
  u32 GetDataSize() const override;
  u64 GetFreeSize() const override;
  int Alloc(u64 size, Allocator *allocator);
  void Clear();
  int Free();
  Result OutData8(void *buffer, u64 size, u64 *outSize, bool *isMark);
  Result OutData16(void *buffer, u64 size, u64 *outSize, bool *isMark);
  Result OutData32(void *buffer, u64 size, u64 *outSize, bool *isMark);
  Result OutData64(void *buffer, u64 size, u64 *outSize, bool *isMark);
  Result InData8(const void *buffer, u64 size, bool isMark);
  Result InData16(const void *buffer, u64 size, bool isMark);
  Result InData32(const void *buffer, u64 size, bool isMark);
  Result InData64(const void *buffer, u64 size, bool isMark);

  Allocator *unknown08; // Inferred role: allocator; original member name unknown.
  u8 *unknown10;        // Inferred role: buffer; original member name unknown.
  u32 m_bufferSize;
  u32 m_dataSize;
  u32 unknown20;  // Inferred role: write position; original member name unknown.
  u32 unknown24;  // Inferred role: read position; original member name unknown.
  u32 unknown28;  // Inferred role: mark position; original member name unknown.
  bool unknown2c; // Inferred role: mark enabled; original member name unknown.
  u8 _2d[0x30 - 0x2d];
};

static_assert(offsetof(StreamBuffer, unknown08) == 0x8, "");
static_assert(offsetof(StreamBuffer, m_bufferSize) == 0x18, "");
static_assert(offsetof(StreamBuffer, unknown24) == 0x24, "");
static_assert(offsetof(StreamBuffer, unknown28) == 0x28, "");
static_assert(offsetof(StreamBuffer, unknown2c) == 0x2c, "");
static_assert(sizeof(StreamBuffer) == 0x30, "");

} // namespace ssd
