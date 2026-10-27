#pragma once
#include <stddef.h>

#include "ml/win_view.h"
#include "ml/work_obj.h"
#include "ml/work_root.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class WinProc;

class WinViewRoot : public WorkObj, public mm::mtl::PtrSingleton<WinViewRoot> {
public:
  static bool isInitialized();
  WinViewRoot(const char *name, WorkObj *parent);
  ~WinViewRoot() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  static WinViewRoot *create(WorkObj *parent);
  static WinView *getCurrent();
  static WinProc *getCurrentProc();
  static void destroyProc(const WinProc *proc);
  static WinView *getView(u32 wid) {
    if (get() == nullptr) {
      return nullptr;
    }
    WorkObj *work = WorkRootState::getWork(wid);
    if (work != nullptr && WorkRootState::getWork(get(), wid) == nullptr && !WorkRootState::isEntryWork(wid, get())) {
      work = nullptr;
    }
    return static_cast<WinView *>(work);
  }
  static WinView *getView(const char *name);
  static bool isCurrent(const WinView *view);
  static void invalidCurrent(WinView *view);
  static bool isCurrentChild(const WinView *view, const WinView *current);

  u8 _1b0[0x1f0 - 0x1b0];
  WinView *unknown1f0; // Inferred role: current view; original member name unknown.
  WinProc *unknown1f8; // Inferred role: current proc; original member name unknown.
  WinProc *unknown200; // Inferred role: render proc; original member name unknown.
  u8 _208[0x210 - 0x208];
};

static_assert(offsetof(WinViewRoot, unknown1f0) == 0x1f0, "");
static_assert(offsetof(WinViewRoot, unknown1f8) == 0x1f8, "");
static_assert(offsetof(WinViewRoot, unknown200) == 0x200, "");
static_assert(sizeof(WinViewRoot) == 0x210, "");

} // namespace ml
