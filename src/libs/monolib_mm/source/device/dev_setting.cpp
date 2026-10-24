#include "ml/dev_setting.h"

#include "mm_mtl/fixed_vector.h"

namespace ml {

LangType DevSetting::m_defaultLang;

DevSetting::DevSetting() : unknown08(nullptr) {}

DevSetting::~DevSetting() {
  if (unknown08 != nullptr) {
    delete unknown08;
    unknown08 = nullptr;
  }
}

void DevSetting::initialize() {
  if (get() != nullptr) {
    get()->unknown08->initialize();
  }
}

void DevSetting::finalize() {
  if (get() != nullptr) {
    get()->unknown08->finalize();
  }
}

LangType DevSetting::getLang() {
  if (get() != nullptr) {
    return get()->unknown08->getLang();
  }
  return m_defaultLang;
}

void DevSetting::setLangDefault(LangType lang) { m_defaultLang = lang; }

mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &DevSetting::getLangList(mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &list) {
  list.clear();
  if (get() != nullptr) {
    return get()->unknown08->getLangList(list);
  }
  return list;
}

void DevSetting::setAutoSleepExtended(SleepExtendType type) {
  if (get() != nullptr) {
    get()->unknown08->setAutoSleepExtended(type);
  }
}

bool DevSetting::isAutoSleepExtended() {
  if (get() != nullptr) {
    return get()->unknown08->isAutoSleepExtended();
  }
  return false;
}

} // namespace ml
