#pragma once
#include "ml/dev_setting.h"

namespace ml {

class DevSettingNx : public unknown075 {
public:
  DevSettingNx();
  ~DevSettingNx() override;
  void initialize() override;
  void finalize() override;
  LangType getLang() const override;
  mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &getLangList(mm::mtl::FixedVector<LangType, DEV_LANG_NUM> &list) const override;
  void setAutoSleepExtended(SleepExtendType type) override;
  bool isAutoSleepExtended() const override;
};

} // namespace ml
