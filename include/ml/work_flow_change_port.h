#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class WorkFlowChangePort : public WorkObj, public mm::mtl::PtrSingleton<WorkFlowChangePort> {
public:
  WorkFlowChangePort(const char *name, WorkObj *parent);
  ~WorkFlowChangePort() override;
  void setup(const char *name);
  bool wkStandbyLogout() override;

  s32 unknown1b0;                 // Inferred role: state; original member name unknown.
  mm::mtl::FixStr<16> unknown1b4; // Inferred role: port name; original member name unknown.
};

static_assert(offsetof(WorkFlowChangePort, unknown1b0) == 0x1b0, "");
static_assert(offsetof(WorkFlowChangePort, unknown1b4) == 0x1b4, "");

} // namespace ml
