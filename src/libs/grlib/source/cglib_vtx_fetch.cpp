#include "grlib/cglib_vtx_fetch.h"

#include "mtl/mem_manager.h"

namespace grlib {

CGLibVtxFetch::CGLibVtxFetch() : unknown00(nullptr), unknown0a(0) {}

CGLibVtxFetch::~CGLibVtxFetch() { release(); }

void CGLibVtxFetch::release() {
  if (unknown0a != 0) {
    if (unknown00 != nullptr) {
      mtl::MemManager::deallocate(unknown00, 0, false);
    }
  }
  unknown00 = nullptr;
  unknown0a = 0;
}

int CGLibVtxFetch::calcFetchWorkSize(int num) { return num << 2; }

} // namespace grlib
