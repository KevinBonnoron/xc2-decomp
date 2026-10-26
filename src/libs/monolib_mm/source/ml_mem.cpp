#include "ml/ml_mem.h"

#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

namespace {
mtl::ALLOC_HANDLE s_productMem;
mtl::ALLOC_HANDLE s_debugMem;
mtl::ALLOC_HANDLE s_graphicMem;
mm::mtl::FixedList<mtl::ALLOC_HANDLE, 64> s_extMems;
} // namespace

void MlMem::setProductMem(mtl::ALLOC_HANDLE handle) { s_productMem = handle; }

mtl::ALLOC_HANDLE MlMem::getProductMem() { return s_productMem; }

void MlMem::setDebugMem(mtl::ALLOC_HANDLE handle) { s_debugMem = handle; }

mtl::ALLOC_HANDLE MlMem::getDebugMem() { return s_debugMem; }

void MlMem::setGraphicMem(mtl::ALLOC_HANDLE handle) { s_graphicMem = handle; }

mtl::ALLOC_HANDLE MlMem::getGraphicMem() { return s_graphicMem; }

void MlMem::removeExtMem(mtl::ALLOC_HANDLE handle) {
  mm::mtl::FixedList<mtl::ALLOC_HANDLE, 64>::iterator it = mm::mtl::find(s_extMems.begin(), s_extMems.end(), handle);
  if (it != s_extMems.end()) {
    s_extMems.erase(it);
  }
}

int MlMem::getExtMemNum() { return s_extMems.size(); }

bool MlMem::isDebug(const void *pointer) { return mtl::MemManager::isArea(s_debugMem, pointer); }

void MlMem::setMemoryPermission(void *address, size_t size, AccessMode mode) {}

} // namespace ml
