#include <stddef.h>
#include <string.h>

#include "ml/critical_section.h"
#include "ml/dev_graph.h"
#include "ml/device.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/win_view_root.h"
#include "ml/work_control.h"
#include "ml/work_cpu.h"
#include "ml/work_obj.h"
#include "ml/work_root.h"
#include "ml/work_system.h"
#include "ml/work_util.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nn/os.h"
#include "nn/time_span.h"
#include "types.h"

namespace ml {

namespace _wrootst {

class WorkRoot : public WorkObj {
public:
  // Defined in the class and with an implicit destructor: the game has the C2, D2 and D0 symbols only (no C1, no D1).
  WorkRoot(const char *name, WorkObj *parent) : WorkObj(name, parent, 0x20) {
    unknown1a8.create(128, unknown54);
    unknown1e8.create(128, unknown54);
  }
  void procParent();
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
unknown001 s_aEntry[384]; // The symbol of the game is 0x1200 bytes, 384 entries of 12 bytes.
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

void WorkRootState::standbyWork(WorkObj *work) {
  work->wkStandby();
  for (reslist<WorkObj *>::Node *node = work->wkGetChild()->begin(); node != work->wkGetChild()->end(); node = node->getNext()) {
    standbyWork(node->value);
  }
  reslist<WorkObj *>::iterator it = work->wkGetChild()->begin();
  while (it != work->wkGetChild()->end()) {
    reslist<WorkObj *>::iterator next = it;
    ++next;
    if ((*it)->unknown4c == WorkObj::WKSTATE_UNKNOWN_5) {
      work->wkRemoveChild(*it);
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
    }
    it = next;
  }
}

void WorkRootState::initialize() {
  _wrootst::s_bThreadRender = _wrootst::s_bThreadRenderReq;
  {
    CS cs(_wrootst::getCriticalSection());
    _wrootst::s_aBitWID = static_cast<u32 *>(mtl::MemManager::allocate(WorkRootMem::getMemState(), 0x100, 4, false, "no name", 0));
    _wrootst::s_apBitWID = static_cast<WorkObj **>(mtl::MemManager::allocate(WorkRootMem::getMemState(), 0x4000, 4, false, "no name", 0));
    for (int i = 0; i < 0x40; i++) {
      _wrootst::s_aBitWID[i] = 0;
    }
    for (int i = 0; i < 0x800; i++) {
      _wrootst::s_apBitWID[i] = nullptr;
    }
  }
  WorkUtil::createWork<_wrootst::WorkRoot>("WorkRoot", nullptr, false);
  entryWork();
  WorkCpu::create(_wrootst::s_pWorkRoot);
  WorkControl::create(_wrootst::s_pWorkRoot);
  Device::create();
  LibMain::create();
  WorkSystem::create();
  do {
    do {
      standbyWork();
    } while (Device::get() == nullptr);
  } while (!Device::isColdStartReady());
}

void WorkRootState::finalize() {
  if (_wrootst::s_pWorkRoot != nullptr) {
    delete _wrootst::s_pWorkRoot;
    _wrootst::s_pWorkRoot = nullptr;
  }
  CS cs(_wrootst::getCriticalSection());
  if (_wrootst::s_aBitWID != nullptr) {
    mtl::MemManager::deallocate(_wrootst::s_aBitWID, 0, false);
    _wrootst::s_aBitWID = nullptr;
  }
  if (_wrootst::s_apBitWID != nullptr) {
    mtl::MemManager::deallocate(_wrootst::s_apBitWID, 0, false);
    _wrootst::s_apBitWID = nullptr;
  }
}

u32 WorkRootState::allocWID(WorkObj *work) {
  CS cs(_wrootst::getCriticalSection());
  u32 wid = 0xffffffff;
  for (u32 i = 0; i < 0x40; i++) {
    u32 bits = _wrootst::s_aBitWID[i];
    if (bits != 0xffffffff) {
      u32 mask = 1;
      for (u32 j = 0; j < 0x20; j++, mask <<= 1) {
        if ((bits & mask) == 0) {
          wid = j + i * 0x20;
          _wrootst::s_aBitWID[i] |= mask;
          _wrootst::s_apBitWID[wid] = work;
          wid |= _wrootst::s_nWidCount++ << 20;
          break;
        }
      }
      break;
    }
  }
  return wid;
}

WorkObj *WorkRootState::getWork(u32 wid) {
  CS cs(_wrootst::getCriticalSection());
  if (wid == 0xffffffff) {
    return nullptr;
  }
  WorkObj *work = _wrootst::s_apBitWID[wid & 0xffff];
  if (work != nullptr && work->unknown50 != wid) {
    return nullptr;
  }
  return work;
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
      if (work != nullptr && work->unknown4c != WorkObj::WKSTATE_UNKNOWN_5) {
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
      if (work != nullptr && work->unknown4c != WorkObj::WKSTATE_UNKNOWN_5) {
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
      if (work != nullptr && work->unknown4c != WorkObj::WKSTATE_UNKNOWN_5) {
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
      if (work != nullptr && work->unknown4c != WorkObj::WKSTATE_UNKNOWN_5 && !parent->wkIsShutdown()) {
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

bool WorkRootState::runSingle() {
  while (WorkRoot::isErrorStop()) {
    WorkCpu::resumeThread();
    WorkCpu::backgroundProcess();
    nn::os::SleepThread(nn::TimeSpan::FromNanoSeconds(1000000));
  }
  WorkCpu::beginFrame();
  standbyWork();
  if (_wrootst::s_bThreadRender) {
    WorkCpu::beginRender();
  }
  WorkCpu::beginUpdate();
  updateWork(_wrootst::s_pWorkRoot);
  WorkCpu::endUpdate();
  if (!_wrootst::s_bThreadRender) {
    WorkCpu::beginRender();
  }
  WorkCpu::endRender();
  tailWork(_wrootst::s_pWorkRoot);
  WorkCpu::endFrame();
  for (mm::mtl::FixedList<WorkObj *, 32>::iterator it = _wrootst::s_frameEnd.begin(); it != _wrootst::s_frameEnd.end(); ++it) {
    (*it)->wkFrameEnd();
  }
  _wrootst::s_bThreadRender = _wrootst::s_bThreadRenderReq;
  return _wrootst::s_pWorkRoot->unknown60.size() != 0;
}

void _wrootst::WorkRoot::procParent() {
  while (unknown1a8.size() != 0) {
    WorkObj *work = unknown1a8.begin()->value;
    WorkObj *parent = unknown1e8.begin()->value;
    if (!work->wkIsWaitException()) {
      if (work->wkIsActive() && !parent->wkIsWaitException() && parent->wkIsActive()) {
        unknown1a8.erase(unknown1a8.begin());
        unknown1e8.erase(unknown1e8.begin());
        work->unknown58->wkRemoveChild(work);
        parent->wkEntryChild(work, false);
      }
    }
  }
  unknown1a8.clear();
  unknown1e8.clear();
}

bool _wrootst::WorkRoot::wkStandbyLogout() {
  if (unknown60.size() != 0) {
    return false;
  }

  return WorkObj::wkStandbyLogout();
}

} // namespace ml
