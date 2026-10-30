#include <stddef.h>

#include "nn/util.h"
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_buffer.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {

void SjisToUTF16(const char *source, char16_t *destination, unsigned long size) {}

void Utf8ToUTF16(const char *source, char16_t *destination, unsigned long size) { nn::util::ConvertStringUtf8ToUtf16Native(reinterpret_cast<u16 *>(destination), size, source); }

void Utf16ToSjis(const char16_t *source, char *destination, unsigned long size) {}

void Utf16ToUTF8(const char16_t *source, char *destination, unsigned long size) { nn::util::ConvertStringUtf16NativeToUtf8(destination, size, reinterpret_cast<const u16 *>(source)); }

char16_t *SjisToUTF16(const char *source, unsigned long *length) { return nullptr; }

bool Utf8ToUTF16(const char *source, MemoryBlock *block) {
  int length;
  nn::util::GetLengthOfConvertedStringUtf8ToUtf16Native(&length, source, TextRef::unknown002(source));
  size_t count = length + 2;
  size_t size = count * sizeof(char16_t);
  if (block->unknown00 != nullptr) {
    Allocator *allocator = SoundMemory::allocator_;
    allocator->DeleteBufferImpl(allocator->GetMemoryBlock(block->unknown00));
  }
  Allocator::Block *buffer = SoundMemory::allocator_->NewBufferImpl(count, sizeof(char16_t), 16);
  block->unknown00 = buffer != nullptr ? buffer->unknown08 : nullptr;
  block->unknown08 = size;
  ClearMemory16(block->unknown00, block->unknown08);
  nn::util::ConvertStringUtf8ToUtf16Native(static_cast<u16 *>(block->unknown00), length + 1, source);
  return true;
}

bool Utf16ToUTF8(const char16_t *source, MemoryBlock *block) {
  int length;
  nn::util::GetLengthOfConvertedStringUtf16NativeToUtf8(&length, reinterpret_cast<const u16 *>(source), TextRef::unknown002(source));
  size_t count = length + 2;
  size_t size = (count + 1) & ~1;
  if (block->unknown00 != nullptr) {
    Allocator *allocator = SoundMemory::allocator_;
    allocator->DeleteBufferImpl(allocator->GetMemoryBlock(block->unknown00));
  }
  Allocator::Block *buffer = SoundMemory::allocator_->NewBufferImpl(count, sizeof(char), 16);
  block->unknown00 = buffer != nullptr ? buffer->unknown08 : nullptr;
  block->unknown08 = size;
  ClearMemory16(block->unknown00, block->unknown08);
  nn::util::ConvertStringUtf16NativeToUtf8(static_cast<char *>(block->unknown00), length + 1, reinterpret_cast<const u16 *>(source));
  return true;
}

} // namespace ssd
