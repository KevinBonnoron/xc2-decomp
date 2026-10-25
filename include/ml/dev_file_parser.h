#pragma once
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"

namespace ml {

class DevFileParser : public WorkObj, public mm::mtl::PtrSingleton<DevFileParser> {
public:
  ~DevFileParser() override {}
  static bool checkCommand(const char *command, const char *expected);
  static bool isBusy();
  static bool isInitialized();
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
};

} // namespace ml
