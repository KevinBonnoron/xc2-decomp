#include "ssd/ssd_debug.h"
#include "ssd/ssd_hash.h"
#include "ssd/ssd_text.h"

namespace ssd {
enum Result : long;

TextRef::TextRef(const TextRef &text) {
  this->text = text.text;
  encodeType = text.encodeType;
  hash = text.hash;
}

TextRef::TextRef(const char *text) { InitImpl(text); }

TextRef::TextRef(const char16_t *text) { InitImpl(text); }

void TextRef::Clear() {
  hash = Hash();
  text = nullptr;
  encodeType = TEXT_ENCODE_NONE;
}

void TextRef::InitImpl(const char *text) {
  this->text = text;
  encodeType = TEXT_ENCODE_UTF8;
  hash = Hash();
  hash.CalcTextHash(text);
}

void TextRef::InitImpl(const char16_t *text) {
  this->text = text;
  encodeType = TEXT_ENCODE_UTF16;
  hash = Hash();
  hash.CalcTextHash(text);
}

void TextRef::Set(const TextRef &text) { log_error(static_cast<Result>(-1), Debug::LogFlag::All, u"TextRef::Set は使用できません。", EmptyText); }

void TextRef::Set(const char *text) { log_error(static_cast<Result>(-1), Debug::LogFlag::All, u"TextRef::Set は使用できません。", EmptyText); }

void TextRef::Set(const char16_t *text) { log_error(static_cast<Result>(-1), Debug::LogFlag::All, u"TextRef::Set は使用できません。", EmptyText); }

} // namespace ssd
