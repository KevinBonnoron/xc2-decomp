#pragma once

namespace nn {
namespace settings {

// The enum name comes from the import of the game nn::settings::LanguageCode::Make(nn::settings::Language);
// its enumerator names are not provable, so callers pass the integer value with a cast.
enum Language {};

struct LanguageCode {
  static LanguageCode Make(Language language);

  char string[8];
};

int GetAvailableLanguageCodeCount();
int GetAvailableLanguageCodes(LanguageCode *codes, int count);

} // namespace settings
} // namespace nn
