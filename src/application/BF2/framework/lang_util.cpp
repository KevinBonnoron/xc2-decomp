#include "framework/lang_util.h"

#include "ml/dev_setting.h"
#include "mm_mtl/fixstr.h"

namespace fw {

namespace {

// Inferred role: lang folders; original type name unknown.
struct unknown082 {
  mm::mtl::FixStr<16> unknown00[LangUtil::LANG_TYPE_MAX];  // Inferred role: lang; original member name unknown.
  mm::mtl::FixStr<16> unknown12c[LangUtil::LANG_TYPE_MAX]; // Inferred role: voice; original member name unknown.
};

unknown082 s_folders;

constexpr LangType FALLBACK_LANG = static_cast<LangType>(1);

} // namespace

void LangUtil::initialize() {
  LangType lang = static_cast<LangType>(ml::DevSetting::getLang());
  m_selectLang = lang;
  m_defaultLang = lang;
  LangType voice = static_cast<LangType>(__builtin_strcmp(s_folders.unknown12c[lang].c_str(), "jp") != 0);
  m_selectVoice = voice;
  m_defaultVoice = voice;
}

void LangUtil::finalize() {}

LangType LangUtil::getDefaultLangType() { return m_defaultLang; }

LangType LangUtil::getDefaultVoiceType() { return m_defaultVoice; }

LangType LangUtil::getLangType() { return m_selectLang; }

LangType LangUtil::getVoiceType() { return m_selectVoice; }

void LangUtil::setLangType(LangType type) {
  LangList langs;
  getLangList(langs);
  for (const std::pair<LangType, mm::mtl::FixStr<16>> &lang : langs) {
    if (lang.first == type) {
      m_selectLang = type;
      return;
    }
  }
  m_selectLang = FALLBACK_LANG;
}

LangUtil::LangList &LangUtil::getLangList(LangList &list) {
  mm::mtl::FixedVector<ml::LangType, ml::DEV_LANG_NUM> devLangs;
  ml::DevSetting::getLangList(devLangs);
  list.clear();
  for (ml::LangType devLang : devLangs) {
    std::pair<LangType, mm::mtl::FixStr<16>> lang;
    lang.first = static_cast<LangType>(devLang);
    lang.second = s_folders.unknown00[lang.first];
    list.push_back(lang);
  }
  return list;
}

void LangUtil::setVoiceType(LangType type) {
  LangList voices;
  getVoiceList(voices);
  for (const std::pair<LangType, mm::mtl::FixStr<16>> &voice : voices) {
    if (voice.first == type) {
      m_selectVoice = type;
      return;
    }
  }
  m_selectVoice = static_cast<LangType>(__builtin_strcmp(s_folders.unknown12c[m_selectLang].c_str(), "jp") != 0);
}

LangUtil::LangList &LangUtil::getVoiceList(LangList &list) {
  list.clear();
  LangList langs;
  getLangList(langs);
  for (const std::pair<LangType, mm::mtl::FixStr<16>> &lang : langs) {
    const mm::mtl::FixStr<16> &folder = s_folders.unknown12c[lang.first];
    bool isFound = false;
    for (const std::pair<LangType, mm::mtl::FixStr<16>> &voice : list) {
      if (__builtin_strcmp(voice.second.c_str(), folder.c_str()) == 0) {
        isFound = true;
        break;
      }
    }
    if (!isFound) {
      std::pair<LangType, mm::mtl::FixStr<16>> voice;
      voice.first = lang.first;
      voice.second = folder;
      list.push_back(voice);
    }
  }
  return list;
}

const mm::mtl::FixStr<16> &LangUtil::getLangFolder() { return s_folders.unknown00[m_selectLang]; }

const mm::mtl::FixStr<16> &LangUtil::getVoiceFolder() { return s_folders.unknown12c[m_selectVoice]; }

} // namespace fw
