#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class WorkObjFlowSystemPause : public WorkObj, public mm::mtl::PtrSingleton<WorkObjFlowSystemPause> {
public:
  static f32 getRate();
  static void releasePause();
  bool wkStandbyLogout() override;
  void wkUpdate() override;

  s32 unknown1b0;  // Inferred role: state; original member name unknown.
  s32 unknown1b4;  // Inferred role: fade counter; original member name unknown.
  bool unknown1b8; // Inferred role: release requested; original member name unknown.
  u8 _1b9[0x1bc - 0x1b9];
  u32 unknown1bc; // Inferred role: target wid; original member name unknown.
};

static_assert(offsetof(WorkObjFlowSystemPause, unknown1b0) == 0x1b0, "");
static_assert(offsetof(WorkObjFlowSystemPause, unknown1b4) == 0x1b4, "");
static_assert(offsetof(WorkObjFlowSystemPause, unknown1b8) == 0x1b8, "");
static_assert(offsetof(WorkObjFlowSystemPause, unknown1bc) == 0x1bc, "");

} // namespace ml
