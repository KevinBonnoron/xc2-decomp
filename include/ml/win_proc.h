#pragma once
#include <stddef.h>

#include "ml/reslist.h"
#include "ml/work_obj.h"
#include "types.h"

namespace ml {

class WinView;

class WinProc : public WorkObj {
public:
  WinProc(const char *name, WorkObj *parent, s16 childNum);
  ~WinProc() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;

  static WinProc *pssGetRoot(WinProc *proc);
  bool pssAttachView(WinView *view);
  WorkObj *pssGetParentView();
  WinView *pssGetView(u32 wid);
  const WinView *pssGetView(u32 wid) const;

  reslist<u32> unknown1a8; // Inferred role: attached view wids; original member name unknown.
  u32 unknown1e8;          // Inferred role: parent view wid; original member name unknown.
  u32 unknown1ec;          // Inferred role: initial value 2; original member name unknown.
};

static_assert(offsetof(WinProc, unknown1a8) == 0x1a8, "");
static_assert(offsetof(WinProc, unknown1e8) == 0x1e8, "");
static_assert(offsetof(WinProc, unknown1ec) == 0x1ec, "");

static_assert(sizeof(WinProc) == 0x1f0, "");

} // namespace ml
