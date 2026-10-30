#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"

namespace ml {

enum LangType : int {
  DEV_LANG_INVALID = 15,
  DEV_LANG_NUM = 15,
};

enum SleepExtendType : int {
  SLEEP_EXTEND_TYPE_NONE,
  SLEEP_EXTEND_TYPE_EXTENDED,
  SLEEP_EXTEND_TYPE_EXTENDED_UNSAFE,
};

namespace setting_detail {

LangType convertLangType(const char *code);

} // namespace setting_detail

// Inferred role: device interface setting; original type name unknown.
class unknown075 {
public:
  virtual ~unknown075() {}
  virtual void initialize() = 0;
  virtual void finalize() = 0;
  virtual LangType getLang() const = 0;
  virtual mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &getLangList(mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &list) const = 0;
  virtual void setAutoSleepExtended(SleepExtendType type) = 0;
  virtual bool isAutoSleepExtended() const = 0;
};

class DevSetting : public mm::mtl::PtrSingleton<DevSetting> {
public:
  DevSetting();
  ~DevSetting() override;
  static void initialize();
  static void finalize();
  static LangType getLang();
  static void setLangDefault(LangType lang);
  static mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &getLangList(mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &list);
  static void setAutoSleepExtended(SleepExtendType type);
  static bool isAutoSleepExtended();

  static LangType m_defaultLang;

  unknown075 *unknown08; // Inferred role: impl; original member name unknown.
};

static_assert(offsetof(DevSetting, unknown08) == 0x08, "");

} // namespace ml
