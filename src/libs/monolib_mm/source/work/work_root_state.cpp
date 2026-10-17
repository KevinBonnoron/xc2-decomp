#include "ml/reslist.h"
#include "ml/work_obj.h"
#include "ml/work_root.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

namespace _wrootst {

class WorkRoot : public WorkObj {
public:
  void procParent();
  ~WorkRoot() override;
  bool wkStandbyLogout() override;
};

WorkRoot *s_pWorkRoot;
bool s_bThreadRenderReq;
bool s_bThreadRender;

} // namespace _wrootst

void WorkRootState::standbyWork() {
  entryWork();
  _wrootst::s_pWorkRoot->procParent();
  standbyWork(_wrootst::s_pWorkRoot);
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

bool WorkRootState::isShutdownAll() { return _wrootst::s_pWorkRoot->m_children.size() == 0; }

void WorkRootState::updateWork() { updateWork(_wrootst::s_pWorkRoot); }

void WorkRootState::tailWork() { tailWork(_wrootst::s_pWorkRoot); }

bool _wrootst::WorkRoot::wkStandbyLogout() {
  if (m_children.size() != 0) {
    return false;
  }

  return WorkObj::wkStandbyLogout();
}

} // namespace ml
