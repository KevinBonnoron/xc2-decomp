#include "framework/lang_util.h"

#include "ml/dev_setting.h"
#include "mm_mtl/fixstr.h"

namespace fw {

namespace {

struct LangFolders {
  mm::mtl::FixStr<16> lang[LangUtil::LANG_TYPE_MAX];
  mm::mtl::FixStr<16> voice[LangUtil::LANG_TYPE_MAX];
};

LangFolders s_folders;

} // namespace

void LangUtil::initialize() {
  LangType lang = static_cast<LangType>(ml::DevSetting::getLang());
  m_selectLang = lang;
  m_defaultLang = lang;
  LangType voice = static_cast<LangType>(__builtin_strcmp(s_folders.voice[lang].c_str(), "jp") != 0);
  m_selectVoice = voice;
  m_defaultVoice = voice;
}

void LangUtil::finalize() {}

LangType LangUtil::getDefaultLangType() { return m_defaultLang; }

LangType LangUtil::getDefaultVoiceType() { return m_defaultVoice; }

LangType LangUtil::getLangType() { return m_selectLang; }

LangType LangUtil::getVoiceType() { return m_selectVoice; }

const mm::mtl::FixStr<16> &LangUtil::getLangFolder() { return s_folders.lang[m_selectLang]; }

const mm::mtl::FixStr<16> &LangUtil::getVoiceFolder() { return s_folders.voice[m_selectVoice]; }

} // namespace fw
