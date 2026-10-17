#include "ml/work_root.h"

#include "mtl/alloc_handle.h"

namespace ml {

namespace _wrootm {

mtl::ALLOC_HANDLE s_hMemFG;
mtl::ALLOC_HANDLE s_hMemTEMP;
mtl::ALLOC_HANDLE s_hStateMem;
mtl::ALLOC_HANDLE s_hStateMemDebug;

} // namespace _wrootm

mtl::ALLOC_HANDLE WorkRootMem::getMemFG() { return _wrootm::s_hMemFG; }

mtl::ALLOC_HANDLE WorkRootMem::getMemTMP() { return _wrootm::s_hMemTEMP; }

mtl::ALLOC_HANDLE WorkRootMem::getMemState() { return _wrootm::s_hStateMem; }

mtl::ALLOC_HANDLE WorkRootMem::getMemStateDebug() { return _wrootm::s_hStateMemDebug; }

} // namespace ml
