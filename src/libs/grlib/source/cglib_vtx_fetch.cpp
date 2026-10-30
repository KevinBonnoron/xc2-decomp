#include "grlib/cglib_vtx_fetch.h"

#include "grlib/cglib_mem_handle.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"

namespace grlib {

CGLibVtxFetch::CGLibVtxFetch() {
  unknown00 = nullptr;
  unknown0a = 0;
}

CGLibVtxFetch::~CGLibVtxFetch() { release(); }

void CGLibVtxFetch::release() {
  if (unknown0a != 0) {
    if (unknown00 != nullptr) {
      mtl::MemManager::deallocate(unknown00, 0, false);
      unknown00 = nullptr;
    }
  } else {
    unknown00 = nullptr;
  }
  unknown0a = 0;
}

int CGLibVtxFetch::calcFetchWorkSize(int num) { return num << 2; }

void CGLibVtxFetch::createFetchObj(CGLibVtxAttr *attributes, int num) {
  int size = calcFetchWorkSize(num);
  release();
  unknown00 = static_cast<NVNvertexAttribState *>(mtl::MemManager::allocate(CGLibMemHandle::s_hFchHandle, size, 4, false, "no name", 0));
  unknown0a = 1;
  setupFetchObj(attributes, num);
}

void CGLibVtxFetch_plf::setupFetchObj(const CGLibVtxAttr *attributes, int num) {
  unknown08 = num;
  for (int i = 0; i < num; i++, attributes++) {
    int location = attributes->unknown04;
    nvnVertexAttribStateSetDefaults(&unknown00[location]);
    nvnVertexAttribStateSetFormat(&unknown00[location], static_cast<NVNformat>(attributes->unknown00), static_cast<int>(attributes->unknown08));
    nvnVertexAttribStateSetStreamIndex(&unknown00[location], attributes->unknown0c);
  }
}

int CGLibVtxFetch::createMemFetchObj(void *memory, CGLibVtxAttr *attributes, int num) {
  release();
  unknown00 = static_cast<NVNvertexAttribState *>(memory);
  unknown0a = 0;
  setupFetchObj(attributes, num);
  return calcFetchWorkSize(num);
}

} // namespace grlib
