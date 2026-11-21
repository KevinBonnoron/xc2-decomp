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

// Inferred type: object of a function static whose guard (0x71014be1b0) MlMem::initialize (0x710077a454) and MlMem::terminate (0x710077a490) share:
// each takes the guard with ldarb, calls __cxa_guard_acquire and __cxa_guard_release, and never touches the object, so its type and its constructor
// are unknown (original type name unknown). The only evidence is the guard, which needs a constructor that clang cannot fold into constant data.
// Forms tried in a shared helper: a plain `static bool` (constant data, no guard: 1 instruction), an ALLOC_HANDLE copied from s_productMem (17
// instructions), a FixedList (registers its destructor: 35). A bool initialised from a runtime value (`static bool = s_productMem.isValid()`) also
// matches but would invent a value no access shows, so the empty constructor is the least that matches.
struct unknown001 {
  unknown001() {}
};

// Inferred helper: returns the shared function static of initialize and terminate (two users, so one guard; a static in each function would give two
// guards); the static is never read; original name unknown.
unknown001 &unknown002() {
  static unknown001 instance;
  return instance;
}
} // namespace

void MlMem::initialize() {
  unknown002();
  mtl::MemManager::initialize();
}

void MlMem::terminate() {
  unknown002();
  mtl::MemManager::terminate();
}

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
