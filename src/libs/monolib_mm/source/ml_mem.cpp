#include "ml/ml_mem.h"

#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

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

void MlMem::addExtMem(mtl::ALLOC_HANDLE handle) {
  mtl::MemoryInfo info;
  if (mtl::MemManager::getMemoryInfo(handle, &info)) {
    mm::mtl::FixedVector<mtl::ALLOC_HANDLE, 8> handles;
    handles.push_back(s_productMem);
    handles.push_back(s_debugMem);
    for (mm::mtl::FixedList<mtl::ALLOC_HANDLE, 64>::iterator it = s_extMems.begin(); it != s_extMems.end(); ++it) {
      handles.push_back(*it);
    }
    mtl::MemoryInfo extInfo;
    for (u32 i = 0; i < handles.size(); i++) {
      mtl::MemManager::getMemoryInfo(handles[i], &extInfo);
    }
    s_extMems.push_back(handle);
  }
}

void MlMem::removeExtMem(mtl::ALLOC_HANDLE handle) {
  mm::mtl::FixedList<mtl::ALLOC_HANDLE, 64>::iterator it = mm::mtl::find(s_extMems.begin(), s_extMems.end(), handle);
  if (it != s_extMems.end()) {
    s_extMems.erase(it);
  }
}

mtl::ALLOC_HANDLE MlMem::getExtMem(u32 index) {
  u32 i = 0;
  for (mm::mtl::FixedList<mtl::ALLOC_HANDLE, 64>::iterator it = s_extMems.begin(); it != s_extMems.end(); ++it) {
    if (i == index) {
      return *it;
    }
    i++;
  }
  return mtl::ALLOC_HANDLE();
}

int MlMem::getExtMemNum() { return s_extMems.size(); }

bool MlMem::isDebug(const void *pointer) { return mtl::MemManager::isArea(s_debugMem, pointer); }

void MlMem::setMemoryPermission(void *address, size_t size, AccessMode mode) {}

} // namespace ml

template mm::mtl::FixedList<::mtl::ALLOC_HANDLE, 128>::iterator mm::mtl::FixedList<::mtl::ALLOC_HANDLE, 128>::erase(mm::mtl::FixedList<::mtl::ALLOC_HANDLE, 128>::iterator);
template mm::mtl::FixedList<::mtl::ALLOC_HANDLE, 64>::iterator mm::mtl::FixedList<::mtl::ALLOC_HANDLE, 64>::erase(mm::mtl::FixedList<::mtl::ALLOC_HANDLE, 64>::iterator);
