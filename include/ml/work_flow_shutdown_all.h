#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class WorkFlowShutdownAll : public WorkObj, public mm::mtl::PtrSingleton<WorkFlowShutdownAll> {
public:
  WorkFlowShutdownAll(const char *name, WorkObj *parent);
  ~WorkFlowShutdownAll() override;
  bool wkStandbyLogout() override;
  void wkUpdate() override;

  s32 unknown1b0; // Inferred role: state; original member name unknown.
};

static_assert(offsetof(WorkFlowShutdownAll, unknown1b0) == 0x1b0, "");

} // namespace ml
