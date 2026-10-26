#include "ml/work_obj.h"

#include "ml/dev_clock.h"
#include "ml/reslist.h"
#include "ml/work_root.h"
#include "ml/work_util.h"

namespace ml {

WorkObj::WorkObj(const char *name, WorkObj *parent, int childNum)
    : unknown4c(WKSTATE_NONE), unknown50(-1), unknown58(parent), unknowna0(0), unknown188(-1), unknown190(0), unknown198(10), unknown19c(false), unknown1a0(nullptr) {
  unknown54 = WorkUtil::getWorkMem();
  unknown08 = name;
  unknown50 = WorkRootState::allocWID(this);
  if (childNum > 0) {
    unknown60.create(childNum, unknown54);
  }

  if (parent != nullptr) {
    if (parent->unknowna0 & 0x40) {
      unknowna0 |= 0x40;
    }
    if (parent->unknowna0 & 0x80) {
      unknowna0 |= 0x80;
    }
    if (parent->unknowna0 & 0x200) {
      unknowna0 |= 0x200;
    }
    if (parent->unknowna0 & 0x100) {
      unknowna0 |= 0x100;
    }
    if (parent->unknowna0 & 0x400) {
      unknowna0 |= 0x400;
    }
    if (parent->wkIsShutdown()) {
      unknowna0 |= 1;
    }
  }
}

mtl::ALLOC_HANDLE WorkUtil::getWorkMem() { return WorkRootState::getWorkMem(); }

WorkObj::~WorkObj() {
  if (unknown60.size() != 0) {
    for (reslist<WorkObj *>::Node *node = unknown60.begin(); node != unknown60.end(); node = node->getNext()) {
    }
  }

  WorkRootState::freeWID(unknown50);
}

const reslist<WorkObj *> *WorkObj::wkGetChild() const { return &unknown60; }

reslist<WorkObj *> *WorkObj::wkGetChild() { return &unknown60; }

bool WorkObj::wkIsCurrent() const {
  if (unknown58 != nullptr) {
    return unknown58->unknown60.begin()->value == this;
  }

  return true;
}

void WorkObj::wkDispState() {}

void WorkObj::wkRequestShutdown() { unknown19c = true; }

void WorkObj::wkSetEvent(EVT event) {
  if (event == 0) {
    unknowna0 |= 1;
  } else {
    unknowna8.add(event);
    unknowna8.set("");
  }

  for (reslist<WorkObj *>::Node *node = unknown60.begin(); node != unknown60.end(); node = node->getNext()) {
    node->value->wkSetEvent(event);
  }
}

void WorkObj::wkSetEventCurrent(EVT event) {
  if (event == 0) {
    unknowna0 |= 1;
  } else {
    unknowna8.add(event);
    unknowna8.set("");
  }
}

void WorkObj::wkSetEventChild(EVT event) {
  for (reslist<WorkObj *>::Node *node = unknown60.begin(); node != unknown60.end(); node = node->getNext()) {
    node->value->wkSetEvent(event);
  }
}

bool WorkObj::wkCheckTimeout(u32 time, bool isTimeout, const char *message) {
  if (unknowna0 & 2) {
    return true;
  }

  return unknown4c < WKSTATE_INIT || unknown4c > WKSTATE_RUN || isTimeout;
}

void WorkObj::wkReplaceHasChild(int childNum) {
  if (childNum < 1) {
    return;
  }

  unknown60.release();
  unknown60.create(childNum, unknown54);
}

void WorkObj::wkTimeoutInit() {
  if (DevClock::get() != nullptr) {
    DevClock::getClockNow(unknown190);
  }
}

void WorkObj::wkStandby() {
  if (unknown19c) {
    unknowna0 |= 1;
    unknown19c = false;
  }

  unknowna0 &= 0xffff;
  while (unknowna8.size() != 0) {
    MsgParam<8>::Param &param = unknowna8.get(0);
    switch (param.msg) {
    case 1:
      unknowna0 |= 2;
      break;
    case 2:
      unknowna0 |= 0x10;
      unknown188 = *reinterpret_cast<u32 *>(param.data);
      break;
    case 4:
      unknowna0 |= 0x40;
      break;
    case 5:
      unknowna0 |= 0x80;
      OnPauseTrigger(true, param.data);
      break;
    case 6:
      unknowna0 &= ~0x80;
      OnPauseTrigger(false, param.data);
      break;
    case 7:
      if (!(unknowna0 & 0x100)) {
        unknowna0 |= 0x200;
      }
      break;
    case 8:
      if (!(unknowna0 & 0x100)) {
        unknowna0 &= ~0x200;
      }
      break;
    case 10:
      unknowna0 |= 0x400;
      OnPauseTrigger(true, param.data);
      break;
    case 11:
      unknowna0 &= ~0x400;
      OnPauseTrigger(false, param.data);
      break;
    case 9:
      unknowna0 |= 0x100;
      break;
    }
    unknowna8.pop();
  }

  if (wkIsWaitException()) {
    if (wkStandbyExceptionRetry(unknown188)) {
      WorkObj *work = WorkRootState::getWork(unknown188);
      if (work != nullptr) {
        work->wkSetEvent(static_cast<EVT>(0));
      }
      unknown188 = -1;
      unknowna0 &= ~0x10;
    }
    return;
  }

  switch (unknown4c) {
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
  unknown4c = WKSTATE_INIT;
  wkTimeoutInit();
  return true;
}

bool WorkObj::wkStandbyRun() {
  if (unknowna0 & 1) {
    unknown4c = WKSTATE_RUN;
    wkTimeoutInit();
  }

  return unknown4c == WKSTATE_RUN;
}

bool WorkObj::wkStandbyShutdown() {
  unknown4c = WKSTATE_SHUTDOWN;
  wkTimeoutInit();
  return true;
}

bool WorkObj::wkStandbyDestruct() { return false; }

bool WorkObj::wkStandbyLogin() {
  unknown4c = WKSTATE_LOGIN;
  wkTimeoutInit();
  return true;
}

bool WorkObj::wkStandbyLogout() {
  unknown4c = WKSTATE_LOGOUT;
  wkTimeoutInit();
  return true;
}

template class reslist<IWorkEvent *>;
template class reslist<unsigned int>;

} // namespace ml
