#include <stddef.h>
#include <string.h>

#include "ml/critical_section.h"
#include "ml/dev_graph.h"
#include "ml/reslist.h"
#include "ml/win_view_root.h"
#include "ml/work_cpu.h"
#include "ml/work_obj.h"
#include "ml/work_root.h"
#include "ml/work_system.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace ml {

namespace _wrootst {

class WorkRoot : public WorkObj {
public:
  void procParent();
  ~WorkRoot() override;
  bool wkStandbyLogout() override;

  reslist<WorkObj *> unknown1a8; // Inferred role: works requesting a parent; original member name unknown.
  reslist<WorkObj *> unknown1e8; // Inferred role: requested parents; original member name unknown.
};

static_assert(offsetof(WorkRoot, unknown1a8) == 0x1a8, "");
static_assert(offsetof(WorkRoot, unknown1e8) == 0x1e8, "");

struct unknown001 {
  u32 unknown00;
  u32 unknown04; // Inferred role: work id; original member name unknown.
  bool unknown08;
};

WorkRoot *s_pWorkRoot;
u32 *s_aBitWID;
WorkObj **s_apBitWID;
s32 s_nWidCount;
CriticalSectionNC s_lockEntry;
s32 s_nEntry;
unknown001 s_aEntry[100];
mm::mtl::FixedList<WorkObj *, 32> s_frameEnd;
bool s_bThreadRenderReq;
bool s_bThreadRender;

CriticalSection &getCriticalSection() {
  static CriticalSection sect;
  return sect;
}

} // namespace _wrootst

void WorkRootState::addFrameEnd(WorkObj *work) { _wrootst::s_frameEnd.push_back(work); }

void WorkRootState::removeFrameEnd(WorkObj *work) {
  mm::mtl::FixedList<WorkObj *, 32>::iterator it = mm::mtl::find(_wrootst::s_frameEnd.begin(), _wrootst::s_frameEnd.end(), work);
  if (it != _wrootst::s_frameEnd.end()) {
    _wrootst::s_frameEnd.erase(it);
  }
}

void WorkRootState::standbyWork() {
  entryWork();
  _wrootst::s_pWorkRoot->procParent();
  standbyWork(_wrootst::s_pWorkRoot);
}

bool WorkRootState::isUsedWID(u32 wid) {
  CS cs(_wrootst::getCriticalSection());
  if (wid == 0xffffffff) {
    return false;
  }
  return _wrootst::s_apBitWID[wid & 0xffff] != nullptr;
}

bool WorkRootState::isEntryWork(u32 wid, const WorkObj *parent) {
  CSNC cs(_wrootst::s_lockEntry);
  for (s32 i = 0; i < _wrootst::s_nEntry; i++) {
    if (_wrootst::s_aEntry[i].unknown04 == wid) {
      if (parent != nullptr) {
        WorkObj *work = getWork(wid);
        do {
          work = work->unknown58;
        } while (work != nullptr && work != parent);
      }
      return true;
    }
  }
  return false;
}

WorkObj *WorkRootState::getWork(WorkObj *parent, u32 wid) {
  CS cs(_wrootst::getCriticalSection());
  if (parent != nullptr) {
    if (parent->unknown50 == wid) {
      return parent;
    }
    for (reslist<WorkObj *>::Node *node = parent->wkGetChild()->begin(); node != parent->wkGetChild()->end(); node = node->getNext()) {
      WorkObj *work = getWork(node->value, wid);
      if (work != nullptr && work->unknown4c != WorkObj::WKSTATE_SHUTDOWN) {
        return work;
      }
    }
  }
  return nullptr;
}

WorkObj *WorkRootState::getWork(WorkObj *parent, const char *name) {
  CS cs(_wrootst::getCriticalSection());
  if (parent != nullptr) {
    if (strcmp(parent->unknown08.c_str(), name) == 0) {
      return parent;
    }
    for (reslist<WorkObj *>::Node *node = parent->wkGetChild()->begin(); node != parent->wkGetChild()->end(); node = node->getNext()) {
      WorkObj *work = getWork(node->value, name);
      if (work != nullptr && work->unknown4c != WorkObj::WKSTATE_SHUTDOWN) {
        return work;
      }
    }
  }
  return nullptr;
}

const WorkObj *WorkRootState::getWork(const WorkObj *parent, const char *name) {
  CS cs(_wrootst::getCriticalSection());
  if (parent != nullptr) {
    if (strcmp(parent->unknown08.c_str(), name) == 0) {
      return parent;
    }
    for (reslist<WorkObj *>::Node *node = parent->wkGetChild()->begin(); node != parent->wkGetChild()->end(); node = node->getNext()) {
      WorkObj *work = getWork(node->value, name);
      if (work != nullptr && work->unknown4c != WorkObj::WKSTATE_SHUTDOWN) {
        return work;
      }
    }
  }
  return nullptr;
}

WorkObj *WorkRootState::getActiveWork(WorkObj *parent, const char *name) {
  CS cs(_wrootst::getCriticalSection());
  if (parent != nullptr) {
    if (!parent->wkIsShutdown() && strcmp(parent->unknown08.c_str(), name) == 0) {
      return parent;
    }
    for (reslist<WorkObj *>::Node *node = parent->wkGetChild()->begin(); node != parent->wkGetChild()->end(); node = node->getNext()) {
      WorkObj *work = getActiveWork(node->value, name);
      if (work != nullptr && work->unknown4c != WorkObj::WKSTATE_SHUTDOWN && !parent->wkIsShutdown()) {
        return work;
      }
    }
  }
  return nullptr;
}

bool WorkRootState::requestParent(WorkObj *work, WorkObj *parent) {
  if (!work->wkIsWaitException()) {
    if (work->wkIsActive() && !parent->wkIsWaitException()) {
      if (parent->wkIsActive()) {
        _wrootst::WorkRoot *root = _wrootst::s_pWorkRoot;
        root->unknown1a8.push_back(work);
        root->unknown1e8.push_back(parent);
        return true;
      }
    }
  }
  return false;
}

void WorkRootState::renderWork() {
  if (_wrootst::s_pWorkRoot != nullptr) {
    DevGraph *graph = DevGraph::get();
    if (graph != nullptr && !graph->wkIsWaitException()) {
      if (graph->wkIsActive() && !WorkCpu::isShutdown()) {
        DevGraph::renderBegin();
        if (!WorkSystem::isOff()) {
          WinViewRoot::renderView();
        }
        DevGraph::renderEnd();
      }
    }
  }
}

void WorkRootState::entryWork() {
  CSNC cs(_wrootst::s_lockEntry);
  for (s32 i = 0; i < _wrootst::s_nEntry; i++) {
    WorkObj *work = getWork(_wrootst::s_aEntry[i].unknown04);
    WorkObj *parent = getWork(_wrootst::s_aEntry[i].unknown00);
    if (parent == nullptr && (parent = _wrootst::s_pWorkRoot) == nullptr) {
      _wrootst::s_pWorkRoot = static_cast<_wrootst::WorkRoot *>(work);
    } else {
      parent->wkEntryChild(work, _wrootst::s_aEntry[i].unknown08);
    }
  }
  _wrootst::s_nEntry = 0;
}

void WorkRootState::entryWork(WorkObj *work, WorkObj *parent, bool isFront) {
  CSNC cs(_wrootst::s_lockEntry);
  s32 index = _wrootst::s_nEntry;
  _wrootst::s_aEntry[index].unknown08 = isFront;
  _wrootst::s_aEntry[index].unknown04 = work->unknown50;
  u32 parentWid;
  if (parent == nullptr) {
    parentWid = 0xffffffff;
  } else {
    parentWid = parent->unknown50;
  }
  _wrootst::s_nEntry = index + 1;
  _wrootst::s_aEntry[index].unknown00 = parentWid;
}

bool WorkRootState::isDebug(WorkObj *work) { return mtl::MemManager::isArea(WorkRootMem::getMemStateDebug(), work); }

mtl::ALLOC_HANDLE WorkRootState::getWorkMem() { return WorkRootMem::getMemState(); }

void WorkRootState::setThreadRender(bool isThreadRender) {
  _wrootst::s_bThreadRenderReq = isThreadRender;
  _wrootst::s_bThreadRender = isThreadRender;
}

bool WorkRootState::isThreadRender() { return _wrootst::s_bThreadRender; }

void WorkRootState::shutdownAll() {
  if (!_wrootst::s_pWorkRoot->wkIsShutdown()) {
    _wrootst::s_pWorkRoot->wkSetEvent(static_cast<WorkObj::EVT>(0));
  }
}

bool WorkRootState::isShutdownAll() { return _wrootst::s_pWorkRoot->unknown60.size() == 0; }

void WorkRootState::updateWork(WorkObj *work) {
  if (!work->wkIsWaitException()) {
    if (work->wkIsActive() && (work->unknowna0 & 0x300) != 0x200 && (work->unknowna0 & 0xc0) != 0xc0 && (work->unknowna0 & 0x400) == 0 && ((work->unknowna0 & 0x800) != 0 || !work->wkIsShutdown())) {
      work->wkUpdate();
    }
  }
  for (reslist<WorkObj *>::Node *node = work->wkGetChild()->begin(); node != work->wkGetChild()->end(); node = node->getNext()) {
    updateWork(node->value);
  }
}

void WorkRootState::tailWork(WorkObj *work) {
  if (!work->wkIsWaitException()) {
    if (work->wkIsActive()) {
      work->wkTail();
    }
  }
  for (reslist<WorkObj *>::Node *node = work->wkGetChild()->begin(); node != work->wkGetChild()->end(); node = node->getNext()) {
    tailWork(node->value);
  }
}

void WorkRootState::updateWork() { updateWork(_wrootst::s_pWorkRoot); }

void WorkRootState::tailWork() { tailWork(_wrootst::s_pWorkRoot); }

bool _wrootst::WorkRoot::wkStandbyLogout() {
  if (unknown60.size() != 0) {
    return false;
  }

  return WorkObj::wkStandbyLogout();
}

} // namespace ml
