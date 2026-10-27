#include <stdlib.h>

#include "ml/imem_manager_finalize.h"
#include "ml/ml_mem.h"
#include "ml/work_root.h"
#include "mm_mtl/fixed_vector.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace ml {

namespace _wrootm {

mtl::ALLOC_HANDLE s_hMemFG;
mtl::ALLOC_HANDLE s_hMemTEMP;
mtl::ALLOC_HANDLE s_hStateMem;
mtl::ALLOC_HANDLE s_hStateMemDebug;
mm::mtl::FixedVector<IMemManagerFinalize *, 32> g_FinalizeCallback;

} // namespace _wrootm

void WorkRootMem::finalize() {
  for (u32 i = 0; i < _wrootm::g_FinalizeCallback.size(); i++) {
    IMemManagerFinalize *callback = *_wrootm::g_FinalizeCallback.at(i);
    if (callback != nullptr) {
      callback->notifyFinalize();
    }
  }
  _wrootm::g_FinalizeCallback.clear();
  if (_wrootm::s_hStateMemDebug.isValid()) {
    mtl::MemManager::erase(_wrootm::s_hStateMemDebug);
    _wrootm::s_hStateMemDebug = mtl::ALLOC_HANDLE();
  }
  if (_wrootm::s_hStateMem.isValid()) {
    mtl::MemManager::erase(_wrootm::s_hStateMem);
    _wrootm::s_hStateMem = mtl::ALLOC_HANDLE();
  }
  if (_wrootm::s_hMemTEMP.isValid()) {
    mtl::MemManager::erase(_wrootm::s_hMemTEMP);
    _wrootm::s_hMemTEMP = mtl::ALLOC_HANDLE();
  }
  if (MlMem::getDebugMem().isValid()) {
    mtl::MemManager::erase(MlMem::getDebugMem());
    MlMem::getDebugMem() = mtl::ALLOC_HANDLE();
  }
  if (MlMem::getGraphicMem().isValid()) {
    mtl::MemManager::erase(MlMem::getGraphicMem());
    MlMem::getGraphicMem() = mtl::ALLOC_HANDLE();
  }
  if (MlMem::getProductMem().isValid()) {
    mtl::MemManager::erase(MlMem::getProductMem());
    MlMem::getProductMem() = mtl::ALLOC_HANDLE();
  }
  free(WorkRoot::getParam()->unknown08);
}

IMemManagerFinalize::IMemManagerFinalize() { _wrootm::g_FinalizeCallback.push_back(this); }

void IMemManagerFinalize::notifyFinalize() {}

mtl::ALLOC_HANDLE WorkRootMem::getMemFG() { return _wrootm::s_hMemFG; }

mtl::ALLOC_HANDLE WorkRootMem::getMemTMP() { return _wrootm::s_hMemTEMP; }

mtl::ALLOC_HANDLE WorkRootMem::getMemState() { return _wrootm::s_hStateMem; }

mtl::ALLOC_HANDLE WorkRootMem::getMemStateDebug() { return _wrootm::s_hStateMemDebug; }

} // namespace ml
