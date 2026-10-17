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

  bool wkIsShutdown() const { return (m_flags & 1) | m_isRequestShutdown; }
  bool wkIsWaitException() const { return (m_flags & 0x10) != 0 || m_msg.find(2) >= 0; }
  bool wkIsActive() const { return (m_state | 1) == WKSTATE_RUN; }

  mm::mtl::FixStr<64> m_name;
  int m_state;
  u32 m_wid;
  mtl::ALLOC_HANDLE m_mem;
  WorkObj *m_parent;
  reslist<WorkObj *> m_children;
  u32 m_flags;
  MsgParam<8> m_msg;
  u32 m_exceptionWid;
  long m_clock;
  int m_priority;
  bool m_isRequestShutdown;
  bool (*m_isEntryAfter)(WorkObj *work, WorkObj *child);
};

static_assert(offsetof(WorkObj, m_state) == 0x4c, "");
static_assert(offsetof(WorkObj, m_parent) == 0x58, "");
static_assert(offsetof(WorkObj, m_children) == 0x60, "");
static_assert(offsetof(WorkObj, m_flags) == 0xa0, "");
static_assert(offsetof(WorkObj, m_msg) == 0xa8, "");
static_assert(offsetof(WorkObj, m_exceptionWid) == 0x188, "");
static_assert(offsetof(WorkObj, m_priority) == 0x198, "");
static_assert(offsetof(WorkObj, m_isEntryAfter) == 0x1a0, "");
static_assert(sizeof(WorkObj) == 0x1a8, "");

} // namespace ml
