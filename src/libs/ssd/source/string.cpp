#include "ssd/ssd_allocator.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_hash.h"
#include "ssd/ssd_text.h"

namespace ssd {

String::String() {
  m_memoryBlock.unknown00 = nullptr;
  m_memoryBlock.unknown08 = 0;
}

String::~String() { FreeImpl(); }

void String::FreeImpl() {
  if (m_memoryBlock.unknown00 != nullptr) {
    Allocator *allocator = SoundMemory::allocator_;
    Allocator::Block *block = allocator->GetMemoryBlock(m_memoryBlock.unknown00);
    allocator->DeleteBufferImpl(block);
    m_memoryBlock.unknown00 = nullptr;
    m_memoryBlock.unknown08 = 0;
  }
}

void String::Set(const char *text) {
  Utf8ToUTF16(text, &m_memoryBlock);
  SSD_ASSERT(m_memoryBlock.unknown00 != nullptr,
             u"Assert : \"%s\", %s:%d, %s",
             u"data_.GetAdrs() != ssd_null",
             u"D:/ssd/ssd51/ssd/sources/util/string.cpp",
             0x41,
             u"メモリが確保できませんでした。: textBuf == nullptr");
  char16_t *buffer = static_cast<char16_t *>(m_memoryBlock.unknown00);
  unknown10 = buffer;
  m_hash = Hash();
  m_hash.CalcTextHash(buffer);
}

void String::Set(const TextRef &text) {
  if (text.unknown18 == TEXT_ENCODE_UTF8) {
    Set(static_cast<const char *>(text.unknown10));
  } else {
    Set(static_cast<const char16_t *>(text.unknown10));
  }
}

} // namespace ssd
