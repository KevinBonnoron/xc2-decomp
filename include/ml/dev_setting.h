#pragma once

namespace ml {

enum LangType : int;

class DevSetting {
public:
  static LangType getLang();
};

} // namespace ml
