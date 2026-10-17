#pragma once
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"

namespace ml {

class DevPerf : public WorkObj, public mm::mtl::PtrSingleton<DevPerf> {
public:
  ~DevPerf() override;
  static bool isInitialized();
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  void wkUpdate() override;
};

} // namespace ml
