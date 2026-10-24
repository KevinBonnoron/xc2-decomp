#include "ml/work_obj.h"

#include "ml/dev_clock.h"
#include "ml/work_root.h"
#include "ml/work_util.h"

namespace ml {

WorkObj::WorkObj(const char *name, WorkObj *parent, int childNum)
    : m_state(WKSTATE_NONE), m_wid(-1), m_parent(parent), m_flags(0), m_exceptionWid(-1), m_clock(0), m_priority(10), m_isRequestShutdown(false), m_isEntryAfter(nullptr) {
  m_mem = WorkUtil::getWorkMem();
  m_name = name;
  m_wid = WorkRootState::allocWID(this);
  if (childNum > 0) {
    m_children.create(childNum, m_mem);
  }

  if (parent != nullptr) {
    if (parent->m_flags & 0x40) {
      m_flags |= 0x40;
    }
    if (parent->m_flags & 0x80) {
      m_flags |= 0x80;
    }
    if (parent->m_flags & 0x200) {
      m_flags |= 0x200;
    }
    if (parent->m_flags & 0x100) {
      m_flags |= 0x100;
    }
    if (parent->m_flags & 0x400) {
      m_flags |= 0x400;
    }
    if (parent->wkIsShutdown()) {
      m_flags |= 1;
    }
  }
}

mtl::ALLOC_HANDLE WorkUtil::getWorkMem() { return WorkRootState::getWorkMem(); }

WorkObj::~WorkObj() {
  if (m_children.size() != 0) {
    for (reslist<WorkObj *>::Node *node = m_children.begin(); node != m_children.end(); node = node->getNext()) {
    }
  }

  WorkRootState::freeWID(m_wid);
}

const reslist<WorkObj *> *WorkObj::wkGetChild() const { return &m_children; }

reslist<WorkObj *> *WorkObj::wkGetChild() { return &m_children; }

bool WorkObj::wkIsCurrent() const {
  if (m_parent != nullptr) {
    return m_parent->m_children.begin()->value == this;
  }

  return true;
}

void WorkObj::wkDispState() {}

void WorkObj::wkRequestShutdown() { m_isRequestShutdown = true; }

void WorkObj::wkSetEvent(EVT event) {
  if (event == 0) {
    m_flags |= 1;
  } else {
    m_msg.add(event);
    m_msg.set("");
  }

  for (reslist<WorkObj *>::Node *node = m_children.begin(); node != m_children.end(); node = node->getNext()) {
    node->value->wkSetEvent(event);
  }
}

void WorkObj::wkSetEventCurrent(EVT event) {
  if (event == 0) {
    m_flags |= 1;
  } else {
    m_msg.add(event);
    m_msg.set("");
  }
}

void WorkObj::wkSetEventChild(EVT event) {
  for (reslist<WorkObj *>::Node *node = m_children.begin(); node != m_children.end(); node = node->getNext()) {
    node->value->wkSetEvent(event);
  }
}

bool WorkObj::wkCheckTimeout(u32 time, bool isTimeout, const char *message) {
  if (m_flags & 2) {
    return true;
  }

  return m_state < WKSTATE_INIT || m_state > WKSTATE_RUN || isTimeout;
}

void WorkObj::wkReplaceHasChild(int childNum) {
  if (childNum < 1) {
    return;
  }

  m_children.release();
  m_children.create(childNum, m_mem);
}

void WorkObj::wkTimeoutInit() {
  if (DevClock::get() != nullptr) {
    DevClock::getClockNow(m_clock);
  }
}

void WorkObj::wkStandby() {
  if (m_isRequestShutdown) {
    m_flags |= 1;
    m_isRequestShutdown = false;
  }

  m_flags &= 0xffff;
  while (m_msg.size() != 0) {
    MsgParam<8>::Param &param = m_msg.get(0);
    switch (param.msg) {
    case 1:
      m_flags |= 2;
      break;
    case 2:
      m_flags |= 0x10;
      m_exceptionWid = *reinterpret_cast<u32 *>(param.data);
      break;
    case 4:
      m_flags |= 0x40;
      break;
    case 5:
      m_flags |= 0x80;
      OnPauseTrigger(true, param.data);
      break;
    case 6:
      m_flags &= ~0x80;
      OnPauseTrigger(false, param.data);
      break;
    case 7:
      if (!(m_flags & 0x100)) {
        m_flags |= 0x200;
      }
      break;
    case 8:
      if (!(m_flags & 0x100)) {
        m_flags &= ~0x200;
      }
      break;
    case 10:
      m_flags |= 0x400;
      OnPauseTrigger(true, param.data);
      break;
    case 11:
      m_flags &= ~0x400;
      OnPauseTrigger(false, param.data);
      break;
    case 9:
      m_flags |= 0x100;
      break;
    }
    m_msg.pop();
  }

  if (wkIsWaitException()) {
    if (wkStandbyExceptionRetry(m_exceptionWid)) {
      WorkObj *work = WorkRootState::getWork(m_exceptionWid);
      if (work != nullptr) {
        work->wkSetEvent(static_cast<EVT>(0));
      }
      m_exceptionWid = -1;
      m_flags &= ~0x10;
    }
    return;
  }

  switch (m_state) {
  case WKSTATE_NONE:
    wkStandbyInit();
  case WKSTATE_INIT:
    if (!wkStandbyLogin()) {
      return;
    }
  case WKSTATE_LOGIN:
    if (!wkStandbyRun()) {
      return;
    }
  case WKSTATE_RUN:
    if (!wkStandbyLogout()) {
      return;
    }
  case WKSTATE_LOGOUT:
    wkStandbyShutdown();
  }
}

bool WorkObj::wkStandbyInit() {
  m_state = WKSTATE_INIT;
  wkTimeoutInit();
  return true;
}

bool WorkObj::wkStandbyRun() {
  if (m_flags & 1) {
    m_state = WKSTATE_RUN;
    wkTimeoutInit();
  }

  return m_state == WKSTATE_RUN;
}

bool WorkObj::wkStandbyShutdown() {
  m_state = WKSTATE_SHUTDOWN;
  wkTimeoutInit();
  return true;
}

bool WorkObj::wkStandbyDestruct() { return false; }

bool WorkObj::wkStandbyLogin() {
  m_state = WKSTATE_LOGIN;
  wkTimeoutInit();
  return true;
}

bool WorkObj::wkStandbyLogout() {
  m_state = WKSTATE_LOGOUT;
  wkTimeoutInit();
  return true;
}

} // namespace ml
