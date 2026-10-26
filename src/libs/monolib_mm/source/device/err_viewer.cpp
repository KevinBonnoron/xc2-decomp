#include "ml/err_viewer.h"

#include "mtl/mem_manager.h"

namespace ml {

s32 ErrViewer::s_nHandle;

bool ErrViewer::isInitialized() {
  ErrViewer *viewer = get();
  if (viewer != nullptr) {
    return viewer->unknown258 == 1;
  }
  return false;
}

bool ErrViewer::isErrorDisp() {
  ErrViewer *viewer = get();
  if (viewer != nullptr) {
    return viewer->unknown26b;
  }
  return false;
}

s32 ErrViewer::createHandle() const { return s_nHandle++; }

void ErrViewer::setup() {}

void ErrViewer::upErrViewer() {}

void ErrViewer::renderDRC() {}

void ErrViewer::term() {
  if (unknown278 != nullptr) {
    mtl::MemManager::deallocate(unknown278, 0, false);
    unknown278 = nullptr;
  }
}

} // namespace ml
