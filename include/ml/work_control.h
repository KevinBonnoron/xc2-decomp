#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {
class CriticalSection;

namespace _wkcnt {

struct PAUSEQ {
  bool unknown00;                // Inferred role: pause flag; original member name unknown.
  mm::mtl::FixStr<16> unknown04; // Inferred role: pause name; original member name unknown.
};

static_assert(offsetof(PAUSEQ, unknown04) == 0x04, "");
static_assert(sizeof(PAUSEQ) == 0x18, "");

extern mm::mtl::FixedQueue<PAUSEQ, 16> s_quePause;

} // namespace _wkcnt

class WorkControl : public WorkObj, public mm::mtl::PtrSingleton<WorkControl> {
public:
  WorkControl(const char *name, WorkObj *parent);
  ~WorkControl() override;
  void wkTail() override;
  bool wkStandbyLogout() override;
  static WorkControl *create(WorkObj *parent);
  static bool setFlowSetup();
  static bool setFlowChangePort(const char *name);
  static bool setFlowSystemPause(u32 wid);
  static bool setFlowShutdownAll(bool);
  static void pause(bool isPause, const char *name);
  static bool hasFlow();
  static CriticalSection &getCriticalSection();

  static s32 s_nPauseNum;
  static s32 s_nSysPauseNum;

  s32 unknown1b0; // Inferred role: state; original member name unknown.
};

static_assert(offsetof(WorkControl, unknown1b0) == 0x1b0, "");

} // namespace ml
