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

  mtl::ALLOC_HANDLE m_mem;
  bool m_isPowerOff;
  bool m_isReset;
  bool m_isSaveLoadInvalidReset;
};

static_assert(offsetof(WorkSystem, m_mem) == 0x1b0, "");
static_assert(sizeof(WorkSystem) == 0x1b8, "");

} // namespace ml
