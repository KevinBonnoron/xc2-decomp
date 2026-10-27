#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class WorkFlowSetup : public WorkObj, public mm::mtl::PtrSingleton<WorkFlowSetup> {
public:
  WorkFlowSetup(const char *name, WorkObj *parent);
  ~WorkFlowSetup() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;

  s32 unknown1b0; // Inferred role: state; original member name unknown.
};

static_assert(offsetof(WorkFlowSetup, unknown1b0) == 0x1b0, "");

} // namespace ml
