#pragma once
#include <stddef.h>

#include "ml/reslist.h"
#include "ml/work_obj.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class WinProc;
class WinView;

class WinViewRoot : public WorkObj, public mm::mtl::PtrSingleton<WinViewRoot> {
public:
  static bool isInitialized();
  WinViewRoot(const char *name, WorkObj *parent);
  ~WinViewRoot() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  static WinViewRoot *create(WorkObj *parent);
  static WinView *getCurrent();
  static WinView *getFullScreenView();
  static WinView *getRootView(WinView *view);
  static WinView *getPointedView(const mm::Pnt<int> &pos);
  static WinProc *getCurrentProc();
  static void destroyProc(const WinProc *proc);
  static WinView *getView(u32 wid);
  static WinView *getView(const char *name);
  static void renderView();
  static bool isCurrent(const WinView *view);
  static void invalidCurrent(WinView *view);
  static void setCurrent(WinView *view);
  static bool isCurrentChild(const WinView *view, const WinView *current);
  static void cutOff(bool cut);

  reslist<u32> unknown1b0; // Inferred role: wids of the views that were current; original member name unknown.
  WinView *unknown1f0;     // Inferred role: current view; original member name unknown.
  WinProc *unknown1f8;     // Inferred role: current proc; original member name unknown.
  WinProc *unknown200;     // Inferred role: render proc; original member name unknown.
  u32 unknown208;          // Inferred role: wid of the previous current view; original member name unknown.
  u8 _20c[0x210 - 0x20c];
};

static_assert(offsetof(WinViewRoot, unknown1b0) == 0x1b0, "");
static_assert(offsetof(WinViewRoot, unknown1f0) == 0x1f0, "");
static_assert(offsetof(WinViewRoot, unknown1f8) == 0x1f8, "");
static_assert(offsetof(WinViewRoot, unknown200) == 0x200, "");
static_assert(offsetof(WinViewRoot, unknown208) == 0x208, "");
static_assert(sizeof(WinViewRoot) == 0x210, "");

} // namespace ml
