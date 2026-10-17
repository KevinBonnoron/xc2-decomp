#pragma once

namespace nn {
namespace settings {

struct LanguageCode {
  char string[8];
};

int GetAvailableLanguageCodeCount();
int GetAvailableLanguageCodes(LanguageCode *codes, int count);

} // namespace settings
} // namespace nn
