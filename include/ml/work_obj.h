#pragma once
#include <stddef.h>

#include "ml/msg_param.h"
#include "ml/reslist.h"
#include "ml/work_event.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

class WorkObj : public IWorkEvent {
public:
  enum EVT {};

  enum WKSTATE {
    WKSTATE_NONE,
    WKSTATE_INIT,
    WKSTATE_LOGIN,
    WKSTATE_RUN,
    WKSTATE_LOGOUT,
    WKSTATE_SHUTDOWN,
  };

  WorkObj(const char *name, WorkObj *parent, int childNum);
  ~WorkObj() override;
  const reslist<WorkObj *> *wkGetChild() const;
  reslist<WorkObj *> *wkGetChild();
  void wkEntryChild(WorkObj *child, bool isFront);
  bool wkIsCurrent() const;
  void wkRemoveChild(WorkObj *child);
  void wkDispState();
  void wkRequestShutdown();
  void wkSetEvent(EVT event);
  void wkSetEventCurrent(EVT event);
  void wkSetEventChild(EVT event);
  bool wkCheckTimeout(u32 time, bool isTimeout, const char *message);
  void wkReplaceHasChild(int childNum);
  void wkTimeoutInit();
  virtual void wkStandby();
  bool wkStandbyInit();
  bool wkStandbyRun();
  bool wkStandbyShutdown();
  bool wkStandbyDestruct();
  virtual void wkUpdate() {}
  virtual void wkRender() {}
  virtual void wkRenderAfter() {}
  virtual void wkTail() {}
  virtual void wkFrameEnd() {}
  virtual bool wkStandbyLogin();
  virtual bool wkStandbyLogout();
  virtual bool wkStandbyExceptionRetry(u32 wid) { return true; }

  bool wkIsShutdown() const { return (unknowna0 & 1) | unknown19c; }
  bool wkIsWaitException() const { return (unknowna0 & 0x10) != 0 || unknowna8.find(2) >= 0; }
  bool wkIsActive() const { return (unknown4c | 1) == WKSTATE_RUN; }

  mm::mtl::FixStr<64> unknown08;                     // Inferred role: name; original member name unknown.
  int unknown4c;                                     // Inferred role: state; original member name unknown.
  u32 unknown50;                                     // Inferred role: wid; original member name unknown.
  mtl::ALLOC_HANDLE unknown54;                       // Inferred role: mem; original member name unknown.
  WorkObj *unknown58;                                // Inferred role: parent; original member name unknown.
  reslist<WorkObj *> unknown60;                      // Inferred role: children; original member name unknown.
  u32 unknowna0;                                     // Inferred role: flags; original member name unknown.
  MsgParam<8> unknowna8;                             // Inferred role: msg; original member name unknown.
  u32 unknown188;                                    // Inferred role: exception wid; original member name unknown.
  long unknown190;                                   // Inferred role: clock; original member name unknown.
  int unknown198;                                    // Inferred role: priority; original member name unknown.
  bool unknown19c;                                   // Inferred role: request shutdown; original member name unknown.
  bool (*unknown1a0)(WorkObj *work, WorkObj *child); // Inferred role: entry after; original member name unknown.
};

static_assert(offsetof(WorkObj, unknown4c) == 0x4c, "");
static_assert(offsetof(WorkObj, unknown58) == 0x58, "");
static_assert(offsetof(WorkObj, unknown60) == 0x60, "");
static_assert(offsetof(WorkObj, unknowna0) == 0xa0, "");
static_assert(offsetof(WorkObj, unknowna8) == 0xa8, "");
static_assert(offsetof(WorkObj, unknown188) == 0x188, "");
static_assert(offsetof(WorkObj, unknown198) == 0x198, "");
static_assert(offsetof(WorkObj, unknown1a0) == 0x1a0, "");
static_assert(sizeof(WorkObj) == 0x1a8, "");

} // namespace ml
