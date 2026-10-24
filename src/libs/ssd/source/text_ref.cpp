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

} // namespace ssd
