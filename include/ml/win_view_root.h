#pragma once
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class WinViewRoot : public WorkObj, public mm::mtl::PtrSingleton<WinViewRoot> {
public:
  static bool isInitialized();
  WinViewRoot(const char *name, WorkObj *parent);
  ~WinViewRoot() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  static WinViewRoot *create(WorkObj *parent);

  u8 _1b0[0x210 - 0x1b0];
};

static_assert(sizeof(WinViewRoot) == 0x210, "");

} // namespace ml
