#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class BufferBase {
public:
  void GetData(u64 size, u64 offset, void *buffer);
  long Read(u64 size, void *buffer);

  u8 *unknown00; // Inferred role: data; original member name unknown.
  u64 unknown08; // Inferred role: data size; original member name unknown.
  u64 unknown10; // Inferred role: read position; original member name unknown.
};

static_assert(offsetof(BufferBase, unknown10) == 0x10, "");

void ClearMemory8(void *buffer, unsigned long size);
void ClearMemory16(void *buffer, unsigned long size);
void ClearMemory32(void *buffer, unsigned long size);
void ClearMemory64(void *buffer, unsigned long size);
void FillMemory8(void *buffer, unsigned long size, unsigned char value);
void FillMemory16(void *buffer, unsigned long size, unsigned char value);
void FillMemory32(void *buffer, unsigned long size, unsigned char value);
void FillMemory64(void *buffer, unsigned long size, unsigned char value);
void CopyMemory8(const void *source, void *destination, unsigned long size);
void CopyMemory16(const void *source, void *destination, unsigned long size);
void CopyMemory32(const void *source, void *destination, unsigned long size);
void CopyMemory64(const void *source, void *destination, unsigned long size);

} // namespace ssd
