#pragma once
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"

namespace ml {

class WinProcRoot : public WorkObj, public mm::mtl::PtrSingleton<WinProcRoot> {
public:
  WinProcRoot(const char *name, WorkObj *parent);
  ~WinProcRoot() override;
  static bool isInitialized();
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  static WinProcRoot *create(WorkObj *parent);
};

static_assert(sizeof(WinProcRoot) == 0x1b0, "");

} // namespace ml
