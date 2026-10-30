#include "ssd/ssd_debug.h"
#include "ssd/ssd_hash.h"
#include "ssd/ssd_text.h"

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

void TextRef::GetText(void *buffer, unsigned long size, TextEncodeType type) const {
  if (unknown18 != type) {
    if (unknown18 == TEXT_ENCODE_UTF8) {
      Utf8ToUTF16(unknown10_utf8, static_cast<char16_t *>(buffer), size);
    } else {
      Utf16ToUTF8(unknown10_utf16, static_cast<char *>(buffer), size);
    }
  } else if (unknown18 == TEXT_ENCODE_UTF8) {
    unknown003(static_cast<char *>(buffer), unknown10_utf8, size);
  } else {
    unknown003(static_cast<char16_t *>(buffer), unknown10_utf16, size);
  }
}

void TextFixedBase::Set(const char *text) {
  Utf8ToUTF16(text, unknown001(), unknown20);
  unknown08 = Hash();
  unknown08.CalcTextHash(static_cast<const char16_t *>(unknown10));
}

void TextFixedBase::Set(const char16_t *text) {
  unknown003(unknown001(), text, unknown20);
  unknown08 = Hash();
  unknown08.CalcTextHash(static_cast<const char16_t *>(unknown10));
}

void TextFixedBase::Set(const TextRef &text) {
  if (text.unknown18 == TEXT_ENCODE_UTF8) {
    Utf8ToUTF16(static_cast<const char *>(text.unknown10), unknown001(), unknown20);
  } else {
    unknown003(unknown001(), static_cast<const char16_t *>(text.unknown10), unknown20);
  }
  unknown08 = Hash();
  unknown08.CalcTextHash(static_cast<const char16_t *>(unknown10));
}

} // namespace ssd
