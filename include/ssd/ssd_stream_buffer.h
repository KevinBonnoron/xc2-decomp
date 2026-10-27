#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class Allocator;

class StreamBufferBase {
public:
  virtual u32 GetBufferSize() const = 0;
  virtual u32 GetDataSize() const = 0;
  virtual u64 GetFreeSize() const = 0;
};

class StreamBuffer : public StreamBufferBase {
public:
  u32 GetBufferSize() const override;
  u32 GetDataSize() const override;
  u64 GetFreeSize() const override;
  void Clear();
  int Free();

  Allocator *unknown08; // Inferred role: allocator; original member name unknown.
  u8 *unknown10;        // Inferred role: buffer; original member name unknown.
  u32 m_bufferSize;
  u32 m_dataSize;
  u32 unknown20; // Inferred role: write position; original member name unknown.
  u32 unknown24; // Inferred role: read position; original member name unknown.
  u8 _28[0x30 - 0x28];
};

static_assert(offsetof(StreamBuffer, unknown08) == 0x8, "");
static_assert(offsetof(StreamBuffer, m_bufferSize) == 0x18, "");
static_assert(offsetof(StreamBuffer, unknown24) == 0x24, "");
static_assert(sizeof(StreamBuffer) == 0x30, "");

} // namespace ssd
