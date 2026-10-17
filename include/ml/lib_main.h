#pragma once
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"

namespace ml {

class LibMain : public WorkObj, public mm::mtl::PtrSingleton<LibMain> {
public:
  LibMain(const char *name, WorkObj *parent);
  ~LibMain() override;
  static bool isInitialized();
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  static LibMain *create();
};

static_assert(sizeof(LibMain) == 0x1b0, "");

} // namespace ml
