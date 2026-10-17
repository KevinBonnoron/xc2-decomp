#include "ml/dev_setting.h"

#include "mm_mtl/fixed_vector.h"

namespace ml {

LangType DevSetting::m_defaultLang;

DevSetting::DevSetting() : m_impl(nullptr) {}

DevSetting::~DevSetting() {
  if (m_impl != nullptr) {
    delete m_impl;
    m_impl = nullptr;
  }
}

void DevSetting::initialize() {
  if (get() != nullptr) {
    get()->m_impl->initialize();
  }
}

void DevSetting::finalize() {
  if (get() != nullptr) {
    get()->m_impl->finalize();
  }
}

LangType DevSetting::getLang() {
  if (get() != nullptr) {
    return get()->m_impl->getLang();
  }
  return m_defaultLang;
}

void DevSetting::setLangDefault(LangType lang) { m_defaultLang = lang; }

mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &DevSetting::getLangList(mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &list) {
  list.clear();
  if (get() != nullptr) {
    return get()->m_impl->getLangList(list);
  }
  return list;
}

void DevSetting::setAutoSleepExtended(SleepExtendType type) {
  if (get() != nullptr) {
    get()->m_impl->setAutoSleepExtended(type);
  }
}

bool DevSetting::isAutoSleepExtended() {
  if (get() != nullptr) {
    return get()->m_impl->isAutoSleepExtended();
  }
  return false;
}

} // namespace ml
