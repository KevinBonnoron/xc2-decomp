#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace ml {

class WorkSystem : public WorkObj, public mm::mtl::PtrSingleton<WorkSystem> {
public:
  WorkSystem(const char *name, WorkObj *parent);
  ~WorkSystem() override;
  static bool isOff();
  static bool isPowerOff();
  static bool isReset();
  static mtl::ALLOC_HANDLE getMem();
  static void setSaveLoadInvalidReset(bool isInvalid);
  void wkUpdate() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  static WorkSystem *create();
  static void setExitFunc(void (*func)());
  static void callExitFunc();

  mtl::ALLOC_HANDLE unknown1b0; // Inferred role: mem; original member name unknown.
  bool unknown1b4;              // Inferred role: power off; original member name unknown.
  bool unknown1b5;              // Inferred role: reset; original member name unknown.
  bool unknown1b6;              // Inferred role: save load invalid reset; original member name unknown.
};

static_assert(offsetof(WorkSystem, unknown1b0) == 0x1b0, "");
static_assert(sizeof(WorkSystem) == 0x1b8, "");

} // namespace ml
