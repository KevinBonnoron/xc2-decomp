#include "ssd/ssd_debug.h"
#include "ssd/ssd_hash.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {
enum Result : long;

TextRef::TextRef(const TextRef &text) {
  this->unknown10 = text.unknown10;
  unknown18 = text.unknown18;
  unknown08 = text.unknown08;
}

TextRef::TextRef(const char *text) { InitImpl(text); }

TextRef::TextRef(const char16_t *text) { InitImpl(text); }

void TextRef::Clear() {
  unknown08 = Hash();
  unknown10 = nullptr;
  unknown18 = TEXT_ENCODE_NONE;
}

void TextRef::InitImpl(const char *text) {
  this->unknown10 = text;
  unknown18 = TEXT_ENCODE_UTF8;
  unknown08 = Hash();
  unknown08.CalcTextHash(text);
}

void TextRef::InitImpl(const char16_t *text) {
  this->unknown10 = text;
  unknown18 = TEXT_ENCODE_UTF16;
  unknown08 = Hash();
  unknown08.CalcTextHash(text);
}

void TextRef::Set(const TextRef &text) { log_error(static_cast<Result>(-1), Debug::LogFlag::All, u"TextRef::Set は使用できません。", EmptyText); }

void TextRef::Set(const char *text) { log_error(static_cast<Result>(-1), Debug::LogFlag::All, u"TextRef::Set は使用できません。", EmptyText); }

void TextRef::Set(const char16_t *text) { log_error(static_cast<Result>(-1), Debug::LogFlag::All, u"TextRef::Set は使用できません。", EmptyText); }

void TextFixedBase::Set(const char *text) {
  Utf8ToUTF16(text, unknown001(), unknown20);
  unknown08 = Hash();
  unknown08.CalcTextHash(static_cast<const char16_t *>(unknown10));
}

void TextFixedBase::Set(const char16_t *text) {
  char16_t *buffer = unknown001();
  char16_t *destination = buffer;
  unsigned long limit = unknown20 - 1;
  while (*text != u'\0' && static_cast<u32>(destination - buffer) < limit) {
    *destination = *text;
    destination++;
    text++;
  }
  *destination = u'\0';
  unknown08 = Hash();
  unknown08.CalcTextHash(static_cast<const char16_t *>(unknown10));
}

void TextFixedBase::Set(const TextRef &text) {
  if (text.unknown18 == TEXT_ENCODE_UTF8) {
    Utf8ToUTF16(static_cast<const char *>(text.unknown10), unknown001(), unknown20);
  } else {
    const char16_t *source = static_cast<const char16_t *>(text.unknown10);
    char16_t *buffer = unknown001();
    char16_t *destination = buffer;
    unsigned long limit = unknown20 - 1;
    while (*source != u'\0' && static_cast<u32>(destination - buffer) < limit) {
      *destination = *source;
      destination++;
      source++;
    }
    *destination = u'\0';
  }
  unknown08 = Hash();
  unknown08.CalcTextHash(static_cast<const char16_t *>(unknown10));
}

} // namespace ssd
