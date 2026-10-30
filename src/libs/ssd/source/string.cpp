#include "ssd/ssd_allocator.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_hash.h"
#include "ssd/ssd_text.h"

namespace ssd {

String::String() {
  unknown20.unknown00 = nullptr;
  unknown20.unknown08 = 0;
}

String::~String() { FreeImpl(); }

void String::FreeImpl() {
  if (unknown20.unknown00 != nullptr) {
    Allocator *allocator = SoundMemory::allocator_;
    Allocator::Block *block = allocator->GetMemoryBlock(unknown20.unknown00);
    allocator->DeleteBufferImpl(block);
    unknown20.unknown00 = nullptr;
    unknown20.unknown08 = 0;
  }
}

void String::Set(const char *text) {
  Utf8ToUTF16(text, &unknown20);
  SSD_ASSERT(unknown20.unknown00 != nullptr,
             u"Assert : \"%s\", %s:%d, %s",
             u"data_.GetAdrs() != ssd_null",
             u"D:/ssd/ssd51/ssd/sources/util/string.cpp",
             0x41,
             u"メモリが確保できませんでした。: textBuf == nullptr");
  char16_t *buffer = static_cast<char16_t *>(unknown20.unknown00);
  unknown10 = buffer;
  unknown08 = Hash();
  unknown08.CalcTextHash(buffer);
}

void String::Set(const TextRef &text) {
  if (text.unknown18 == TEXT_ENCODE_UTF8) {
    Set(static_cast<const char *>(text.unknown10));
  } else {
    Set(static_cast<const char16_t *>(text.unknown10));
  }
}

} // namespace ssd
