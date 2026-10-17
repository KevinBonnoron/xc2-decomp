#include "device/nx/dev_setting_nx.h"

#include "mm_mtl/fixed_vector.h"
#include "nn/diag.h"
#include "nn/oe.h"
#include "nn/settings.h"

namespace ml {

DevSettingNx::DevSettingNx() {}

DevSettingNx::~DevSettingNx() {}

void DevSettingNx::initialize() {
  LangType lang = getLang();
  if (lang == DEV_LANG_INVALID) {
// The log records its line number.
#line 37
    NN_LOG("getLang() is DEV_LANG_INVALID!!\n");
  } else {
    DevSetting::m_defaultLang = lang;
  }
}

void DevSettingNx::finalize() {}

LangType DevSettingNx::getLang() const {
  nn::settings::LanguageCode code = nn::oe::GetDesiredLanguage();
  return setting_detail::convertLangType(code.string);
}

mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &DevSettingNx::getLangList(mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &list) const {
  list.clear();
  nn::settings::LanguageCode codes[DEV_LANG_NUM];
  int count = nn::settings::GetAvailableLanguageCodes(codes, nn::settings::GetAvailableLanguageCodeCount());
  for (int i = 0; i < count; i++) {
    LangType lang = setting_detail::convertLangType(codes[i].string);
    if (lang != DEV_LANG_INVALID) {
      list.push_back(lang);
    }
  }
  return list;
}

void DevSettingNx::setAutoSleepExtended(SleepExtendType type) {
  if (type != SLEEP_EXTEND_TYPE_NONE) {
    switch (type) {
    case SLEEP_EXTEND_TYPE_EXTENDED:
      nn::oe::SetUserInactivityDetectionTimeExtended(true);
      break;
    case SLEEP_EXTEND_TYPE_EXTENDED_UNSAFE:
      nn::oe::SetUserInactivityDetectionTimeExtendedUnsafe(true);
      break;
    }
  } else {
    switch (nn::oe::GetUserInactivityDetectionTimeExtensionMode()) {
    case 1:
      nn::oe::SetUserInactivityDetectionTimeExtended(false);
      break;
    case 2:
      nn::oe::SetUserInactivityDetectionTimeExtendedUnsafe(false);
      break;
    }
  }
}

bool DevSettingNx::isAutoSleepExtended() const { return nn::oe::IsUserInactivityDetectionTimeExtended(); }

} // namespace ml
