#pragma once

namespace ml {

enum LangType : int;
enum SleepExtendType : int;

class DevSetting {
public:
  static LangType getLang();
  static void setAutoSleepExtended(SleepExtendType type);
};

} // namespace ml
