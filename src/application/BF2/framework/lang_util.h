#pragma once
#include <utility>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace fw {

enum LangType : u32;

class LangUtil {
public:
  static const int LANG_TYPE_MAX = 15;

  typedef mm::mtl::FixedVector<std::pair<LangType, mm::mtl::FixStr<16>>, LANG_TYPE_MAX> LangList;

  static void initialize();
  static void finalize();
  static LangType getDefaultLangType();
  static LangType getDefaultVoiceType();
  static LangType getLangType();
  static LangType getVoiceType();
  static void setLangType(LangType type);
  static LangList &getLangList(LangList &list);
  static void setVoiceType(LangType type);
  static LangList &getVoiceList(LangList &list);
  static const mm::mtl::FixStr<16> &getLangFolder();
  static const mm::mtl::FixStr<16> &getVoiceFolder();

  static LangType m_selectLang;
  static LangType m_selectVoice;
  static LangType m_defaultLang;
  static LangType m_defaultVoice;
};

} // namespace fw
