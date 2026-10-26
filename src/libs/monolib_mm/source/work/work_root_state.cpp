#include "ml/critical_section.h"
#include "ml/reslist.h"
#include "ml/work_obj.h"
#include "ml/work_root.h"
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
};

struct unknown001 {
  u32 unknown00;
  u32 unknown04; // Inferred role: work id; original member name unknown.
  u32 unknown08;
};

WorkRoot *s_pWorkRoot;
u32 *s_aBitWID;
WorkObj **s_apBitWID;
s32 s_nWidCount;
CriticalSectionNC s_lockEntry;
s32 s_nEntry;
unknown001 s_aEntry[100];
bool s_bThreadRenderReq;
bool s_bThreadRender;

CriticalSection &getCriticalSection() {
  static CriticalSection sect;
  return sect;
}

} // namespace _wrootst

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

void WorkRootState::updateWork() { updateWork(_wrootst::s_pWorkRoot); }

void WorkRootState::tailWork() { tailWork(_wrootst::s_pWorkRoot); }

bool _wrootst::WorkRoot::wkStandbyLogout() {
  if (unknown60.size() != 0) {
    return false;
  }

  return WorkObj::wkStandbyLogout();
}

} // namespace ml
